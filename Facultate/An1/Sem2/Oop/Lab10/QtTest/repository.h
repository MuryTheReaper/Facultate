#pragma once
#include "disciplina.h"
#include "my_vector.h"
#include <vector> // NOLINT
//#include <ostream>

class repository {

private:
  std::vector<disciplina> list;

  bool exist(const disciplina &x) const;

public:
  repository() = default;

  repository(const repository &x) = delete;

  ~repository() = default;

  repository &operator=(const repository &) = delete;

  repository(repository &&) = default;

  repository &operator=(repository &&) = delete;

  void add(const disciplina &x);

  void remove(const disciplina &x);

  void modify(const disciplina &x);

  const disciplina &find(const disciplina &x) const;

  const std::vector<disciplina> &get_all() const noexcept;
};

class repoException {

private:
  std::string msg;

public:
  repoException(std::string m) : msg{m} {}
  std::string getMsg() const { return msg; }
  friend std::ostream &operator<<(std::ostream &out, const repoException &ex);
};
