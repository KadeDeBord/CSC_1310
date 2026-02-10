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

void Business::resizeGameArray(){
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

void Business::resizeRentItemArray(){
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
            resizeGameArray();
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
           resizeRentItemArray();
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
    int chosenGame;
    
    printGameNames();

    for(int i = 0; i < sizeof(rentItemArray); i++){
        cout <<"Which game would you like the " << rentItemArray[i] << "to be associated with?" <<endl;
        cout<< "Enter the number of the game from the list above, or enter -1 to skip this item." << endl;

        while(!cin || chosenGame != -1 && (chosenGame < 1 || chosenGame > numGames)){
            cin >> chosenGame;
            cin.ignore();

        }

        if(chosenGame != -1){
            rentItemArray[i]->setGameAssociation(gameArray[(chosenGame-1)]);
        }else{
            cout << "Skipping this item " << endl;
        }
        
    }
}

void Business::addGameToArray(){
    string gameName;
    string gameDescription;
    float gameCost;
    int numPlayers;	
    int maxOccupancy; 
    float gameDurationInHours; 

    cout <<"What is the name of the game? " << endl;
    getline(cin, gameName);

    cout << "What is the description?" << endl;
    getline(cin, gameDescription);

    cout << "What is the cost to play the game? " <<endl;
    cout << "Enter 0 (zero) if the game is free." <<endl;
    cin >> gameCost;
    cin.ignore();

    cout << "What is the number of players?" << endl;
    cout << "If pricing is per game instead of per player, enter 0 (zero)" << endl;
    cin >> numPlayers;
    cin.ignore();

    cout << "What is the maximum number of people who can play the game simultaneously? " << endl;
    cin >> maxOccupancy;
    cin.ignore();

    cout << "What is the duration of the game? " << endl;
    cout << "If the duration is unknown, enter 0 (zero)" << endl;
    cin >> gameDurationInHours;
    cin.ignore();

    
    if(numGames == maxGames){
        resizeGameArray();
    }
    numGames += 1;
    Game* newGame = new Game(new Text(gameName.c_str()), new Text(gameDescription.c_str()), gameCost, numPlayers, maxOccupancy, gameDurationInHours);
    gameArray[numGames] = newGame;
    
}

void Business::editGameInArray(){
    int editNum;

    printGameNames();

    cout <<"Which game would you like to edit?" << endl;
    cout << "Enter a number from the list of games above" << endl;
    cin >> editNum;
    cin.ignore();

    gameArray[editNum-1]->editGameDetails();


}

void Business::removeGameFromArray(){
    int delGame;

    printGameNames();

    cout<<"Which game would you like to remove? " << endl;
    cout << "Enter a number from the list of games above." << endl;
    cin >> delGame;
    cin.ignore();

     for(int i = 0; i < sizeof(rentItemArray); i++){
        if(rentItemArray[i]->getGameAssociation() == gameArray[delGame-1]){
            rentItemArray[i]->setGameAssociation(nullptr);
        }

     }

    gameArray[delGame-1]->~Game();
    delete[] gameArray[delGame-1];

}

void Business::addRentItemToArray(){
    int gameAssociation;
    string itemName;
    string itemDescription;
    float itemCost;
    int howManyInStock;	
    float rentDurationInHours; 

    printGameNames();

    cout <<"What is the game that this rentItem is associated with? " << endl;
    cout <<"Enter the number of the game listed above" << endl;
    cin >> gameAssociation;
    cin.ignore();

    cout << "What is the name of the rental item? " << endl;
    getline(cin, itemName);

    cout << "What is the description?" << endl;
    getline(cin, itemDescription);

    cout << "What is the cost to rent this item? " <<endl;
    cout << "Enter 0 (zero) if the rental fee is free." <<endl;
    cin >> itemCost;
    cin.ignore();

    cout << "How many of this item do you have in stock?" << endl;
    cin >> howManyInStock;
    cin.ignore();

    cout << "How long (in hours) can this item be rented out?" << endl;
    cin >> rentDurationInHours;
    cin.ignore();

    
    if(numRentItems == maxRentItems){
        resizeRentItemArray();
    }
    numRentItems += 1;
    RentItem* newItem = new RentItem(gameArray[gameAssociation-1], new Text(itemName.c_str()), new Text(itemDescription.c_str()), itemCost, howManyInStock, rentDurationInHours);
    rentItemArray[numRentItems] = newItem;
}

void Business::editRentItemInArray(){
    int editNum;

    printRentItemNames();

    cout <<"Which rental item would you like to edit?" << endl;
    cout << "Enter a number from the list of items above" << endl;
    cin >> editNum;
    cin.ignore();

    rentItemArray[editNum-1]->editRentItemDetails();
}

void Business::removeRentItemFromArray(){
    int delItem;

    printRentItemNames();

    cout<<"Which rental item would you like to remove? " << endl;
    cout << "Enter a number from the list of items above." << endl;
    cin >> delItem;
    cin.ignore();


    rentItemArray[delItem-1]->~RentItem();
    delete[] rentItemArray[delItem-1];
}

void Business::printGameNames(){
    cout << "Here is the list of games you currently have: " << endl;
    for(int i = 0; i < sizeof(gameArray); i ++){
        cout << i+1 << ":\t\t" << gameArray[i]->getGameName()->getText() << endl << endl; 
    }
}

void Business::printRentItemNames(){
    cout << "Here is the list of rent items you currently have: " << endl;
    for(int i = 0; i < sizeof(rentItemArray); i ++){
        cout << i+1 << ":\t\t" << rentItemArray[i]->getItemName()->getText() << endl << endl; 
    }
}

void Business::printGames(){
    cout << "Here is the list of all your games: " << endl;
     for(int i = 0; i < sizeof(gameArray); i ++){
        cout<< "****************************************" << endl;

        cout << "GAME" << i+1 << endl;
        gameArray[i]->printGameDetails();

    }
}

void Business::printRentItems(){
    cout << "Here is the list of all your rental items: " << endl;
     for(int i = 0; i < sizeof(rentItemArray); i ++){
        cout<< "****************************************" << endl;

        cout << "RENT ITEM" << i+1 << endl;
        rentItemArray[i]->printRentItemDetails();


    }
}

void Business::saveData(){
    string gameFile;
    string itemFile;

    cin.ignore();
    cout << "\n\nWhat do you want to name the file containing the games?\n";
    getline(cin, gameFile);
    ofstream outGameFile(gameFile); 

    for (int i = 0; i < numGames; i ++)
    {
        outGameFile
        << gameArray[i]->getGameName()->getText() << '\n'
        << gameArray[i]->getGameDescription()->getText() << '\n'
        << gameArray[i]->getGameCost() << '\n'
        << gameArray[i]->getNumPlayers() << '\n'
        << gameArray[i]->getMaxOccupancy() << '\n'
        << gameArray[i]->getGameDurationInHours() << '\n';
    }
    outGameFile << '\n';

    cout << "What do you want to name the file containing the rent items?\n";
    getline(cin, itemFile);
    ofstream outItemFile(itemFile);

    for (int i = 0; i < numRentItems; i++)
    {
        outItemFile
        << rentItemArray[i]->getItemName()->getText() << '\n'
        << rentItemArray[i]->getItemDescription()->getText() << '\n'
        << rentItemArray[i]->getItemCost() << '\n'
        << rentItemArray[i]->getHowManyInStock() << '\n'
        << rentItemArray[i]->getRentDurationInHours() << '\n';
    }
    outItemFile << '\n';

    cout << "\n\nAll data has been saved to " << gameFile << " and " << itemFile << "\n";
}
