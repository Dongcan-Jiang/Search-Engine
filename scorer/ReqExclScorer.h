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
            if(excl->doc() < docID) {
                excl->advance(docID);
            }
        }while(excl->doc() == docID);
        return docID;
    }

    int advance(int doc) {
        #ifdef _DEBUG_ADVANCE_
        assert(docID < doc);
        #endif
        req->advance(doc);
        if (req->doc() == DOC_EXHAUSTED)
            return docID = DOC_EXHAUSTED;
        int reqdoc = req->doc();
        if (excl->doc() < reqdoc)
            excl->advance(reqdoc);
        if (excl->doc() != reqdoc)
            return docID = reqdoc;
        else
            return next();
    }

};

#endif // REQEXCLSCORER_H_INCLUDED
