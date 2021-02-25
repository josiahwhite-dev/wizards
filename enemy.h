#pragma once
#include<iostream>
#include<string>


//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"

#ifndef ENEMY_H
#define ENEMY_H
class enemy{

    public:

    enemy();
    //enemy(std::string enemytype);

    std::string myType;

    int health;
    int attk;
    int magic; 
    int def;
    int level;

    //Behaviours

    //Needs virtual int as it doesnt make sense
    //For a typeless enemy to have an attack     
    virtual int attack(player* user) = 0;

    //private:
    
~enemy();
};

class wizard : public enemy{

    public:

    wizard();
    int attack(player* user) override;

~wizard();
};


class pheonix : public enemy{

    public:

    pheonix();
    int attack(player* user) override;

~pheonix();
};


class horse : public enemy{

    public:

    horse();
    int attack(player* user) override;

~horse();
};




#endif