#ifndef WHITESPACEANALYZER_H_INCLUDED
#define WHITESPACEANALYZER_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
using namespace std;
#include "Analyzer.h"
#include "Token.h"

class WhitespaceAnalyzer : public Analyzer   {
public:
    vector<Token> toTokens(const string &text) {}
    string toTerm(const string &str) {};
};

#endif // WHITESPACEANALYZER_H_INCLUDED
