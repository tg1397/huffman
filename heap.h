/* ************************************************************************
NAME: Trisha Gagnon
DATE: 12/9
DESC: Heap Documentation
*************************************************************************** */
#include <cstdlib>
struct hnode {

  unsigned char letter;
  size_t count;
  
  hnode *left, *right;

  hnode(unsigned char letter, size_t count, hnode *left = NULL, hnode *right = NULL) :
    letter(letter), count(count), left(left), right(right) {}
};

typedef hnode * heap_element;

class heap {
public:
  heap(size_t (*p)(const heap_element));
  void insert(const heap_element&);
  heap_element remove();
  size_t size() const;
private:
  heap_element _data[256];
  size_t _size;
  size_t (*priority)(const heap_element);
  size_t parent(size_t) const; 
  void swap(size_t, size_t); 
  size_t left_child(size_t) const;
  size_t right_child(size_t) const;
  void reheap_up(size_t);
  void reheap_down(size_t);

};