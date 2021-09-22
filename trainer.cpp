//
//  trainer.cpp
//  Actual Project 3
//
//  Created by Grant Finn on 4/5/21.
//

#include <string> // we use strings for names in the trainer class, and in other classes the trainer references, so we need to include strings here.
#include <iostream> // we use cout and cin statement here, so we need this
#include <math.h> // math.h is used for the floor function
#include <vector>
#include "trainer.hpp" // we need to know what class we're building! duh!
#include "fastMove.hpp"

using namespace std; //used for convenience
//chooseActive  is the primary function for setting the variable activePoke, which denotes what pokemon the trainer will use in attacks. when chooseActive is run, at startup or whenever a pokemon
//feints, it will show the user their entire roster and each pokemon's current HP. they are prompted to enter a number to choose an active pokemon. they cannot choose a dead pokemon or a number
//outside of their roster's range. This function requires no arguments, just a calling object.
void trainer::chooseActive() {
    while (true) {
        cout<<"\n" << name << ", choose active Pokemon:" << endl << roster[battleRoster[0]].getName() << " : " << roster[battleRoster[0]].getCurrentHP() << " HP" <<
            endl << roster[battleRoster[1]].getName() << " : " << roster[battleRoster[1]].getCurrentHP() << " HP" << endl << roster[battleRoster[2]].getName() << " : " << roster[battleRoster[2]].getCurrentHP() << " HP" << endl << "[1,2,3]: ";
        cin >> activePoke;
        if ((activePoke < 4) && (activePoke > 0) && (roster[battleRoster[(activePoke - 1)]].getCurrentHP() > 0)) {
            activePoke -= 1;
            break;
        }
        else
            cout << "Something went wrong, please try again." << endl;
    }
}
void trainer::chooseBattleRoster() {
     cout << name <<", choose your three Pokemon to battle! \nEnter three numbers in a row to represent each Pokemon." << endl;
    for (int i = 0; i < roster.size(); i++) {
        cout << i << " - " << roster[i].getName()<< endl;
    }
    cout << "Enter Pokemon number: ";
    cin >> battleRoster[0];
    cout << "Enter Pokemon number: ";
    cin >> battleRoster[1];
    cout << "Enter Pokemon number: ";
    cin >> battleRoster[2];
    cout << "The pokemon on your roster are " << roster[battleRoster[0]].getName() << ", " << roster[battleRoster[1]].getName() << ", and " << roster[battleRoster[2]].getName() << "!" << endl << endl;
}
trainer::trainer() { //default constructor that gives no pokemon, no shields and a null name. the Punished.
    name = "null";
    shields = 0;
}
//the intended constructor for trainer classes. Must have a name and three pokemon objects to add to the roster, because having constructors and other code to accomodate for a partially filled roster
//was going to be painful.
trainer::trainer(std::string Name, pokemon& roster1, pokemon& roster2, pokemon& roster3, pokemon& roster4, pokemon& roster5, pokemon& roster6) {
    name = Name;
    roster.push_back(roster1);
    roster.push_back(roster2);
    roster.push_back(roster3);
    roster.push_back(roster4);
    roster.push_back(roster5);
    roster.push_back(roster6);
    shields = 2;
    //note how this constructor calls on chooseBattleRoster right out the gate!
    chooseBattleRoster();
}
//simple function for referring to how many shields a trainer has. has no preconditions, and simply returns the calling object's value of shields.
int trainer::getShields() {
    return shields;
}
float trainer::getCooldown(/*fastMove& fastMove*/) const{
    return roster[battleRoster[activePoke]].getFast().getFastMoveCoolDown();//fastMove.getFastMoveCoolDown();
}
float trainer::getDuration(/*fastMove& fastMove*/) const {
    return roster[battleRoster[activePoke]].getFast().getFastMoveDuration();//fastMove.getFastMoveCoolDown();
}
void trainer::changeWaitTime(float num) {
    waitTime += num;
    if (waitTime < 0)
        waitTime = 0;
}
float trainer::getWaitTime() const{
    return waitTime;
}
//oh god. here we go. the battle functions.

//below us, we have the two functions used for attacks , one for fast atacks (fastAttack) and one for charged attacks (chargedAttack). they have one precondition, which is the trainer whose active
//pokemon you are attempting to attack. they both function fairly similarly, with some minor differences. they both tell us, first and foremost, whose pokemon is attacking, what their name is, and
//what attack they're using first. Then they move on to making the calculations given to us by the professor for the assignment. They make the temporary values cATK_attacker/defender,  and totalDamage,
//and then they define them based on given parameters. they are sure to cross reference for STAB multipliers (which I refer to as attack resonance) and the type matchup chart, which is the
//previously/later discussed 2D array in the pokemon class. if the pokemon has two types (a fact denoted by that pokemon's bool value twoTypes!), then this type matchup is run twice, each time with a
//different one of that pokemon's types. this total damage we just calculated is subtracted from the attacked pokemon's health, the attacking pokemon's energy changes accordingly, and if the attacked
//trainer's pokemon has just fainted, they are prompted to pick a new one from their roster.


void trainer::fastAttack(trainer & enemy) {
    //there are no stipulations as to whether or not a fast attack can occur; they just do.
    cout << name << "'s " << roster[battleRoster[activePoke]].getName() << " used " << roster[battleRoster[activePoke]].getFastName() << "!" << endl;

    //Edited by Dylan Binu. For loop that runs in half second intervals with each iteration, until the duration of a fast move is exhausted.
  /*  for(int i = 0; i < (enemy.getDuration() * 2) - 1; i++) {
    }
    */
    int cATK_attacker = (roster[battleRoster[activePoke]].getBA() + roster[battleRoster[activePoke]].getIA()) * roster[battleRoster[activePoke]].refCPM(roster[battleRoster[activePoke]].getLVL());
    int cDEF_defender = (enemy.roster[enemy.battleRoster[enemy.activePoke]].getBD() + enemy.roster[enemy.battleRoster[enemy.activePoke]].getID()) * enemy.roster[enemy.battleRoster[enemy.activePoke]].refCPM(enemy.roster[enemy.battleRoster[enemy.activePoke]].getLVL());
    int totalDamage;
    if (enemy.roster[enemy.battleRoster[enemy.activePoke]].checkTwoTypes()) //if the nemy pokemon has two types,
    {
        totalDamage = floor(0.5 * roster[battleRoster[activePoke]].getFastPower() * cATK_attacker / cDEF_defender *
            roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(),
                enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(),
                    enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].fastResonanceCheck()) + 1;
        enemy.roster[enemy.battleRoster[enemy.activePoke]].subtractHealth(totalDamage);
        //Edited by Dylan Binu. Move effectiveness messages.
    if  ((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) > 1)
    {
        cout << "It was super effective!" << endl;
    }
    if ((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) < 1)
    {
        cout << "It was not very effective!" << endl;
    }
    }
    else {
        totalDamage = floor(0.5 * roster[battleRoster[activePoke]].getFastPower() * cATK_attacker/cDEF_defender * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].fastResonanceCheck()) + 1;
    enemy.roster[enemy.battleRoster[enemy.activePoke]].subtractHealth(totalDamage); //here we take the damage we just calculated and subtract it from the enemy's health
        //Edited by Dylan Binu. Move effectiveness messages.
    if((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].fastResonanceCheck()) > 1) {
        cout << "It was super effective!" << endl;
    }
    if((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getFastType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].fastResonanceCheck()) < 1) {
        cout << "It was not very effective!" << endl;
    }
    }
    if (enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() <= 0)
    {
       enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP();
    }
        
        
    cout << enemy.roster[enemy.battleRoster[enemy.activePoke]].getName() << " Has taken " << totalDamage << " damage, and is now at " << enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() << " HP!" << endl;
    //attacking pokemon's energy is increased by their fast attack's delta
    roster[battleRoster[activePoke]].changeEnergy(roster[battleRoster[activePoke]].getFastDelta());
   // if (!(enemy.notDead()))
     //   break;
    if (enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() <= 0)
    {
        cout<< "\n"<< enemy.roster[enemy.battleRoster[enemy.activePoke]].getName() << " Has taken a critical hit and has fainted!\n"<<endl;
    }
     
    if (enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() <= 0 && enemy.notDead()==true)
        enemy.chooseActive();
    changeWaitTime((getCooldown() + getDuration()) * 2);
}
void trainer::chargedAttack(trainer & enemy) {
    //for charged attacks, we need to make sure that the attacking/active pokemon of the attacker has accrued enough energy to successfully do their charged attack. if they have not, the code just
    //treats it like a fluke and keeps going.
    if (roster[battleRoster[activePoke]].getEnergy() >= roster[battleRoster[activePoke]].getChargedCost()) {
        //but if they have, the code makes some temporary values in order to easily interface with the player.
        bool chargeBlocked = false;
        char input;
        //it needs to interface with the player because it needs to know whether or not the defending trainer wants to use a shield to block the incoming attack. first it needs to know if the defender
        //even has any shields.
        if (enemy.getShields() > 0) {
            //if they do, they're given the option.
            cout << "The target of a charged attack, " << enemy.name << ", has at least one shield (" << enemy.getShields() << " total) remaining! Do they wish to block the incoming attack? [Y/N]" << endl << ": ";
            cin >> input;
            if ((input == 'Y') || (input == 'y'))
                chargeBlocked = true;
        }
        //if they block the attack, they lose a shield and the attacker loses their energy.
        if (chargeBlocked) {
            cout << enemy.name << " Blocked " << name << "'s " << roster[battleRoster[activePoke]].getName() << "'s charged attack, " << roster[battleRoster[activePoke]].getChargedName() << "!";
            roster[battleRoster[activePoke]].changeEnergy(-1 * (roster[battleRoster[activePoke]].getChargedCost()));
            enemy.shields -= 1;
        }
        //if they don't, huzzah! attack!
        else {
            cout << name << "'s " << roster[battleRoster[activePoke]].getName() << " used " << roster[battleRoster[activePoke]].getChargedName() << "!" << endl;
            int cATK_attacker = (roster[battleRoster[activePoke]].getBA() + roster[battleRoster[activePoke]].getIA()) * roster[battleRoster[activePoke]].refCPM(roster[battleRoster[activePoke]].getLVL());
            int cDEF_defender = (enemy.roster[enemy.battleRoster[enemy.activePoke]].getBD() + enemy.roster[enemy.battleRoster[enemy.activePoke]].getID()) * enemy.roster[enemy.battleRoster[enemy.activePoke]].refCPM(enemy.roster[enemy.battleRoster[enemy.activePoke]].getLVL());
            int totalDamage;
            if (enemy.roster[enemy.battleRoster[enemy.activePoke]].checkTwoTypes()) //if the nemy pokemon has two types,
            {
                totalDamage = floor(0.5 * roster[battleRoster[activePoke]].getChargedPower() * cATK_attacker / cDEF_defender * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) + 1;
                enemy.roster[enemy.battleRoster[enemy.activePoke]].subtractHealth(totalDamage);
                //Edited by Dylan Binu. Move effectiveness messages.
                if ((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) > 1)
                {
                    cout << "It was super effective!" << endl;
                }
                if ((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(1)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) < 1)
                {
                    cout << "It was not very effective!" << endl;
                }
            }
            else {
                totalDamage = floor(0.5 * roster[battleRoster[activePoke]].getChargedPower() * cATK_attacker / cDEF_defender * roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].chargedResonanceCheck()) + 1;
            enemy.roster[enemy.battleRoster[enemy.activePoke]].subtractHealth(totalDamage); //here we take the damage we just calculated and subtract it from the enemy's health

            //Edited by Dylan Binu. Move effectiveness messages.
            if((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].fastResonanceCheck()) > 1) {
                cout << "It was super effective!" << endl;
            }
            if((roster[battleRoster[activePoke]].refTypeMatchup(roster[battleRoster[activePoke]].getChargedType(), enemy.roster[enemy.battleRoster[enemy.activePoke]].getType(0)) * roster[battleRoster[activePoke]].fastResonanceCheck()) < 1) {
                cout << "It was not very effective!" << endl;
            }
            }
            cout << enemy.roster[enemy.battleRoster[enemy.activePoke]].getName() << " Has taken " << totalDamage << " damage, and is now at " << enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() << " HP!" << endl;
            roster[battleRoster[activePoke]].changeEnergy(-1 * (roster[battleRoster[activePoke]].getChargedCost()));
            if (enemy.roster[enemy.battleRoster[enemy.activePoke]].getCurrentHP() <= 0 && enemy.notDead() == true)
                enemy.chooseActive();
        }
    }
    //this is the fluke mentioned above, when a pokemon can't charge attack but tries to.
    else {
        cout << name << "'s " << roster[battleRoster[activePoke]].getName() << " tried to use " << roster[battleRoster[activePoke]].getChargedName() << ", but didn't have enough energy!" << endl;
    }
}

void trainer::turnAgainst(trainer& enemy) {
    bool wrong = true;
    while (wrong) {
        wrong = false;

        cout << "\nIt is " << name << "'s turn!"<< endl;
        cout << " | " << roster[battleRoster[activePoke]].getName() << " | " << roster[battleRoster[activePoke]].getCurrentHP()
            << " HP | " << roster[battleRoster[activePoke]].getEnergy() << " Energy |" << endl;
        cout << "1 - Fast Attack - " << roster[battleRoster[activePoke]].getFastName() << endl;
        if (roster[battleRoster[activePoke]].getEnergy() >= roster[battleRoster[activePoke]].getChargedCost())
            cout << "2 - Charged Attack - " << roster[battleRoster[activePoke]].getChargedName() << endl;
        else
            cout << "2 - Charged Attack - NOT ENOUGH ENERGY" << endl;
        cout << "3 - Change active Pokemon" << endl;
        cout << "\nChoose your action: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            fastAttack(enemy);
            break;
        case 2:
            chargedAttack(enemy);
            break;
        case 3:
            chooseActive();
            break;
        default:
            cout << "Something went wrong!";
            wrong = true;

                
        } //Switch bracket

        
        
        
    }   //While

    
}

//Returns false if current HP if any of the  is less than or equal to 0. Returns true otherwise.
bool trainer::notDead() {
    if (roster[battleRoster[0]].getCurrentHP() <= 0 && roster[battleRoster[1]].getCurrentHP() <= 0 && roster[battleRoster[2]].getCurrentHP() <= 0) {
        return false;
    }
    else {

        return true;
    }
}


