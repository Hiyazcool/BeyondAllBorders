#include "axpch.h"
#include"Define.h"
#pragma once

#include <bitset>
#include <array>
#include <atomic>
#include <cstdint>
#include <vector>
#include <memory>
#include <type_traits>
#include <tuple>
#include <functional>
#include <iostream>
#include <cassert>
namespace Auxilium{

namespace ecs {

    constexpr std::size_t MAX_COMPONENTS = 64;
    using ComponentMask = std::bitset<MAX_COMPONENTS>;
    using TypeIndex = std::size_t;

    inline TypeIndex nextTypeIndex() {
        static std::atomic<TypeIndex> next{ 0 };
        return next.fetch_add(1, std::memory_order_relaxed);
    }

    template<typename T>
    inline TypeIndex component_type_index() {
        static TypeIndex idx = nextTypeIndex();
        return idx;
    }

    struct Entity {
        std::uint32_t archetype = 0;
        std::uint32_t index = 0;
    };

    struct ComponentStorageBase {
        virtual ~ComponentStorageBase() = default;
        virtual void* getPtr(std::size_t i) = 0;
        virtual std::size_t size() const = 0;
    };

    template<typename T>
    struct ComponentStorage : ComponentStorageBase {
        std::vector<T> data;

        void push(const T& v) { data.push_back(v); }
        void push(T&& v) { data.push_back(std::move(v)); }

        void* getPtr(std::size_t i) override { return &data[i]; }
        std::size_t size() const override { return data.size(); }
    };

    struct Archetype {
        ComponentMask mask;
        std::vector<TypeIndex> componentTypes; // order of storages
        std::vector<std::unique_ptr<ComponentStorageBase>> storages;
        std::array<int, MAX_COMPONENTS> typeToIndex;

        Archetype() {
            typeToIndex.fill(-1);
        }

        // Create storage for a type T; called in the archetype creation phase.
        template<typename T>
        void addStorageFor() {
            TypeIndex tid = component_type_index<T>();
            assert(tid < MAX_COMPONENTS);
            typeToIndex[tid] = static_cast<int>(storages.size());
            componentTypes.push_back(tid);
            storages.emplace_back(std::make_unique<ComponentStorage<T>>());
            mask.set(tid);
        }

        // Number of entities in this archetype (all storages have same length)
        std::size_t entityCount() const {
            if (storages.empty()) return 0;
            return storages[0]->size();
        }

        template<typename T>
        T& get(std::size_t i) {
            TypeIndex tid = component_type_index<T>();
            int si = typeToIndex[tid];
            assert(si >= 0);
            auto* st = static_cast<ComponentStorage<T>*>(storages[si].get());
            return st->data[i];
        }

        // Emplace entity components in the same order as componentTypes.
        template<typename... Comps>
        void emplaceEntity(Comps&&... comps) {
            static_assert(sizeof...(Comps) == sizeof...(Comps), "pack ok");
            // compile-time check not possible here for archetype order; user must pass components in same order
            emplace_impl(0, std::forward<Comps>(comps)...);
        }

    private:
        // helper to push values to each storage in order
        template<typename First, typename... Rest>
        void emplace_impl(std::size_t idx, First&& first, Rest&&... rest) {
            // push to storages[idx]
            auto* base = storages[idx].get();
            using T = std::decay_t<First>;
            auto* typed = static_cast<ComponentStorage<T>*>(base);
            typed->data.push_back(std::forward<First>(first));
            if constexpr (sizeof...(Rest) > 0) {
                emplace_impl(idx + 1, std::forward<Rest>(rest)...);
            }
        }

        // base case (no components) - shouldn't normally happen for archetypes with no components
        void emplace_impl(std::size_t) {}
    };

    class Registry {
    public:
        // Create an archetype for the given component set (template args define the storage order).
        template<typename... Components>
        std::size_t createArchetype() {
            static_assert(sizeof...(Components) > 0, "Archetype must have at least one component.");
            Archetype arch;
            (arch.addStorageFor<Components>(), ...);
            archetypes.push_back(std::move(arch));
            return archetypes.size() - 1;
        }

        // Add an entity to a specific archetype. The components must be provided in the same order as the archetype template.
        template<typename... Components>
        Entity createEntity(std::size_t archetypeIndex, Components&&... comps) {
            assert(archetypeIndex < archetypes.size());
            Archetype& arch = archetypes[archetypeIndex];
            // basic sanity: ensure archetype has the same number of components as provided
            assert(arch.storages.size() == sizeof...(Components));
            arch.emplaceEntity(std::forward<Components>(comps)...);
            Entity e;
            e.archetype = static_cast<std::uint32_t>(archetypeIndex);
            e.index = static_cast<std::uint32_t>(arch.entityCount() - 1);
            return e;
        }

        // Query: iterate over every archetype that contains all Requested components, and for each entity call func(Entity, Requested&...)
        template<typename... Requested, typename Func>
        void each(Func&& func) {
            static_assert(sizeof...(Requested) > 0, "Query must request at least one component.");
            ComponentMask required;
            (required.set(component_type_index<Requested>()), ...);

            for (std::size_t a = 0; a < archetypes.size(); ++a) {
                Archetype& arch = archetypes[a];
                if ((arch.mask & required) != required) continue; // archetype doesn't contain all requested components

                std::size_t n = arch.entityCount();
                // precompute storage indices for requested types in this archetype
                std::array<int, sizeof...(Requested)> sidx = getStoreIdxArray<Requested...>(arch);

                for (std::size_t i = 0; i < n; ++i) {
                    call_with_components<Requested...>(arch, sidx, i, func, static_cast<std::uint32_t>(a));
                }
            }
        }

    private:
        std::vector<Archetype> archetypes;

        template<typename... Requested>
        static std::array<int, sizeof...(Requested)> getStoreIdxArray(const Archetype& arch) {
            std::array<int, sizeof...(Requested)> arr{};
            std::size_t pos = 0;
            ((arr[pos++] = arch.typeToIndex[component_type_index<Requested>()]), ...);
            return arr;
        }

        // Unpack and call user lambda with references
        template<typename... Requested, typename Func, std::size_t... I>
        static void call_with_components_impl(Archetype& arch, const std::array<int, sizeof...(Requested)>& idxs, std::size_t entIndex, Func& func, std::index_sequence<I...>, std::uint32_t archetypeIdx) {
            // Get typed references by casting storage pointers
            // Note: archetype.get<T>(i) could be used but we need to call with the type pack
            func(Entity{ archetypeIdx, static_cast<std::uint32_t>(entIndex) }, static_cast<std::add_lvalue_reference_t<Requested>>(*static_cast<Requested*>(arch.storages[idxs[I]]->getPtr(entIndex)))...);
        }

        template<typename... Requested, typename Func>
        static void call_with_components(Archetype& arch, const std::array<int, sizeof...(Requested)>& idxs, std::size_t entIndex, Func& func, std::uint32_t archetypeIdx) {
            call_with_components_impl<Requested...>(arch, idxs, entIndex, func, std::index_sequence_for<Requested...>{}, archetypeIdx);
        }
    };

} // namespace ecs
}