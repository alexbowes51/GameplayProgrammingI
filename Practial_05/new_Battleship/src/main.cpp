#include <iostream>

using namespace std;

class Coordinate{
    public:
        int x;
        int y;
};


class Ship{
    public:
    Ship(){
        cout << "Constructed a Ship" << endl;
    }
    void launch(){
        cout << "Launching a ship" << endl;
    }
};

class Missile{
    public:
        Missile(){

        }
        Coordinate coordinate;
        int r;

        bool check_collision(Ship ship){
            cout << "Check Collision Here" << endl;
            ship.launch();
            return false;
        }

};

class PlayerShip : public Ship{
    public:
        PlayerShip(){

        }
        Coordinate coordinate;
        int r;

};

class EnemyShip : public Ship{
    public:
        EnemyShip(){

        }
        Coordinate coordinate;
        int r;
};

int main(){
    PlayerShip player;
    EnemyShip enemy;
    Missile p_m;
    Missile e_m;

    p_m.check_collision(enemy);

    e_m.check_collision(player);

}
