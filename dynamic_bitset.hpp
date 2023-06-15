#ifndef DYNAMIC_BITSET_HPP
#define DYNAMIC_BITSET_HPP

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
    unsigned char& m_byte;
    char m_bit;

  public:
    reference(dynamic_bitset& bitset, size_t index);
    reference& operator=(bool value);
    explicit operator bool() const;
  };

public:
  explicit dynamic_bitset(size_t size);
  [[nodiscard]] size_t size() const;
  [[nodiscard]] size_t capacity() const;
  void resize(size_t size);
  void clear();
  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_bitset& bitset);
  friend std::ostream& operator<<(std::ostream &os, const dynamic_bitset::reference &bit);
  reference operator[](size_t index);
  const reference operator[](size_t index) const;
};

#endif  //DYNAMIC_BITSET_HPP
