#ifndef STANDARDANALYZER_H_INCLUDED
#define STANDARDANALYZER_H_INCLUDED

class StandardAnalyzer : public Analyzer   {
public:
    vector<Token> toTokens(const string &text) {
        vector<Token> tokens;
        size_t start = 0;
        size_t position = 0;
        for (size_t i = 0; i <= text.size(); i++) {
            if (i == text.size() || isspace(text[i]) || ispunct(text[i])) {
                if (i != start) {
                    string token = text.substr(start, i-start);
                    string term = toTerm(token);
                    Token t(token,position,term);
                    position++;
                    tokens.push_back(t);
                }
                start = i+1;
            }
            if (i<text.size()-1 && ((isdigit(text[i])&&isalpha(text[i+1]))||(isdigit(text[i+1])&&isalpha(text[i])))) {
                string token = text.substr(start, i+1-start);
                string term = toTerm(token);
                Token t(token,position,term);
                position++;
                tokens.push_back(t);
                start = i+1;
            }
        }
        return tokens;
    }

    string toTerm(const string &str) {
        string term = str;
        for (size_t i = 0; i< str.size(); i++)
            term[i] = tolower(str[i]);
        return term;
    }


};

#endif // STANDARDANALYZER_H_INCLUDED
