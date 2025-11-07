#pragma once
namespace Catalyst::ECS {
	struct Component {

		#define COMPONENT_TYPE(type)  static const uint ComponentID;\
										virtual const char* GetName() const override { return #type; }
		#define COMPONENT_ID(ID) static constexpr
	};
								
	
}