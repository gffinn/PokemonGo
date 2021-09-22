# PokemonGo
CSC 275 Final project - develop a working PokemonGo game
Background Information:

Each Pokemon Species in Pokemon GO has a set of hidden Base Attributes (baseATK, baseDEF, and baseSTA) which are used in calculating HP, outgoing damage, and incoming damage.  As an example, let’s look at Wobbuffet:

https://gamepress.gg/pokemongo/pokemon/202



In this example, every Wobuffet has baseATK =  60, baseDEF = 106, and baseSTA = 382.  

Each individual Pokemon also has a set of visible Individual Values (IVs) (ivATK, ivDEF, ivSTA) which are also used in the calculation of HP, outgoing damage, and incoming damage.  As an example, these two Pikachu have their own individual values representing how powerful they are for their species:

 


The Pikachu on the left has ivATK = 0, ivDEF = 0, ivSTA = 0.  The Pikachu on the right has ivATK = 3, ivDEF = 0, and ivSTA = 2.  Individual Values each range from 0 to 15.  
Each Pokemon has a level ranging from 1 to 40.  In the real pokemon GO game, levels increment by 0.5.  For this assignment, you can simply have them increment by 1 if you wish.  The pokemon’s level is used to look up a “CP Multiplier” or CPM from a table of values found here:

https://gamepress.gg/pokemongo/cp-multiplier

This table of values can be stored in a constant array and indexed by the pokemon’s level – 1.  For example, CPM[7] would give the appropriate CPM value for a level 8 pokemon.

Each Pokemon has a Hit Point score (HP) which tracks the amount of damage a Pokemon can suffer in battle before feigning.  The total HP is calculated by the formula:  

HP = floor( (baseSTA + ivSTA) * CPM[level-1] )

In C++, the floor function can be used from the <math.h> library.

Each Pokemon species has one or two types from the following list:

https://gamepress.gg/pokemongo/pokemon-go-type-chart

Types are used in the calculations of outgoing and incoming damage based upon the weaknesses and strengths described in the chart.  

Two types of Moves exist in Pokemon GO:  Fast Moves and Charge Moves.  
Each Move has a Damage Type:  The list of Damage Types is the same as the list of Pokemon types from the chart above.

Each Pokemon species has a list of Fast Moves they can learn.  Pokemon know one Fast Move from that list at any given time.

Each Pokemon species also has a list of Charge Moves they can learn.  Pokemon know one or two Charge Moves from that list at any given time.

You can learn a new move from the pokemon’s list by replacing an existing one (replace a fast move with a new fast move or a charge move with a new charge move)

Fast Moves are basic attacks that deal damage and charge up energy.  They have these main statistics in PVP:

Base Power:  Some non-negative integer.  [Used to compute total damage.]
Duration: Some non-negative floating point number.  [Amount of time the attack animation takes to complete.]
Energy Delta:  Some non-negative integer.  [Amount of Energy returned and stored by the Pokemon.]
Move Cooldown:  Some non-negative floating point number.  [Amount of time following the attack animation before the move can be used again.]

Example Fast Move (Counter):
https://gamepress.gg/pokemongo/pokemon-move/counter

Charge Moves are special attacks which can be used after charging enough Energy through Fast Moves.  Once used, an amount of Energy is spent for the attack.  Charge Moves can be Shielded.  Each Trainer has up to 2 Shields per battle.  Charge moves have the following statistics in PvP:

Base Power: Some non-negative integer.  [Used to compute total damage.]
Charge Energy:  Some negative integer.  [Amount of energy needed to activate.  Spent when used.]

Example:
https://gamepress.gg/pokemongo/pokemon-move/power-punch

Each Pokemon has some maximum energy it can store.  For this project, you may use a constant of 500 total energy for this maximum energy storage limit across all pokemon.   

Damage from a move used by an attacker against a defender is calculated by the following formula:

TotalDamage =  floor( 0.5  * BasePower * cATK_attacker / cDEF_defender * Multipliers ) + 1

Where:

cATK_attacker = ( baseATK + ivATK ) * CPM[ attackerlvl – 1 ]
cDEF_defender = ( baseDEF + ivDEF ) * CPM[ defenderlvl – 1 ]

And multipliers include:

Same Type Attack Bonus (STAB):  * 1.2 multiplier if the pokemon uses an attack of its own type.  Example:  Pikachu (an electric pokemon) using Thunderbolt (an electric move).

Effectiveness:  Ranges depending upon the type of the move being used and the types of the defender.  Refer to the type chart:  https://gamepress.gg/pokemongo/pokemon-go-type-chart

Additional details on calculations can be found here:

https://gamepress.gg/pokemongo/damage-mechanics

Credit to Reddit user u/Qmike.

Each Trainer has a list of owned Pokemon, which can be stored as a vector of Pokemon objects.  These are the pokemon the Trainer has available to choose from when battling. 

Each Trainer has a battle team of 3 Pokemon which are chosen from the Owned list.  This could be stored as an array of three integer indexes to the owned Pokemon vector.  

Each Trainer has 2 shields which can be used during a given battle.  Shields are used to block the damage of an incoming Charge Move.  

Implementing a full combat system in the main function is optional.  It is also permissible to simply test the functions and classes without having a game implemented.  For some details on how combat works:

In a battle between two trainers (handled at the application level), each trainer uses their battle team of 3 pokemon.  When a Charge Move is used against the trainer’s pokemon, the defending Trainer may choose to use a Shield if one is available.  Using a shield reduces the total number of shields available by 1.  A trainer battle ends when one of the two trainers’ set of three pokemon have all been reduced to 0 HP. 

On a trainer’s turn, if the trainer’s pokemon is not on cooldown or in the middle of using a fast move, the trainer can choose to make a Fast Move, a Charge Move (if there is enough energy available), to delay (take no action), or to Switch to another pokemon from their set of 3.  Only a pokemon with > 0 HP can be used in battle.  

Pokemon HP totals should be reset back to their maximum values after the trainer battle is over.  As such, you should have storage for the pokemon’s MaxHP along with its CurrentHP.  MaxHP is the calculated total from the formula provided.  CurrentHP starts as equal to MaxHP at the start of the battle and is depleted as attack damage is dealt.  Damage from a Fast Move is applied after the attack animation is completed.  Damage from a Charge Move is applied after the defending trainer decides whether or not the Shield the attack.  Charge Moves have no delay other than pausing to give the defending trainer the opportunity to choose to shield or not.  

Project Requirements:

You will be writing new classes based upon the Fighter / Power classes from project 1.  The new classes should be implemented in a way that facilitates development of a Pokemon Go battling game, based upon the background information provided.  You must:

1)	Write a new class for Fast Moves
2)	Write a new class for Charge Moves
3)	Write a new class for Pokemon 
4)	Write a new class for Trainer
5)	Use real or near-real formulas for Pokemon Go-type damage calculations and HP calculation.
6)	Write a main function which tests all classes and functions.
7)	Document your functions / variables / test cases with comments.
8)	Use at least 6 pokemon chosen from the following list along with the powers of the 6 you choose.  Use the real base attributes and their real power lists as provided in these links.

 Pikachu - https://gamepress.gg/pokemongo/pokemon/25
   Zekrom - https://gamepress.gg/pokemongo/pokemon/644
   Charizard – https://gamepress.gg/pokemongo/pokemon/6
   Deoxys (Normal Forme) - https://gamepress.gg/pokemongo/pokemon/386
   Metagross – https://gamepress.gg/pokemongo/pokemon/376
   Squirtle – https://gamepress.gg/pokemongo/pokemon/7
   Scizor – https://gamepress.gg/pokemongo/pokemon/212
   Jigglypuff – https://gamepress.gg/pokemongo/pokemon/39
   Clefairy – https://gamepress.gg/pokemongo/pokemon/35
   Lucario – https://gamepress.gg/pokemongo/pokemon/448
   Salamence – https://gamepress.gg/pokemongo/pokemon/373
   Charmander – https://gamepress.gg/pokemongo/pokemon/4
   Bulbasaur - https://gamepress.gg/pokemongo/pokemon/1

9)	Note:  your damage calculations should work even if I make two completely different pokemon with new moves etc.  It will need to work for different varieties of move and type combinations.  
10)	You may work together as a class regarding development of the design specification.  However, actual programming must be done individually.  
a.	You can work together on the interface (.h, header) files.
i.	That is, the contents of the .h files including the class definitions, the purpose, preconditions and postconditions of functions, the prototypes for public member functions, and the private member variables.
b.	You cannot work together on documentation other than in the interface files.
c.	You cannot work together on the application (main.cpp) file
i.	That is, you cannot work together on the main function or other contents of main.cpp.
d.	You cannot work together on the implementation files
i.	That is, you cannot work together on the .cpp files or any of the member function or operator overload definitions, constructor definitions, etc.
e.	Anything not listed above:  Assume you cannot work together on it unless otherwise approved by the instructor and added to this specification as an addendum.
11)	Let me know as soon as you have questions so that I can try to address them.  Don’t wait until the last minute, as this project requires creative work on your part.  Creativity wont be rushed at the last minute
