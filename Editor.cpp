#include "Editor.h"
Editor::Editor(std::string file)
{
    this->document.file = file;
    // now we will call a function that will read from file
    this->document.readFromFile(file);
    //setting lines
    this->document.line_number = this->document.lines.size() - 1;
}
Editor::Editor()
{
    //no name of file was inserted, than we initialize it to empty.
    this->document.file = "";
    this->document.line_number = 0;
}
void Editor::loop()
{
    std::string input = "";
    // while (std::cin >> input)
    while (std::getline(std::cin, input))
    {
        if (input.compare("q") == 0)
            break;
        else if (input[0] == 13)
            std::cout << "?" << std::endl;

        if (checkPlusOrMinus(input))
        {
            int number = extractNumber(input);
            //we call the moving lines function
            //std::cout <<number << std::endl;
            this->document.moveLine(input[0], number); // this function is not done yet
            //std::cout << this->document.line_number << std::endl;
        }
        else if (isANumber(input))
        {
            int lineNum = stoi(input);
            if (this->document.lines.size() >= lineNum)
            {
                if (lineNum == 0)
                {
                    std::cout << "?" << std::endl;
                }
                else
                {
                    std::cout << lineNum << std::endl;
                    this->document.line_number = lineNum - 1;
                    std::cout << this->document.lines[lineNum - 1] << std::endl;
                    // std::cout << " " << std::endl;
                }
            }
            else
                std::cout << "?" << std::endl;
        }
        // for example /sivan/
        else if (checkSlash(input, 0, input.size() - 1, 1))
        {
            std::string searchInput = input.substr(1, input.size() - 2);
            this->document.search(searchInput);
        }

        else
        {
            // switch case on the first parameter of the input
            switch (input[0])
            {
            case 'w': // writting to file
                      // checking if >=2 in order to check that the second
                      // cell contains spcace and afterwards contains the name of the file
                //std::cout << "entered the switch of writing " << std::endl;
                if (input.length() >= 3 && input[1] == 32)
                {
                    std::string fileName = input.substr(2);
                    this->document.wrtieToFile(fileName);
                }
                else
                {
                    std::cout << "?" << std::endl;
                }
                break;
            case 'i': // insert
                insert(1);
                this->document.printVec();
                break;
            case 'a': //appand
                insert(2);
                this->document.printVec();
                break;
            case '$': //moves to the end of the vector
                this->document.line_number = this->document.lines.size() - 1;
                break;
            case 'd': //removes current line
                this->document.lines.erase(this->document.lines.begin() + this->document.line_number);
                break;
            case 'c': //replace a line with one or more lines
                insert(3);
                break;
            case 'j':
                concatRows();
                break;
            case 's':
                // checking for slashes
                if (checkSlash(input, 1, input.size() - 1, 2))
                {
                    std::string inputToSearch;
                    std::string inputToReplace;
                    int count = 0;
                    for (char &c : input)
                    {
                        if (c == '/')
                            count++;
                        else if (count == 1)
                        {
                            inputToSearch += c;
                        }
                        else if (count == 2)
                        {
                            inputToReplace += c;
                        }
                    }
                    this->document.searchAndReplace(inputToSearch, inputToReplace);
                }
                break;
            default:
                std::cout << "?" << std::endl;
                break;
            }
        }
    }
}
// function to check if the first char is + or -, then we know it refers to moving lines.
bool Editor::checkPlusOrMinus(std::string input)
{
    if (input[0] == ('+') || input[0] == ('-'))
        return true;
    return false;
}
/*
this function is using sstream include, there is a struct that when we build
it with a certain string it can convert it to int.
therefore we put the string (not with the +/- , thats why we use substring) and we will
get the number
*/
int Editor::extractNumber(std::string input)
{
    int number = 0;
    std::string numFromString = input.substr(1);
    std::stringstream extracted(numFromString);
    extracted >> number;
    return number;
}
// function to insert from the user a string until '.' is giver
void Editor::insert(int flag)
{
    std::vector<std::string> temp;
    std::string input;
    // the function getline helps us inset a full sentence with spaces and doesnt split
    // it like cin
    while (std::getline(std::cin, input))
    {
        if (input.length() == 1 && input[0] == '.')
            break;
        //inserting each time a new line into the vector
        if (!(input.compare("") == 0))
            temp.emplace_back(input);
    }
    //inserting to the vector what we might of overide in the insertion before
    // we insert from what we saved before in the temp vector
    if (flag == 1)
        this->document.insert(temp);
    else if (flag == 2)
        this->document.appand(temp);
    /*
        here in flag==3 we replace the current line we r in with the input from
        the user.
        after the user insert more lines
         we call appand to insert after the line
    */

    else if (flag == 3)
    {
        this->document.lines[this->document.line_number] = temp[0];
        temp.erase(temp.begin());
        this->document.appand(temp);
    }
}
bool Editor::isANumber(std::string input)
{
    int length = input.length();
    for (size_t i = 0; i < length; i++)
    {
        if (input[i] < '0' || input[i] > '9')
            return false;
    }
    return true;
}
bool Editor::checkSlash(std::string input, int index1, int index2, int flag)
{
    // if to begin with we dont have an ending slash or begin one, we can return false
    if (input[index1] != '/' || input[index2] != '/')
        return false;
    // now in case 2' we need in advanced to check for a middle slash '/'
    if (flag == 2)
    {
        int count = 0;
        for (char &c : input)
        {
            if (c == '/')
                count++;
        }
        return count == 3 ? true : false;
    }
    return true;
}
void Editor::concatRows()
{
    int currentLine = this->document.line_number;
    if (currentLine + 1 < this->document.lines.size())
    {
        std::string str = this->document.lines[currentLine + 1];
        this->document.lines[currentLine] += " " + str;
        this->document.lines.erase(this->document.lines.begin() + currentLine + 1);
    }
}