#ifndef INVERTEDINDEX_H_INCLUDED
#define INVERTEDINDEX_H_INCLUDED

#include <unordered_map>
#include <algorithm>
class InvertedIndex {
public:
    unordered_map<string, vector<Posting>> invertedindex;
    vector<string> order;
    void addDocTokens(int docID, vector<Token> tokens);
    void mapOrder() {
        for(auto &p : invertedindex) {
            order.push_back(p.first);
        }
        sort(order.begin(), order.end());
    }
    string toString();
    void save() {}
};

void InvertedIndex::addDocTokens(int docID, vector<Token> tokens) {
    for (auto &token : tokens) {
        auto iter = invertedindex.find(token.term);
        if(iter == invertedindex.end()) {
            Posting posting (docID, vector<int>{token.position});
            vector<Posting> postingList = {posting};
            invertedindex.insert(pair<string,vector<Posting>>(token.term, postingList));
        }
        else {
            vector<Posting> postingList = invertedindex[token.term];
            if(postingList.back().docID != docID) {
                Posting posting (docID, vector<int>{token.position});
                postingList.push_back(posting);
            }
            else {
                postingList.back().position.push_back(token.position);
            }
        }
    }
}

string InvertedIndex::toString() {
    string s;
    for(auto &o : order) {
        s += o;
        s += ":";
        for (auto &posting : invertedindex[o])
            s += posting.toString();
        s += "\n";
    }
    return s;
}
#endif // INVERTEDINDEX_H_INCLUDED
