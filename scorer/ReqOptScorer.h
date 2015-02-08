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
    int next() {
        docID = req->next();
        docScore = req->score();
        if(opt->doc()==docID || opt->advance(docID)== docID)
            docScore += opt->score();
        return docID ;
    }

    int cost() {
        return scost;
    }

    ~ReqOptScorer() {}
};

#endif // REQOPTSCORER_H_INCLUDED
