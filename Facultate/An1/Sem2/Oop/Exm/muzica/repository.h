#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "melodie.h"
#include <vector>

using std::vector;

class repository {
private:
  vector<melodie> list;

  string file;

  void loadFromFile();
  void storeToFile();

public:
  repository(const string &file) : file{file} { loadFromFile(); };

  repository(const repository &x) = delete;

  ~repository() = default;

  repository &operator=(const repository &) = delete;

  repository(repository &&) = default;

  repository &operator=(repository &&) = delete;

  const vector<melodie> &getAll() const noexcept;

  void modify(const melodie &x);

  const melodie &find(const melodie &x) const;
};

#endif // REPOSITORY_H
