#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

class Token {
    string token;
    int position;
    string term;
};

class WhitespaceAnalyzer {
    vector<Token> toTokens(string str) {}
};

class TextField {
public:
    string text;
    TextField(string s) {}
};

class StoredField {
public:
    string fieldname;
    string stored;
    StoredField(string name, string s) {}
};

class Document {
public:
    shared_ptr<TextField> textField;
    map<string, string> storedfield;
    void setTextField(shared_ptr<TextField> textf) {textField = textf;}
    void addStoredField(shared_ptr<StoredField> storedf) {}
    string getStoredField(string fieldname) {} //传入的参数“title”是个匿名的string对象，那么这里为什么不用考虑左右值的问题？
};

class Posting {
    int docid;
    vector<int> position;
};

class IndexWriter {
    shared_ptr<WhitespaceAnalyzer> analyzer;
public:
    IndexWriter(string index_dir, shared_ptr<WhitespaceAnalyzer> whitespaceanalyzer){}
    map<string, vector<Posting>> invertedindex;
    void setStoredField(vector<string> &&fieldname){} //如果不加&&（左值？）和调用时的匿名对象参数（右值）会有冲突吗？
    void addDocument(Document doc) {}
    void close(){}
};

//继承，虚基类之类的很久没写忘记了，待会儿上网看看资料
class Query {
};
class TermQuery: public Query{
public:
    TermQuery(string item){}
};


class ScoreDoc {
public:
    int doc;
};

class IndexSearch {
public:
    IndexSearch(string index_dir){}
    vector<ScoreDoc> search(shared_ptr<Query> query){}
    Document doc(int docid){}
    void close(){}
};


class IndexandSearch {
public:
    /* 为什么原来的这个写法是错误的
    string[][] dataset = {
          {"doc1", "a b c d e f g"},
          {"doc2", "x a e c d"},
          {"doc3", "l x y t"},
          {"doc4", "k b r d w"},
          {"doc5", "u t w x a"},
          {"doc6", "m t a"}
    };
    */
    string index_dir="index.txt";
    vector<vector<string>> dataset = {
         {"doc1", "a b c d e f g"},
         {"doc2", "x a e c d"},
         {"doc3", "l x y t"},
         {"doc4", "k b r d w"},
         {"doc5", "u t w x a"},
         {"doc6", "m t a"}
    };

    void index() {
        IndexWriter iw(index_dir, make_shared<WhitespaceAnalyzer>());
        iw.setStoredField(vector<string>{"title"}); //这样写会有左右值的问题吗？
        for (auto data : dataset) {
            Document doc;
            shared_ptr<TextField> textField = make_shared<TextField>(data[1]);//is textField a name or a pointer?
            shared_ptr<StoredField> titleField = make_shared<StoredField>("title", data[0]);
            //TextField和StoredField也只是对string作了一层封装并没有其他的处理，
            //为什么要多这一层而不是直接定义doc.setTextField(string)和 doc.addStoredField(string, string)?
            //在doc对象内部分别把她们赋给doc.textfield和doc.storedfield??
            doc.setTextField(textField);
            doc.addStoredField(titleField);
            iw.addDocument(doc);
        }
        iw.close();
    }

    void searchitem(string item) {
        IndexSearch is(index_dir);

        shared_ptr<Query> query = make_shared<TermQuery>(item);
        vector<ScoreDoc> docs = is.search(query); //search好像是c++中的关键字，不会有影响吗？
        //需要重载ScoreDoc类的 = 才能把返回值正常全部复制到vector<ScoreDoc>？？
        //如果改用vector<SocreDoc>* docs 指针能避免上述问题？
        for (auto &sd : docs) {  //sd为什么要用引用？直接auto sd也可以？
            Document doc = is.doc(sd.doc);
            //需要重载Document类的 = 才能把类里面所有的变量正常复制赋值？

            //cout << doc.getStoredField("title").stringValue() <<endl;
            cout << doc.getStoredField("title")<<endl; //为什么不能把.stringValue()简化去掉。

        }
        is.close();
    }

};


int main()
{
    IndexandSearch test;
    test.index();
    test.searchitem("a");
    return 0;
}
