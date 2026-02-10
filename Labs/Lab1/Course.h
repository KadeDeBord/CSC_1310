#include <string>
using namespace std;

class course{
    public:
        string name;
        string location; 
        int num_sections;
        int num_credit_hrs;
        string* sections;
};

course* createCourse(string name, string location, int credithrs, int sectionNum);

void destroyCourse(course* myCourse);

void printCourse(course* myCourse);