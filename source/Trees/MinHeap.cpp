#include "MinHeap.hpp"
#include "../Functions/functions.hpp"
#include <iostream>

MinHeap::MinHeap(unsigned int cap){
    array = new int[capacity];
    capacity = cap;
    size = 0;
}
MinHeap::~MinHeap(){
  delete [] array;
}


int floor(int x)
{
  return (int)x;
}

/*void MinHeap::moreBigger()
{
    int *bigArray = new int[capacity * 2];
    for (size_t i = 1; i <= size; i++)
    {
        bigArray[i] = array[i];
    }
    array = bigArray;
    delete[] bigArray;
}*/
/** swim()
   * Restores the heap order property after an element is pushed. Assumes the
   * new element has been pushed at the end of the heap array (right-most node
   * in the bottom level of the tree), and swaps it upwards the tree until it's
   * greater than its parent.
   */
void MinHeap::swim(){
   int i = size;
   while(i != 0 && array[i/2] < array[i]){
       swap(&array[i], &array[i/2]);
       i = i/2;
   }
}

/** sink(int i)
   * Restores the heap order property after element removal. Assumes the element
   * at the end of the heap array has been swapped with the root, and the size
   * has been decremented (effectively removing the last element in the heap
   * array). It then swaps the element at the root down the tree until both
   * children are greater than it.
   */
void MinHeap::sink(int i){
    /*if(array[i] > array[(2*i)+1] && array[i] > array[(2*i)]){
        return;
    }
    else if(array[i] > array[2*i]){
        swap(&array[i], &array[2*i]);
        return sink(2*i);
    }
    else if(array[i] > array[(2*i)+1]){
        swap(&array[i], &array[2*i]);
        return sink(2*i+1);
    }*/
    while((i<size && (i*2 < size)) && (array[i] > array[i*2] || array[i] > array[(i*2)+1])){
        if(array[i] > array[i*2] && array[i*2] < array[(i*2) +1]){
            swap(&array[i], &array[i*2]);
            i *= 2;
        }
        else if(array[i] > array[(i*2)+1]){
            swap(&array[i], &array[(i*2)+1]);
            i = (i * 2) + 1;
        }
        else{
            break;
        }
    }
    
}

/** search(int i, int data)
   * Recursively searches for data in the MinHeap's subtree rooted at i,
   * returning true if the data is found and false if i is greater than or
   * equal to size or data is less than the MinHeap's value at i.
   */
bool MinHeap::search(int i, int data)
{
    if(size == 0){
        throw "nothing to search";
    }
    for(int j = 1; j<=size;j++){
        if(array[j] == i){
            return true;
        }
    }
    return search(i,data);
}

/** erase(int i, int data)
   * Recursively searches for data in the MinHeap's subtree rooted at i,
   * calling remove on i if data is found in the tree.
   * Does nothing if data is not found in the subtree.
   */
void MinHeap::erase(int i, int data)
{
    if (array[i] == data)
    {
        if (array[i] == array[size])
        {
            remove(array[i]);
        }
    }
    else{
         erase(++i,data);
    }
}

void MinHeap::swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}



/** push(int data)
   * Inserts data into the MinHeap such that the heap order property is
   * preserved.
   * Assumes duplicate elements will not be pushed.
   */
void MinHeap::push(int data)
{
    if (size == capacity){
        int *bigArray = new int[capacity * 2];
        for (size_t i = 1; i <= size; i++)
        {
            bigArray[i] = array[i];
        }
        array = bigArray;
        delete[] bigArray;
        //moreBigger(); function couldn't figure how to incorporate it
    }
    size++;
    array[size] = data;
    /*int i = size;
    while(i != 0 && array[i/2] > array[i]){
       swap(&array[i], &array[i/2]);
       i = i/2;
    }*/
}

/** count()
   * Returns the number of elements in the MinHeap.
   */
int MinHeap::count()
{
    return size;
}

/** pop()
   * Removes and returns the minimum element in the MinHeap, preserving the
   * heap order property.
   * Throws an error if the heap is empty.
   */
int MinHeap::pop()
{
    if (size == 0)
    {
        throw "Empty heap";
    }
    swap(&array[size], &array[1]);
    size--;
    sink(array[1]);
    return array[size];
}

/** peek()
   * Returns the minimum element in the MinHeap without modifying its contents.
   * Throws an error if the heap is empty.
   */
int MinHeap::peek()
{
    if (size == 0)
    {
        throw "Empty Heap";
    }
    return array[1];
}

/** search(int data)
   * Searches the MinHeap for the given data, returning true if the data is
   * found and false otherwise.
   */
bool MinHeap::search(int data)
{
    int i = 0;
    while(i < size){
        if(i>=size || size == 0){
        throw "Empty"; 
        }else if(data<array[i]){
        return false; 
        }else if(array[i]==data){
        return true;
        }else{
        return search(i++, data); 
        } 
    } 
}

/** remove(int i)
   * Removes the element at index i in the MinHeap tree (indexed left-to-right,
   * top-to-bottom) and returns its value.
   * Throws an error if the heap is empty or the index is out of bounds.
   */
int MinHeap::remove(int i){
    if(i>size || size == 0 || i == 0){
       throw "Error"; 
    }
    if(!search(array[i])){
      throw "Not found";
    }
    int ret = array[i];
    swap(&array[size], &array[i]);
    size--;
    sink(i);
    return ret; 
   
  }

/** erase(int data)
   * Searches the MinHeap for the given data, and deletes it if it's found,
   * preserving the heap order property.
   * Does nothing if data is not found.
   */
void MinHeap::erase(int data)
{
    erase(0, data);
}

/** print()
   * Prints the contents of the MinHeap tree to the ostream from left-to-right,
   * top-to-bottom.
   */
void MinHeap::print(std::ostream &oss)
{
    for(int i = 0; i <= size; i++){
        oss << array[i] << ", ";
    }
    std::cout << "\n";
}