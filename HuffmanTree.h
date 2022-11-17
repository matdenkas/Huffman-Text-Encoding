#include <bitset>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct leaf {
  char character = (char)0; // nullchar
  leaf *left = nullptr;
  leaf *right = nullptr;
};

typedef std::pair<int, leaf *> LeafFreq;
typedef std::unordered_map<char, int> CharFrequenciesMap;

class HuffmanTree {
private:
  leaf *head;
  size_t depth;

public:
  void generateTree(std::string);
  std::string encodeChar(char);
  void decodeChar(char);
  void print2DUtil();

private:
  CharFrequenciesMap buildFreqMap(std::string);
  std::vector<LeafFreq> sortFreqMap(CharFrequenciesMap &);
  void insertLeafFreq(std::vector<LeafFreq> &, LeafFreq);
  int recursive_getTreeDepth(leaf *, int);
  std::string recursive_getCharBitPath(leaf *, char, std::string);
  void recursive_print2DUtil(leaf *, int);
};