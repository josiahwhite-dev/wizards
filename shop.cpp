#include<iostream>
#include<string>

//These declaration files solve the problem of circular dependancy
//As player needs enemy & enemy needs player to function
#include"player.fwd.h"


//Actual declarations
#include"player.h"
#include"shop.h"

using namespace std;

      shop::shop(){

        //Prices of Items
        potion = 10;
        sword = 50;
        shield = 50;
        staff = 50; 
    
      }

        //Takes in a user, ther request, and their money. 
        int shop::sell(player *user, string request, int munny){

        if (request.compare("POTION")==0){
            if (munny >= potion){
                //Adds Potion:
                user->potionCount++;
                //Deducts Money:
                user->munny-=potion;

            cout<<"     SUCCESSFULLY PURCHASED! YOUR POTION COUNT IS: "<<user->potionCount<<"\n    ";
            }else{
                cout<<"     Insufficient Funds\n    ";
            }

        }else if(request.compare("SWORD")==0){

            if (munny >= sword){
                //Adds Attack
                user->attack+= 10;
                //Deducts Money
                user->munny-=sword;

                cout<<"     SUCCESSFULLY PURCHASED! YOUR ATTACK IS: "<<user->attack<<"\n    ";
            }else{
                cout<<"     Insufficient Funds\n    ";
            }

        }else if(request.compare("STAFF")==0){

             if (munny >= staff){
                //Adds Magic
                user->magic+= 10;
                //Deducts Money
                user->munny-=staff;
            cout<<"     SUCCESSFULLY PURCHASED! YOUR MAGIC IS: "<<user->magic<<"\n    ";
            }else{
                cout<<"     Insufficient Funds\n    ";
            }

        }else if(request.compare("SHIELD")==0){

             if (munny >= shield){
                //Adds Defense
                user->def+= 10;
                //Deducts Money
                user->munny-=shield;
                cout<<"     SUCCESSFULLY PURCHASED! YOUR DEFENSE IS: "<<user->def<<"\n    ";
            }else{
                cout<<"     Insufficient Funds!\n   ";
            }

        }else if (request.compare("QUIT") == 0){

        cout << string( 80, '\n' );
        cout<<"CANNOT QUIT HERE!\n";
        cout<<"\033[1;31m     PLEASE ENTER A VALID CHOICE: \n     \033[0m\n     ";

        }else{

        cout << string( 80, '\n' );
        cout << "\n         POTION      SWORD     STAFF     SHIELD     \n\n         EXIT\n";
        cout<<"\033[1;31m     PLEASE ENTER A VALID CHOICE: \n     \033[0m\n     ";
       
        }

        cout<<"\033[1;34m             CURRENT FUNDS: ₡ \033[0m  "<<user->munny<<"\n     ";


        }        //For selling items


