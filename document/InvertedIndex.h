#ifndef INVERTEDINDEX_H_INCLUDED
#define INVERTEDINDEX_H_INCLUDED

#include <unordered_map>
#include <algorithm>

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
    void save() {}
};



#endif // INVERTEDINDEX_H_INCLUDED
