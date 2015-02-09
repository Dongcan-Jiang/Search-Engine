#ifndef QUERYPARSER_H_INCLUDED
#define QUERYPARSER_H_INCLUDED

#include <stack>
#include <string>
#include <vector>
#include "TermQuery.h"
#include "BooleanQuery.h"
class QueryParser {
public:
    string text;
    vector<string> tokens;
    stack<int> symbols;
    stack<shared_ptr<Query>> querys;

    QueryParser(const string& s) {
        text = s;
    }

    void toTokens() {
        size_t start = 0;
        for (size_t i = 0; i <= text.size(); i++) {
            if (i == text.size() || isspace(text[i]) || (i>=1 && (text[i-1]=='+'||text[i-1]=='-'||text[i-1]=='('||text[i-1]==')'))) {
                if(i != start) {
                    if(i>=2 && text[i-1]==')' && !isspace(text[i-2])) {
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

        /*test toTokens
        //for(auto s : tokens) {
            cout <<s<<"|";
        }
        */

    }

    shared_ptr<Query> getQuery() {
        toTokens();
        for(size_t i = 0 ; i < tokens.size(); i++) {
            if(tokens[i]=="+"||tokens[i]=="-") {
                symbols.push(tokens[i][0]);
                if(i < tokens.size()-1 && tokens[i+1] != "("){
                    i++;
                    querys.push(make_shared<TermQuery>(tokens[i]));
                }
                continue;
            }
            if(tokens[i]=="(") {
                if(tokens[i-1]!="+"&&tokens[i-1]!="-"){
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
                            cout<<"Something Wrong"<<endl;
                    }
                }
                symbols.pop();
                querys.push(q);
                continue;
            }
            symbols.push('s');
            querys.push(make_shared<TermQuery>(tokens[i]));
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
                    cout<<"Something Wrong"<<endl;
            }
        }
        return q;
    }

};


#endif // QUERYPARSER_H_INCLUDED
