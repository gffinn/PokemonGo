//
//  main.cpp
//  Actual Project 3
//
//  Created by Grant Finn on 4/5/21.


//  I was not able to implement the waitime/cooldown feature. I think there was an issue in the trainer.cpp that
//  I could not track down.

#include <iostream>
#include <math.h> //references that classes in other files use rand, floor, srand, etc.
#include <array> //included as other files use arrays
#include <time.h> //included as the time function is used as a seed for srand
#include "trainer.hpp" // the trainer file already includes the other headers to function, but we'll put those up here as well for clarity.
#include "pokemon.hpp"//^^
#include "fastMove.hpp"//^^
#include "chargedMove.hpp"//^^
using namespace std;

/*void battle(trainer& trainerA, trainer& trainerB) {
    while (trainerA.notDead() && trainerB.notDead()) {
        trainerA.changeCooldown(-1);
        trainerB.changeCooldown(-1);

        trainerA.turnAgainst(trainerB);
        if (trainerB.notDead())
            trainerB.turnAgainst(trainerA);
    }
}
*/
int main(int argc, const char * argv[]) {

//Creating quick attack objects
    fastMove quickAttack("Quick Attack", 7, 5, 1, 1.0, 1); //Pikachu fast move
    fastMove firespin("Fire Spin", 10, 14, 1, 1.0, 1); //Charmander
    fastMove tackle("Tackle", 5, 5, 0, .5, 1); //Squritle
    fastMove feint("Feint Attack", 9, 10, 10, 1, 1); //Jigglypuff
    fastMove ember("Ember", 10, 10, 1, 1, 1); //Charmander
    fastMove vinewhip("Vine Whip", 8, 5, 3, 1, 1); //Bulbasaur
    
//creating charged moves objects
    chargedMove thunderbolt("Thunderbolt", 90, 55, 5); //Pikachu
    chargedMove dragonclaw("Dragon Claw", 50, 35, 15); //Charmander
    chargedMove aquajet("Aqua Jet", 45, 45, 2); //Squirtle
    chargedMove gyro("Gyro Ball", 80, 60, 16); //Jigglypuff
    chargedMove flameburst("Flame Burst", 70, 55, 1); //Charmander
    chargedMove powerwhip("Power Whip", 90, 50, 3); //Bulbasaur
    
//creating pokemon objects
    pokemon pikachu("Pikachu", 4, 112, 96, 111, 12, quickAttack, thunderbolt);
    pokemon charizard("Charizard", 1, 7, 223, 173, 186, 23, firespin, dragonclaw);
    pokemon squirtle("Squirtle", 2, 94, 121, 127, 40, tackle, aquajet);
    pokemon jigglypuff("Jigglypuff", 17, 0, 80, 41, 251, 19, feint, gyro);
    pokemon charmander("Charmander", 1, 116, 93, 118, 33, ember, flameburst);
    pokemon bulbasaur("Bulbasaur", 3, 14, 118, 111, 128, 18, vinewhip, powerwhip);
    
//Creating trainer objects
    trainer alder("Alder", pikachu, charmander, charizard, squirtle, jigglypuff, bulbasaur);
    trainer diantha("Diantha", pikachu, charmander, charizard, squirtle, jigglypuff, bulbasaur);
    
//Choosing the 3 battling Pokemon
    alder.chooseActive();
    diantha.chooseActive();
    
    
// Battle

    while (alder.notDead() == true && diantha.notDead() == true)
    {
        alder.turnAgainst(diantha);
        if (diantha.notDead() == true && diantha.notDead() == true)
        {
            diantha.turnAgainst(alder);
        }
    }
    
//Winner Statement
    if (alder.notDead()==true)
    {
        for (int i=0; i<10; i++)
        {
            cout<<" * ";
        }
        cout<< "\n  Alder has won the battle"<<endl;
        for (int i=0; i<10; i++)
        {
            cout<<" * ";
        }
        cout << "\n"<<endl;
        
    }
    else
    {
        for (int i=0; i<10; i++)
        {
            cout<<" * ";
        }
        cout<< "\n  Diantha has won the battle"<<endl;
        for (int i=0; i<10; i++)
        {
            cout<<" * ";
        }
        cout << "\n"<<endl;
    }
    
 
  
    
    
    // I need to refrence notdead function in where we select a pokenmon after one dies
    
    
    return 0;
}
