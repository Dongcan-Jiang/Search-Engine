#include "test/test.h"

int main(int argc, char*argv[]) {
    const string HELPS[] = {
        "./main -i INDEX_DIR -d DATA_DIR            : build index",
        "./main -s INDEX_DIR -b QUERY_STR [-f]      : boolean search (-f means FuzzyQuery)",
        "./main -s INDEX_DIR -p QUERY_STR [DIS] [-f]: phrase query within DIS (-f means FuzzyQuery)",
        "./main -h                                  : show help message"

    };
    if(argc >= 2 && string(argv[1]) == "-h"){
        for(auto &h : HELPS)
            cout << h << endl;
        return 0;
    }
    try{
        if(argc < 5)
            throw invalid_argument("Command Error.");
        fileTest(argc, argv);
    }catch(invalid_argument &i) {
        cout << "error: " <<i.what()<<endl;
        for(auto &h : HELPS)
            cout << h << endl;
    }
    //simpleTest();
    return 0;
}
