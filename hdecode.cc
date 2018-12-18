/* ************************************************************************
NAME: Trisha
DATE: 11/27
DESC: Decoding the Huffman Tree fed in by Encode
***************************************************************************
*/

#include <iostream>
#include <cstdlib>
#include <fstream>

//CITE: Eric Collins
//DESC: Help with figuring out recursive decode before abandoning it and helping
//DESC: working out the actually functioning decode

using namespace std;

struct hnode {

  unsigned char letter;
  hnode *left, *right;

  hnode(unsigned char letter, hnode *left = NULL, hnode *right = NULL) :
    letter(letter), left(left), right(right) {}
};


hnode * readTree(ifstream & fin)
{
  //reads in the tree in the file with a left to right traversal
  char type;
  type = fin.get();
  if (type == 'L')
    return new hnode(fin.get());

  else {
    hnode * left = readTree(fin);
    hnode * right = readTree(fin);
    return new hnode('&', left, right);
  }
}


string int2bit(size_t character)
{
  //transforms a size_t from an unsigned char into an 8 length bit string
  string result = "";
  size_t i;
  size_t power;
  for (i = 0, power = 128; i < 8; i++, power /= 2) {
    if (character >= power) {
      result += '1';
      character -= power;
    }
    else
      result += '0';  
  }
  return result;
}


bool isLeaf(hnode* root)
{
  //precondition: root
  if (!root->left)
    return true;
  return false;
}


void printTree(hnode * root) 
{
  //prints the tree, preorder, left to right
  if (root) {
    char type;
    if (!root->left) {
      type = 'L';
    }
    else {
      type = 'I';
    }
    printTree(root->left);
    printTree(root->right);
    
  }
}


int main(int argc, char ** argv)
{
  //reading in the encoded data
  ifstream fin(argv[argc - 1]);
  string ttle = string(argv[1]);
  ttle = ttle.substr(0, ttle.length() - 4);
  ofstream fout((ttle).c_str());
  
  size_t length;
  fin >> length;
  hnode * tree = readTree(fin);
  printTree(tree);
  string encodedchar = "";
  hnode * descender = tree;
  size_t final = 0;
  while (true) {
    size_t b = fin.get();

    if (!fin)
      break;

    //read bits
    //descend tree
    //get new hnode
    //check if leaf
    encodedchar += int2bit(b);

    while (encodedchar.length() > 0 && final < length) {
    
      if (isLeaf(descender)) {
	fout << descender->letter;
	final++;
	descender = tree;
      }
      if (encodedchar.substr(0,1) == "0")
	descender = descender->left;
      else
	descender = descender->right;
      
      encodedchar = encodedchar.substr(1);
    }
  }
  remove(argv[1]);
}

//Worked kinda hard at this so leaving it in
/*
My attempt at a recursive solution
string decode(string binary, hnode * root, size_t length)
{
  string result = "";
  while (binary.length() > 0 and result.length() < length) {
    cout << "Start: " << binary << endl;
    if (isLeaf(root)) {
      cout << root->letter << endl;
      return result += root->letter;
      //result += root -> letter;
      //cout << result << endl;
      //decode(binary, trueroot, trueroot, fout);
      //return;
    }

    if (binary.substr(0,1) == "0") {
      cout << "Left:  ";
      binary = binary.substr(1);
      cout << binary << endl;
      return result += decode(binary, root->left, length);
    }
    else {
      binary = binary.substr(1);
      cout << "Right: " << binary << endl;
      return result += decode(binary, root->right, length);
    }
  }
  return result;
}
*/