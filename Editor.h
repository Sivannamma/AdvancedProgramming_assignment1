#include <stdlib.h>
#include<iostream>
#include "string"
#include "Document.h"
#include<sstream>
class Editor
{
public:
    Document document;
    // outline constructors
    Editor(std::string file);
    Editor();
    // outline functions
    void loop();
    void ed();
    void ed_text();
    bool checkPlusOrMinus(std::string input);
    int extractNumber(std::string input);
    void insert(int flag);
    bool isANumber(std::string input);
    // this function is in order to check if the first index of the
    // input is / and the ladt index of the input is /
    bool checkSlash(std::string input,int index1, int index2,int flag); 
    void concatRows();
};