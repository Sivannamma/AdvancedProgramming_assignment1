#include <stdlib.h>
#include "string"
#include <vector>
#include <iostream>
#include <algorithm> // functions like std::find
#include <fstream> // for reading and writing to files
class Document
{
public:
    std::string file;
    int line_number;
    std::vector <std::string> lines;
    void moveLine(char sign,int number);
    void insert(std::vector<std::string> temp);
    void appand(std::vector<std::string> temp);
    void printVec();
    bool search(std::string input);
    bool searchAndReplace(std::string inputOld,std::string inputNew);
    bool wrtieToFile(std::string fileName);
    bool readFromFile(std::string fileName);
};