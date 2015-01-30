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

    vector<Token> toTokens(const string &text) {
        vector<Token> tokens;
        int start = 0;
        int position = 0;
        for (int i = 0; i < text.size(); i++) {
            if (isspace(text[i])) {
                if (i!=start) {
                    string token = text.substr(start, i-start);
                    string term = toTerm(token);
                    Token t(token,position,term);
                    position++;
                    tokens.push_back(t);
                }
                start = i+1;
            }
        }
        return tokens;
    }

    string toTerm(const string &str) {
        string term = str;
        for (int i = 0; i< str.size(); i++)
            term[i] = tolower(str[i]);
        return term;
    }


};

#endif // WHITESPACEANALYZER_H_INCLUDED
