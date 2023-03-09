#ifndef DEVICE_H
#define DEVICE_H
#include <iostream>

using std::string;

class device {

private:
  string tip;
  string model;
  int an;
  string culoare;
  float pret;

public:
  device(const string &tip, const string &model, const int &an,
         const string &culoare, const float &pret)
      : tip{tip}, model{model}, an{an}, culoare{culoare}, pret{pret} {};

  device(const device &x)
      : tip{x.tip}, model{x.model}, an{x.an}, culoare{x.culoare},
        pret{x.pret} {};

  ~device() = default;

  device &operator=(const device &) = default;

  device(device &&) = default;

  device &operator=(device &&) = default;

  const string get_tip() const noexcept { return tip; };

  const string get_model() const noexcept { return model; };

  const int get_an() const noexcept { return an; };

  const string get_culoare() const noexcept { return culoare; };

  const float get_pret() const noexcept { return pret; };
};

#endif // DEVICE_H
