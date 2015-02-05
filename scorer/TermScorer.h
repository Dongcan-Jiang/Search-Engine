#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

class TermScorer: public Scorer{
public:
    ifstream &in;
    int begin;
    int end;
    int offset;
    TermScorer(ifstream &fin, int begin, int end):in(fin) {
        this->begin = begin;
        this->end = end;
        offset = -1;
    }
    int doc() {
        if(offset < begin);
            return -1;
        if(offset >= end)
            return DOC_EXHAUSTED;
        int docID;
        in.seekg(offset);
        in.read((char*)&docID, sizeof(int));
        return docID;
    }
    int score() {}
    int next() {
        if(offset < begin)
            offset = begin;
        else{
            if(offset >= end)
                return DOC_EXHAUSTED;
            else {
                int tf;
                in.seekg(offset+sizeof(int)).read((char*)&tf, sizeof(int));
                offset = in.seekg(offset+sizeof(int)*(tf+2)).tellg();
            }
        }
        return 1;
    }
    int advance(int doc) {}
    int cost() {}
    ~TermScorer() {}

};

#endif // TERMSCORER_H_INCLUDED
