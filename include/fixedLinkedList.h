#ifndef fixedLinkedList_H
#define fixedLinkedList_H

#include <stddef.h>
#include <stdint.h>

template <typename T, size_t MaxSize> class FixedLinkedList
{
private:
  struct Node
  {
    T value;
    Node* next = nullptr;
  };

  Node nodes[MaxSize];
  Node* head = nullptr;
  Node* freeNodes = nullptr;   // Pointer to the head of the free nodes list
  size_t size = 0;

public:
  FixedLinkedList()
  {
    // Initialize the free list
    for (size_t i = 0; i < MaxSize - 1; ++i)
    {
      nodes[i].next = &nodes[i + 1];
    }
    nodes[MaxSize - 1].next = nullptr;
    freeNodes = &nodes[0];
  }

  bool add(const T& value)
  {
    if (size >= MaxSize || freeNodes == nullptr)
    {
      return false;   // No more free nodes
    }

    // Extract the first free node
    Node* newNode = freeNodes;
    freeNodes = freeNodes->next;

    newNode->value = value;
    newNode->next = nullptr;

    // Add to the end of the list
    if (head == nullptr)
    {
      head = newNode;
    }
    else
    {
      Node* current = head;
      while (current->next != nullptr)
      {
        current = current->next;
      }
      current->next = newNode;
    }

    size++;
    return true;
  }

  bool remove(size_t index)
  {
    if (index >= size)
    {
      return false;   // Index out of bounds
    }

    Node* toDelete = nullptr;

    if (index == 0)
    {
      toDelete = head;
      head = head->next;
    }
    else
    {
      Node* current = head;
      for (size_t i = 0; i < index - 1; ++i)
      {
        current = current->next;
      }
      toDelete = current->next;
      current->next = toDelete->next;
    }

    // Add the removed node back to the free list
    toDelete->next = freeNodes;
    freeNodes = toDelete;

    size--;
    return true;
  }

  T* get(size_t index)
  {
    if (index >= size)
    {
      return nullptr;   // Index out of bounds
    }

    Node* current = head;
    for (size_t i = 0; i < index; ++i)
    {
      current = current->next;
    }

    return &(current->value);
  }

  size_t getSize() const { return size; }

  // Iterator class definition
  class Iterator
  {
  private:
    Node* currentNode;

  public:
    Iterator(Node* node) : currentNode(node) {}

    // Prefix increment
    Iterator& operator++()
    {
      if (currentNode)
        currentNode = currentNode->next;
      return *this;
    }

    // Dereference
    T& operator*() const { return currentNode->value; }

    // Equality check
    bool operator==(const Iterator& other) const { return currentNode == other.currentNode; }

    // Inequality check
    bool operator!=(const Iterator& other) const { return currentNode != other.currentNode; }
  };

  // Return iterator to the beginning of the list
  Iterator begin() const { return Iterator(head); }

  // Return iterator to the end of the list (nullptr signifies end)
  Iterator end() const { return Iterator(nullptr); }
};

#endif
