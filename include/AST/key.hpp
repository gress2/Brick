#ifndef BRICK_AST_KEY_HPP_
#define BRICK_AST_KEY_HPP_

namespace brick::AST
{
  template <class T>
  class key {
    public:
      using data_type = unsigned long long int;
    private:
      union {
        T external_;
        data_type internal_;
      };
    public:
      explicit constexpr key(const T&);
      explicit constexpr operator T() const;
      constexpr data_type data() const noexcept;
  };

  template <class T>
  constexpr key<T>::key(const T& data)
    : internal_(data)
  {}

  template <class T>
  constexpr key<T>::operator T() const {
    return external_;
  }

  template <class T>
  constexpr typename key<T>::data_type key<T>::data() const noexcept {
    return internal_;
  }
}

#endif
