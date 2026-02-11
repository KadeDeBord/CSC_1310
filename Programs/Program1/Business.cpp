#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> 
#include "Business.h"

using namespace std;

/*************************************************************
 *  CONSTRUCTOR: Business()
 *  PURPOSE: Initializes a Business object with a name and
 *           maximum capacity for games and rental items.
 *  PARAMETERS: Text* sN - business name pointer
 *              int mG - maximum number of games
 *              int mRI - maximum number of rental items
 *************************************************************/
Business::Business(Text* sN, int mG, int mRI){
    businessName = sN;
    maxGames = mG;
    maxRentItems = mRI;
    numGames = 0;
    numRentItems = 0;
    
    rentItemArray = new RentItem*[maxRentItems];
    
    gameArray = new Game*[maxGames];
}

/*************************************************************
 *  DESTRUCTOR: ~Business()
 *  PURPOSE: Releases all dynamically allocated memory for
 *           games, rental items, and their arrays.
 *************************************************************/
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

/*************************************************************
 *  FUNCTION: resizeGameArray()
 *  PURPOSE: Doubles the capacity of the game array when it
 *           becomes full. Copies existing games to new array.
 *************************************************************/
void Business::resizeGameArray(){
    cout << "\n\nRESIZING GAME ARRAY...from " << maxGames << " to a new size of " << (maxGames * 2) << endl << endl;
            
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

/*************************************************************
 *  FUNCTION: resizeRentItemArray()
 *  PURPOSE: Doubles the capacity of the rental item array
 *           when it becomes full. Copies existing items to
 *           new array.
 *************************************************************/
void Business::resizeRentItemArray(){
     cout << "\n\nRESIZING rentItem ARRAY...from " << maxRentItems << " to a new size of " << (maxRentItems * 2) << endl << endl;
            
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

/*************************************************************
 *  FUNCTION: getNumGames()
 *  PURPOSE: Returns the current number of games in the array
 *************************************************************/
int Business::getNumGames(){
    return numGames;
}

/*************************************************************
 *  FUNCTION: getnumRentItems()
 *  PURPOSE: Returns the current number of rental items in
 *           the array
 *************************************************************/
int Business::getnumRentItems(){
    return numRentItems;
}

/*************************************************************
 *  FUNCTION: addGamesFromFile()
 *  PURPOSE: Reads games from a file and adds them to the
 *           game array. Each game record consists of:
 *           name, description, cost, numPlayers, 
 *           maxOccupancy, and duration.
 *************************************************************/
void Business::addGamesFromFile(){
    string filename;
    string gameName;
    string gameDescription;
    float gameCost;
    int numPlayers;
    int maxOccupancy;
    float gameDurationInHours;

    cin.ignore();
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
        cout << gameName << " was added to the array" << endl;
        numGames++;
    }
    
    inputFile.close();
    cout << "\nAll games from " << filename << " have been added" << endl;
}

/*************************************************************
 *  FUNCTION: addItemsFromFile()
 *  PURPOSE: Reads rental items from a file and adds them to
 *           the rental item array. Each item record consists
 *           of: name, description, cost, howManyInStock,
 *           and rentDurationInHours.
 *************************************************************/
void Business::addItemsFromFile(){
    string filename;
    string rentItemName;
    string rentItemDescription;
    float rentItemCost;
    int howManyInStock;
    float rentItemDurationInHours;

    cin.ignore();
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
        cout << rentItemName << " was added to the array" << endl;
        numRentItems++;
    }

    inputFile.close();
    cout << "\nAll items from " << filename << " have been added" << endl;
}

/*************************************************************
 *  FUNCTION: addGameToItem()
 *  PURPOSE: Associates each rental item with a game. Allows
 *           user to select which game each rental item is
 *           used with, or skip if no association needed.
 *************************************************************/
void Business::addGameToItem(){
    int chosenGame = 0;
    
    printGameNames();

    for(int i = 0; i < numRentItems; i++){
        cout <<"Which game would you like the " << rentItemArray[i]->getItemName()->getText() << " to be associated with?" <<endl;
        cout<< "Enter the number of the game from the list above, or enter -1 to skip this item." << endl;

        while(!(cin >> chosenGame) || (chosenGame != -1 && (chosenGame < 1 || chosenGame > numGames))){
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
        }
        cin.ignore();
        cout << endl;

        if(chosenGame != -1){
            rentItemArray[i]->setGameAssociation(gameArray[(chosenGame-1)]);
        }else{
            cout << "Skipping this item " << endl;
        }
        
    }
}

/*************************************************************
 *  FUNCTION: addGameToArray()
 *  PURPOSE: Prompts user to enter game details (name,
 *           description, cost, players, occupancy, duration)
 *           and adds a new game to the game array.
 *************************************************************/
void Business::addGameToArray(){
    string gameName;
    string gameDescription;
    float gameCost;
    int numPlayers;	
    int maxOccupancy; 
    float gameDurationInHours; 

    cin.ignore();
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
    Game* newGame = new Game(new Text(gameName.c_str()), new Text(gameDescription.c_str()), gameCost, numPlayers, maxOccupancy, gameDurationInHours);
    gameArray[numGames] = newGame;
    numGames += 1;
    
}

/*************************************************************
 *  FUNCTION: editGameInArray()
 *  PURPOSE: Allows user to select a game from the list and
 *           edit its details (name, description, cost, etc).
 *************************************************************/
void Business::editGameInArray(){
    int editNum;

    printGameNames();

    cout <<"Which game would you like to edit?" << endl;
    cout << "Enter a number from the list of games above" << endl;
    cin >> editNum;
    cin.ignore();

    gameArray[editNum-1]->editGameDetails();


}

/*************************************************************
 *  FUNCTION: removeGameFromArray()
 *  PURPOSE: Allows user to select a game to remove. Removes
 *           the game, updates any rental items associated
 *           with it, and shifts remaining games down in array.
 *************************************************************/
void Business::removeGameFromArray(){
    int delGame;

    printGameNames();

    cout<<"Which game would you like to remove? " << endl;
    cout << "Enter a number from the list of games above." << endl;
    cin >> delGame;
    cin.ignore();

     for(int i = 0; i < numRentItems; i++){
        if(rentItemArray[i]->getGameAssociation() == gameArray[delGame-1]){
            rentItemArray[i]->setGameAssociation(nullptr);
        }
     }

    delete gameArray[delGame-1];
    
    // Shift games down to fill the gap
    for(int i = delGame-1; i < numGames-1; i++){
        gameArray[i] = gameArray[i+1];
    }
    numGames--;
}

/*************************************************************
 *  FUNCTION: addRentItemToArray()
 *  PURPOSE: Prompts user to enter rental item details
 *           (name, description, cost, stock, duration) and
 *           associates it with a selected game.
 *************************************************************/
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
    RentItem* newItem = new RentItem(gameArray[gameAssociation-1], new Text(itemName.c_str()), new Text(itemDescription.c_str()), itemCost, howManyInStock, rentDurationInHours);
    rentItemArray[numRentItems] = newItem;
    numRentItems += 1;
}

/*************************************************************
 *  FUNCTION: editRentItemInArray()
 *  PURPOSE: Allows user to select a rental item from the
 *           list and edit its details (name, description,
 *           cost, stock quantity, rental duration).
 *************************************************************/
void Business::editRentItemInArray(){
    int editNum;

    printRentItemNames();

    cout <<"Which rental item would you like to edit?" << endl;
    cout << "Enter a number from the list of items above" << endl;
    cin >> editNum;
    cin.ignore();

    rentItemArray[editNum-1]->editRentItemDetails();
}

/*************************************************************
 *  FUNCTION: removeRentItemFromArray()
 *  PURPOSE: Allows user to select a rental item to remove
 *           from the rental item array.
 *************************************************************/
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

/*************************************************************
 *  FUNCTION: printGameNames()
 *  PURPOSE: Displays a numbered list of all games currently
 *           in the game array.
 *************************************************************/
void Business::printGameNames(){
    cout << "Here is the list of games you currently have: " << endl;
    for(int i = 0; i < numGames; i ++){
        cout << i+1 << ":\t" << gameArray[i]->getGameName()->getText() << endl; 
    }
}

/*************************************************************
 *  FUNCTION: printRentItemNames()
 *  PURPOSE: Displays a numbered list of all rental items
 *           currently in the rental item array.
 *************************************************************/
void Business::printRentItemNames(){
    cout << "Here is the list of rent items you currently have: " << endl;
    for(int i = 0; i < numRentItems; i ++){
        cout << i+1 << ":\t" << rentItemArray[i]->getItemName()->getText() << endl; 
    }
}

/*************************************************************
 *  FUNCTION: printGames()
 *  PURPOSE: Displays detailed information for all games in
 *           the game array including name, description,
 *           cost, players, occupancy, and duration.
 *************************************************************/
void Business::printGames(){
    cout << "Here is the list of all your games: " << endl;
     for(int i = 0; i < numGames; i ++){
        cout<< "****************************************" << endl;

        cout << "GAME" << i+1 << endl;
        gameArray[i]->printGameDetails();

    }
}

/*************************************************************
 *  FUNCTION: printRentItems()
 *  PURPOSE: Displays detailed information for all rental
 *           items in the array including name, description,
 *           cost, stock quantity, and rental duration.
 *************************************************************/
void Business::printRentItems(){
    cout << "Here is the list of all your rental items: " << endl;
     for(int i = 0; i < numRentItems; i ++){
        cout<< "****************************************" << endl;

        cout << "RENT ITEM" << i+1 << endl;
        rentItemArray[i]->printRentItemDetails();


    }
}

/*************************************************************
 *  FUNCTION: saveData()
 *  PURPOSE: Prompts user for filenames and saves all games
 *           and rental items to separate output files in a
 *           format that can be read back with addGamesFromFile()
 *           and addItemsFromFile().
 *************************************************************/
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
