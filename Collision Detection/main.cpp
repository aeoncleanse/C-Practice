#include <iostream>

using namespace std;

int main()
{
    /*
    Welcome player
        create an overall "gamestate" object to contain all elements of the game?
    ask for map size
        initiate maps in new thread while waiting on next input
    ask for unit count
        initiate units in new thread
    ask for prop count
        initiate props in new thread

    we need the map size, probably just a coordinate
        also list of units, list of props, list of projectiles for later
        different lists of moving units and projectiles

    begin game, use a loop that increments once per second to start with
        each second, calculate new position of any moving objects
        props and projectiles are eliminated on contact with a unit
        calculate and handle unit vs unit collisions first
        then calculate prop vs unit and projectile vs unit collisions simultaneously in their own threads


    */

    cout << "Hello world!" << endl;
    return 0;
}
