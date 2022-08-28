#pragma once
#include "PhysObject.h";

class PhysicScene {
	public:
		PhysObject* items;

		PhysicScene(PhysObject * array) {
			items = array;
		}
};

