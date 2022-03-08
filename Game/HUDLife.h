#pragma once
#include "Object.h"
class HUDLife : public Object
{
public:
	HUDLife(){}

	void UpdateLife(int newLife);
	void UpdateSpaceships(int newSpaceships);

private:
	
	Image* lifeBox = nullptr;
	Image* life1 = nullptr;
	Image* life2 = nullptr;
	Image* life3 = nullptr;
	Image* life4 = nullptr;
	Image* life5 = nullptr;
	Image* life6 = nullptr;
	Image* life7 = nullptr;
	Image* life8 = nullptr;
	Image* life9 = nullptr;
	Image* life10 = nullptr;
	
	Animation spaceshipPos = {3,3,1,true};
	Image* spaceship1 = nullptr;
	Image* spaceship2 = nullptr;
	Image* spaceship3 = nullptr;

	Image* lifes[10];

	using Super = Object;
	void Construct() override;
	void Start() override;
	void Update() override;

};

