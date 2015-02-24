#ifndef REQOPTSCORER_H_INCLUDED
#define REQOPTSCORER_H_INCLUDED

#include "Scorer.h"

class ReqOptScorer:public Scorer {
public:
    shared_ptr<Scorer> req;
    shared_ptr<Scorer> opt;
    ReqOptScorer(shared_ptr<Scorer> req, shared_ptr<Scorer> opt){
        this->req = req;
        this->opt = opt;
        scost = req->cost();
    }

    int score() {
        return docScore;
    }

    int findOpt() {
        if (docID == DOC_EXHAUSTED)
            return docID;
        docScore = req->score();
        if (opt->doc() <= docID) {
            if (opt->doc() == docID || opt->advance(docID) == docID)
                docScore += opt->score();
        }
        return docID ;
    }

    int next() {
        docID = req->next();
        return findOpt();
    }

    int advance(int doc) {
        #ifdef _DEBUG_ADVANCE_
        assert(docID < doc);
        #endif
        docID = req->advance(doc);
        return findOpt();
    }
};

#endif // REQOPTSCORER_H_INCLUDED
