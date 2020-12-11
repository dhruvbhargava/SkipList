#pragma once
#include <iostream>
#include <vector>
#include<algorithm>
#include<math.h>

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
    SkipList(int _size, std::vector<KeyType> keys)
    {
        //sort the keys
        size = _size;
        sort(keys.begin(), keys.end());
        _height = (int)floor(log2((float)size));

        Node<KeyType> *newNode = NULL;
        std::vector<Node<KeyType> *> levelTemps = std::vector<Node<KeyType> *>(_height);
        //create the (-infinite) lower bounding nodes for each level
        for (int i = _height - 1; i > -1; i--)
        {
            levelTemps[i] = new Node<KeyType>(ValType::MINUSINFINITY);
            if (i != _height - 1)
                levelTemps[i + 1]->bottom = levelTemps[i];
        }
        topLeft->right = levelTemps[_height - 1];
        //create levels
        int level;
        for (int keyIndex = 1; keyIndex < keys.size(); keyIndex++)
        {
            level = 0;
            while (level < _height - 1 and (int) pow(2, level) % keyIndex != 0 and keyIndex % 2 == 0)
                level++;
            int i = 0;
            while (i <= level)
            {
                newNode = new Node<KeyType>(keys[keyIndex], ValType::VAL);
                levelTemps[i]->right = newNode;
                levelTemps[i] = newNode;
                if (i != 0)
                    levelTemps[i]->bottom = levelTemps[i - 1];
                i++;
            }
        }
        levelTemps[_height - 1]->right = topRight;
    }

    void visualize()
    {
        int i = _height - 1;
        Node<KeyType> *tempSupereme = topLeft->right;
        Node<KeyType> *temp;
        while (i >= 0)
        {

            temp = tempSupereme;
            while (temp->right != NULL)
            {
                std::cout << temp->val << std::string(i + 1, '-');
            }
            if (tempSupereme->bottom != NULL)
            {
                tempSupereme = tempSupereme->bottom;
            }
            std::cout << "\n";
        }
    }
};