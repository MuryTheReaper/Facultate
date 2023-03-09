#ifndef OBSERVER_H
#define OBSERVER_H

#include <algorithm>
#include <vector>

class observer {

public:
  virtual void update() = 0;

  virtual ~observer() = default;

  observer() = default;

  observer(const observer &x) = delete;

  observer &operator=(const observer &) = delete;

  observer(observer &&) = default;

  observer &operator=(observer &&) = delete;
};

class observable {

private:
  std::vector<observer *> observers;

public:
  void addObserver(observer *obs) { observers.push_back(obs); }

  void removeObserver(observer *obs) {
    observers.erase(std::remove(observers.begin(), observers.end(), obs),
                    observers.end());
  }

  void notify() {
    for (auto obs : observers) {
      obs->update();
    }
  }
};

#endif // OBSERVER_H
