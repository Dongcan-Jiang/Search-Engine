#include "test/test.h"

int main(int argc, char*argv[]) {
    /*
    StandardAnalyzer test;
    vector<Token> tokens;
    tokens = test.toTokens("I've got 100MB space, which 102,400KB.");
    for (size_t i = 0; i< tokens.size(); i++)
        cout << tokens[i].toString()<< "+";
    */
    assert(argc >= 5);
    fileTest(argv);
    //simpleTest();
    return 0;
}
