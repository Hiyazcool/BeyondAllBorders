#include "GeneralDefines.h"
#include "CatalystAPI.h"
#include <type_traits>
namespace Catalyst {
	constexpr uint MAX_BUFFER_SIZE_DEFAULT = 20;
	constexpr uint ALLOC_CHUNK_SIZE_DEFAULT = 10;
	template<typename T>
	class ListIterator {
	public:
		using ValueType = T;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
		ListIterator(PointerType);
		ListIterator& operator++ () {

		}
		ListIterator	operator++ (int) {

		}
		ListIterator& operator-- () {

		}
		ListIterator	operator-- (int) {

		}
		ReferenceType	operator[] (int _index) {

		}
		PointerType		operator-> () {

		}
		ReferenceType	operator*  () {

		}
		bool operator==	(const ListIterator& other);
		bool operator!=	(const ListIterator& other) const;
	private:
		PointerType ptr;
	};
	template<typename T>
	// An Unsorted Expandable List with Free Index Placement and Active Size Control
	class CATALYST_API List {
		// Array of Objects/Values
		T* dataArray;
		// Array of Free Indices in dataArray
		uint* freeIndicesArray;
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
		using	ValueType = T;
		using	Iterator = ListIterator<List<T>>;
	private:
		/* Reallocation Function
		*/
		void ReAlloc(uint64);
		void ReAlloc();
		const uint64 AddToListAtIndex(const uint64&, const T&);
		const uint64 AddToListAtIndex(const uint64&, T&&);

	public:
		List();
		List(uint _maxBufferSize, uint _allocChunkSize);
		List(uint _maxBufferSize, uint _allocChunkSize, bool _allowConsolidation, bool _allowIndexTracking, bool _efficientTrackedIndexSize);
		~List();
		// Clears List and ReAllocates it to a Minimum Size. Returning True if Successful
		bool Clear(bool callDestructors = false);
		// Removes All Free Indices that are Between Filled Indexs. Returning True if Successful
		bool Consolidate();

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
		inline T& operator[](const uint64&);
		inline T* GetPointer(const uint64&);
		inline T Get(const uint64&);

		// Copies Given Object/Value to the First Free Space in the List, ReAllocating More if Needed. Returns the Index Number of Object/Value
		const uint64 AddToList(const T&);
		// Moves Given Object/Value to the First Free Space in the List, ReAllocating More if Needed. Returns the Index Number of Object/Value
		const uint64 AddToList(T&&);
		// Searchs Array Until it Finds a Match to the Given Parameter, then removes the Object/Value from the list Adding Index to the Free Indices or Consolidates If Beyond Threshold and Allowed, Returning True if Successful
		bool RemoveSearch(const T&);
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
	inline void List<T>::ReAlloc(uint64 capacity) {
		T* newArray = new T[capacity];
		for (uint64 i = 0; i < List<T>::dataSize; i++)
			newArray[i] = std::move(List<T>::dataArray[i]);
		delete[] List<T>::dataArray;
		List<T>::dataArray = newArray;
		List<T>::dataCapacity = capacity;
	}
	template<typename T>
	inline void List<T>::ReAlloc()
	{
		ReAlloc(AllocChunkSize + dataCapacity);
	}
	template<typename T>
	inline const uint64 List<T>::AddToListAtIndex(const uint64&, const T&) {
		return 0;
	}
	template<typename T>
	inline const uint64 List<T>::AddToListAtIndex(const uint64&, T&&) {
		return 0;
	}
	
	template<typename T>
	List<T>::List() :
		dataArray(nullptr),
		freeIndicesArray(nullptr),
		dataSize(0),
		freeIndicesSize(0),
		MaxBufferSize(MAX_BUFFER_SIZE_DEFAULT),
		AllocChunkSize(ALLOC_CHUNK_SIZE_DEFAULT),
		AllowConsolidation(false) {
		dataArray = new T[List<T>::AllocChunkSize];
		freeIndicesArray = new uint[16];
		dataCapacity = List<T>::AllocChunkSize;
#ifdef DEBUG
#endif // DEBUG
	}
	template<typename T>
	inline List<T>::List(uint _maxBufferSize, uint _allocChunkSize) :
		dataArray(nullptr),
		freeIndicesArray(nullptr),
		dataSize(0),
		freeIndicesSize(0),
		MaxBufferSize(_maxBufferSize),
		AllocChunkSize(_allocChunkSize),
		AllowConsolidation(false) {
		dataArray = new T[List<T>::AllocChunkSize];
		freeIndicesArray = new uint[16];
		dataCapacity = List<T>::AllocChunkSize;
#ifdef DEBUG
#endif // DEBUG
	}
	template<typename T>
	inline List<T>::List(uint _maxBufferSize, uint _allocChunkSize, bool _allowConsolidation, bool _allowIndexTracking, bool _efficientTrackedIndexSize) :
		dataArray(nullptr),
		freeIndicesArray(nullptr),
		dataSize(0),
		dataCapacity(0),
		freeIndicesSize(0),
		MaxBufferSize(_maxBufferSize),
		AllocChunkSize(_allocChunkSize),
		AllowConsolidation(_allowConsolidation) {
		dataArray = new T[List<T>::AllocChunkSize];
		freeIndicesArray = new uint[16];
		dataCapacity = List<T>::AllocChunkSize;
#ifdef DEBUG
#endif // DEBUG	
	}
	template<typename T>
	inline List<T>::~List() {
		delete[] dataArray;
		delete[] freeIndicesArray;
#ifdef DEBUG

#endif // DEBUG	
	}
	/*template<typename T>
	inline T* List<T>::operator=(List<T>& other)
	{
		return other;
	}
	template<typename T>
	inline T* const List<T>::operator=(const List<T>&) const
	{
		return true;
	}*/
	template<typename T>
	inline bool List<T>::Clear(bool callDestructors)
	{
		if (callDestructors)
			for (uint64 i = 0; i < dataSize; i++)
				if (dataArray[i] != nullptr)
					dataArray[i].~T();
		dataSize = 0;
		dataCapacity = 0;
		ReAlloc(AllocChunkSize);
		return true;
	}
	template<typename T>
	inline bool List<T>::Consolidate()
	{
		return false;
	}
	template<typename T>
	inline uint64 const List<T>::GetSize() const
	{
		return dataSize;
	}
	template<typename T>
	inline uint64 List<T>::GetSize()
	{
		return dataSize;
	}
	template<typename T>
	inline void List<T>::operator+=(const T&)
	{
	}
	template<typename T>
	inline void List<T>::operator+=(T&&)
	{
	}
	template<typename T>
	inline void List<T>::operator-=(T&)
	{
	}
	template<typename T>
	inline T& const List<T>::operator[](const uint64& index) const
	{
		return dataArray[index];
	}
	template<typename T>
	inline T& List<T>::operator[](const uint64& index)
	{
		return dataArray[index];
	}
	template<typename T>
	inline T* List<T>::GetPointer(const uint64& index)
	{
		return dataArray[index];
	}
	template<typename T>
	inline T List<T>::Get(const uint64& index)
	{
		return dataArray[index];
	}
	template<typename T>
	inline const uint64 List<T>::AddToList(const T& var)
	{
		if(dataSize == dataCapacity)
			ReAlloc();
		dataArray[dataSize] = var;
		return dataSize++;
	}
	template<typename T>
	inline const uint64 List<T>::AddToList(T&&)
	{
		return 0;
	}
	template<typename T> 
	inline bool List<T>::RemoveSearch(const T& var)
	{
		for (uint i = 0; i < dataCapacity; i++)
			if (dataArray[i] == var){
				dataArray[i] = NULL;
				dataSize--;
				return true;
			}
		return false;
	}
	template<typename T>
	inline bool List<T>::RemoveFromList(const uint64&)
	{
		return false;
	}
	template<typename T>
	inline bool const List<T>::operator==(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool const List<T>::operator!=(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool const List<T>::operator<=(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool const List<T>::operator>=(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool const List<T>::operator<(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool const List<T>::operator>(const uint64&) const
	{
		return nullptr;
	}
	template<typename T>
	inline bool ListIterator<T>::operator==(const ListIterator& other)
	{
		return false;
	}
	template<typename T>
	inline bool ListIterator<T>::operator!=(const ListIterator& other) const
	{
		return false;
	}
	template<typename T>
	inline ListIterator<T>::ListIterator(PointerType)
	{
	}
	//template<typename T>
	//inline ListIterator& ListIterator<T>::operator++()
	//{
	//	
	//}
	//template<typename T>
	//inline ListIterator ListIterator<T>::operator++(int)
	//{
	//	return ListIterator();
	//}
	//template<typename T>
	//inline ListIterator& ListIterator<T>::operator--()
	//{
	//	// TODO: insert return statement here
	//}
	//template<typename T>
	//inline ListIterator ListIterator<T>::operator--(int)
	//{
	//	return ListIterator();
	//}
	//template<typename T>
	//inline ReferenceType ListIterator<T>::operator[](int _index)
	//{
	//	return ReferenceType();
	//}
	//template<typename T>
	//inline PointerType ListIterator<T>::operator->()
	//{
	//	return PointerType();
	//}
	//template<typename T>
	//inline ReferenceType ListIterator<T>::operator*()
	//{
	//	return ReferenceType();
	//}
}

#pragma endregion