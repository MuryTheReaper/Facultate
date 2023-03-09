#pragma once

template <typename ElementType> class IteratorVector;

template <typename ElementType> class vector_dinamic {
private:
  int capacity;
  int dim;
  ElementType *elems;

  void redim();

public:
  vector_dinamic() : capacity{1}, dim{0}, elems{new ElementType[capacity]} {}

  ~vector_dinamic() { delete[] elems; }

  vector_dinamic(const vector_dinamic &x);

  vector_dinamic &operator=(const vector_dinamic &x);

  vector_dinamic(vector_dinamic &&x);

  vector_dinamic &operator=(vector_dinamic &&x);

  ElementType &operator[](int index) const { return *(elems + index); }

  void push_back(const ElementType &x);

  int size() const noexcept { return dim; }

  void remove(const ElementType &x);

  friend class IteratorVector<ElementType>;

  IteratorVector<ElementType> begin() const;
  IteratorVector<ElementType> end() const;
};

template <typename ElementType> void vector_dinamic<ElementType>::redim() {
  if (dim < capacity)
    return;

  ElementType *eNou = (new ElementType[2 * capacity]);

  // copiem vechile valori in noua zona
  for (int i = 0; i < dim; i++) {
    *(eNou + i) = *(elems + i);
  }
  // dublam capacitatea
  capacity = 2 * capacity;

  // eliberam vechea zona
  delete[] elems;

  // vectorul indica spre noua zona
  elems = eNou;
}

template <typename ElementType>
vector_dinamic<ElementType>::vector_dinamic(const vector_dinamic &x)
    : capacity{x.capacity}, dim{x.dim}, elems{new ElementType[x.capacity]} {

  for (int i = 0; i < dim; i++) {
    *(elems + i) = *(x.elems + i);
  }
}

template <typename ElementType>
vector_dinamic<ElementType> &
vector_dinamic<ElementType>::operator=(const vector_dinamic<ElementType> &x) {

  if (this == &x) {
    return *this;
  }

  delete[] elems;
  elems = (new ElementType[x.capacity]);
  for (int i = 0; i < x.dim; i++) {
    *(elems + i) = *(x.elems + i);
  }
  dim = x.dim;
  capacity = x.capacity;

  return *this;
}

template <typename ElementType>
vector_dinamic<ElementType>::vector_dinamic(vector_dinamic &&x)
    : capacity{x.capacity}, dim{x.dim}, elems{x.elems} {

  x.elems = nullptr;
  x.dim = 0;
  x.capacity = 0;
}

template <typename ElementType>
vector_dinamic<ElementType> &
vector_dinamic<ElementType>::operator=(vector_dinamic<ElementType> &&x) {

  if (this == &x) {
    return *this;
  }

  delete[] elems;
  elems = x.elems;
  dim = x.dim;
  capacity = x.capacity;
  x.elems = nullptr;
  x.dim = 0;
  x.capacity = 0;
}

template <typename ElementType>
void vector_dinamic<ElementType>::push_back(const ElementType &x) {
  redim();
  *(elems + dim) = x;
  dim++;
}

template <typename ElementType>
void vector_dinamic<ElementType>::remove(const ElementType &x) {
  int poz = -1;
  for (int i = 0; i < dim; i++) {
    if (*(elems + i) == x) {
      poz = i;
      break;
    }
  }

  if (poz == -1)
    return;

  for (int i = poz; i < dim - 1; i++) {
    *(elems + i) = *(elems + i + 1);
  }

  dim--;
}

template <typename ElementType>
IteratorVector<ElementType> vector_dinamic<ElementType>::begin() const {

  return IteratorVector<ElementType>(*this);
}

template <typename ElementType>
IteratorVector<ElementType> vector_dinamic<ElementType>::end() const {

  return IteratorVector<ElementType>(*this, dim);
}

template <typename ElementType> class IteratorVector {
private:
  const vector_dinamic<ElementType> &x;
  int poz = 0;

public:
  IteratorVector(const vector_dinamic<ElementType> &x) noexcept;
  IteratorVector(const vector_dinamic<ElementType> &x, int poz) noexcept;
  bool valid() const;
  ElementType &element() const;
  void next();
  ElementType &operator*();
  IteratorVector &operator++();
  bool operator==(const IteratorVector &x) noexcept;
  bool operator!=(const IteratorVector &x) noexcept;
};

template <typename ElementType>
IteratorVector<ElementType>::IteratorVector(
    const vector_dinamic<ElementType> &x) noexcept
    : x{x} {}

template <typename ElementType>
IteratorVector<ElementType>::IteratorVector(
    const vector_dinamic<ElementType> &x, int poz) noexcept
    : x{x}, poz{poz} {}

template <typename ElementType>
bool IteratorVector<ElementType>::valid() const {
  return poz < x.dim;
}

template <typename ElementType>
ElementType &IteratorVector<ElementType>::element() const {
  return x.elems[poz];
}

template <typename ElementType> void IteratorVector<ElementType>::next() {
  poz++;
}

template <typename ElementType>
ElementType &IteratorVector<ElementType>::operator*() {
  return element();
}

template <typename ElementType>
IteratorVector<ElementType> &IteratorVector<ElementType>::operator++() {
  next();
  return *this;
}

template <typename ElementType>
bool IteratorVector<ElementType>::operator==(
    const IteratorVector<ElementType> &x) noexcept {

  return poz == x.poz;
}

template <typename ElementType>
bool IteratorVector<ElementType>::operator!=(
    const IteratorVector<ElementType> &x) noexcept {

  return !(*this == x);
}
