#include<iostream>
#include<string>

//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"

//Actual declarations
#include"player.h"
#include"enemy.h"

using namespace std;


enemy::enemy(){

    health = 100;
    attk = 10;
    magic = 10; 
    def = 10;

}


wizard::wizard(){
    
    health = health*0.6;
    attk = attk*1.0;
    magic = magic*3.0;
    def = def*0.7;

}

int wizard::attack(player* user){

    //Wizard casts a spell
    //Uses magic stat to take away from health
    //Slightly negated by users defence
    if ((user->def * 0.5) < magic){
    user->health -= magic - (user->def*0.1);
    }

}


pheonix::pheonix(){
    
    health = health*0.8;
    attk = attk*1.5;
    magic = magic*1.5;
    def = def*1.0;

}

int pheonix::attack(player* user){

    //Pheonix uses attack and magic
    //Takes away from health
    //Slightly stronger than others, but defence negates more
    if ((user->def * 0.7) < (attk+magic)){
    user->health -= ((attk+magic)*0.8) - (user->def*0.2); 
    }
}



horse::horse(){
    
    health = health*2;
    attk = attk*1.9;
    magic = magic*1.0;
    def = def*2;

}

int horse::attack(player* user){

    //Horse uses just attack
    //Takes away from user health
    //Slightly weaker, but has higher defence 
    if ((user->def*0.8) < attk){
    user->health -= attk - ((user->def)*0.4); 
    }
}
