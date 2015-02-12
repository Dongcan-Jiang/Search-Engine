#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace util {


using namespace std;

string joinPath(const string& path, const string &filename);
bool isDir(const char *path);
bool isFile(const char *path);
string stem(const string & s);
template <typename Func>
void traverse(const string &path,const Func &func) {
    DIR *dir = opendir(path.c_str());
    struct dirent *ent;
    while ((ent = readdir(dir))) {
        string filename = ent->d_name;
        if (filename.find(".") == 0) continue;
        string fullPath = joinPath(path, filename);
        if (isFile(fullPath.c_str())) {
            func(fullPath);
        } else if (isDir(fullPath.c_str())) {
            traverse(fullPath, func);
        }
    }
    closedir(dir);
}

}

#endif // UTIL_H_INCLUDED

