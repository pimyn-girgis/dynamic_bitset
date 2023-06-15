#ifndef DYNAMIC_BITSET_HPP
#define DYNAMIC_BITSET_HPP

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <istream>
#include <ostream>
#include <vector>

class dynamic_bitset {
private:
  static const size_t bits_per_char{sizeof(unsigned char) * 8};
  std::vector<unsigned char> m_bits;
  size_t m_size;
  class reference {
  private:
    unsigned char &m_byte;
    char m_bit;

  public:
    reference(dynamic_bitset &bitset, size_t index);
    reference &operator=(bool value);
    operator bool() const;
  };

public:
  explicit dynamic_bitset();
  explicit dynamic_bitset(size_t size);
  [[nodiscard]] size_t size() const; // returns the number of bits
  [[nodiscard]] size_t capacity() const; // returns the capacity of the underlying vector
  [[nodiscard]] bool all() const; // returns true if all bits are set or if the bitset is empty
  [[nodiscard]] bool none() const; // returns true if no bits are set or if the bitset is empty
  [[nodiscard]] bool any() const;     // returns true if not none()
  [[nodiscard]] size_t count() const; // returns the number of set bits
  void flip(size_t index);            // flips the bit at the given index
  void resize(size_t size);           // resizes the bitset to the given size
  void clear();                       // clears the bitset
  friend std::ostream &operator<<(std::ostream &os,
                                  const dynamic_bitset &bitset);
  friend std::ostream &operator<<(std::ostream &os,
                                  const dynamic_bitset::reference &bit);
  dynamic_bitset operator=(const std::string &bitstring);
  dynamic_bitset operator=(const unsigned int);
  dynamic_bitset operator~() const;
  dynamic_bitset operator&(const dynamic_bitset &bitset) const;
  dynamic_bitset operator|(const dynamic_bitset &bitset) const;
  dynamic_bitset operator^(const dynamic_bitset &bitset) const;
  dynamic_bitset operator<<(size_t shift) const; // to be defined
  dynamic_bitset operator>>(size_t shift) const; // to be defined
  bool operator==(const dynamic_bitset &bitset) const;

  reference operator[](size_t index);
  const reference operator[](size_t index) const;
};

#endif // DYNAMIC_BITSET_HPP
