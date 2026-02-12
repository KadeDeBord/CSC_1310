/******************************************************************************
	                       CSC 1310 Lab 2 Fall 2025
	Filename: 		Driver.cpp
	Author: 		April Crockett and Kade DeBord
	Date Created: 	1/21/2026
	Date Modified:	2/5/2026
	Purpose: 		This program allows people to adopt pets. However, the
	purpose of this assignment is to refresh student's memories on
	the topics in the last 1/4th of the 1300 semester (listed below)
	and to practice	with Makefiles:
	     -Arrays / Pointers / Dynamic Memory Allocation
	     -Structures
	     -Classes / Objects
		 
	To Compile with the Makefile, type make in the Command Prompt /Terminal
******************************************************************************/
#include <iostream>
#include "Pet.h"
using namespace std;

//***create Adopter structure - it should contain the person's name as one member and a Pet as the other member
//When the Pet object is created in the structure, the default constructor is called
struct Adopter{
    string name;
    Pet adoptedPet;
};

int main() {
	/*
		Below is an array of 10 Pet objects with a full initialization list.
		Notice that for each object, the overloaded constructor is called.
	*/
    Pet petArray[10] = {    Pet("KIRA", "Cat: Domestic Medium Hair", 
                                "https://www.petfinder.com/cat/kira-77746445/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/", .5),
                            Pet("LUCY", "Dog: German Shorthaired Pointer Mix", 
                                "https://www.petfinder.com/dog/lucy-77794903/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/",1),
                            Pet("TURNER","Dog: Labrador Retriever Mix",
                                "https://www.petfinder.com/dog/turner-77794900/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/",.5),
                            Pet("BONUS","Dog: Siberian Husky & Labrador Retriever Mix",
                                "https://www.petfinder.com/dog/bonus-77746525/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/",.5),
                            Pet("WREN (Odie Mae)","Dog: Dachshund Mix",
                                "https://www.petfinder.com/dog/wren-odie-mae-73674766/tn/cookeville/tennessee-dachshund-rescue-tn890/",10),
                            Pet("JERRY","Dog: Pitt Bull Terrier Mix",
                                "https://www.petfinder.com/dog/jerry-77687976/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/",3),
                            Pet("HONEY BUN","Cat: Domestic Short Hair",
                                "https://www.petfinder.com/cat/honey-bun-77814080/tn/cookeville/cookeville-putnam-county-animal-shelter-tn132/",.5),
                            Pet("SHADOW","Rabbit: Bunny Rabit Mix",
                                "https://www.petfinder.com/rabbit/shadow-76190934/tn/cookeville/heaven-on-earth-rabbit-rescue-tn1009/",1),
                            Pet("GANDALF","Rat: small",
                                "https://www.petfinder.com/small-furry/gandalf-77490265/ky/bowling-green/bowling-green-warren-county-humane-society-ky18/",1),
                            Pet("SIR OINKS A-LOT","Pig",
                                "https://www.petfinder.com/barnyard/sir-oinks-a-lot-adoptable-77684658/ga/chickamauga/walker-county-animal-shelter-ga964/",2)
    };

    int numAdopters;
    int adoptedPetNum;

    cout << "\nHow many people are coming in to adopt a pet today?\n";
    cout << "ENTER 1-10: ";
    cin >> numAdopters;
    cin.ignore();
	
	//***dynamically allocate an array (named adopterArray) of type "Adopter" that is of size numAdopters. 
    Adopter* adopterArray = new Adopter[numAdopters];
	
	
	//Get User Input
    for(int i=0; i<numAdopters; i++)
    {
        cout << "\n**********ADOPTER " << i+1 << endl;
        cout << "Name: ";
		//***read in the name - it should be able to contain spaces
        getline(cin, adopterArray[i].name);
        
		
        cout << "\nWhat type of pet would " << adopterArray[i].name << " like to adopt?\n";
        
		//***use this for loop to print each of the Pet's types in the Pet array but only if they are not yet adopted.
        int lastDisplayed = 0;
        for(int j=0; j<10; j++)
        {
            if(petArray[j].getAdoptionStatus() == false){
                cout << j+1 << ") " << petArray[j].getType() << endl;
                lastDisplayed = j+1; // store the displayed (1-based) number
            }
        }
        if(lastDisplayed == 0){
            cout << "No pets available to adopt.\n";
            break;
        }
        cout << "ENTER 1 through " << lastDisplayed << ": ";
        cin >> adoptedPetNum;
        cin.ignore();
        // convert user choice (1-based) to array index (0-based)
        int chosenIndex = adoptedPetNum - 1;
        // set this Pet's "adopted" attribute to true and assign to adopter
        if(chosenIndex >= 0 && chosenIndex < 10){
            petArray[chosenIndex].changeAdoptionStatus(true);
            adopterArray[i].adoptedPet = petArray[chosenIndex];
        } else {
            cout << "Invalid selection. No pet assigned.\n";
        }
		
		

    }

	//Print Results
    cout << "\n\n**********Here are all the adopters with their pets:\n";
	//do NOT change the for loop below!
    for(int i=0; i<numAdopters; i++)
    {
        cout << "Adopter:" << adopterArray[i].name << endl;
        adopterArray[i].adoptedPet.printPet();
    }
	
	//***release the dynamically allocated array!
	delete [] adopterArray;

    return 0;
}