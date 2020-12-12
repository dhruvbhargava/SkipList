#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

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
    Node *bottom = NULL;
    Node *right = NULL;

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
    SkipList();
    SkipList(int _size, std::vector<KeyType> keys)
    {
        size = _size;
        sort(keys.begin(), keys.end());
        _height = (int)floor(log2((float)size));
        std::cout << "height:::" << _height << std::endl;
        Node<KeyType> *newNode = NULL;
        std::vector<Node<KeyType> *> levelTemps = std::vector<Node<KeyType> *>(_height);
        //create the (-infinite) lower bounding nodes for each level
        for (int i = _height - 1; i > -1; i--)
        {
            levelTemps[i] = new Node<KeyType>(keys[0], ValType::VAL);
            if (i != _height - 1)
                levelTemps[i + 1]->bottom = levelTemps[i];
        }
        topLeft->right = levelTemps[_height - 1];

        //create levels
        int level;
        for (int keyIndex = 1; keyIndex < keys.size(); keyIndex++)
        {
            level = 0;
            while (level < _height - 1 and keyIndex % (int)pow(2, level + 1) == 0 and keyIndex % 2 == 0)
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
        // levelTemps[_height - 1]->right = topRight;
    }
    void search(KeyType val)
    {
        int i = _height - 1;
        Node<KeyType> *tempSupereme = topLeft->right;
        Node<KeyType> *temp = tempSupereme;
        int indexCounter = 0;
        while (i >= 0)
        {

            if (temp == NULL)
            {
                std::cout << "bhag bsdk" << std::endl;
                break;
            }
            std::cout << temp->val << " ";
            if (temp->right->val <= val)
            {
                temp = temp->right;
                indexCounter += pow(2, i);
            }
            else if (temp->val == val)
            {
                std::cout << "index hai::" << indexCounter << std::endl;
                break;
            }
            else
            {
                temp = temp->bottom;
                i--;
                std::cout << std::endl;
            }
        }
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
                std::cout << temp->val << std::string(i == 0 ? 1 : i % 2 == 0 and i != 0 ? 3 * (i) + 1 : 3 * i, '-');
                temp = temp->right;
            }
            if (tempSupereme->bottom != NULL)
            {
                tempSupereme = tempSupereme->bottom;
            }
            std::cout << temp->val << "\n";
            int k = size / (i + 1);
            if (i != 0)
            {
                while (k >= i)
                {
                    std::cout << "|" << std::string(i == 0 ? 1 : i % 2 == 0 and i != 0 ? 3 * (i) + 1 : 3 * i, ' ');
                    k--;
                }
                std::cout << "|" << std::endl;
            }
            i--;
        }
    }
};