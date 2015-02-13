#ifndef POSITIONABLESCORER_H_INCLUDED
#define POSITIONABLESCORER_H_INCLUDED

#include "Scorer.h"

class PositionAbleScorer: public Scorer {
public:
    /*
    virtual int doc() = 0;

    virtual int score() = 0;

    virtual int next() = 0;

    virtual int cost() = 0;

    virtual int advance(int doc) = 0;
*/
    virtual vector<int> getPosition() = 0;

    virtual ~PositionAbleScorer() {}

};


#endif // POSITIONABLESCORER_H_INCLUDED
