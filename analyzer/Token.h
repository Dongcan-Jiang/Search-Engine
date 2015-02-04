#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

class Token {

public:
    string token;
    int position;
    string term;

    Token(const string &token, int position, const string &term){
        this->token = token;
        this->position = position;
        this->term = term ;
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
