#pragma once
#include "Object.h"

class EndMenuUI: public Object
{
	using Super = Object;
protected:
	void Construct() override;
	void Start() override;

};

