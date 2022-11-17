#include "ByteBuffer.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

/*
  unsigned char buffer;
  unsigned int bufferIndex;
  std::fstream filestream;

public:
  ByteBuffer(std::string);
  ~ByteBuffer();

 void operator<< (const std::vector<bool>&);

private:
  void pactByte(bool);
  void writeByte();
*/

ByteBuffer::ByteBuffer(std::string fileName) {
  fileStream.open(fileName);
  buffer = (char)0;
  bufferIndex = 0;
  bitsWritten = 0;
}

ByteBuffer::~ByteBuffer() { close(); }

void ByteBuffer::operator<<(const std::vector<bool> &bytes) {
  for (auto const &bit : bytes) {
    std::cout << "Packing bit: " << bit << std::endl;
    pactByte(bit);
  }
  return;
}

void ByteBuffer::close() {
  if (buffer != (char)0) {
    flushBuffer();
  }

  if (fileStream.is_open()) {
    fileStream << bitsWritten;
    fileStream.close();
  }

  return;
}

void ByteBuffer::pactByte(const bool bit) {

  if (bit) { // if the bit is a 1, write a one at the index buffer
    buffer |= (0x80 >> bufferIndex);
  }
  bufferIndex++;

  if (bufferIndex == SIZEOFBYTE) {
    writeByte();
  }

  std::cout << "Buffer: " << buffer << " Index: " << bufferIndex << std::endl;
}

void ByteBuffer::writeByte() {

  fileStream << buffer;
  buffer = (char)0;
  bufferIndex = 0;
  bitsWritten += 8;

  std::cout << "Wrote: " << buffer << std::endl;

  return;
}

void ByteBuffer::flushBuffer() {

  fileStream << buffer;
  buffer = (char)0;
  bufferIndex = 0;
  bitsWritten += bufferIndex;

  return;
}
