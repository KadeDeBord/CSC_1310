#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> 
#include "Business.h"

using namespace std;

Business::Business(Text* sN, int mG, int mRI){
    businessName = sN;
    maxGames = mG;
    maxRentItems = mRI;
    numGames = 0;


    RentItem** rentItemArray = new RentItem*[maxRentItems];

    Game** gameArray = new Game*[maxGames];
}

Business::~Business(){
    cout << "Business Destructor: " << endl;

    for(int i = 0; i < sizeof(gameArray); i++){
        cout << "RELEASING MEMORY FOR GAME IN ARRAY: " << gameArray[i].getGameName();
        gameArray[i]->~Game();

    }

    for(int i = 0; i < sizeof(rentItemArray); i++){
        cout << "RELEASING MEMORY FOR RENT ITEM IN ARRAY: " << rentItemArray[i].getItemName();
        rentItemArray[i]->~RentItem();

    }
}

int Business::getNumGames(){
    return numGames;
}

int Business::getnumRentItems(){
    return numRentItems;
}

void Business::addGamesFromFile(){
    string filename;
    string newInfo;

    cout << "What is the name of the file that contains games? " << endl;
    getline(cin, filename);

    
    ifstream inputFile(filename);
    
    while (getline(inputFile, newInfo)){
        if(sizeof(gameArray) < /*Num items + 1*/){
            cout << "RESIZING GAME ARRAY...from " << sizeof(gameArray) << " to a new size of " << (sizeof(gameArray) * 2) << endl;
            //make new game array
             Game** newGameArray = new Game*[(sizeof(gameArray)*2)];

            for(int i = 0; i < sizeof(gameArray); i++){
                newGameArray[i] = gameArray[i];
            }
        }

    }
}