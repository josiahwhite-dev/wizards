#include<iostream>
#include<string>


//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"


//Actual declarations
#include"enemy.h"
#include"player.h"





using namespace std;



player::player(string name){

    //Defaults 
    myName = name;
    health = 100;
    attack = 20;
    magic = 10;
    munny = 50;
    def = 10;
    potionCount = 0;
    

}

player::player(string savedName, int savedAttack,int savedMagic,int savedDef,int savedMunny,int savedPotions, int savedHealth, int savedLevel){

    myName = savedName;
    health = savedHealth;
    attack = savedAttack;
    magic = savedMagic;
    munny = savedMunny;
    def = savedDef;
    potionCount = savedPotions;
    level = savedLevel;

}


int player::damage(enemy* target){

    float modifier;
    modifier = level/5;
    //Attacks enemy, but is also negated by all of enemy's defence
    //In this case, a horse cannot be beat, as attack is 20 and defence is 20 to begin with.
    if (attack > target->def*(1.0 + level/5)){
    target->health -= (attack*(0.1*(attack/10)) - target->def*(1.0 + modifier));
    }
 

}        //For giving damage

int player::spell(enemy* target){

    //Casts a spell; starts off weaker, but has potential to do more
    //Due to less defence use
    float modifier;
    modifier = level/5;
    
    if (magic > (target->def)* (0.8 + level/5)){
    target->health -= ((magic*(0.1*(magic/10))) - (target->def)* (0.8 + modifier)); 
    }


}        //For giving damage

int player::use(){

        //Adds 20hp, removes a potion 
        health += 20;
        potionCount--;

}      //For using an item

