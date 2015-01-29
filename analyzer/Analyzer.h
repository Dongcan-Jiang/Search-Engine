#ifndef ANALYZER_H_INCLUDED
#define ANALYZER_H_INCLUDED
#include <iostream>
using namespace std;

class Analyzer {
public:
    virtual string toTerm(const string &str) = 0;
    virtual vector<Token> toTokens(const string &text) = 0;
    virtual ~Analyzer() {}
};

#endif // ANALYZER_H_INCLUDED
