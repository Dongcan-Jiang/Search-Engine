#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

class TermScorer {
public:
    ifstream &in;
    int offset;
    TermScorer() {}
    int doc() {}
    int score() {}
    int next() {}
    int advance(int doc) {}
    int cost() {}
    ~TermScorer() {}

};

#endif // TERMSCORER_H_INCLUDED
