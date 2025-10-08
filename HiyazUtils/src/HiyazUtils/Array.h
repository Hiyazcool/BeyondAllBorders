#pragma once
	/* 		
		Todo:
			Iterator
			Dedicated Search Function
			Remove Function
				Via Index or Search
			Add At Place Function
				Via Index
				Or In Front
			Shift Array Left Or Right
				Maybe do Via offset index variable????
					reduce lag of manually moving variables
					Would need Bounds checking
					Temporary index shift while Async creates new???
						Could be Fun
			Comparison
				Between list
					Return Instances of Same obj / seperate for same types
				num of Items
			Scramble
				Create a Second Array of Indexs Temp then Async them into another??
					Check if index is null if true go to new location to provide easier access?
						Lock ones being used on Main
			ToString Function
				A TryToString to all obj in list
	*/
namespace HiyazUtils {
	template<typename T>
	class ArrayIterator {
	public:
		using ValueType = T::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;
		ArrayIterator(PointerType _ptr) :
			ptr(_ptr) {
		}
		ArrayIterator& operator++() {
			ptr++;
			return *this;
		}
		ArrayIterator operator++(int) {
			ArrayIterator iterator = *this;
			++(*this);
			return iterator;
		}
		ArrayIterator& operator--() {
			ptr--;
			return *this;
		}
		ArrayIterator operator--(int) {
			ArrayIterator iterator = *this;
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
		bool operator==(const ArrayIterator& other) const {
			return ptr != other.ptr;
		}
		bool operator!=(const ArrayIterator& other) const {
			return !(*this == other);
		}
	private:
		PointerType ptr;
	};
	template<size_t Size, typename T>
	class  Array {
		T dataArray[Size];
		size_t dataSize = Size;
	public:
		using ValueType = T;
		using Iterator = ArrayIterator<Array<Size,T>>;
		inline constexpr int GetSize() const {
			return dataSize;
		}
		inline T& operator[](size_t _index) {
			return dataArray[_index];
		}
		inline const T& operator[](size_t _index) const {
			return dataArray[_index];
		}
		inline Iterator begin() {
			return Iterator(dataArray);
		}
		inline Iterator end() {
			return Iterator(dataArray + dataSize);
		}
	};
}