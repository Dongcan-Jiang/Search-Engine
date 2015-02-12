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
    char str[s.size()];
    for(size_t i = 0; i < s.size(); i++)
        str[i]=s[i];
    int k = ::stem(str,0,s.size()-1);
    str[k+1]='\0';
    string st(str);
    return st;
}



} // THE END OF NAMESPACE util
