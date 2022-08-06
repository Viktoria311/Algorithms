#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include "bin_tree.h"

int main()
{
    std::vector<int> vec_numbers;

    std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<> distr(1, 100);
    std::cout << "Create vector with random elements from 1 to 100 " << std::endl;
    for (int i = 0; i < 17; ++i)
    {
        vec_numbers.push_back(distr(generator));
        std::cout << vec_numbers.at(i) << " " ;
    }
    std::cout << std::endl;

    std::cout << "and create the bynary tree with the same elements." << std::endl;
    bin_tree<int> test_tree;
    for (auto i : vec_numbers)
    {
        test_tree.insert(i);
    }

    std::random_shuffle(vec_numbers.begin(), vec_numbers.end());

    std::cout << "detele a middle of the tree elements" << std::endl;
     for (int i = 0; i < static_cast<int>(vec_numbers.size())/2; ++i)
         test_tree.remote(vec_numbers.at(i));

     std::cout << "vector elements: " << std::endl;
     for (auto i : vec_numbers)
         std::cout << i << "   ";
     std::cout << std::endl;

     std::cout << "remainibg tree elements: " << std::endl;

     for (auto i : vec_numbers)
     {
        auto p_int = test_tree.find(i);
        if (p_int != nullptr)
           std::cout << p_int->value << " " ;
        else
           std::cout << "   " ;
     }

    return 0;
}
