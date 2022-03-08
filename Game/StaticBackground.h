#pragma once
#include "Object.h"

class StaticBackground : public Object
{
	using Super = Object;
protected:
	void Construct() override;
	void Start() override;
};

