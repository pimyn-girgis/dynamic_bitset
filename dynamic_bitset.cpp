#include "dynamic_bitset.hpp"

dynamic_bitset::reference::reference(dynamic_bitset& bitset, size_t index)
    : m_byte{bitset.m_bits[index / bits_per_char]} {
  m_bit = (char)(1 << (index % bits_per_char));
}

dynamic_bitset::reference& dynamic_bitset::reference::operator=(bool value) {
  if (value) {
    m_byte |= m_bit;
  } else {
    m_byte &= ~m_bit;
  }
  return *this;
}

dynamic_bitset::reference::operator bool() const {
  return m_byte & m_bit;
}

dynamic_bitset::dynamic_bitset(size_t size)
    : m_bits(size / bits_per_char + bool(size % bits_per_char)),
      m_size(size) {}

size_t dynamic_bitset::size() const {
  return m_size;
}

size_t dynamic_bitset::capacity() const {
  return m_bits.capacity() * bits_per_char;
}

void dynamic_bitset::resize(size_t size) {
  m_bits.resize(size / bits_per_char + bool(size % bits_per_char));
  m_size = size;
}

void dynamic_bitset::clear() {
  m_bits.clear();
  m_size = 0;
}

dynamic_bitset::reference dynamic_bitset::operator[](size_t index) {
  return {*this, index};
}

const dynamic_bitset::reference dynamic_bitset::operator[](size_t index) const {
  return {*const_cast<dynamic_bitset*>(this), index};
}

std::ostream& operator<<(std::ostream& os, const dynamic_bitset::reference& bit) {
  return os << (bool)bit;
}

std::ostream& operator<<(std::ostream& os, const dynamic_bitset& bitset) {
  for (size_t i{0}; i < bitset.m_size; ++i) {
    os << bitset[i];
  }
  return os;
}
