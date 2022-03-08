#pragma once
#include "Object.h"
#include "Vector3.h"

class BackgroundParalax: public Object
{	
	using Super = Object;
public:
	BackgroundParalax(){}
protected:

	Image* image1 = nullptr;
	Image* image2 = nullptr;

	Vector3 initialPosition;
	void Construct() override;
	void Start() override;
	void Update() override;
};

