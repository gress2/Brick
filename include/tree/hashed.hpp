#ifndef BRICK_TREE_HASHED_HPP_
#define BRICK_TREE_HASHED_HPP_

#include <functional>

namespace brick::tree
{
  template <class T, class Hash = std::size_t>
  class hashed
  {
    public:
      using value_type = T;
      using hash_type = Hash;
    private:
      value_type value_;
      hash_type hash_;
    public:
      explicit constexpr hashed(const T&);
      explicit constexpr hashed(T&&);
      hashed& operator=(const T&);
      hashed& operator=(T&&);
      explicit constexpr operator T() const;
      constexpr hash_type operator()() const noexcept;
      hash_type operator()(const T&);
  };

  template <class T, class H>
  constexpr hashed<T, H>::hashed(const T& value)
    : value_(value), hash_(std::hash<T>{}(value))
  {}

  template <class T, class H>
  constexpr hashed<T, H>::hashed(T&& value)
    : value_(std::move(value)), hash_(std::hash<T>{}(std::move(value)))
  {}

  template <class T, class H>
  hashed<T, H>& hashed<T, H>::operator=(const T& value) {
    value_ = value;
    hash_ = std::hash<T>(value);
  }

  template <class T, class H>
  hashed<T, H>& hashed<T, H>::operator=(T&& value) {
    value_ = std::move(value);
    hash_ = std::hash<T>()(std::move(value));
  }

  template <class T, class H>
  constexpr hashed<T, H>::operator T() const {
    return value_;
  }

  template <class T, class H>
  constexpr typename hashed<T, H>::hash_type hashed<T, H>::operator()() const noexcept {
    return hash_;
  }

  template <class T, class H>
  typename hashed<T, H>::hash_type hashed<T, H>::operator()(const T& value) {
    value_ = value;
    hash_ = std::hash<T>(value);
    return hash_;
  }
}

#endif
