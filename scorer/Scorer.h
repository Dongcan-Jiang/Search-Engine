#ifndef SCORER_H_INCLUDED
#define SCORER_H_INCLUDED

class Scorer {
public:
    virtual int doc() = 0;
    virtual int score() = 0;
    virtual int next() = 0;
    virtual int advance(int doc) = 0;
    virtual ~Scorer() {}

};

#endif // SCORER_H_INCLUDED
