#include "include/skiplist.h"
#include <iostream>
#include <vector>

int main()
{
    int size;
    std::cout << "enter the size" << std::endl;
    std::cin >> size;
    std::vector<int> vals = std::vector<int>(size);
    for (int i = 0; i < size; i++)
    {
        std::cin >> vals[i];
    }
    SkipList<int> skip = SkipList<int>(size,vals);
    skip.visualize();
}