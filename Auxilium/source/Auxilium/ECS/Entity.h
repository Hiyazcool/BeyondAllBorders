#include "axpch.h"
#include "Define.h"
#pragma once
struct Entity {
public:
	uint32 ID;
	operator unsigned long() const {
		return ID;
	}
};