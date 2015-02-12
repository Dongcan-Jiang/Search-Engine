#ifndef STANDARDANALYZER_H_INCLUDED
#define STANDARDANALYZER_H_INCLUDED
#include "../util/util.h"

class StandardAnalyzer : public Analyzer   {
public:
    vector<Token> toTokens(const string &text) {
        vector<Token> tokens;
        size_t start = 0;
        size_t position = 0;
        for (size_t i = 0; i <= text.size(); i++) {
            if (i == text.size() || !isalnum(text[i]) || (i>=1 && ((isdigit(text[i])&&isalpha(text[i-1]))||(isdigit(text[i-1])&&isalpha(text[i]))))) {
                if (i != start) {
                    string token = text.substr(start, i-start);
                    string term = toTerm(token);
                    Token t(token,position,term);
                    position++;
                    tokens.push_back(t);
                }
                if(i == text.size() || !isalnum(text[i]))
                    start = i+1;
                else
                    start = i;
            }
        }
        return tokens;
    }

    string toTerm(const string &str) {
        string term = str;
        for (size_t i = 0; i< str.size(); i++)
            term[i] = tolower(str[i]);
        term = util::stem(term);
        return term;
    }

};

#endif // STANDARDANALYZER_H_INCLUDED
