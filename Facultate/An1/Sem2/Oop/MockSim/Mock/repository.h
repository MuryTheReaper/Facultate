#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "device.h"
#include <vector>

using std::vector;

class repository {

private:
  vector<device> list;

  string file;

  void loadFromFile();

public:
  repository(const string &file) : file{file} { loadFromFile(); };

  repository(const repository &x) = delete;

  ~repository() = default;

  repository &operator=(const repository &) = delete;

  repository(repository &&) = default;

  repository &operator=(repository &&) = delete;

  const vector<device> &get_all() const noexcept;
};

#endif // REPOSITORY_H
