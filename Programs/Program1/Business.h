#ifndef BUSINESS_H
#define BUSINESS_H

#include "Game.h"
#include "RentItem.h"
#include "Text.h"


class Business {
    private:

        int numGames;
        int maxGames;
        int numRentItems;
        int maxRentItems;
        Game** gameArray;
        RentItem** rentItemArray;
        Text* businessName;

        void resizeRentItemArray();

        void resizeGameArray();



    public:
    Business(Text*, int, int);

    ~Business();

    int getNumGames();

    int getnumRentItems();

    void addGamesFromFile();

    void addItemsFromFile();

    void addGameToItem();

    void addGameToArray();

    void editGameInArray();

    void removeGameFromArray();

    void addRentItemToArray();

    void editRentItemInArray();

    void removeRentItemFromArray();

    void printGameNames();

    void printRentItemNames();

    void printGames();

    void printRentItems();

    void saveData();

};

#endif