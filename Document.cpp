#include "Document.h"
void Document::moveLine(char sign, int number)
{

    if (sign == '+')
    {
        if (this->line_number + number > this->lines.size() - 1)
            std::cout << "?" << std::endl;
        else
            this->line_number += number;
    }
    else
    {
        if (this->line_number - number < 0)
            std::cout << "?" << std::endl;
        else
            this->line_number -= number;
    }
}
void Document::insert(std::vector<std::string> temp)
{
    this->lines.insert(this->lines.begin() + this->line_number, temp.begin(), temp.end());
    this->line_number = this->lines.size() - 1;
}
void Document::appand(std::vector<std::string> temp)
{
   // std::cout << this->line_number << std::endl;
    this->lines.insert(this->lines.begin() + this->line_number + 1, temp.begin(), temp.end());
    this->line_number = this->lines.size() - 1;
}
void Document::printVec()
{
    for (auto &it : this->lines)
    {
        std::cout << it << std::endl;
    }
}
// the function recieves an input and needs to search the first apperance in the text
// from the number of line we r in and forward. if not found forward, we need to search backwards.
// we r using the function .find(givvenAWordToSearch) and it goes over our string , if we didnt
// find the word, we check if it reached std::string:nops
bool Document::search(std::string input)
{

    int itr;
    //we are searching from the line we r now ---> to the end of the text
    for (auto line = lines.begin() + line_number; line != lines.end(); ++line)
    {
        std::string str = *line;
        itr = str.find(input);
        if (itr != std::string::npos)
        {
            std::cout << *line << std::endl;
            return true;
        }
    }
    // if we reach here , it means in the previous for we couldnt find the
    // spesific word in our text

    // we search from the begining ---> to the line we r in right now
    for (auto line = lines.begin(); line != lines.begin() + line_number; ++line)
    {
        std::string str = *line;
        itr = str.find(input);
        if (itr != std::string::npos)
        {
            std::cout << *line << std::endl;
            return true;
        }
    }
    std::cout << "?" << std::endl;
    return false;
}
bool Document::searchAndReplace(std::string inputOld, std::string inputNew)
{
    std::string str = lines[line_number];
    //  std::cout << "note : "+lines[line_number] << std::endl;
    int itr = str.find(inputOld);
    //  std::cout << itr << std::endl;
    if (itr != std::string::npos)
    {
        lines[line_number].replace(itr, inputOld.length(), inputNew);
        //[itr]=inputNew;
        return true;
    }
    return false;
}
bool Document::wrtieToFile(std::string fileName)
{
    //std::cout << "im here" << std::endl;
    std::ofstream myfile(fileName);
    if (myfile.is_open())
    {
        for (std::string &line : lines)
        {
            myfile << line + "\n";
        }
        myfile.close();
        return true;
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
        return false;
    }
}
bool Document::readFromFile(std::string fileName)
{
    std::string line;
    std::ifstream myfile(fileName);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (!(line.compare("") == 0))
                lines.emplace_back(line);
        }
        myfile.close();
        return true;
    }
    else
        std::cout << "Unable to open file";
    return false;
}