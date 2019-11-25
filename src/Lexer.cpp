#include "Lexer.h"
#include <sstream>
#include <iostream>

//#define TESTINTERNAL //uncomment to compile with test main.

Lexer *Lexer::instancePtr = nullptr;

Lexer *Lexer::instance()
{
    if (!instancePtr)
    {
        instancePtr = new Lexer;
    }

    return instancePtr;
}

std::vector<std::string> Lexer::tokenizeInput(const std::string &input, const char tokenChar)
{
    std::stringstream parser(input);
    std::string token;
    std::vector<std::string> tokens;

    while (getline(parser, token, tokenChar))
    {
        if (token != "")
            tokens.push_back(token);
    }

    return tokens;
}

std::vector<std::string> Lexer::tokenizeInput(const char *input, const char token)
{

    return tokenizeInput(convertCharPtr(input), token);
}

void Lexer::processInputHistory(const char token)
{

    for (unsigned i = 0; i < inputHistory.size(); ++i)
    {
        if (inputHistory[i].size() > 0)
        { // fix by pionix for empty inputs
            processInput(tokenizeInput(inputHistory[i], token));
        }
        // add in future : if returns false inform the user.
    }

    inputHistory.clear();
}

bool Lexer::pushInput(const std::string &input)
{
    inputHistory.push_back(input);
    return true;
}

bool Lexer::pushInput(const char *input)
{
    inputHistory.push_back(convertCharPtr(input));
    return true; // useless bool for now. maybe we put a limit for input count in future
}

void Lexer::resetHistory()
{
    commandStream.clear();
}

void Lexer::printHistory()
{

    if (commandStream.empty())
    {
        std::cout << "Command stream is empty\n";
        return;
    }

    for (unsigned i = 0; i < commandStream.size(); ++i)
    {
        std::cout << "Command " << i + 1 << ":";
        printCommand(commandStream[i]);
    }
}

void Lexer::printCommand(const Command c) const
{

    switch (c)
    {
    case Command::SEL:
        std::cout << "SELECT";
        break;

    case Command::INS:
        std::cout << "INSERT";
        break;

    case Command::UPD:
        std::cout << "UPDATE";
        break;

    case Command::DEL:
        std::cout << "DELETE";
        break;
    }
    std::cout << std::endl;
}

bool Lexer::addCommand(const Command c)
{
    commandStream.push_back(c);
    return true;
}

std::string Lexer::convertCharPtr(const char *input) const
{
    std::string temp = "";

    for (int i = 0; input[i] != 0; ++i)
    {
        temp += input[i];
    }

    return temp;
}

void Lexer::processCommands()
{
    for (unsigned i = 0; i < commandStream.size(); ++i)
    {
        printCommand(commandStream[i]);
        //commandObject.run()
    }
    commandStream.clear();
}

// NOTE: this function is really primitive version.
// I assumed that there might be more than one command in the given vector. I might be wrong.
// v1.1
bool Lexer::processInput(const std::vector<std::string> &v)
{

    for (auto itr = tempCommandList.begin(); itr != tempCommandList.end(); ++itr)
    {
        if (v[0] == itr->first)
        {
            commandStream.push_back(itr->second);
            return true;
        }
    }
    return false;
}

Lexer::Lexer()
{
    //used map for now, might change the structure or command names later.
    tempCommandList.insert(std::pair<std::string, Command>("insert", Command::INS));
    tempCommandList.insert(std::pair<std::string, Command>("delete", Command::DEL));
    tempCommandList.insert(std::pair<std::string, Command>("select", Command::SEL));
    tempCommandList.insert(std::pair<std::string, Command>("update", Command::UPD));
}

#ifdef TESTINTERNAL

int main()
{

    Lexer::instance()->processInput(Lexer::instance()->tokenizeInput("insert abdullah update kusgulu insert", ' '));
    Lexer::instance()->printHistory();
    Lexer::instance()->processCommands();
}

#endif