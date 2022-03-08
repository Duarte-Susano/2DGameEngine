#include "LifeInterface.h"

void LifeInterface::DecreaseLife(int quantaty)
{
	if (quantaty < 0)
	{
		life += quantaty;
		if (life <= 0)
		{
			life = 0;
			isAlive = false;
		}
	}
	else
	{
		life -= quantaty;
		if (life <= 0)
		{
			life = 0;
			isAlive = false;
		}
	}

}

void LifeInterface::IncreaseLife(int quantaty)
{
	if (quantaty > 0)
	{
		life += quantaty;
		if (life > maxLife)
		{
			life = maxLife;
		}

		if (!isAlive && life > 0)
		{
			isAlive = true;
		}
	}
}

void LifeInterface::ResetLife()
{
	life = maxLife;
	isAlive = true;
}
