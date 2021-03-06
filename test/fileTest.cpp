#include "test.h"

string readText(const string &path) {
    ifstream fin(path, ios::binary);
    int length = fin.seekg(0,ios::end).tellg();
    char s[length+1];
    fin.seekg(0,ios::beg);
    fin.read(s,length);
    s[length] = '\0';
    string text(s);
    fin.close();
    return text;
}

void readFromFile(IndexWriter &iw, const string &path) {
    Document doc;
    string text = readText(path);
    shared_ptr<TextField> textField = make_shared<TextField>(text);
    int t = path.rfind('/')+1;
    shared_ptr<StoredField> titleField = make_shared<StoredField>("title", path.substr(t,path.size()-t));
    shared_ptr<StoredField> pathField = make_shared<StoredField>("path", path);
    /*
    int f = text.find(' ');
    shared_ptr<StoredField> firstWordField = make_shared<StoredField>("firstword",text.substr(0,f));
    */
    doc.setTextField(textField);
    doc.addStoredField(titleField);
    doc.addStoredField(pathField);
    //doc.addStoredField(firstWordField);
    iw.addDocument(doc);
}

void fileTestIndex(const string & INDEX_DIR, const string & FILE_PATH) {
    IndexWriter iw(INDEX_DIR, make_shared<StandardAnalyzer>());
    iw.setStoredField(vector<string>{"title", "path"});

    util::traverse(FILE_PATH, [&iw](const string & path){
        readFromFile(iw, path);
    });

    iw.close();
}

void fileTestSearchitem(const string & INDEX_DIR, shared_ptr<Query> query) {
    IndexSearcher is(INDEX_DIR);
    vector<ScoreDoc> docs = is.search(query);

    for (auto &sd : docs) {
        Document doc = is.doc(sd.doc);
        cout << sd.doc << " : " << doc.getStoredField("title")->stringValue() <<endl;
    }

    is.close();
}

void fileTest(int argc, char*argv[]) {
    if(string(argv[1])=="-i") {
        if(string(argv[3])!="-d")
            throw invalid_argument("Command Error.");
        const string INDEX_DIR = argv[2];
        const string FILE_PATH = argv[4];
        fileTestIndex(INDEX_DIR,FILE_PATH);
    }else if(string(argv[1])=="-s") {
        const string INDEX_DIR = argv[2];
        string s = argv[4];
        QueryParser parser;
        shared_ptr<Query> query;

        //test
        //if (string(argv[3])=="-t") {
          //  query = make_shared<FuzzyQuery>(s);
        //}
        //test

        if(string(argv[3])=="-b") {
            if(argc > 5 && string(argv[5])=="-f")
                parser.fuzzy = true;
            query = parser.getBooleanQuery(s, make_shared<StandardAnalyzer>());
        } else if(string(argv[3])=="-p"){
            if (argc == 5)
                query = parser.getPhraseQuery(s,make_shared<StandardAnalyzer>());
            if(argc == 6) {
                if (string(argv[5])!="-f") {
                    query = parser.getPhraseQuery(s,make_shared<StandardAnalyzer>());
                    dynamic_pointer_cast<PhraseQuery>(query)->setDis(atoi(argv[5]));
                } else {
                    parser.fuzzy = true;
                    query = parser.getPhraseQuery(s,make_shared<StandardAnalyzer>());
                }
            }
            if(argc == 7) {
                if (string(argv[6]) != "-f")
                    throw invalid_argument("Command Error.");
                else {
                    parser.fuzzy = true;
                    query = parser.getPhraseQuery(s,make_shared<StandardAnalyzer>());
                    dynamic_pointer_cast<PhraseQuery>(query)->setDis(atoi(argv[5]));
                }
            }
        } else {
            throw invalid_argument("Command Error.");
        }

        cout<<"Query: "<<query->toString()<<endl;

        fileTestSearchitem(INDEX_DIR, query);
    }else {
        throw invalid_argument("Command Error.");
    }
}
