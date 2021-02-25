#pragma once
#include<iostream>
#include<string>

//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"


#ifndef PLAYER_H
#define PLAYER_H
class player{


    public:

      //gplayer();
      player(std::string name);
      player(std::string savedName, int savedAttack,int savedMagic,int savedDef,int savedMunny,int savedPotions, int savedHealth, int savedLevel);

        std::string myName;

        int health;
        int attack;
        int magic; 
        int munny;
        int level;

        int potionCount;

    //Behaviours
      

        int damage(enemy* target);        //For giving damage
        int spell(enemy* target);        //For giving spell damage

        int use();      //For using an item

   

        int def;    //Only used in this class, not needed public

    
       

    ~player();
};


#endif 