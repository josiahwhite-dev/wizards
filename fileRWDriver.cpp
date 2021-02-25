#include<iostream>
#include<string>

//For generating a random number
#include<stdlib.h>
#include <ctime>

//For reading from file
#include<fstream>
#include<limits>
#include<sstream>

//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"
#include"enemy.fwd.h"


//Actual declarations
#include"player.h"
#include"enemy.h"
#include"shop.h"    
using namespace std;

//Saving to & reading from file
extern fstream& saveToFile(player *user);
extern string& readUsername(int num);      //string for reading names
extern int readStats(int num);

int tester(){
    
    player *user;
    user = new player("test");

    for(int i; i < 1000; i++){
        user->attack = i;
        user->magic = i;
        user->def = i;
        user->health = i;
        user->munny = i;
        user->potionCount = i;

        saveToFile(user);

    }


}