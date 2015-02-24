#ifndef SKIPPER_H_INCLUDED
#define SKIPPER_H_INCLUDED

class Skipper {
public:
    int docID = -1;
    int poffset = -1;
    static const int DOC_EXHAUSTED = INT_MAX;
    ifstream &in;
    int begin;
    int soffset = -1;
    int num;
    int skip = 0;
    int preid = -1;
    int prepoffset = -1;


    Skipper(ifstream &fin, int begin):in(fin) {
        this->begin = begin;
        in.seekg(begin).read((char*)&num, sizeof(int));
    }

    int next() {
        if(num == 0)
            return docID = DOC_EXHAUSTED;
        preid = docID;
        prepoffset = poffset;
        if(soffset < begin) {
            soffset = begin;
            soffset += sizeof(int);
            in.seekg(soffset).read((char*)&docID, sizeof(int));
            in.seekg(soffset+sizeof(int)).read((char*)&poffset, sizeof(int));
            skip++;
        }
        else{
            if (skip == num)
                return docID = DOC_EXHAUSTED;
            else {
                soffset += sizeof(int)*2;
                in.seekg(soffset).read((char*)&docID, sizeof(int));
                in.seekg(soffset+sizeof(int)).read((char*)&poffset, sizeof(int));
                skip++;
            }
        }
        return docID;
    }


    int doc() {return docID;}
    int offset() {return poffset;}


};

#endif // SKIPPER_H_INCLUDED
