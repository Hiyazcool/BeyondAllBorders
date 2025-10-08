#pragma once
#include "Define.h"
#include "IPrintable.h"
namespace HiyazUtils {
	template<typename T>
	class GridIterator {

	};
	template<size_t X, size_t Y, typename T>
	class Grid : IPrintable {
		T dataGrid[X][Y];
	public:
		virtual const char* PrintDebugInfo() {
			return " WIP";
		}

		virtual const char* const ToString() {
			return " WIP";
		}
		using ValueType = T;
		using Iterator = GridIterator<Grid<X,Y,T>>;
		const uint x = X;
		const uint y = Y;
		inline T& const operator()(uint _x, uint _y) const {
			return dataGrid[_x][_y];
		}
		inline T& operator()(uint _x, uint _y) {
			return dataGrid[_x][_y];
		}
		T(&operator [](size_t _x))[Y]
		{
				return dataGrid[_x];
		}

	};
}

