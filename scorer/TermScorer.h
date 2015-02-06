#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

class TermScorer: public Scorer{
public:
    ifstream &in;
    int begin;
    int end;
    int offset;
    TermScorer(ifstream &fin, int begin, int end, int df):in(fin) {
        this->begin = begin;
        this->end = end;
        offset = -1;
        scost = df;
    }

    int score() {return{};}
    int next() {
        if(offset < begin) {
            offset = begin;
            in.seekg(offset).read((char*)&docID, sizeof(int));
        }
        else{
            int tf;
            in.seekg(offset+sizeof(int)).read((char*)&tf, sizeof(int));
            offset += sizeof(int)*(tf+2);
            if(offset >= end)
                return docID = DOC_EXHAUSTED;
            else {
                in.seekg(offset).read((char*)&docID, sizeof(int));
            }
        }
        return docID;
    }

    int cost() {
        return scost;
    }
    ~TermScorer() {}

};

#endif // TERMSCORER_H_INCLUDED
