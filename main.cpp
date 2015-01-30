#include "test/test.h"

int main() {

    WhitespaceAnalyzer test;
    vector<Token> tokens;
    tokens = test.toTokens("a b c ");
    for (size_t i = 0; i< tokens.size(); i++)
        cout << tokens[i].toString()<< "+";

  //  simpleTest();
    return 0;
}
