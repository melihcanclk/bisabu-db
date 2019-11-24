#include "TestDictionary.h"
#include "TestControllers/Test.h"

#include "../src/Lexer.h"

#include <string>
#include <vector>

Test LexerTest()
{
    return Test([]() {
        // process input wont print anything
        // change tests accordingly

        std::vector<std::string> v;
        Lexer *l = Lexer::instance();

        bool success = true;

        if (l == NULL)
            return false;

        std::string longString(10000, 'a');
        v = l->tokenizeInput(longString, 'a');
        if (v.size() != 10000)
            success = false;

        v = l->tokenizeInput("Burakcan Asa", ' ');
        if (v.size() != 2)
            success = false;
        std::cout << "***************" << std::endl;

        v = l->tokenizeInput("Burakcan Asa", 'e');
        if (v.size() != 0)
        {
            // should enter error message
            success = false;
        }
        std::cout << "***************" << std::endl;

        // note by pion
        // this is multi-char constant
        // we might not need to handle this
        // right now it has overflow so don't test it
        //v = l->processInput("Öküz Sümük", 'ü');
        //problem with turkish characters
        std::cout << "***************" << std::endl;

        v = l->tokenizeInput("abbc", 'b');
        std::cout << v.size();
        if (v.size() != 2)
        {
            success = false;
            // problem in consecutive chars, it creates 3 substrings
        }

        //////////////////////////////////////
        // PROCESSINPUT FUNCTION TESTS DONE //
        //////////////////////////////////////

        return success;
    },
                "LexerTest");
}
