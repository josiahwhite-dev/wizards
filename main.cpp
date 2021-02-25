//Standard libraries
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


//Actual declarations of classes and their behaviour/stats
#include"player.h"
#include"enemy.h"
#include"shop.h"    
using namespace std;

//global var (for savegame)
fstream savegame;

//functions

//Saving to & reading from file
fstream& saveToFile(player *user);
string& readUsername(int num);      //string for reading names
int readStats(int num);

//Player experience functions
int fight(player *user);
int shopping(player *user);

//Displaying characters
void printWizard();
void printPheonix();
void printHorse();
void printPlayer();

//Clearing the Screen
void clearScreen();

//Quitting the game
void quit(player *user);

//Testing the game
void tester();

int main(){

//Name/Choice/Action for use throughout
string choice; 
string name;
string action;

//One variable for breaking the game loop;
int breaker = 0;
player *user;

//This section is for running code that will test all cases. 
string testChoice;
while(testChoice.compare("N") != 0){
    
    cout<<"TESTING MODE: Y/N:\n";
    cin>>testChoice;
    if(testChoice.compare("Y")==0){
    tester();
    }
}



    //Prints 80 new lines and presents user with choice of game
    //notation in cout is for formatting 
    clearScreen();
    cout << "\033[1;31m     NEW\n     LOAD\n\033[0m\n";
    cout << "\033[1;36m     PLEASE ENTER YOUR CHOICE: \033[0m\n     ";
    cin>>choice;

    clearScreen();



    //User Menu Interaction 
    while (breaker <= 0){
    if (choice.compare("NEW") == 0){


        //Shows player, takes name
        printPlayer();    
        cout<<"\033[1;31m     WHAT IS YOUR NAME?: \n     \033[0m\n      ";
        cin>>name;

        //Makes so that name cannot be greater than 20 characters
        name = name.substr(0, 20);

        //Creates a player with the given name
        user = new player(name);

        clearScreen();
        break;

    }else if(choice.compare("LOAD") == 0){
        
       cout<<"\033[1;31m     LOADING... \n     \033[0m\n";

        //Reads in all the values, initialises a player
        string savedName = readUsername(0);
        int savedAttack = readStats(1);
        int savedMagic = readStats(2);
        int savedDef = readStats(3);
        int savedMunny = readStats(4);
        int savedPotions =  readStats(5);
        int savedHealth = readStats(6);
        int savedLevel = readStats(7);
        
        //Makes so that name cannot be greater than 20 characters
        savedName = savedName.substr(0, 20);

        user = new player(savedName,savedAttack,savedMagic,savedDef,savedMunny,savedPotions,savedHealth, savedLevel);


        break;
    
    }else if (choice.compare("QUIT") == 0){

        quit(user);

    }else{

        cout << "\033[1;31m     NEW\n     LOAD\n\033[0m\n";
        cout<<"\033[1;31m     PLEASE ENTER A VALID CHOICE: \n     \033[0m\n     ";
        cin>>choice;
        clearScreen();
    }
        
    }

    //////////////////////////////////
    //  After the new / Load menu   //
    //////////////////////////////////

    cout<<"\033[1;31m     HELLO, "<<user->myName<<"\033[0m\n";

   
    //Starting actual game
    while (breaker <= 0){

    //Resetting HP after every fight
    user->health = 100;
    


    cout << "\n         FIGHT     SHOP\n\n";
    cout<<"\033[1;31m     WHAT DO YOU WISH TO DO? \n     \033[0m\n      ";

    cin>>action;
    
    if (action.compare("FIGHT")==0){
        fight(user);

    }else if(action.compare("SHOP")==0){

        clearScreen();
        shopping(user);
        
    }else if (action.compare("QUIT") == 0){

        quit(user);
         

    }else{
        clearScreen();
        cout<<"\033[1;31m     PLEASE ENTER A VALID CHOICE: \n     \033[0m\n     ";

    }

    }

    


}




void clearScreen(){

    cout << string( 80, '\n' );

}

    ///////////////
    //  FIGHT   //
    //////////////

int fight(player* user){

    string combatChoice;

    //Generates a random number between 1 and 3 using ctime
    //Creates a new enemy of that type 
   int enemyPicker = 1 + (rand() % 3);
   enemy *enemy = NULL;

   switch (enemyPicker)
   {
   case 1:
        enemy = new wizard();
        break;
    case 2:
        enemy = new pheonix();
        break;

    case 3:
        enemy = new horse();
        break;
   }
    

    while (enemy->health > 0 && user->health > 0){

    printPlayer();
     //Healthbar for Player
    cout <<"                [\033[1;31m"<< string( (user->health/10), '#' )<<"\033[0m]("<<user->health<<")\n";
    
    switch (enemyPicker)
   {
   case 1:
        printWizard();
        break;
    case 2:
        printPheonix();
        break;

    case 3:
        printHorse();
        break;
   }

    //Healthbar for Enemy
    cout <<"                [\033[1;31m"<< string( (enemy->health/10), '#' )<<"\033[0m]("<<enemy->health<<")\n";
    


    cout << "\n         (A) ATTACK      (S) SPELL     (I) ITEM\n\n";
    cout<<"\033[1;31m             WHAT DO YOU WISH TO DO? \n     \033[0m\n  ";
    cin>>combatChoice;

    if (combatChoice.compare("A")==0){
     
        user->damage(enemy);
        enemy->attack(user);
        

    }else if(combatChoice.compare("S")==0){
        
        user->spell(enemy);
        enemy->attack(user);
        

    }else if(combatChoice.compare("I")==0){
       
        cout << "\n                      POTION * "<<user->potionCount<<"\n\n";
        cout<<"\033[1;31m             USE       BACK \n     \033[0m\n  ";
        cin>>combatChoice;

        if (combatChoice.compare("USE")==0){
     
            if (user->potionCount > 0){
                user->use();
            }else{
                cout<<"\033[1;34m\n\n\n\n     NO POTIONS TO USE!\033[0m\n";
            }

        }else if (combatChoice.compare("BACK")==0){
     
           

        }



    }else if (combatChoice.compare("QUIT") == 0){

         quit(user);

    }

    }
    clearScreen();

    if (enemy->health <= 0){
        cout<<"\n     WIN!    +50 MUNNY\n";
        user->munny += 50;
        user->level+=1;
    }else{
        cout<<"\n     LOSS!   +10 MUNNY\n";
        user->munny += 10;
    }
  


}

    //////////////
    //  SHOP    //
    /////////////

int shopping(player *user){
    string request; 

    shop *store; 
    store = new shop(); 

    cout<<"\033[1;34m             CURRENT FUNDS: ₡ \033[0m  "<<user->munny<<endl;
    cout << "\n         POTION (₡10)      SWORD (₡50)     STAFF (₡50)     SHIELD (₡50)     \n\n         EXIT\n";
    cout<<"\033[1;31m             WHAT DO YOU WISH TO BUY? \n     \033[0m\n  ";

    while(request.compare("EXIT")!=0){
    cin>>request;

    store->sell(user,request,user->munny);
    }
    clearScreen();
        
}

    //////////////////////
    //  READ FROM FILE  //
    /////////////////////

//Reads username
string& readUsername(int num){

        //Used for returning username
        string* userStat;
        userStat = new string;
        
        //Reads in from savegame.txt   
        ifstream login("savegame.txt");
        for(int i = 0; i < num; i++){
            
            //Gets line, sets it to username
            getline(login, *userStat);
        }

        //Also need to do outside of loop to properly store it 
        getline(login, *userStat);
        
        return(*userStat);

}

//same as above for stats
int readStats(int num){

          //Used for returning username
        string* userStat;
        userStat = new string;
        
        //Reads in from savegame.txt   
        ifstream login("savegame.txt");
        for(int i = 0; i < num; i++){
            
            //Gets line, sets it to username
            getline(login, *userStat);
        }

        //Also need to do outside of loop to properly store it 
        getline(login, *userStat);

        std::stringstream stream(*userStat);
        int stat;
        stream>>stat;
        
        return(stat);


}

    //////////////////////
    //  SAVE TO FILE    //
    /////////////////////


fstream& saveToFile(player *user){
        savegame.open("savegame.txt", fstream::out);

        //Saving name and stats
        savegame << user->myName<<"\n"<<user->attack<<"\n"<<user->magic<<"\n"<<user->def<<"\n"<<user->munny<<"\n"<<user->potionCount<<"\n"<<user->health<<"\n"<<user->level;
        savegame.close();
}

    //////////////
    //  QUIT    //
    /////////////

void quit(player *user){
    
    string quitter;

     cout << "\n                        YES      NO     \n\n";
     cout<<"\033[1;31m             ARE YOU SURE YOU WISH TO QUIT? \n     \033[0m\n  ";
     cin>>quitter;

    if (quitter.compare("YES") == 0){
    saveToFile(user);
    clearScreen();
    exit(0);
    }else{
        return;
    }
}



void printPlayer(){

            cout<<"\033[1;37m" << R"(
         _,.
        ,` -.)
       ( _/-\\-._
      /,|`--._,-^|            ,
      \_| |`-._/||          ,'|
        |  `-, / |         /  /
        |     || |        /  /
         `r-._||/   __   /  /
     __,-<_     )`-/  `./  /
    '  \   `---'   \   /  /
        |           |./  /
        /           //  /
    \_/' \         |/  /
     |    |   _,^-'/  /
     |    , ``  (\/  /_
      \,.->._    \X-=/^
      (  /   `-._//^`
       `Y-.____(__}
        |     {__)
              ()
)"<<"\033[0m";

}

void printWizard(){

            cout<<"\033[1;34m" << R"(
                                ____
                              .'* *.'
                           __/_*_*(_
                          / _______ \
                         _\_)/___\(_/_
                        / _((\- -/))_ \
                        \ \())(-)(()/ /
                         ' \(((()))/ '
                        / ' \)).))/ ' \
                       / _ \ - | - /_  \
                      (   ( .;''';. .'  )
                      _\"__ /    )\ __"/_
                        \/  \   ' /  \/
                         .'  '...' ' )
                          / /  |  \ \
                         / .   .   . \
                        /   .     .   \
                       /   /   |   \   \
                     .'   /    b    '.  '.
                 _.-'    /     Bb     '-. '-._
             _.-'       |      BBb       '-.  '-.
            (________mrf\____.dBBBb.________)____)

)" <<"\033[0m"<< '\n';

}

void printPheonix(){

            cout<<"\033[1;33m" << R"(
                                                        (                           
                  ) )( (                           ( ) )( (
               ( ( ( )  ) )                     ( (   (  ) )(
              ) )     ,,\\\                     ///,,       ) (
           (  ((    (\\\\//                     \\////)      )
            ) )    (-(__//                       \\__)-)     (
           (((   ((-(__||                         ||__)-))    ) )
          ) )   ((-(-(_||           ```\__        ||_)-)-))   ((
          ((   ((-(-(/(/\\        ''; 9.- `      //\)\)-)-))    )
           )   (-(-(/(/(/\\      '';;;;-\~      //\)\)\)-)-)   (   )
        (  (   ((-(-(/(/(/\======,:;:;:;:,======/\)\)\)-)-))   )
            )  '(((-(/(/(/(//////:%%%%%%%:\\\\\\)\)\)\)-)))`  ( (
           ((   '((-(/(/(/('uuuu:WWWWWWWWW:uuuu`)\)\)\)-))`    )
             ))  '((-(/(/(/('|||:wwwwwwwww:|||')\)\)\)-))`    ((
          (   ((   '((((/(/('uuu:WWWWWWWWW:uuu`)\)\))))`     ))
                ))   '':::UUUUUU:wwwwwwwww:UUUUUU:::``     ((   )
                  ((      '''''''\uuuuuuuu/``````         ))
                   ))            `JJJJJJJJJ`           ((
                     ((            LLLLLLLLLLL         ))
                       ))         ///|||||||\\\       ((
                         ))      (/(/(/(^)\)\)\)       ((
                          ((                           ))
                            ((                       ((
                              ( )( ))( ( ( ) )( ) (()

)"<<"\033[0m"<< '\n';

}

void printHorse(){

                cout<<"\033[1;35m" << R"(
                                      /
                           __       //
                           -\= \=\ //
                         --=_\=---//=--
                       -_==/  \/ //\/--
                        ==/   /O   O\==--
           _ _ _ _     /_/    \  ]  /--
          /\ ( (- \    /       ] ] ]==-
         (\ _\_\_\-\__/     \  (,_,)--
        (\_/                 \     \-
        \/      /       (   ( \  ] /)
        /      (         \   \_ \./ )
        (       \         \      )  \
        (       /\_ _ _ _ /---/ /\_  \
         \     / \     / ____/ /   \  \
          (   /   )   / /  /__ )   (  )
          (  )   / __/ '---`       / /
          \  /   \ \             _/ /
          ] ]     )_\_         /__\/
          /_\     ]___\
         (___)

)" <<"\033[0m"<< '\n';

}

    //////////////
    //  TESTING //
    /////////////


void tester(){
    
    //Dummy Player
    player *testUser;
    testUser = new player("test");

    //Dummy Shop
    shop *store; 
    store = new shop(); 

    //Runs through many iterations 
    for(int i = 0; i < 1000; i++){
        testUser->myName += to_string(i);
        testUser->attack = i;
        testUser->magic = i;
        testUser->def = i;
        testUser->health = i;
        testUser->munny = i;
        testUser->potionCount = i;
        testUser->level= i;

        saveToFile(testUser);


        //Ensuring test input is same as what is read
        string savedName = readUsername(0);
        int savedAttack = readStats(1);
        int savedMagic = readStats(2);
        int savedDef = readStats(3);
        int savedMunny = readStats(4);
        int savedPotions =  readStats(5);
        int savedHealth = readStats(6);
        int savedLevel = readStats(7);

        if(savedName != testUser->myName){
            cout<<"ERROR: NAME\n";
        }

        if(savedAttack != testUser->attack){
            cout<<"ERROR: ATTACK\n";
        }

        if(savedMagic != testUser->magic){
            cout<<"ERROR: MAGIC\n";
        }

        if(savedDef != testUser->def){
            cout<<"ERROR: DEFENSE\n";
        }

        if(savedMunny != testUser->munny){
            cout<<"ERROR: MUNNY\n";
        }

        if(savedPotions != testUser->potionCount){
            cout<<"ERROR: POTION\n";
        }

        if(savedHealth != testUser->health){
            cout<<"ERROR: HEALTH\n";
        }


        //Testing shopping:
        string request;

        if(i > 0){
            
            cout<<"Loop "<<i<<" Potion";
            request="POTION";
            store->sell(testUser,request,i);
 


            cout<<"Loop "<<i<<" Staff";
            request="STAFF";
            store->sell(testUser,request,i);
            cout<<i;


        }



        
    }





}