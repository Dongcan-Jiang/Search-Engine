#include "test/test.h"

int main(int argc, char*argv[]) {
    const string HELPS[] = {
        "./main -i INDEX_DIR -d DATA_DIR        : build index",
        "./main -s INDEX_DIR -b QUERY_STR       : boolean search",
        "./main -s INDEX_DIR -b QUERY_STR [DIS] : phrase query within DIS",
        "./main -h                              : show help message"

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

/*
bool fetchTermID(int &lowerbound, int &upperbound) {
        int low = 0;
        int high = 4;
        int mid;
        string s;
        string fuzzyTerm = "ke";
        vector<string> getTerm = {"absolute", "keep", "kei", "key", "zoo"};
        int fsize = fuzzyTerm.size();
        while (high >= low) {
            mid = (low+high)/2;
            s = getTerm[mid];
            if (s.substr(0, fsize) > fuzzyTerm)
                high = mid - 1;
            else {
                if (s.substr(0, fsize) < fuzzyTerm)
                    low = mid + 1;
                else {
                    lowerbound = mid-1;
                    upperbound = mid+1;
                        while(lowerbound != -1 && getTerm[lowerbound].substr(0,fsize) == fuzzyTerm){
                            lowerbound--;
                        }
                    lowerbound++;
                        while(upperbound != 5 && getTerm[upperbound].substr(0,fsize) == fuzzyTerm) {
                            upperbound++;
                        }

                    return true;
                }
            }
        }
        return false;
    }


int main() {
    int lowerbound = -1;
    int upperbound = -1;
    fetchTermID(lowerbound, upperbound);
    cout<<lowerbound<<" "<<upperbound;
}
*/
