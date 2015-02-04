#include "fs.h"

#include <cassert>

namespace fs {

using namespace std;

/** 声明为static以保证其他文件无法调用这个函数 **/
static mode_t getMode(const char *path) {
  struct stat st;
  int res = stat(path, &st);
  assert(res == 0); // 利用assert来保证调用正确
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

} // THE END OF NAMESPACE fs
