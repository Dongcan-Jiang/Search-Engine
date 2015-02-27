#include "util.h"

#include <cassert>


int stem(char * p, int i, int j);

namespace util {

using namespace std;

static mode_t getMode(const char *path) {
    struct stat st;
    int res = stat(path, &st);
    assert(res == 0);
    return st.st_mode;
}

bool isDir(const char *path) {
    return S_ISDIR(getMode(path));
}

bool isFile(const char *path) {
    return S_ISREG(getMode(path));
}

string joinPath(const string& path, const string &filename) {
    string res = path;
    res += "/";
    res += filename;
    return res;
}



string stem(const string & s){
    if(s.size() == 0)
        return s;
    char str[s.size()+1];
    strcpy(str,s.c_str());
    int k = ::stem(str,0,s.size()-1);
    str[k+1]='\0';
    return str;
}

int editDistance(const string &s1, const string &s2) {
    int l1 = s1.size()+1;
    int l2 = s2.size()+1;
    int dis[l1][l2];
    for (int i = 0; i < l1; i++) {
        dis[i][0] = i;
    }
    for (int j = 0; j < l2; j++) {
        dis[0][j] = j;
    }
    for (int i = 1 ; i< l1; i++) {
        for (int j = 1;  j< l2; j++) {
            int k = 1;
            if (s1[i-1] == s1[j-1])
                k = 0;
            dis[i][j] = min({dis[i-1][j]+1, dis[i][j-1]+1, dis[i-1][j-1]+k});
        }
    }
    return dis[l1-1][l2-1];
}


} // THE END OF NAMESPACE util
