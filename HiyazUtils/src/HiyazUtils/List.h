#pragma once
#include <iostream>
#include <iterator>
#include "IPrintable.h"
#include "Define.h"
#ifdef DEBUG
#include "Log.h"
using namespace Log;
#endif // DEBUG

namespace HiyazUtils {
	namespace List {
		/*
			Todo:
			*	Dedicated Search Function
			*	Remove Function
					Via Index or Search
			*	Add At Place Function
					Via Index
					Or In Front
				Shift Array Left Or Right
					Maybe do Via offset index variable????
						reduce lag of manually moving variables
						Would need Bounds checking
						Temporary index shift while Async creates new???
							Could be Fun
			*	Comparison
					Between OldList
						Return Instances of Same obj / seperate for same types
					num of Items
				Scramble
					Create a Second Array of Indexs Temp then Async them into another??
						Check if index is null if true go to new location to provide easier access?
							Lock ones being used on Main
				ToString Function
					A TryToString to all obj in OldList

			*	Add a Free Index Array?

		*****   (...args) Overload Returns Array of Objects/Values at Given Indices


				Make a Queue Object

		*/
		constexpr uint MAX_BUFFER_SIZE_DEFAULT = 20;
		constexpr uint ALLOC_CHUNK_SIZE_DEFAULT = 10;
		template<typename T>
		class ListIterator {
		public:
			using ValueType = T::ValueType;
			using PointerType = ValueType*;
			using ReferenceType = ValueType&;
			ListIterator(PointerType);
			ListIterator& operator++ ();
			ListIterator	operator++ (int);
			ListIterator& operator-- ();
			ListIterator	operator-- (int);
			ReferenceType	operator[] (int _index);
			PointerType		operator-> ();
			ReferenceType	operator*  ();
			bool operator==	(const ListIterator& other);
			bool operator!=	(const ListIterator& other) const;
		private:
			PointerType ptr;
		};
		template<typename T>
		// An Unsorted Expandable List with Free Index Placement and Active Size Control
		class List : IPrintable {
			// Array of Objects/Values
			T*		dataArray;
			// Array of Free Indices in dataArray
			uint*	freeIndicesArray;
			// Current Amount of Free Indices
			uint	freeIndicesSize;
			// Current Amount of Objects/Values in dataArray
			uint64	dataSize;
			// Current Capacity of dataArray
			uint64	dataCapacity;
		public:
			// Most Amount of Free Indices Allowed
			uint	MaxBufferSize; 
			// Amount of Slots to Increase By
			uint	AllocChunkSize;
			/* Allow the List to Automatically Consolidate List and Resize to Save Memory - Default False
			*  *WARNING* Will Change Indices of At Least Some Object/Values 
			*  *WARNING* This Could Allow the List To get Extremly Long, and Waste Space if Many Values were Deleted if Left False
			*  Consider Using Consolidate or TrackedConsolidate Every So Often if you Leave This Off
			*  If You Use This While Tracking Indices, Set AllowIndexTracking to True to Acquire Correct Indices Relocations
			*  If you wish to Control When Consolidations Happen Use Consolidation Function Instead or TrackedConsolidation Function for Tracking Indices
			*/
			bool	AllowConsolidation;
			/* Allow the List to Track Indices While Consolidating - Default False
			*  Generates Array of uint64s (Unsigned Long Long) Automatically After Consolidate is Called
			*  If you wish to Manually Consolidate and Track Indices Use TrackedConsolidation Function Instead
			*/
			bool	AllowIndexTracking;
			/* Determines the Generation of Index Tracking Array - Default True
			*  If True  - Array Contains the Previous Indices, Accessed by there Current Index ( Array[NewIndex] -> Value = OldIndex)
			*  If False - Array Contains the New Indices, accessed by the Old Index ( Array[OldIndex] -> Value = NewIndex)
			*/
			bool	EfficientTrackedIndexSize;
			using	ValueType = T;
			using	Iterator = ListIterator<List<T>>;
		private:
			/* Reallocation Function 
			*/
			void ReAlloc(uint64 = AllocChunkSize + dataCapacity); 
			const uint64 AddToListAtIndex(const uint64&, const T&);
			const uint64 AddToListAtIndex(const uint64&, T&&);
		public:
			List();
			List(uint _maxBufferSize, uint _allocChunkSize);
			List(uint _maxBufferSize, uint _allocChunkSize, bool _allowConsolidation, bool _allowIndexTracking, bool _efficientTracledIndexSize);
			// Clears List and ReAllocates it to a Minimum Size. Returning True if Successful
			bool Clear();
			// Removes All Free Indices that are Between Filled Indexs. Returning True if Successful
			bool Consolidate();
			/* Removes All Free Indices that are Between Filled Indexs.
			*  Returns Array of Old/New Indices - uint64 (unsigned long long) 
			*  boolean Parameter Determines Array Layout, Default is Set to Class Field EfficientTrackedIndexSize  
			*  If True  - Array Contains the Previous Indices, Accessed by there Current Index ( Array[NewIndex] -> Value = OldIndex)
			*  If False - Array Contains the New Indices, accessed by the Old Index ( Array[OldIndex] -> Value = NewIndex)
			*/
			uint64* TrackedConsolidation(bool = EfficientTrackedIndexSize);
			/* Removes All Free Indices that are Between Filled Indexs. Returns True if Successful.
			*  uint64* Parameter is the Array that is Filled with Old/New Indices
			*  boolean Parameter Determines Layout, Default is Set to Class Field EfficientTrackedIndexSize
			*  If True  - Array Contains the Previous Indices, Accessed by there Current Index ( Array[NewIndex] -> Value = OldIndex)
			*  If False - Array Contains the New Indices, accessed by the Old Index ( Array[OldIndex] -> Value = NewIndex)
			*/
			bool TrackedConsolidation(uint64*, bool = EfficientTrackedIndexSize);

			// Returns Current Size of List
			inline uint64 const GetSize() const;
			// Returns Current Size of List
			inline uint64		GetSize();
			
			// Operator Overload Equivalent of Copier AddToList Function
			inline void operator+=(const T&);
			// Operator Overload Equivalent of Mover AddToList Function
			inline void operator+=(T&&);
			// Searchs List for Exact Reference, and Removing it
			inline void operator-=(T&);
			
			//Returns A Reference of the Object/Value at Given Index, Includes Bound Checking
			inline T& const operator[](const uint64&) const;
			//Returns A Reference of the Object/Value at Given Index, Includes Bound Checking
			inline T&		 operator[](const uint64&);

			// Copies Given Object/Value to the First Free Space in the List, ReAllocating More if Needed. Returns the Index Number of Object/Value
			const uint64 AddToList(const T&);
			// Moves Given Object/Value to the First Free Space in the List, ReAllocating More if Needed. Returns the Index Number of Object/Value
			const uint64 AddToList(T&&);
			
			// Removes Object/Value, at the Given Index, from the List. Adding Index to the Free Indices or Consolidates If Beyond Threshold and Allowed, Returning True if Successful
			bool RemoveFromList(const uint64&);
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator == (const uint64&) const;
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator != (const uint64&) const;
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator <= (const uint64&) const;
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator >= (const uint64&) const;
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator <  (const uint64&) const;
			// Compares Length to Supplied uint64 (unsigned long long)
			bool const operator >  (const uint64&) const;

			Iterator begin() {
				return Iterator(dataArray);
			}
			Iterator end() {
				return Iterator(dataArray + dataSize);
			}
		};
#pragma region Template Implementation
		template<typename T>
		List<T>::List() :
			dataArray					(nullptr),
			freeIndicesArray			(nullptr),
			dataSize					(0),
			dataCapacity				(0),
			freeIndicesSize				(0),
			MaxBufferSize				(MAX_BUFFER_SIZE_DEFAULT),
			AllocChunkSize				(ALLOC_CHUNK_SIZE_DEFAULT),
			AllowConsolidation			(false),
			AllowIndexTracking			(false),
			EfficientTrackedIndexSize	(true)	{
			ReAlloc();
			Clear();
#ifdef DEBUG
			DebugLog( "Created List" );
#endif // DEBUG
		}
#pragma endregion
#pragma region Old List **Deprecated**
		template<typename T>
		class OldListIterator {
		public:
			using ValueType = T::ValueType;
			using PointerType = ValueType*;
			using ReferenceType = ValueType&;
			OldListIterator(PointerType _ptr) :
				ptr(_ptr) {
			}
			OldListIterator& operator++() {
				ptr++;
				return *this;
			}
			OldListIterator operator++(int) {
				OldListIterator iterator = *this;
				++(*this);
				return iterator;
			}
			OldListIterator& operator--() {
				ptr--;
				return *this;
			}
			OldListIterator operator--(int) {
				OldListIterator iterator = *this;
				--(*this);
				return iterator;
			}
			ReferenceType operator[](int _index) {
				return *(ptr + _index);
			}
			PointerType operator->() {
				return ptr;
			}
			ReferenceType operator*() {
				return *ptr;
			}
			bool operator==(const OldListIterator& other) const {
				return ptr != other.ptr;
			}
			bool operator!=(const OldListIterator& other) const {
				return !(*this == other);
			}
		private:
			PointerType ptr;
		};
		template<typename T>
		class OldList : IPrintable
		{
			void ReAlloc(size_t _capacity);
			T* dataArray = nullptr;
			uint* freeIndices = nullptr;
			size_t AddToListAtIndex(T&&, uint);
			size_t AddToListAtIndex(const T&, uint);
			size_t	dataSize = 0;
			size_t	dataCapacity = 0;
			size_t  freeIndicesSize = 0;
		public:
			size_t MaxBufferSize = 10;
			size_t AllocChunkSize = 5;
			using ValueType = T;
			using Iterator = OldListIterator<OldList<T>>;
			virtual const char* PrintDebugInfo();
			virtual const char* const ToString();
			OldList();
			~OldList();
			void AddToList(const T&);
			void AddToList(T&&);
			void PushBack(const T& value);
			void PushBack(T&& value);
			void Popback();
			void Clear();
			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			size_t const GetSize() const;
			size_t GetSize();
			template<typename ... Args>
			T& EmplaceBack(Args&&... args) {
				if (dataSize > dataCapacity - 1)
					ReAlloc(dataCapacity + dataCapacity / 2);
				new(&dataArray[dataSize]) T(std::forward<Args>(args)...);
				return dataArray[dataSize++];
			}
			uint AddWithIndex(T& _value);
			template<typename ComparisonType>
			bool operator==(ComparisonType _other) {
				if (typeid(ValueType) == typeid(ComparisonType))
					return true;
				return false;
			}
			template<typename ComparisonType>
			bool operator!=(ComparisonType _other) {
				if (typeid(ValueType) == typeid(ComparisonType))
					return false;
				return true;
			}
			void operator+=(auto _other);
			void operator-=(T _other);
			void operator-=(uint _other);
			Iterator begin() {
				return Iterator(dataArray);
			}
			Iterator end() {
				return Iterator(dataArray + dataSize);
			}
		};
#pragma region Template Implementation
		template<typename T>
		const char* OldList<T>::PrintDebugInfo() {
			return "Not Implemented Yet";
		}
		template<typename T>
		const char* const OldList<T>::ToString() {
			return "Not Implemented Yet";
		}
		template<typename T>
		OldList<T>::OldList() {
			ReAlloc(5);
		}
		template<typename T>
		OldList<T>::~OldList() {
			Clear();
			::operator delete(dataArray, dataCapacity * sizeof(T));
			delete[] freeIndices;
		}
		template<typename T>
		void OldList<T>::PushBack(const T& value) {
			if (dataSize > dataCapacity - 1)
				ReAlloc(dataCapacity + dataCapacity / 2);
			else if (freeIndicesSize > 0) {
				AddAtIndex(value, freeIndices[0]);
			}
			else {
				dataArray[dataSize] = value;
				dataSize++;
			}
		}
		template<typename T>
		void OldList<T>::PushBack(T&& value) {
			if (dataSize > dataCapacity - 1)
				ReAlloc(dataCapacity + dataCapacity / 2);
			dataArray[dataSize] = std::move(value);
			dataSize++;
		}
		template<typename T>
		void OldList<T>::Popback() {
			if (dataSize > 0) {
				dataSize--;
				dataArray[dataSize].~T();
			}
		}
		template<typename T>
		void OldList<T>::Clear()
		{
			try
			{
				for (size_t i = 0; i < dataSize; i++)
					dataArray[i].~T();
			}
			catch (std::invalid_argument e) {

			}
			dataSize = 0;
			ReAlloc(AllocChunkSize);
		}
		template<typename T>
		T& OldList<T>::operator[](size_t index) {
			if (index > dataSize + 1) {

			}
			return dataArray[index];
		}
		template<typename T>
		const T& OldList<T>::operator[](size_t index) const {
			if (index > dataSize + 1) {

			}
			return dataArray[index];
		}
		template<typename T>
		size_t const OldList<T>::GetSize() const { return dataSize; }
		template<typename T>
		size_t OldList<T>::GetSize() { return dataSize; }
		template<typename T>
		uint OldList<T>::AddWithIndex(T& _value) {
			if (dataSize > dataCapacity - 1)
				ReAlloc(dataCapacity + dataCapacity / 2);
			dataArray[dataSize] = _value;
			return dataSize++;
		}
		template<typename T>
		void OldList<T>::operator+=(auto _other) {
			EmplaceBack(_other);
		}
		template<typename T>
		void OldList<T>::operator-=(T _other) {

		}
		template<typename T>
		void OldList<T>::operator-=(uint _other) {
			if (_other < dataSize) {
				dataArray[_other] = NULL;
				dataSize--;
			}

		}

		template<typename T>
		void OldList<T>::ReAlloc(size_t _capacity) {
			T* newBlock = (T*)::operator new(_capacity * sizeof(T));
			if (_capacity < dataSize)
				dataSize = _capacity;
			for (size_t i = 0; i < dataSize; i++)
				newBlock[i] = std::move(dataArray[i]);
			::operator delete(dataArray, dataCapacity * sizeof(T));
			dataArray = newBlock;
			dataCapacity = _capacity;
		}
#pragma endregion
#pragma endregion
	}
}