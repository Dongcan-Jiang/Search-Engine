#ifndef REQEXCLSCORER_H_INCLUDED
#define REQEXCLSCORER_H_INCLUDED

#include "Scorer.h"

class ReqExclScorer:public Scorer {
public:
    shared_ptr<Scorer> req;
    shared_ptr<Scorer> excl;

    ReqExclScorer(shared_ptr<Scorer>req, shared_ptr<Scorer>excl){
        this->req = req;
        this->excl = excl;
        scost = req->cost() + excl->cost();
    }

    int score() {return{};}

    int next() {
        if(excl->doc() == DOC_EXHAUSTED)
            return docID = req->next();
        do{
            docID = req->next();
        }while(excl->doc() == docID || excl->advance(docID) == docID);
        return docID;
    }

    int cost() {
        return scost;
    }

    ~ReqExclScorer() {}
};

#endif // REQEXCLSCORER_H_INCLUDED
