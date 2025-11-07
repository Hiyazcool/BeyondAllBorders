#ifndef AUX_REGISTRY
#define AUX_REGISTRY

#pragma once
#include "axpch.h"
#include "Archetype.h"
/*	Need to Ensure thaqt I can Multi Thread this all, 
*	Entity Command Buffer to allow creating entities on threads?
*	Temp List for Entities with a low lifespan that can be promoted???
*	
/*/
class AXLM_API Registry {
public:
	// will give unique ID to each comp and allow assignment of comp to entities
	void RegisterComponent();
	// Will Trim excess memory Called upon autosave or user defined intervals????
	void RecyclePhase();
	Entity CreateEntity();
	IComponent AddComponent(Entity e);


private:
	uint32 nextComponentID;
	uint32 nextArchetypeID;
	List<uint32> freeEntityIDs;

	std::unordered_map<uint32, Archetype&> entityIndex;

};	
#endif

