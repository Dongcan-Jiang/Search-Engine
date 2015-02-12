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
        scost = req->cost();
    }

    int score() {return{};}

    int next() {
        do{
            docID = req->next();
            if(docID == DOC_EXHAUSTED)
                break;
            if(excl->doc() > docID)
                break;
        }while(excl->doc() == docID || excl->advance(docID) == docID);
        return docID;
    }

};

#endif // REQEXCLSCORER_H_INCLUDED
