/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include <map>
#include "vector.h"
using namespace std;

static map<char,char> letter2Digit = {
    {'A','0'},{'E','0'},{'I','0'},{'O','0'},{'U','0'},{'H','0'}, {'W','0'}, {'Y','0'},
    {'B','1'},{'F','1'},{'P','1'},{'V','1'},
    {'C','2'},{'G','2'},{'J','2'},{'K','2'},{'Q','2'},{'S','2'}, {'X','2'}, {'Z','2'},
    {'D','3'},{'T','3'},
    {'L','4'},
    {'M','5'},{'N','5'},
    {'R','6'}
};


string removeNonLetters(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

string encodeLetter2Digit(string s) {
    string res = "";
    for (char c : s) {
        res += letter2Digit[toUpperCase(c)];
    }
    return res;
}

//Coalesce adjacent duplicate digits
string coalesceDigits(string s) {
   string res;
   for (int i = 0; i < s.length(); ++i) {
       while(i+1 < s.length() && s[i] == s[i+1]){
           i++;
       }
       res += s[i];
   }
   return res;
}

string removeAllZero(string s){
    string res;
    for (char c:  s) {
        if(c != '0'){
            res += c;
        }
    }
    return res;
}

string paddingOrTruncate(string s){
   while(s.length() < 4){
        s += "0";
   }
   return s.substr(0, 4);
}




string soundex(string s) {
    s = removeNonLetters(s);
    char first = toUpperCase(s[0]);
    s = encodeLetter2Digit(s);
    s = coalesceDigits(s);
    s[0] = first;
    s = removeAllZero(s);
    s = paddingOrTruncate(s);

    return s;
}


/*
 * input a file that contains a set of surnames,
 * and you will be required to input some surnames,
 * program will respond the matched surnames of the file
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    //为数据库里的名字编码
    map<string,Vector<string>> code2databaseNames;
    for(auto start = databaseNames.begin(); start != databaseNames.end(); start++){
        string code = soundex(*start);
        if (code2databaseNames.count(code) != 1){
            code2databaseNames[code] = Vector<string>();
        }
        code2databaseNames[code].add(*start);
    }

    //遍历map，排序
    for(auto &t : code2databaseNames){
          t.second.sort();
    }

   while(1){
       string surname = getLine("Enter a surname (RETURN to quit) :");
       if (surname == "") {
           break;
       }
       string code = soundex(surname);
       cout << "Soundex code is " << code << endl;
       cout << "Match from database: " <<  code2databaseNames[code] << endl;
   }
   cout << "All done." << endl;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here
STUDENT_TEST("expose the bug in the given implementation of removeNonLetters"){
    EXPECT_EQUAL(removeNonLetters("2Ken"),"Ken");
}

STUDENT_TEST("Hammerman is coded to H565"){
    EXPECT_EQUAL(soundex("Hammerman"),"H565");
    EXPECT_EQUAL(soundex("Haner-McAllister"),"H565");
    EXPECT_EQUAL(soundex("Hanrahan"),"H565");
    EXPECT_EQUAL(soundex("Honarmand"),"H565");
}


