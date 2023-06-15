#include "dynamic_bitset.hpp"
#define VECTOR_SIZE(size) (size / bits_per_char + bool(size % bits_per_char))

dynamic_bitset::reference::reference(dynamic_bitset &bitset, size_t index)
    : m_byte{bitset.m_bits[index / bits_per_char]},
      m_bit{char(1 << (index % bits_per_char))} {}

dynamic_bitset::reference &dynamic_bitset::reference::operator=(bool value) {
  if (value) {
    m_byte |= m_bit;
  } else {
    m_byte &= ~m_bit;
  }
  return *this;
}

dynamic_bitset::reference::operator bool() const { return m_byte & m_bit; }

dynamic_bitset::dynamic_bitset() : m_size{0} {}

dynamic_bitset::dynamic_bitset(size_t size)
    : m_bits(VECTOR_SIZE(size)), m_size{size} {}

size_t dynamic_bitset::size() const { return m_size; }

size_t dynamic_bitset::capacity() const {
  return m_bits.capacity() * bits_per_char;
}

bool dynamic_bitset::all() const {
  return m_size == 0 ||
         m_bits.back() == 1 << (m_size % 8 - 1) &&
             for_each(m_bits.begin(), m_bits.end() - 1,
                      [](unsigned char byte) { return byte == 0xFF; });
}

bool dynamic_bitset::none() const {
  return m_size == 0 ||
         for_each(m_bits.begin(), m_bits.end(),
                  [](unsigned char byte) { return byte == 0x00; });
}

bool dynamic_bitset::any() const { return !none(); }

size_t dynamic_bitset::count() const {
  size_t count{0};
  for (size_t i{0}; i < m_size; ++i) {
    count += (*this)[i];
  }
  return count;
}

void dynamic_bitset::flip(size_t index) { (*this)[index] = !(*this)[index]; }

void dynamic_bitset::resize(size_t size) {
  m_bits.resize(VECTOR_SIZE(size));
  m_bits.back() &=
      (1 << (size % 8)) - 1; // important for none() to function properly
  m_size = size;
}

void dynamic_bitset::clear() {
  m_bits.clear();
  m_size = 0;
}

dynamic_bitset::reference dynamic_bitset::operator[](size_t index) {
  if (index >= m_size) {
    throw std::out_of_range("Index out of range");
  }
  return {*this, index};
}

const dynamic_bitset::reference dynamic_bitset::operator[](size_t index) const {
  return const_cast<dynamic_bitset &>(*this)[index];
}

std::ostream &operator<<(std::ostream &os,
                         const dynamic_bitset::reference &bit) {
  return os << (bool)bit;
}

std::ostream &operator<<(std::ostream &os, const dynamic_bitset &bitset) {
  for (size_t i{bitset.m_size}; i > 0; --i) {
    os << bitset[i - 1];
  }
  return os;
}

dynamic_bitset dynamic_bitset::operator=(const std::string &bitstring) {
  resize(bitstring.size());
  for (size_t i{0}; i < m_size; ++i) {
    (*this)[i] = bitstring[m_size - i - 1] != '0';
  }
  return *this;
}

template <typename T>
dynamic_bitset dynamic_bitset::operator=(T value) {
  resize(sizeof(value) * 8);
  memcpy(m_bits.data(), &value, sizeof(value));
  return *this;
}
template dynamic_bitset dynamic_bitset::operator=<int>(int);
template dynamic_bitset dynamic_bitset::operator=<unsigned int>(unsigned int);
template dynamic_bitset dynamic_bitset::operator=<long>(long);
template dynamic_bitset dynamic_bitset::operator=<unsigned long>(unsigned long);
template dynamic_bitset dynamic_bitset::operator=<long long>(long long);
template dynamic_bitset dynamic_bitset::operator=<unsigned long long>(
    unsigned long long);

bool dynamic_bitset::operator==(const dynamic_bitset &bitset) const {
  return m_size == bitset.m_size &&
         !memcmp(m_bits.data(), bitset.m_bits.data(), VECTOR_SIZE(m_size));
}

dynamic_bitset dynamic_bitset::operator~() const {
  dynamic_bitset result(m_size);
  for (size_t i{0}; i < VECTOR_SIZE(m_size); ++i) {
    result.m_bits[i] = ~m_bits[i];
  }
  return result;
}

dynamic_bitset dynamic_bitset::operator&(const dynamic_bitset &bitset) const {
  dynamic_bitset result(m_size);
  for (size_t i{0}; i < VECTOR_SIZE(m_size); ++i) {
    result.m_bits[i] = m_bits[i] & bitset.m_bits[i];
  }
  return result;
}

dynamic_bitset dynamic_bitset::operator|(const dynamic_bitset &bitset) const {
  dynamic_bitset result(m_size);
  for (size_t i{0}; i < VECTOR_SIZE(m_size); ++i) {
    result.m_bits[i] = m_bits[i] | bitset.m_bits[i];
  }
  return result;
}

dynamic_bitset dynamic_bitset::operator^(const dynamic_bitset &bitset) const {
  dynamic_bitset result(m_size);
  for (size_t i{0}; i < VECTOR_SIZE(m_size); ++i) {
    result.m_bits[i] = m_bits[i] ^ bitset.m_bits[i];
  }
  return result;
}

dynamic_bitset dynamic_bitset::operator<<(size_t shift) const {
  dynamic_bitset result(m_size);
  return result;
}

dynamic_bitset dynamic_bitset::operator>>(size_t shift) const {
  dynamic_bitset result(m_size);
  return result;
}

#undef VECTOR_SIZE
