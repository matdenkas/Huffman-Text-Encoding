#include "HuffmanTree.h"
#include <bitset>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void HuffmanTree::generateTree(std::string str) {
  CharFrequenciesMap charFrequenciesMap = buildFreqMap(str);

  std::vector<LeafFreq> sortedCharFreq = sortFreqMap(charFrequenciesMap);

  // Build huffman tree from the least frequent values to the most
  // frequent values, combining the leafs and resorting them untill
  // we have only one head leaf;
  while (sortedCharFreq.size() > 1) {

    // pop first two pairs
    LeafFreq firstPair = sortedCharFreq[0];
    LeafFreq secondPair = sortedCharFreq[1];
    sortedCharFreq.erase(sortedCharFreq.begin());
    sortedCharFreq.erase(sortedCharFreq.begin());

    // build a new singular leaf
    int total = firstPair.first + secondPair.first;
    leaf *newLeaf = new leaf;
    // by binding the two leafs to this one
    newLeaf->left = firstPair.second;
    newLeaf->right = secondPair.second;
    LeafFreq newPair(total, newLeaf);

    // Then resort the pair into the vector
    insertLeafFreq(sortedCharFreq, newPair);
  }

  // Assighn the constructed huffman tree to the class and its depth
  this->head = sortedCharFreq[0].second;
  this->depth = (size_t)recursive_getTreeDepth(this->head, 0);

  std::cout << "Size: " << depth << std::endl;

  return;
}

// Encodes a character in the hoffmin tree, returns "" if char isn't there
std::string HuffmanTree::encodeChar(char c) {
  return recursive_getCharBitPath(head, c, "");
}

void HuffmanTree::decodeChar(char) { return; }

/// Finds the frequencie a character appears in a certain text
CharFrequenciesMap HuffmanTree::buildFreqMap(std::string str) {

  CharFrequenciesMap charFrequenciesMap;

  for (auto &ch : str) { // for each character

    // check if its in the map
    CharFrequenciesMap::iterator pair = charFrequenciesMap.find(ch);
    if (pair == charFrequenciesMap.end()) { // add it if not
      charFrequenciesMap.insert({{ch, 1}});
    } else { // incrament it if it is
      pair->second++;
    }
  }

  return charFrequenciesMap;
}

/// Takes a map of Character frequences and sorts them in a vector by frequency
std::vector<LeafFreq> HuffmanTree::sortFreqMap(CharFrequenciesMap &charFrequenciesMap) {

  std::vector<LeafFreq> sortedCharFreq;
  for (auto &it : charFrequenciesMap) {

    leaf *newLeaf = new leaf;
    newLeaf->character = it.first;
    LeafFreq newPair(it.second, newLeaf);
    insertLeafFreq(sortedCharFreq, newPair);
  }

  return sortedCharFreq;
}

void HuffmanTree::insertLeafFreq(std::vector<LeafFreq> &vec, LeafFreq newPair) {
  auto vec_it = vec.begin();
  bool placed = false;
  while (vec_it != vec.end() && !placed) {
    if (newPair.first < vec_it->first) {
      vec.insert(vec_it, newPair);
      placed = true;
    }
    ++vec_it;
  }

  if (!placed) { // if a place for it was not found
    vec.push_back(newPair);
  }

  return;
}

int HuffmanTree::recursive_getTreeDepth(leaf *leaf, int i) {
  i++;

  // if no children just return
  if (leaf->left == nullptr && leaf->right == nullptr) {
    return i;
  }

  // for each child recurse
  int left = 0;
  int right = 0;
  if (leaf->left != nullptr) {
    left = recursive_getTreeDepth(leaf->left, i);
  }
  if (leaf->right != nullptr) {
    right = recursive_getTreeDepth(leaf->right, i);
  }

  // return the bigger number;
  if (left > right) {
    return left;
  } else
    return right;
}

// recursively gets the bitpath to a character returns "" if not found
std::string HuffmanTree::recursive_getCharBitPath(leaf *leaf, char c,
                                                  std::string path) {
  // If the leaf has no children then it has a character that might be the one
  // we need
  if (leaf->left == nullptr && leaf->right == nullptr) {
    // return nothing if its not the char we want, path otherwise
    return leaf->character == c ? path : "";
  } else {                              // recurse
    std::string leftPath = path + '1';  // encode a 1 for left
    std::string rightPath = path + '0'; // encode a 0 for right

    // left
    if (leaf->left != nullptr) {
      leftPath = recursive_getCharBitPath(leaf->left, c, leftPath);
    } else {
      leftPath = "";
    }

    // right
    if (leaf->right != nullptr) {
      rightPath = recursive_getCharBitPath(leaf->right, c, rightPath);
    } else {
      rightPath = "";
    }
    // return path to correct char or empty set
    if (rightPath != "") {
      return rightPath;
    } else
      return leftPath;
  }
}

void HuffmanTree::print2DUtil() { recursive_print2DUtil(head, 0); }

#define COUNT 10
// Function to print binary tree in 2D
// It does reverse inorder traversal
void HuffmanTree::recursive_print2DUtil(leaf *root, int space) {
  // Base case
  if (root == NULL)
    return;

  // Increase distance between levels
  space += COUNT;

  // Process right child first
  recursive_print2DUtil(root->right, space);

  // Print current node after space
  // count
  std::cout << std::endl;
  for (int i = COUNT; i < space; i++)
    std::cout << " ";
  std::cout << root->character << "\n";

  // Process left child
  recursive_print2DUtil(root->left, space);
}
