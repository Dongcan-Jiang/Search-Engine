#ifndef QUERY_H_INCLUDED
#define QUERY_H_INCLUDED
#include <iostream>
using namespace std;
//�̳У������,��̬��֪ʶ

#include "../scorer/Scorer.h"
#include "../document/IndexSearcher.h"

class IndexSearcher;

class Query {
public:
    virtual shared_ptr<Scorer> getScorer(IndexSearcher &is) = 0;
    virtual ~Query() {}

};

#endif // QUERY_H_INCLUDED
