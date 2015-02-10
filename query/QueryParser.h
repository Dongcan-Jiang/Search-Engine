#ifndef QUERYPARSER_H_INCLUDED
#define QUERYPARSER_H_INCLUDED

#include <stack>
#include <string>
#include <vector>
#include "TermQuery.h"
#include "BooleanQuery.h"
class QueryParser {
public:
    vector<string> toTokens(const string& text) {
        vector<string> tokens;
        size_t start = 0;
        for (size_t i = 0; i <= text.size(); i++) {
            if (i == text.size() || isspace(text[i]) || (i>=1 && (text[i-1]=='+'||text[i-1]=='-'||text[i-1]=='('||text[i-1]==')'))) {
                if(i != start) {
                    if(i>=2 && text[i-1]==')' && !(isspace(text[i-2]) || text[i-2]=='+'||text[i-2]=='-'||text[i-2]=='('||text[i-2]==')')) {
                        string token = text.substr(start, i-1-start);
                        tokens.push_back(token);
                        start = i-1;
                    }
                    string token = text.substr(start, i-start);
                    tokens.push_back(token);
                }
                if(i == text.size() || isspace(text[i]))
                    start = i+1;
                else
                    start = i;
            }
        }
        return tokens;
    }

    shared_ptr<Query> getQuery(const string &text, shared_ptr<Analyzer> analyzer) {
        vector<string> tokens = toTokens(text);
        stack<int> symbols;
        stack<shared_ptr<Query>> querys;
        for(size_t i = 0 ; i < tokens.size(); i++) {
            if(tokens[i]=="+"||tokens[i]=="-") {
                symbols.push(tokens[i][0]);
                if(i+1 == tokens.size() || tokens[i+1] == "+" || tokens[i+1] == "-" ||tokens[i+1] == ")")
                    throw runtime_error("Parser error:Symbol error");
                if(tokens[i+1] != "("){
                    i++;
                    querys.push(make_shared<TermQuery>(analyzer->toTerm(tokens[i])));
                }
                continue;
            }
            if(tokens[i]=="(") {
                if(i==0 || (tokens[i-1]!="+" && tokens[i-1]!="-")){
                    symbols.push('s');
                }
                symbols.push(tokens[i][0]);
                continue;
            }
            if(tokens[i] == ")") {
                shared_ptr<BooleanQuery> q= make_shared<BooleanQuery>();
                while(symbols.top()!='('){
                    int symbol = symbols.top();
                    symbols.pop();
                    if(symbols.empty())
                        throw runtime_error("Parser error:Symbol error");
                    switch (symbol) {
                        case '+' :
                            q->add(BooleanQuery::MUST, querys.top());
                            querys.pop();
                            break;
                        case '-' :
                            q->add(BooleanQuery::MUST_NOT, querys.top());
                            querys.pop();
                            break;
                        case 's' :
                            q->add(BooleanQuery::SHOULD, querys.top());
                            querys.pop();
                            break;
                        default:
                            throw runtime_error("Parser error: Symbol error");
                    }
                }
                symbols.pop();
                querys.push(q);
                continue;
            }
            symbols.push('s');
            querys.push(make_shared<TermQuery>(analyzer->toTerm(tokens[i])));
        }
        shared_ptr<BooleanQuery> q= make_shared<BooleanQuery>();
        while(!symbols.empty()){
            int symbol = symbols.top();
            symbols.pop();
            switch (symbol) {
                case '+' :
                    q->add(BooleanQuery::MUST, querys.top());
                    querys.pop();
                    break;
                case '-' :
                    q->add(BooleanQuery::MUST_NOT, querys.top());
                    querys.pop();
                    break;
                case 's' :
                    q->add(BooleanQuery::SHOULD, querys.top());
                    querys.pop();
                    break;
                default:
                    throw runtime_error("Parser error: Symbol error");
            }
        }
        return q;
    }

};


#endif // QUERYPARSER_H_INCLUDED
