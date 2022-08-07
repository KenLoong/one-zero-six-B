#include <iostream>
#include "console.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
#include "perfect.h"
#include "soundex.h"
using namespace std;


//引入了#include "console.h"，这是standford的标准库,不知道为何我引入成功了
//难道在安装qt的过程中我安装了？？？
int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

//    findPerfects(40000);
    // Comment out the above line and uncomment below line 
    // to switch between running perfect.cpp and soundex.cpp
    soundexSearch("res/surnames.txt");

    cout << endl << "main() completed." << endl;
    return 0;
}


// Do not remove or edit below this line. It is here to to confirm that your code
// conforms to the expected function prototypes needed for grading
void confirmFunctionPrototypes() {
    long n = 0;
    bool b;
    string s;

    n = divisorSum(n);
    b = isPerfect(n);
    findPerfects(n);

    n = smarterSum(n);
    b = isPerfectSmarter(n);
    findPerfectsSmarter(n);

    n = findNthPerfectEuclid(n);

    s = removeNonLetters(s);
    s = soundex(s);
    soundexSearch(s);
}
