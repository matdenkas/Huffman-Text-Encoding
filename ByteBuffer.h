#include <string>
#include <vector>
#include <fstream>

const int SIZEOFBYTE = 8;

class ByteBuffer {

private:
  unsigned char buffer;
  unsigned int bufferIndex;
  std::fstream fileStream;
  unsigned bitsWritten;

public:
  ByteBuffer(std::string);
  ~ByteBuffer();

  void operator<< (const std::vector<bool>&); 
  void close();
private:
  void pactByte(const bool);
  void writeByte();
  void flushBuffer();
};