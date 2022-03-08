#include "ECS.h"

ComponentTypeID getUniqueComponentID()
{
	static ComponentTypeID lastID = 0u;
	return ++lastID;
}

