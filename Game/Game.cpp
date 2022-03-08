
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "GameEngine.h"

#include "Spaceship.h"
#include "Missile.h"
#include "Companion.h"

#include "DroneEnemy.h"
#include "LonerEnemy.h"
#include "RusherEnemy.h"
#include "BossEnemy.h"
#include "EnemyAttack.h"
#include "LevelSpawner.h"

#include "RockAsteroidBig.h"
#include "MetalAsteroidBig.h"
#include "MetalAsteroidMedium.h"
#include "MetalAsteroidSmall.h"

#include "StaticBackground.h"
#include "BackgroundParalax.h"

#include "WeaponPowerUp.h"
#include "CompanionPowerUp.h"
#include "ShieldPowerUp.h"

#include "HUDLife.h"
#include "HUDScore.h"
#include "MainMenuUI.h"
#include "EndMenuUI.h"
#include "YouWon.h"

int main(int argc, char ** argv)
{   
    GameEngine* engine = engine->GetGameEngine();

    engine->Init("Xennon Clone!!!", 900, 600);


    Level level1;
    Level MainMenu;
    Level EndMenu;
    Level youWon;


    //BACKGROUND_____________________
    MainMenu.AddObject(new StaticBackground);
    EndMenu.AddObject(new StaticBackground);
    youWon.AddObject(new StaticBackground);
    level1.AddObject(new StaticBackground);
    level1.AddObject(new BackgroundParalax);

    //UI__________________________________
    HUDLife* hudLife = new HUDLife();
    level1.AddObject(hudLife);
    HUDScore* hudScore = new HUDScore();
    level1.AddObject(hudScore);

    MainMenu.AddObject(new MainMenuUI(&level1, engine));
    EndMenu.AddObject(new EndMenuUI());
    youWon.AddObject(new YouWon());

    //PLAYER______________________________
    Spaceship* spaceship = new Spaceship(&level1, engine, &EndMenu, hudLife);
    level1.AddObject(spaceship);

    //LevelSpawner_______________________________________
    level1.AddObject(new LevelSpawner(&level1, hudScore,spaceship,engine, &youWon));

    //level1.SpawnObject(new BossEnemy(Vector3{ 790,300,0 }, &level1, spaceship, hudScore, engine, &youWon));

    //ENGINE____________
    //set level to load and start() objects
    engine->LoadLevel(&MainMenu);

    //loop
    engine->RunEngine();
    

    MainMenu.EmptyLevel();
    level1.EmptyLevel();

    delete (engine);

    return 0;
}
