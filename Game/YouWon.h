#pragma once
#include "Object.h"

class YouWon : public Object
{
	using Super = Object;
protected:
	void Construct() override;
	void Start() override;

};

