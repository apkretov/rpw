#include <utility>  // move
#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;

StrVec::StrVec(std::initializer_list<std::string> il) : StrVec() {
  for (const auto &s : il)
    push_back(s);
}

#ifdef ORIG
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
#else //MINE
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e) const {
#endif
  auto b2 = alloc.allocate(e - b);
  return {b2, std::uninitialized_copy(b, e, b2)};
}

void StrVec::reallocate() {
  auto new_cap_sz = size() ? 2 * size() : 1;
  auto new_first_elem = alloc.allocate(new_cap_sz);
  auto new_first_free = new_first_elem;
  auto old_first_elem = first_elem;
#ifdef ORIG
  for (size_type i = 0; i != size(); ++i)
	  alloc.construct(new_first_free++, std::move(*old_first_elem++));
#else //MINE
  for (size_type i = 0; i != size(); ++i)
	  construct_at(new_first_free++, std::move(*old_first_elem++));
#endif
  free();
  first_elem = new_first_elem;
  first_free = new_first_free;
  cap = first_elem + new_cap_sz;
}

void StrVec::free() {
  if (first_elem) {
#ifdef ORIG
	  for (auto p = first_free; p != first_elem; alloc.destroy(--p)) { }
#else //MINE
	  for (auto p = first_free; p != first_elem; --p)
		  destroy_at(p);

#endif
    alloc.deallocate(first_elem, cap - first_elem);
  }
}

StrVec::StrVec(const StrVec &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  first_elem = data.first;
  first_free = cap = data.second;
}

StrVec::~StrVec() {
  free();
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  first_elem = data.first;
  first_free = cap = data.second;
  return *this;
}


void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
#ifdef ORIG
  alloc.construct(first_free++, s);
#else //MINE
  construct_at(first_free++, s);
#endif
}

void StrVec::pop_back() {
  if (size() > 0)
#ifdef ORIG
    alloc.destroy(--first_free);
#else //MINE
    destroy_at(--first_free);
#endif
}

void StrVec::reserve(size_type n) {
  if (n > capacity()) {
    auto new_first_elem = alloc.allocate(n);
    auto new_first_free = new_first_elem;
    auto old_first_elem = first_elem;
    for (size_type i = 0; i != size(); ++i)
#ifdef ORIG
      alloc.construct(new_first_free++, std::move(*old_first_elem++));
#else //MINE
      construct_at(new_first_free++, std::move(*old_first_elem++));
#endif
    free();
    first_elem = new_first_elem;
    first_free = new_first_free;
    cap = first_elem + n;
  }
}

void StrVec::resize(size_type n, const std::string &s) {
  if (n > size()) {
    for (int i = n - size(); i != 0; --i)
      push_back(s);
  } else if (n < size()) {
    for (int i = size() - n; i != 0; --i)
      pop_back();
  }
}
