#pragma once
class LifeInterface
{
public:
	int maxLife = 5;
	int life = maxLife;
	bool isAlive = true;

	virtual void DecreaseLife(int quantaty);
	virtual void IncreaseLife(int quantaty);
	virtual void ResetLife();
};

