#ifndef INVERTEDINDEX_H_INCLUDED
#define INVERTEDINDEX_H_INCLUDED

#include <unordered_map>
#include <algorithm>
#include <cassert>
#include "Posting.h"
class InvertedIndex {
public:
    unordered_map<string, vector<Posting>> invertedIndex;
    void addDocTokens(int docID, const vector<Token> &tokens) {
        for (auto &token : tokens) {
            auto iter = invertedIndex.find(token.term);
            if(iter == invertedIndex.end()) {
                Posting posting (docID, {token.position});
                invertedIndex[token.term] = {posting};
            }else {
                vector<Posting> &postingList = iter->second;
                if(postingList.back().docID != docID) {
                    Posting posting (docID, {token.position});
                    postingList.push_back(posting);
                }else {
                    postingList.back().position.push_back(token.position);
                }
            }
        }
    }

    vector<string> mapOrder() {
        vector<string> order;
        for(auto &p : invertedIndex) {
            order.push_back(p.first);
        }
        sort(order.begin(), order.end());
        return order;
    }
    string toString() {
        string s;
        vector<string> order = mapOrder();
        for(auto &o : order) {
            s += o;
            s += ":";
            for (auto &posting : invertedIndex[o]) {
                s += posting.toString();
                s += " ";
            }
            s += "\n";
        }
        return s;
    }
    void save(const string & indexDir) {
        ofstream indexTable,indexTerm,indexPostinglist;
        indexTable.open(indexDir+"/"+"indextable", ios::binary);
        indexTerm.open(indexDir+"/"+"indexterm", ios::binary);
        indexPostinglist.open(indexDir+"/"+"indexpostinglist", ios::binary);
        assert(indexTable);
        assert(indexTerm);
        assert(indexPostinglist);
        vector<string> order = mapOrder();
        for (auto &o : order) {
            int t = indexTerm.tellp();
            indexTable.write((char*)&t, sizeof(t));
            indexTerm.write(o.c_str(), o.size()+1);

            t = indexPostinglist.tellp();
            indexTable.write((char*)&t, sizeof(t));
            for (auto &posting : invertedIndex[o]) {
                posting.writeTo(indexPostinglist);
            }


            int df = (int)invertedIndex[o].size();
            indexTable.write((char*)&df, sizeof(df));
        }
        indexPostinglist.close();
        indexTerm.close();
        indexTable.close();
    }
};



#endif // INVERTEDINDEX_H_INCLUDED
