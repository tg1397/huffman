/* ************************************************************************
NAME: Trisha
DATE: 11/27
DESC: Encoding a string read in from an input file
***************************************************************************
*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "heap.h"

using namespace std;

//CITE: Lia Jundt 
//DESC: Walking me through encoding 8-length bit strings into chars
//CITE: Alex Dennis
//DESC: The code for creating an output file
//CITE: Will May 
//DESC: Help debugging my encoder to prevent '00000000' from being incorrectly
//encoded
//CITE: Ava Tankala
//DESC: Help talking through reusing the original file to encode characters



void printTree(hnode * root, ofstream & fout) 
{
  //Pre-order, left to right traversal
  if (root) {
    char type;
    if (!root->left) {
      type = 'L';

      fout << type << root->letter;
    }
    else {
      type = 'I';

      fout << type;
    }
    printTree(root->left, fout);
    printTree(root->right, fout);

  }
}

size_t priority(hnode* n)
{
  return n->count;
}





int COUNTS[256];
string CODES[256];

void codeMaker(hnode *root, char appender)
{
  //Descends the tree, adding the new direction to every leaf it reaches
  if(root) {
    if (!root->left) {
      size_t i = root->letter;
      CODES[i] = appender + CODES[i];
    }
    else {
    codeMaker(root->left, appender);
    codeMaker(root->right, appender);
    }
  }
}


hnode * build_tree()
{
  //Creates a heap of all the pointers to all the leafs within the tree
  heap order(&priority);
  
  for (size_t i = 0; i < 256; i++)
    if (COUNTS[i] > 0)
      order.insert(new hnode(i, COUNTS[i]));
  while (order.size() > 1) {
    //takes the smallest two, creates a new node as their root
    //prepends every string in CODES
    hnode *left = order.remove();
    codeMaker(left, '0');
    hnode *right = order.remove();
    codeMaker(right, '1');
    order.insert(new hnode('&', left->count + right->count, left, right));
  }
  //returns root
  return order.remove();  // :-0
}

int bit2int(string bin)
{
  //Turns 1byte in string form to an int.
  int start = 128;
  int total = 0;
  for(size_t i = 0; i < bin.length(); i++) {
    if (bin[i] == '1') 
      total += start;
    start /= 2;
  }
  return total;
}

unsigned char codedchar(string bin)
{
  //takes a string, creates an int from it, then makes a char from that
  int thing = bit2int(bin);
  unsigned char code = thing; 
  return code; 
  
}


int main(int argc, char ** argv)
{
  
  ifstream fin(argv[argc - 1]);
  for (size_t i = 0; i < 256; i++) {
    COUNTS[i] = 0;
    CODES[i] = "";
  }
  ofstream fout((string(argv[1]) + ".huf").c_str());

  // read the file
  string inpt = "";
  size_t filelength = 0;
  while (true) {
    int b = fin.get();
    if (!fin) {
      fin.close();
      break;
    }
    filelength++;
    inpt += b;
    COUNTS[b]++;
  }

  fout << filelength;

  // build the tree
  hnode * tree = build_tree();
  printTree(tree, fout);
 
 
  // read the file again, outputing each character's coded char
  ifstream in(argv[1]);
  string binary = "";  

  while (true) {
 
    string tempbinary = "";
    if (!in)
      break;
 

    //Dueling while loops
    while (binary.length() < 8) {
      //Slowly grows the loop, adding the new codes to binary
      int b = in.get();
      if (b < 0)
	break;
 
      string code = CODES[b];
      binary = binary + code;
    }

    while (binary.length() >= 8) {
      //Accounts for if binary > 16
      //uses tempbinary to write over, then rewrites binary
      tempbinary = binary.substr(0,8);
      fout << codedchar(tempbinary);
      binary = binary.substr(8);
    }
  }

  //gets the last character
  while (binary.length() < 8) 
    binary += '0';
 
  fout << codedchar(binary);
  remove(argv[1]);
}