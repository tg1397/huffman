/* ************************************************************************
NAME: Trisha Gagnon
DATE: 12/9
DESC: Heap Implementation
*************************************************************************** */

#include "heap.h"
#include <cstdlib>



//private
size_t heap::parent(size_t child) const
{
  return (child - 1) / 2;
}
void heap::swap(size_t first, size_t second)
{
  heap_element change = _data[first];
  _data[first] = _data[second];
  _data[second] = change;
}

void heap::reheap_up(size_t tree)
{
  if (tree == 0)
    return;
  size_t par = parent(tree);
  if (priority(_data[tree]) < priority(_data[par])) {
    swap(tree, par);
    reheap_up(par);
  }
}

size_t heap::left_child(size_t par) const
{
  return (par * 2) + 1;
}
size_t heap::right_child(size_t par) const
{
  return (par * 2) + 2;
}

void heap::reheap_down(size_t tree)
{
  if ((2 * tree) + 1 > _size)
    return;
  size_t child = left_child(tree);
  size_t compare = right_child(tree);
  if (!compare > _size && priority(_data[compare]) < priority(_data[child]))
    child = compare;
  if (priority(_data[child]) < priority(_data[tree])) {
    swap(tree, child);
    reheap_down(child);
  }
}

//public
heap::heap(size_t (*p)(const heap_element)): _size(0), priority(p) {}

void heap::insert(const heap_element & item)
{
  _data[_size] = item;
  _size++;
  reheap_up(_size-1);
}

heap_element heap::remove()
{
  heap_element removed = _data[0];
  _data[0] = _data[_size - 1];
  _size--;
  reheap_down(0);
  return removed;
}

size_t heap::size() const
{
  return _size;
}