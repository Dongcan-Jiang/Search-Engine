#include "test/test.h"


int main(int argc, char*argv[]) {
    /*
    StandardAnalyzer test;
    vector<Token> tokens;
    tokens = test.toTokens("I've got 100MB space, which 102,400KB.");
    for (size_t i = 0; i< tokens.size(); i++)
        cout << tokens[i].toString()<< "+";
    */
    const string HELPS[] = {
        "./main -i INDEX_DIR -d DATA_DIR  : build index",
        "./main -s INDEX_DIR -b QUERY_STR : boolean search",
        "./main -h                        : show help message"
    };
    if(argc >= 2 && string(argv[1]) == "-h"){
        for(auto &h : HELPS)
            cout << h << endl;
        return 0;
    }
    try{
        if(argc < 5)
            throw invalid_argument("Command Error.");
        fileTest(argv);
    }catch(invalid_argument &i) {
        cout << "error: " <<i.what()<<endl;
        for(auto &h : HELPS)
            cout << h << endl;
    }
    //simpleTest();
    return 0;
}
