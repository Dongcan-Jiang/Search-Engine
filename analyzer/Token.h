#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;
class Token {
    string token;
    int position;
    string term;
public:
    Token(string token, int position, string term){
        this->token.assign(token);
        this->position = position;
        this->term.assign(term);
    }
    string toString(){
        string s = "(";
        s+=token;
        s+=",";
        s+=to_string(position);
        s+=",";
        s+=term;
        s+=")";
        return s;
    }
};

#endif // TOKEN_H_INCLUDED
