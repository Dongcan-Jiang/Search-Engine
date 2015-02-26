#ifndef TERMSCORER_H_INCLUDED
#define TERMSCORER_H_INCLUDED

#include "PositionAbleScorer.h"
#include "Skipper.h"

class TermScorer: public PositionAbleScorer {
public:
    istream &in;
    int begin;
    int end;
    int offset;
    Skipper skipper;
    TermScorer(istream &fin, int begin, int end, int df):in(fin), skipper(in, end) {
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
        #ifdef _DEBUG__GETPOSITION_
        assert(offsetCopy >= begin && offsetCopy < end);
        #endif
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
        #ifdef _DEBUG_ADVANCE_
        assert(docID < doc);
        #endif
        if (end == 0)
            return docID = DOC_EXHAUSTED;
        while(skipper.doc() <= doc) {
            skipper.next();
        }
        if (skipper.preid > docID) {
            docID = skipper.preid;
            offset = skipper.prepoffset;
        }
        if (docID == doc)
            return docID;
        else
            return Scorer::advance(doc);
    }

};

#endif // TERMSCORER_H_INCLUDED
