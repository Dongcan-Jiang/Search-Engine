#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

#include "PositionAbleScorer.h"
#include "Skipper.h"
class TermScorer: public PositionAbleScorer {
public:
    ifstream &in;
    int begin;
    int end;
    int offset;
    Skipper skipper;
    int id = -1;
    int poffset = -1;
    TermScorer(ifstream &fin, int begin, int end, int df):in(fin), skipper(in, end) {
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

    int advance(int doc) {
        while(skipper.doc() < doc && skipper.next() <= doc) {
            id = skipper.doc();
            poffset = skipper.offset();
        }
        if (id > docID) {
            docID = id;
            offset = poffset;
        }
        if (docID == doc)
            return docID;
        else
            return Scorer::advance(doc);
    }

};

#endif // TERMSCORER_H_INCLUDED
