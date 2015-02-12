#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

#include "Scorer.h"

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
            if(offset >= end)
                return docID = DOC_EXHAUSTED;
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

    vector<int> getPosition() {
        vector<int> pos;
        int offsetCopy = offset;
        assert(offsetCopy >= begin && offsetCopy < end);
        int tf;
        in.seekg(offsetCopy+sizeof(int)).read((char*)&tf, sizeof(int));
        offsetCopy += sizeof(int)*2;
        for(int i = 0; i < tf; i++){
            int position;
            in.seekg(offsetCopy).read((char*)&position, sizeof(int));
            pos.push_back(position);
            offsetCopy += sizeof(int);
        }
        return pos;
    }

};

#endif // TERMSCORER_H_INCLUDED
