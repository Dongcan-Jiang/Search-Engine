#ifndef STOREDIFSTREAM_H_INCLUDED
#define STOREDIFSTREAM_H_INCLUDED
#include "Document.h"
class StoredIfstream {
public:
    ifstream sfieldTable,sfieldText;
    vector<string> fieldName;
    static const int ROW_LENGTH = sizeof(int);
    int DOC_NUM;
    StoredIfstream(const string &indexDir) {
        sfieldTable.open(indexDir+"/"+"storedfieldtable", ios::binary);
        assert(sfieldTable);
        sfieldText.open(indexDir+"/"+"storedfieldtext", ios::binary);
        assert(sfieldText);

        ifstream sfieldNamelist;
        sfieldNamelist.open(indexDir+"/"+"storedfieldnamelist", ios::binary);
        assert(sfieldNamelist);
        string name;
        while (getline(sfieldNamelist, name, '\0')) {
            fieldName.push_back(name);
        }
        sfieldNamelist.close();

        DOC_NUM = sfieldTable.seekg(0,ios::end).tellg()/ROW_LENGTH;
    }
    int getDocBegin(int docID) {
        int address;
        sfieldTable.seekg(ROW_LENGTH*docID).read((char*)&address,sizeof(address));
        return address;
    }
    Document doc(int docID) {
        Document d;
        sfieldText.seekg(getDocBegin(docID));
        string stored;
        for (auto& n : fieldName) {
            getline(sfieldText, stored, '\0');
            d.addStoredField(make_shared<StoredField>(n,stored));

        }
        return d;
    }
    string toString(int docID) {
        return doc(docID).toString();
    }
    string toString() {
        string s;
        for(int i = 0; i < DOC_NUM; i++)
            s += toString(i);
        return s;
    }
    void close() {
        sfieldTable.close();
        sfieldText.close();
    }
};

#endif // STOREDIFSTREAM_H_INCLUDED
