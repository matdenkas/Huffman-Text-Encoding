#include "ByteBuffer.h"
#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include <string>

std::string lyrics = "Beto is super cool";

int main() {
  std::cout << "Hello World!\n";

  HuffmanTree HT;
  HT.generateTree(lyrics);

  std::fstream fs("out.bin");
  for (char &c : lyrics) {
    fs << HT.encodeChar(c);
  }
  fs.close();

  HT.print2DUtil();

  /**
  ByteBuffer bb("out.a");

  std::vector<bool> v = {0,0,0,0,1,1,0,0};

  bb << v;
  bb.close();

  unsigned char c;
  std::fstream fs("out.bin");
  fs >> c;

  std::cout << c << std::endl;
  fs.close();
  **/
}