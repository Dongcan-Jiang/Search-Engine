#ifndef TERMQUERY_H_INCLUDED
#define TERMQUERY_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;
#include "Query.h"

class TermQuery: public Query{
public:
    TermQuery(const string &item){}
};


#endif // TERMQUERY_H_INCLUDED
