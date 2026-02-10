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
    numRentItems = 0;

    rentItemArray = new RentItem*[maxRentItems];

    gameArray = new Game*[maxGames];
}

Business::~Business(){
    cout << "Business Destructor: " << endl;

    for(int i = 0; i < sizeof(gameArray); i++){
        cout << "RELEASING MEMORY FOR GAME IN ARRAY: " << gameArray[i]->getGameName()->getText();
        delete gameArray[i];

    }
    delete gameArray;


    for(int i = 0; i < sizeof(rentItemArray); i++){
        cout << "RELEASING MEMORY FOR RENT ITEM IN ARRAY: " << rentItemArray[i]->getItemName()->getText();
        delete rentItemArray[i];

    }
    delete rentItemArray;

}

int Business::getNumGames(){
    return numGames;
}

int Business::getnumRentItems(){
    return numRentItems;
}

void Business::addGamesFromFile(){
    string filename;
    string gameName;
    string gameDescription;
    float gameCost;
    int numPlayers;
    int maxOccupancy;
    float gameDurationInHours;

    cout << "What is the name of the file that contains games? " << endl;
    getline(cin, filename);

    ifstream inputFile(filename);
    
    if(!inputFile.is_open()){
        cout << "Error: Could not open file " << filename << endl;
        return;
    }
    
    while (getline(inputFile, gameName)){
        // Read game description
        getline(inputFile, gameDescription);
        
        // Read game cost
        inputFile >> gameCost;
        inputFile.ignore();
        
        // Read number of players
        inputFile >> numPlayers;
        inputFile.ignore();
        
        // Read max occupancy
        inputFile >> maxOccupancy;
        inputFile.ignore();
        
        // Read game duration in hours
        inputFile >> gameDurationInHours;
        inputFile.ignore();
        
        // Check if we need to resize
        if(numGames >= maxGames){
            cout << "RESIZING GAME ARRAY...from " << maxGames << " to a new size of " << (maxGames * 2) << endl;
            
            // Create new game array with double capacity
            Game** newGameArray = new Game*[(maxGames * 2)];
            
            // Copy existing games to new array
            for(int i = 0; i < numGames; i++){
                newGameArray[i] = gameArray[i];
            }
            
            // Delete old array and update pointer
            delete [] gameArray;
            gameArray = newGameArray;
            maxGames = maxGames * 2;
        }
        
        // Create new Game and add to array
        Text* name = new Text(gameName.c_str());
        Text* description = new Text(gameDescription.c_str());
        gameArray[numGames] = new Game(name, description, gameCost, numPlayers, maxOccupancy, gameDurationInHours);
        numGames++;
    }
    
    inputFile.close();
}

void Business::addItemsFromFile(){
    string filename;
    string rentItemName;
    string rentItemDescription;
    float rentItemCost;
    int howManyInStock;
    float rentItemDurationInHours;

    cout << "What is the name of the file that contains rentItems? " << endl;
    getline(cin, filename);

    ifstream inputFile(filename);
    
    if(!inputFile.is_open()){
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    while (getline(inputFile, rentItemName)){
        // Read rentItem description
        if(!getline(inputFile, rentItemDescription)) break;

        // Read rentItem cost
        if(!(inputFile >> rentItemCost)) break;
        inputFile.ignore();

        // Read how many in stock
        if(!(inputFile >> howManyInStock)) break;
        inputFile.ignore();

        // Read rentItem duration in hours
        if(!(inputFile >> rentItemDurationInHours)) break;
        inputFile.ignore();

        // Check if we need to resize
        if(numRentItems >= maxRentItems){
            cout << "RESIZING rentItem ARRAY...from " << maxRentItems << " to a new size of " << (maxRentItems * 2) << endl;
            
            // Create new rentItem array with double capacity
            RentItem** newrentItemArray = new RentItem*[(maxRentItems * 2)];
            
            // Copy existing rentItems to new array
            for(int i = 0; i < numRentItems; i++){
                newrentItemArray[i] = rentItemArray[i];
            }
            
            // Delete old array and update pointer
            delete [] rentItemArray;
            rentItemArray = newrentItemArray;
            maxRentItems = maxRentItems * 2;
        }

        // Create new rentItem and add to array
        Text* name = new Text(rentItemName.c_str());
        Text* description = new Text(rentItemDescription.c_str());
        rentItemArray[numRentItems] = new RentItem(name, description, rentItemCost, howManyInStock, rentItemDurationInHours);
        numRentItems++;
    }

    inputFile.close();
}

void Business::addGameToItem(){

}

void Business::addGameToArray(){

}

void Business::editGameInArray(){

}

void Business::removeGameFromArray(){

}

void Business::addRentItemToArray(){

}

void Business::editRentItemInArray(){

}

void Business::removeRentItemFromArray(){

}

void Business::printGameNames(){

}

void Business::printRentItemNames(){

}

void Business::printGames(){

}

void Business::printRentItems(){

}

void Business::saveData(){

}
