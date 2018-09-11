#pragma once

//todo: doxygen

#include <vector>
#include <algorithm>
#include <map>

template <
  class Key, 
  class T,
  class Allocator = std::allocator<std::pair<Key, T>>
>
class flat_map {
public:
  using key_type               = Key;
  using mapped_type            = T;
  using value_type             = std::pair<Key, T>;
  using vector_type            = std::vector<value_type, Allocator>;
  using allocator_type         = typename vector_type::allocator_type;
  using size_type              = typename vector_type::size_type;
  using difference_type        = typename vector_type::difference_type;
  using reference              = typename vector_type::reference;
  using const_reference        = typename vector_type::const_reference;
  using pointer                = typename vector_type::pointer;
  using const_pointer          = typename vector_type::const_pointer;
  using iterator               = typename vector_type::iterator;
  using const_iterator         = typename vector_type::const_iterator;
  using reverse_iterator       = typename vector_type::reverse_iterator;
  using const_reverse_iterator = typename vector_type::const_reverse_iterator;

  flat_map() = default;

  ~flat_map() = default;

  flat_map(const vector_type& r) noexcept
    : cache_(r)
  { }

  flat_map(std::initializer_list<value_type> l) noexcept
    : cache_(l)
  { }

  template <class InputIterator>
  flat_map(InputIterator first, InputIterator last) {
    cache_.insert(cache_.end(), first, last);
  }

  iterator begin() noexcept {
    return cache_.begin();
  }

  const_iterator begin() const noexcept {
    return cache_.begin();
  }

  const_iterator cbegin() const noexcept {
    return cache_.cbegin();
  }

  reverse_iterator rbegin() noexcept {
    return cache_.rbegin();
  }

  const_reverse_iterator rbegin() const noexcept {
    return cache_.rbegin();
  }

  iterator end() noexcept {
    return cache_.end();
  }

  const_iterator end() const noexcept {
    return cache_.end();
  }

  const_iterator cend() const noexcept {
    return cache_.cend();
  }

  reverse_iterator rend() noexcept {
    return cache_.rend();
  }

  const_reverse_iterator rend() const noexcept {
    return cache_.rend();
  }

  bool empty() const noexcept {
    return cache_.empty();
  }

  size_type size() const noexcept {
    return cache_.size();
  }

  void reserve(size_type count) {
    cache_.reserve(count);
  }

  void shrink_to_fit() {
    cache_.shrink_to_fit();
  }

  vector_type& container() noexcept {
    return cache_;
  }

  const vector_type& container() const noexcept {
    return cache_;
  }

  void clear() noexcept {
    cache_.clear();
  }

  void swap(flat_map& other) {
    cache_.swap( other.cache_ );
  }

  std::pair<iterator, bool> insert(value_type x) {
    for(auto it = cache_.begin(); it != cache_.end(); ++it)
      if(*it == x)
        return std::pair<iterator, bool>( it, false ); //already exists
    return std::pair<iterator, bool>( cache_.insert(cache_.end(), x), true ); //inserted
  }

  iterator insert(iterator hint, value_type x) {
    return cache_.insert(cache_.end(), x); //should be optimized with the hint
  }

  iterator insert(const_iterator hint, value_type x) {
    return cache_.insert(cache_.end(), x); //should be optimized with the hint
  }

  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    for(auto it = first; it != last; ++it)
      cache_.insert( cache_.end(), *it );
  }

  template <class... Ts>
  std::pair<iterator, bool> emplace(Ts&&... xs) {
    const iterator &emplaced = cache_.emplace(cache_.end(), std::forward<Ts>(xs)...);
    for(iterator it = cache_.begin(); it != cache_.end(); ++it)
      if(it->first == emplaced->first && it != emplaced) {
        cache_.erase(emplaced);
        return std::pair<iterator, bool>(it, false);
      }
    return std::pair<iterator, bool>(emplaced, true); //invalidates iterator
  }

  template <class... Ts>
  iterator emplace_hint(const_iterator hint, Ts&&... xs) {
    return cache_.emplace(cache_.end(), std::forward<Ts>(xs)...); //should be optimized with the hint
  }

  iterator erase(const_iterator i) {
    return cache_.erase(i);
  }

  iterator erase(const_iterator first, const_iterator last) {
    return cache_.erase(first, last);
  }

  size_type erase(const key_type& key) {
    const const_iterator it = find(key);
    if(it != cache_.cend())
      cache_.erase(it);
    return cache_.size();
  }

  template <class K>
  mapped_type& at(const K& key) {
    for(auto &it : cache_)
      if(it.first == key)
        return it.second;
    throw std::out_of_range("Can't find any value with the key");
  }

  template <class K>
  const mapped_type& at(const K& key) const {
    for(auto &it : cache_)
      if(it.first == key)
        return it.second;
    throw std::out_of_range("Can't find any value with the key");
  }

  mapped_type& operator[](const key_type& key) {
    for(auto& it : cache_)
      if(it.first == key)
        return it.second;
    return (*cache_.insert(cache_.end(), value_type())).second;
  }

  template <class K>
  iterator find(const K& key) {
    return std::find(cache_.begin(), cache_.end(), key);
  }

  template <class K>
  const_iterator find(const K& key) const {
    return std::find(cache_.cbegin(), cache_.cend(), key);
  }

  template <class K>
  size_type count(const K& key) const {
    return std::count(cache_.begin(), cache_.end(), key);
  }

private:
  vector_type cache_;

};

template <class K, class T, class A>
bool operator==(const flat_map<K, T, A>& xs, const flat_map<K, T, A>& ys) {
  return xs.size() == ys.size() &&
    std::equal(xs.begin(), xs.end(), ys.begin());
}

template <class K, class T, class A>
bool operator!=(const flat_map<K, T, A>& xs, const flat_map<K, T, A>& ys) {
  return !operator==(xs, ys);
}

template <class K, class T, class A>
bool operator<(const flat_map<K, T, A>& xs, const flat_map<K, T, A>& ys) {
  return std::lexicographical_compare(xs.begin(), xs.end(), ys.begin(), ys.end());
}

template <class K, class T, class A>
bool operator>=(const flat_map<K, T, A>& xs, const flat_map<K, T, A>& ys) {
  return !operator<(xs, ys);
}
