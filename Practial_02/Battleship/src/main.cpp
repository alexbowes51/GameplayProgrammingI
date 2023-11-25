#include <iostream>
#include <cmath>


int const MAXSHIPS = 4;
int XcordArray[MAXSHIPS];
int YcordArray[MAXSHIPS];
int Width[MAXSHIPS];
int Heigth[MAXSHIPS];

int MissleSelect = 0;
int MissleX = 0;
int MissleY = 0;
int MissleRadius = 2;

int EneMissleY = 0;
int EneMissleX = 0;
int EneMissleRadius = 2;


 int enemyshipsXcords[MAXSHIPS];
 int enemyshipsYcords[MAXSHIPS];
 int enemyshipsWidth[MAXSHIPS];
 int enemyshipsHeight[MAXSHIPS];

  int pos_x = 0;
  int pos_y = 0;

void placeships()
{
    int count = 1;
	for (int i = 0; i < MAXSHIPS; i++)
	{
		
        std::cout << "Enter another poistion that between 0 - 8" << std::endl;
		std::cout << "Enter ship " << count << " X Poistion and Y Poistion " << std::endl;
		bool Input = false;

		while(!Input){
			std::cin >> XcordArray[i] >> YcordArray[i];
			Width[i] = 1;
			Heigth[i] = 1;

			//checks if input is less than 0 and greater than 8
         if(XcordArray[i] >= 1  && XcordArray[i] <= 8 && YcordArray[i] >= 1 && YcordArray[i] <= 8){
	 		Input = true;
		
			bool dup = false;
			for(int j = 0;j < i; j++){
   	 		 //checks for the array for the same position
   	 		if(XcordArray[i] == XcordArray[j] && YcordArray[i] == YcordArray[j]  ){
     		 dup = true;
	 		 break;
			 }
			}

			if(dup){
				 std::cout << "You have a ship already there enter new poistion" << std::endl;
				 Input = false;
			} 
			 }
			else {
				std::cout << "ERROR: Enter new Poisiton of X and Y 0-8" << std::endl;
			} 
		}
		
	
	
        std::cout << "Ship " << count << " poistion is = " << XcordArray[i] << " X " << YcordArray[i] << " Y " << std::endl;

        count++;
		}
	}
	
void Enemyships()
{
srand((unsigned)time(0));

   for (int i = 0; i < MAXSHIPS; i++)
   {
     enemyshipsXcords[i] = (rand() % 8) + 1;
     enemyshipsYcords[i] = (rand() % 8) + 1;
	 enemyshipsHeight[i] = 1;
	 enemyshipsWidth[i] = 1;

     std::cout << "//Enemy X Position = " << enemyshipsXcords[i] << "//Enemy Y Poistion = " << enemyshipsYcords[i] << std::endl;

}

};

void Firing()
{
 	std::cout << "Please select a warhead 1 = Warhead 2 = Nuclear" << std::endl;
 	std::cin >> MissleSelect;
    
	std::cout << "Great choice President :)" << std::endl;

	std::cout << "Please enter the Postion you want to DESTROY" << std::endl;
	std::cout << "Position X + Y = ";
    std::cin >> MissleX >> MissleY;
};



void enemyFiring()
{
  std::cout << "ENEMY IS FIRING" << std::endl;

  EneMissleX = (rand() % 8) + 1;
  EneMissleY = (rand() % 8) + 1;
};

void checkHit() {
    for (int i = 0; i < MAXSHIPS; i++) {
        // Calculate the distance between player missile and enemy ship
        double playerDistance = std::sqrt((enemyshipsXcords[i] - MissleX) * (enemyshipsXcords[i] - MissleX) +
            (enemyshipsYcords[i] - MissleY) * (enemyshipsYcords[i] - MissleY));

        // Calculate the distance between enemy missile and player ship
        double enemyDistance = std::sqrt((XcordArray[i] - EneMissleX) * (XcordArray[i] - EneMissleX) +
            (YcordArray[i] - EneMissleY) * (YcordArray[i] - EneMissleY));

        if (playerDistance <= MissleRadius) {
            std::cout << "You hit the enemy's ship " << (i+1) << " :)" << std::endl;
            enemyshipsXcords[i] = -1;
            enemyshipsYcords[i] = -1;
        } else {
            std::cout << "You missed the enemy's ship " << (i+1) << " :(" << std::endl;
        }

        if (enemyDistance <= EneMissleRadius) {
            std::cout << "Enemy hit your ship " << (i+1) << " :(" << std::endl;
            XcordArray[i] = -1;
            YcordArray[i] = -1;
        } else {
            std::cout << "Enemy missed your ship " << (i+1) << " :)" << std::endl;
        }
    }
}

bool isGameOver() {
    bool allPlayerShipsDestroyed = true;
    bool allEnemyShipsDestroyed = true;

    for (int i = 0; i < MAXSHIPS; i++) {
        if (XcordArray[i] != -1) {
            // If a player ship exists, set allPlayerShipsDestroyed to false
            allPlayerShipsDestroyed = false;
            break;
        }
    }

    for (int i = 0; i < MAXSHIPS; i++) {
        if (enemyshipsXcords[i] != -1) {
            // If an enemy ship exists, set allEnemyShipsDestroyed to false
            allEnemyShipsDestroyed = false;
            break;
        }
    }

    // The game is over if all player ships or all enemy ships are destroyed
    return allPlayerShipsDestroyed || allEnemyShipsDestroyed;
}




int main()
{
    placeships();
    Enemyships();

    while (!isGameOver()) {
        Firing();
        enemyFiring();
        checkHit();
    }

    std::cout << "Game Over!" << std::endl;

    return 0;
}