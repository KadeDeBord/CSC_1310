#include <iostream>
#include <string>

using namespace std;

class Pet{
    private:
        string name;
        string type;
        string url;
        float age;
        bool adopted;
    public:
        //default constructor
        Pet(){
           name = "Test";
           type = "default";
           url = "thisisatest.com"; 
           age = 0;
           adopted = false;
        }
        //overloaded
        Pet(string N, string T, string U, float A, bool adopted = false){
            name = N;
            type = T;
            url = U;
            age = A;
            this->adopted = adopted;
        }
        //Accessor functions
        string getName(){
            return name;
        }
        string getType(){
            return type;
        }
        string getUrl(){
            return url;
        }
        float getAge(){
            return age;
        }
        bool getAdoptionStatus(){
            return adopted;
        }

        //mutator functions
        void changeName(string newname){
            name = newname;
            
        }
        void changeType(string newtype){
            type = newtype;
            
        }
        void changeUrl(string newurl){
            url = newurl;
            
        }
        void changeAge(float newage){
            age = newage;
            
        }
        void  changeAdoptionStatus(bool newstatus){
            adopted = newstatus;
            
        }

        //print the pet
        void printPet(){
            cout << "\tNAME: " << name << endl;
            cout << "\tTYPE: " << type << endl;
            cout << "\tURL: " << url << endl;
            cout << "\tAGE(In years): " << age << endl;
            if (adopted == true){
                cout << "\tADOPTED: " << "Yes" << endl;
            }else if(adopted == false){
                cout << "\tADOPTED: " << "No" << endl;
            }
        }
};