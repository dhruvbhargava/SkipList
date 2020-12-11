#include <iostream>
#include <vector>

enum ValType
{
    MINUSINFINITY,
    PLUSINFINITY,
    VAL
};
template <typename KeyType>
class Node
{
public:
    KeyType val;
    ValType valType;
    Node *bottom;
    Node *right;

    Node(KeyType _val, ValType _valType)
    {
        val = _val;
        valType = _valType;
    }
    Node(ValType _valType)
    {
        valType = _valType;
    };
};

template <typename KeyType>
class SkipList
{
    int _height;
    int size;
    
public:
    Node<KeyType> *topLeft = new Node<KeyType>(ValType::MINUSINFINITY);
    Node<KeyType> *topRight = new Node<KeyType>(ValType::PLUSINFINITY);
    
    //initializes with empty skip list
    SkipList();
    //initializes with perfect skip list
    SkipList(int _size, std::vector<KeyType> values);
    //returns index by key
    int retrieve(KeyType key);
    int insertkey(KeyType key);
    int deleteKey(KeyType key);
    void visualize();
};