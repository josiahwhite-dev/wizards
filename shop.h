#pragma once
#include<iostream>
#include<string>

//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"


#ifndef SHOP_H
#define SHOP_H
class shop{


    public:


      shop();


        int potion;
        int sword;
        int shield;
        int staff; 
    

    //Behaviours
      

        int sell(player *user, std::string request, int munny);        //For selling items


    
       

    ~shop();
};


#endif 