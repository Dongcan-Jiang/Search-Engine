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



} // THE END OF NAMESPACE util
