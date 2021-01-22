//
// Created by Quaro Tamarillo on 1/19/21.
//

#include "vector.hpp"
#include <vector>
#include "gtest/gtest.h"

template <typename T, typename S>
void checkTwoVectors(T & std_vector, S & ft_vector) {
    typename T::iterator std_it = std_vector.begin();
    typename T::iterator std_ite = std_vector.end();
    typename S::iterator ft_it = ft_vector.begin();
    typename S::iterator ft_ite = ft_vector.end();
    EXPECT_EQ(std_vector.size(), ft_vector.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

template <typename T, typename S>
void printTwoVectors(T & std_vector, S & ft_vector) {
    typename T::iterator std_it = std_vector.begin();
    typename T::iterator std_ite = std_vector.end();
    typename S::iterator ft_it = ft_vector.begin();
    typename S::iterator ft_ite = ft_vector.end();
    std::cout << "std_vector:\t";
    while (std_it != std_ite)
        std::cout << ' ' << *std_it++;
    std::cout << std::endl;
    std::cout << "ft_vector:\t";
    while (ft_it != ft_ite)
        std::cout << ' ' << *ft_it++;
    std::cout << std::endl;
}

TEST(Vector_Base, empty_constructor) {
    std::vector<int>            std_vector;
    ft::vector<int>             ft_vector;
    checkTwoVectors(std_vector, ft_vector);
    for (int i = 0; i < 5; i++) {
        std_vector.push_back(1);
        ft_vector.push_back(1);
        checkTwoVectors(std_vector, ft_vector);
    }
    checkTwoVectors(std_vector, ft_vector);

    std::vector<char>           std_vector2;
    ft::vector<char>            ft_vector2;
    checkTwoVectors(std_vector2, ft_vector2);
    for (char i = 'a'; i < 'e'; i++) {
        std_vector2.push_back(i);
        ft_vector2.push_back(i);
        checkTwoVectors(std_vector2, ft_vector2);
    }
    checkTwoVectors(std_vector2, ft_vector2);

    std::vector<std::string>    std_vector3;
    ft::vector<std::string>     ft_vector3;
    checkTwoVectors(std_vector3, ft_vector3);
    int n = 4;
    while (n--) {
        std_vector3.push_back("abc");
        ft_vector3.push_back("abc");
    }
    checkTwoVectors(std_vector3, ft_vector3);

    std::vector<double>            std_vector5;
    ft::vector<double>             ft_vector5;
    checkTwoVectors(std_vector5, ft_vector5);
    for (int i = 0; i < 10; i++) {
        std_vector5.push_back(1);
        ft_vector5.push_back(1);
        checkTwoVectors(std_vector5, ft_vector5);
    }
    checkTwoVectors(std_vector5, ft_vector5);
}

TEST(Vector_Base, fill_constructor) {
    std::vector<int> std_vector(4);
    ft::vector<int> ft_vector(4);
    checkTwoVectors(std_vector, ft_vector);
    for (int i = 0; i < 10; i++) {
        std_vector.push_back(1);
        ft_vector.push_back(1);
        checkTwoVectors(std_vector, ft_vector);
    }
    checkTwoVectors(std_vector, ft_vector);

    std::vector<std::string> std_vector2(10, "abc");
    ft::vector<std::string> ft_vector2(10, "abc");
    checkTwoVectors(std_vector2, ft_vector2);

    std::vector<char> std_vector3(0);
    ft::vector<char> ft_vector3(0 );
    checkTwoVectors(std_vector3, ft_vector3);
}

TEST(Vector_Base, range_constructor) {
    std::vector<std::string> std_vector(10, "abc");
    ft::vector<std::string> ft_vector(10, "abc");

    checkTwoVectors(std_vector, ft_vector);
    std::vector<std::string> std_vector2(std_vector.begin(), (std_vector.end()));
    ft::vector<std::string> ft_vector2(ft_vector.begin(), (ft_vector.end()));
    checkTwoVectors(std_vector, ft_vector);
    checkTwoVectors(std_vector2, ft_vector2);


    std::vector<int> std_vector3(10, 12);
    ft::vector<int> ft_vector3(10, 12);
    std::vector<int> std_vector4(std_vector3.begin(), --std_vector3.end());
    ft::vector<int> ft_vector4(ft_vector3.begin(), --ft_vector3.end());
    checkTwoVectors(std_vector3, ft_vector3);
    checkTwoVectors(std_vector4, ft_vector4);

}

TEST(Vector_Base, copy_constructor) {
    std::vector<int> std_to_copy_vector (4,100);
    std::vector<int> std_vector (std_to_copy_vector);
    ft::vector<int> ft_to_copy_vector (4,100);
    ft::vector<int> ft_vector (ft_to_copy_vector);
    checkTwoVectors(std_vector, ft_vector);

    std::vector<int> std_vector2;
    ft::vector<int> ft_vector2;
    for (int i = 0; i < 4; i++) {
        std_vector2.push_back(i);
        ft_vector2.push_back(i);
    }
    std::vector<int> std_vector3(std_vector2);
    ft::vector<int> ft_vector3(ft_vector2);
    checkTwoVectors(std_vector3, ft_vector3);
    checkTwoVectors(std_vector2, ft_vector2);
}

TEST(Vector_Base, construct_from_arrays) {
    int myints[] = {16,2,77,29};
    std::vector<int> std_vector (myints, myints + sizeof(myints) / sizeof(int) );
    ft::vector<int> ft_vector (myints, myints + sizeof(myints) / sizeof(int) );
    checkTwoVectors(std_vector, ft_vector);
}

TEST(Vector_Base, operator_equal) {
    std::vector<int> std_vector (3, 0);
    std::vector<int> std_vector2 (5,0);
    ft::vector<int> ft_vector (3,0);
    ft::vector<int> ft_vector2 (5,0);

    std_vector = std_vector2;
    std_vector2 = std::vector<int>();
    ft_vector = ft_vector2;
    ft_vector2 = ft::vector<int>();
    checkTwoVectors(std_vector, ft_vector);
    checkTwoVectors(std_vector2, ft_vector2);

    std::vector<int> std_vector3;
    ft::vector<int> ft_vector3;
    std_vector3.push_back(1);
    ft_vector3.push_back(1);

    std::vector<int> std_vector4;
    ft::vector<int> ft_vector4;
    std_vector3.push_back(2);
    ft_vector3.push_back(2);
    std_vector4 = std_vector3;
    ft_vector4 = ft_vector3;
    checkTwoVectors(std_vector3, ft_vector3);
    checkTwoVectors(std_vector4, ft_vector4);
}


/* Iterators */
TEST(Vector_Iterators, iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<std::string> std_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::vector<std::string> ft_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoVectors(std_vector, ft_vector);

    std::vector<std::string>::iterator std_it = std_vector.begin();
    std::vector<std::string>::iterator std_ite = std_vector.end();
    ft::vector<std::string>::iterator ft_it = ft_vector.begin();
    ft::vector<std::string>::iterator ft_ite = ft_vector.end();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();
    std_ite = std_vector.end();
    ft_ite = ft_vector.end();
    EXPECT_EQ(*(std_it + 3), *(ft_it + 3));
    EXPECT_EQ(*(std_ite - 4), *(ft_ite - 4));

    std_it += 2;
    ft_it += 2;
    std_ite -= 3;
    ft_ite -= 3;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_ite;
    ft_it = ft_ite;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();
    for (size_t i = 0; i < std_vector.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);
}

TEST(Vector_Iterators, const_iterator) {
    char chars[] = {'a','b','c', 'd', 'e', 'f', 'g', 'h', 'k'};
    std::vector<char> std_vector (chars, chars + sizeof(chars) / sizeof(char) );
    ft::vector<char> ft_vector (chars, chars + sizeof(chars) / sizeof(char) );
    checkTwoVectors(std_vector, ft_vector);

    std::vector<char>::const_iterator std_it = std_vector.begin();
    std::vector<char>::const_iterator std_ite = std_vector.end();
    ft::vector<char>::const_iterator ft_it = ft_vector.begin();
    ft::vector<char>::const_iterator ft_ite = ft_vector.end();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();
    std_ite = std_vector.end();
    ft_ite = ft_vector.end();
    EXPECT_EQ(*(std_it + 3), *(ft_it + 3));
    EXPECT_EQ(*(std_ite - 4), *(ft_ite - 4));

    std_it += 2;
    ft_it += 2;
    std_ite -= 3;
    ft_ite -= 3;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_ite;
    ft_it = ft_ite;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_vector.begin();
    ft_it = ft_vector.begin();
    for (size_t i = 0; i < std_vector.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);
}

TEST(Vector_Iterators, reverse_iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<std::string> std_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::vector<std::string> ft_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoVectors(std_vector, ft_vector);

    std::vector<std::string>::reverse_iterator std_it = std_vector.rbegin();
    std::vector<std::string>::reverse_iterator std_ite = std_vector.rend();
    ft::vector<std::string>::reverse_iterator ft_it = ft_vector.rbegin();
    ft::vector<std::string>::reverse_iterator ft_ite = ft_vector.rend();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));
    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();
    std_ite = std_vector.rend();
    ft_ite = ft_vector.rend();
    EXPECT_EQ(*(std_it + 3), *(ft_it + 3));
    EXPECT_EQ(*(std_ite - 4), *(ft_ite - 4));

    std_it += 2;
    ft_it += 2;
    std_ite -= 3;
    ft_ite -= 3;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_ite;
    ft_it = ft_ite;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();
    for (size_t i = 0; i < std_vector.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);

    std::vector<int> std_vector2 (5);
    ft::vector<int> ft_vector2 (5);
    std::vector<int>::reverse_iterator std_it2 = std_vector2.rbegin();
    ft::vector<int>::reverse_iterator ft_it2 = ft_vector2.rbegin();
    int i = 0;
    int i2 = 0;
    for (std_it2 = std_vector2.rbegin(); std_it2!= std_vector2.rend(); ++std_it2)
        *std_it2 = ++i;
    for (ft_it2 = ft_vector2.rbegin(); ft_it2 != ft_vector2.rend(); ++ft_it2)
        *ft_it2 = ++i2;
    checkTwoVectors(std_vector2, ft_vector2);

    std::vector<int> std_vector3 (5);
    ft::vector<int> ft_vector3 (5);
    std::vector<int>::reverse_iterator std_it3 = std_vector3.rbegin();
    ft::vector<int>::reverse_iterator ft_it3 = ft_vector3.rbegin();
    for (; std_it3 != std_vector3.rend(); ++std_it3)
        *std_it3 = ++i;
    for (; ft_it3 != ft_vector3.rend(); ++ft_it3)
        *ft_it3 = ++i2;
   checkTwoVectors(std_vector3, ft_vector3);
}

TEST(Vector_Iterators, const_reverse_iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<std::string> std_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::vector<std::string> ft_vector (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoVectors(std_vector, ft_vector);

    std::vector<std::string>::const_reverse_iterator std_it = std_vector.rbegin();
    std::vector<std::string>::const_reverse_iterator std_ite = std_vector.rend();
    ft::vector<std::string>::const_reverse_iterator ft_it = ft_vector.rbegin();
    ft::vector<std::string>::const_reverse_iterator ft_ite = ft_vector.rend();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));
    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();
    std_ite = std_vector.rend();
    ft_ite = ft_vector.rend();
    EXPECT_EQ(*(std_it + 3), *(ft_it + 3));
    EXPECT_EQ(*(std_ite - 4), *(ft_ite - 4));

    std_it += 2;
    ft_it += 2;
    std_ite -= 3;
    ft_ite -= 3;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_ite;
    ft_it = ft_ite;
    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);

    std_it = std_vector.rbegin();
    ft_it = ft_vector.rbegin();
    for (size_t i = 0; i < std_vector.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);
}


/* Capacity */
TEST(Vector_Capacity, size) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    EXPECT_EQ(std_vector.size(), ft_vector.size());

    for (int i = 0; i < 10; i++) {
        std_vector.push_back(i);
        ft_vector.push_back(i);
    }
    EXPECT_EQ(std_vector.size(), ft_vector.size());
}

TEST(Vector_Capacity, max_size) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    EXPECT_EQ(std_vector.max_size(), ft_vector.max_size());

    std::vector<int> std_vector2(20, 2);
    ft::vector<int> ft_vector2(20, 2);
    EXPECT_EQ(std_vector2.max_size(), ft_vector2.max_size());

    std::vector<double> std_vector3(5);
    ft::vector<double> ft_vector3(5);
    for (int i=0; i<100; i++) {
        std_vector3.push_back(i);
        ft_vector3.push_back(i);
    }
    EXPECT_EQ(std_vector3.max_size(), ft_vector3.max_size());
}

TEST(Vector_Capacity, resize) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    for (int i = 1;i < 10; i++) {
        std_vector.push_back(i);
        ft_vector.push_back(i);
    }

    std_vector.resize(5);
    std_vector.resize(8, 100);
    std_vector.resize(12);
    std_vector.resize(12);
    std_vector.resize(11);
    ft_vector.resize(5);
    ft_vector.resize(8, 100);
    ft_vector.resize(12);
    ft_vector.resize(12);
    ft_vector.resize(11);
    checkTwoVectors(std_vector, ft_vector);
}

TEST(Vector_Capacity, capacity) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    EXPECT_EQ(std_vector.capacity(), ft_vector.capacity());

    std::vector<int> std_vector2(20, 2);
    ft::vector<int> ft_vector2(20, 2);
    EXPECT_EQ(std_vector2.capacity(), ft_vector2.capacity());

    std::vector<double> std_vector3(5);
    ft::vector<double> ft_vector3(5);
    for (int i=0; i<100; i++) {
        std_vector3.push_back(i);
        ft_vector3.push_back(i);
    }
    EXPECT_EQ(std_vector3.capacity(), ft_vector3.capacity());
}

TEST(Vector_Capacity, empty) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    EXPECT_EQ(std_vector.empty(), ft_vector.empty());

    std_vector.push_back(12);
    ft_vector.push_back(12);
    EXPECT_EQ(std_vector.empty(), ft_vector.empty());
}

TEST(Vector_Capacity, reserve) {
    std::vector<int>::size_type std_capacity;
    ft::vector<int>::size_type ft_capacity;

    std::vector<int> std_vector;
    ft::vector<int> ft_vector;

    std_capacity = std_vector.capacity();
    ft_capacity = ft_vector.capacity();
    for (int i = 0; i < 100; ++i) {
        std_vector.push_back(i);
        ft_vector.push_back(i);
        if (std_capacity != std_vector.capacity()) {
            std_capacity = std_vector.capacity();
        }
        if (ft_capacity != ft_vector.capacity()) {
            ft_capacity = ft_vector.capacity();
        }
        EXPECT_EQ(std_capacity, ft_capacity);
    }

    std_vector.reserve(120);
    ft_vector.reserve(120);
    EXPECT_EQ(std_vector.capacity(), ft_vector.capacity());

    std_vector.reserve(12);
    ft_vector.reserve(12);
    EXPECT_EQ(std_vector.capacity(), ft_vector.capacity());
}


/* Element access */
TEST(Vector_Element_acces, operator_) {
    std::vector<int> std_vector (10);
    std::vector<int>::size_type sz = std_vector.size();
    ft::vector<int> ft_vector (10);
    ft::vector<int>::size_type sz2 = ft_vector.size();

    for (unsigned i = 0; i < sz; i++) {
        std_vector[i] = i;
        ft_vector[i] = i;
    }

    for (unsigned i = 0; i < sz / 2; i++)
    {
        int temp;
        temp = std_vector[sz - 1 - i];
        std_vector[sz - 1 - i] = std_vector[i];
        std_vector[i] = temp;
    }
    for (unsigned i = 0; i < sz2 / 2; i++)
    {
        int temp;
        temp = ft_vector[sz2 - 1 - i];
        ft_vector[sz2 - 1 - i] = ft_vector[i];
        ft_vector[i] = temp;
    }
    checkTwoVectors(std_vector, ft_vector);

    std::string myints2[] = {"asfasd","second","thrid"};
    std::vector<std::string> std_vector2 (myints2, myints2 + sizeof(myints2) / sizeof(std::string) );
    std::vector<std::string> ft_vector2 (myints2, myints2 + sizeof(myints2) / sizeof(std::string) );

    std::string *pointer = &std_vector2[0];
    pointer++;
    pointer++;
    pointer--;
    std::string *pointer2 = &ft_vector2[0];
    pointer2++;
    pointer2++;
    pointer2--;

    EXPECT_EQ(*pointer, *pointer2);
}

TEST(Vector_Element_acces, at) {
    std::vector<int> std_vector (10);
    ft::vector<int> ft_vector (10);

    std::string result = "";
    std::string result2 = "";

    try {
        for (unsigned i = 0; i < 100; i++) {
            std_vector.at(i) = i;
        }
    }
    catch (std::exception &e) {
        result = e.what();
    }
    ASSERT_THROW(std_vector.at(30), std::out_of_range);
    try {
        for (unsigned i = 0; i < 100; i++) {
            ft_vector.at(i) = i;
        }
    }
    catch (std::exception &e) {
        result2 = e.what();
    }
    ASSERT_THROW(ft_vector.at(30), std::out_of_range);
    checkTwoVectors(std_vector, ft_vector);
    EXPECT_EQ(result, result2);
}

TEST(Vector_Element_acces, back_end) {
    std::vector<int> std_vector;
    std_vector.push_back(78);
    std_vector.push_back(16);
    std_vector.front() -= std_vector.back();

    ft::vector<int> ft_vector;
    ft_vector.push_back(78);
    ft_vector.push_back(16);
    ft_vector.front() -= ft_vector.back();

    EXPECT_EQ(std_vector.front(), ft_vector.front());
    EXPECT_EQ(std_vector.back(), ft_vector.back());

    std_vector.push_back(10);
    while (std_vector.back() != 0)
        std_vector.push_back ( std_vector.back() - 1 );
    ft_vector.push_back(10);
    while (ft_vector.back() != 0)
        ft_vector.push_back ( ft_vector.back() - 1 );
    EXPECT_EQ(std_vector.front(), ft_vector.front());
    EXPECT_EQ(std_vector.back(), ft_vector.back());

    checkTwoVectors(std_vector, ft_vector);
}


/* Modifiers */
TEST(Vector_Modifiers, assign) {
    std::vector<int> std_first;
    std::vector<int> std_second;
    std::vector<int> std_third;

    std_first.assign (7, 100);

    std::vector<int>::iterator std_it;
    std_it= std_first.begin() + 1;

    std_second.assign (std_it, std_first.end() - 1);

    int myints[] = { 1776, 7, 4};
    std_third.assign (myints, myints + 3);

    ft::vector<int> ft_first;
    ft::vector<int> ft_second;
    ft::vector<int> ft_third;

    ft_first.assign (7, 100);

    ft::vector<int>::iterator ft_it;
    ft_it = ft_first.begin() + 1;

    ft_second.assign (ft_it, ft_first.end() - 1);

    ft_third.assign (myints, myints + 3);

    checkTwoVectors(std_first, ft_first);
    checkTwoVectors(std_second, ft_second);
    checkTwoVectors(std_third, ft_third);
}

TEST(Vector_Modifiers, push_back) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;
    for (int i = 0; i < 100; i++){
        std_vector.push_back (i);
        ft_vector.push_back (i);
    }
    checkTwoVectors(std_vector, ft_vector);

    std::vector<std::string> std_vector2;
    ft::vector<std::string> ft_vector2;
    std_vector2.push_back("first");
    std_vector2.push_back("second");
    std_vector2.push_back("123");
    std_vector2.push_back("567");
    ft_vector2.push_back("first");
    ft_vector2.push_back("second");
    ft_vector2.push_back("123");
    ft_vector2.push_back("567");
    checkTwoVectors(std_vector2, ft_vector2);
}

TEST(Vector_Modifiers, pop_back) {
    std::vector<int> std_vector(1, 4);
    ft::vector<int> ft_vector(1, 4);
    int sum (0);
    int sum2 (0);

    sum += std_vector.back();
    sum2 += ft_vector.back();
    std_vector.pop_back();
    ft_vector.pop_back();
    std_vector.push_back (100);
    std_vector.push_back (200);
    std_vector.push_back (300);
    ft_vector.push_back (100);
    ft_vector.push_back (200);
    ft_vector.push_back (300);

    while (!std_vector.empty() && !ft_vector.empty())
    {
        sum += std_vector.back();
        sum2 += ft_vector.back();
        std_vector.pop_back();
        ft_vector.pop_back();
    }
    EXPECT_EQ(std_vector.empty(), ft_vector.empty());
    checkTwoVectors(std_vector, ft_vector);
    EXPECT_EQ(sum, sum2);
}

TEST(Vector_Modifiers, insert) {
    int array[] = {1, 2, 3, 4 };
    std::vector<int> std_vector(array, array + sizeof(array) / sizeof(int));
    ft::vector<int> ft_vector(array, array + sizeof(array) / sizeof(int));
    EXPECT_EQ(*std_vector.insert(std_vector.begin() + 2, 12),
              *ft_vector.insert(ft_vector.begin() + 2, 12));
    checkTwoVectors(std_vector, ft_vector);
    EXPECT_EQ(*std_vector.insert(std_vector.end(), 14),
              *ft_vector.insert(ft_vector.end(), 14));
    checkTwoVectors(std_vector, ft_vector);

    std::vector<int> std_vector2;
    ft::vector<int> ft_vector2;
    EXPECT_EQ(*std_vector2.insert(std_vector2.begin(), 12),
              *ft_vector2.insert(ft_vector2.begin(), 12));
    checkTwoVectors(std_vector2, ft_vector2);

    EXPECT_EQ(*std_vector2.insert(std_vector2.begin(), 13),
              *ft_vector2.insert(ft_vector2.begin(), 13));
    checkTwoVectors(std_vector2, ft_vector2);

    std::vector<int> std_vector3 (3, 100);
    std::vector<int>::iterator std_it;
    std_it = std_vector3.begin();
    std_it = std_vector3.insert (std_it , 200 );

    ft::vector<int> ft_vector3 (3, 100);
    ft::vector<int>::iterator ft_it;
    ft_it = ft_vector3.begin();
    ft_it = ft_vector3.insert (ft_it , 200 );

    std_vector3.insert (std_it, 2, 300);
    ft_vector3.insert (ft_it, 2, 300);
    checkTwoVectors(std_vector3, ft_vector3);

    std_it = std_vector3.begin();
    ft_it = ft_vector3.begin();
    EXPECT_EQ(*std_it, *ft_it);

    std::vector<int> anothervector (2,400);
    ft::vector<int> anothervector2 (2,400);
    checkTwoVectors(anothervector, anothervector2);
    std_vector3.insert (std_it + 2, anothervector.begin(), anothervector.end());
    ft_vector3.insert (ft_it + 2, anothervector2.begin(), anothervector2.end());
    checkTwoVectors(std_vector3, ft_vector3);

    int myarray [] = { 501,502,503 };
    std_vector3.insert (std_vector3.begin(), myarray, myarray + 3);
    ft_vector3.insert (ft_vector3.begin(), myarray, myarray + 3);
    checkTwoVectors(std_vector3, ft_vector3);
}

TEST(Vector_Modifiers, erase) {
    std::vector<int> std_vector;
    ft::vector<int> ft_vector;

    for (int i = 1; i <= 12; i++) {
        std_vector.push_back(i);
        ft_vector.push_back(i);
    }

    EXPECT_EQ(*std_vector.erase (std_vector.begin() + 5),
              *ft_vector.erase(ft_vector.begin() + 5));
    checkTwoVectors(std_vector, ft_vector);

    EXPECT_EQ(*std_vector.erase (std_vector.begin() + 3),
              *ft_vector.erase(ft_vector.begin() + 3));
    checkTwoVectors(std_vector, ft_vector);

    EXPECT_EQ(*std_vector.erase (std_vector.begin()),
              *ft_vector.erase(ft_vector.begin()));
    checkTwoVectors(std_vector, ft_vector);

    EXPECT_EQ(*std_vector.erase (std_vector.end() - 2),
              *ft_vector.erase(ft_vector.end() - 2));
    checkTwoVectors(std_vector, ft_vector);

    printTwoVectors(std_vector, ft_vector);
    EXPECT_EQ(*std_vector.erase (std_vector.begin(), std_vector.begin() + 6),
              *ft_vector.erase (ft_vector.begin(), ft_vector.begin() + 6));
    checkTwoVectors(std_vector, ft_vector);
}

TEST(Vector_Modifiers, swap) {
    std::vector<int> foo (3,100);
    std::vector<int> bar (5,200);
    foo.swap(bar);

    ft::vector<int> foo2 (3,100);
    ft::vector<int> bar2 (5,200);
    foo2.swap(bar2);

    checkTwoVectors(foo, foo2);
    checkTwoVectors(bar, bar2);
}

TEST(Vector_Modifiers, clear) {
    std::vector<int> std_vector;
    std_vector.push_back (100);
    std_vector.push_back (200);
    std_vector.push_back (300);

    ft::vector<int> ft_vector;
    ft_vector.push_back (100);
    ft_vector.push_back (200);
    ft_vector.push_back (300);

    checkTwoVectors(std_vector, ft_vector);

    std_vector.clear();
    std_vector.push_back (1101);
    std_vector.push_back (2202);

    ft_vector.clear();
    ft_vector.push_back (1101);
    ft_vector.push_back (2202);

    checkTwoVectors(std_vector, ft_vector);
}


/* Non-member function overloads */
TEST(Vector_NonMember_Fuction_Overloads, relational_operators) {
    int std_ints[] = {10, 20, 30};
    std::vector<int> a(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    std::vector<int> b(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    int std_ints2[] = {10, 20};
    std::vector<int> c(std_ints2, std_ints2 + sizeof(std_ints2) / sizeof(int) );

    int ft_ints[] = {10, 20, 30};
    ft::vector<int> a2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int) );
    ft::vector<int> b2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int));
    int ft_ints2[] = {10, 20};
    ft::vector<int> c2(ft_ints2, ft_ints2 + sizeof(ft_ints2) / sizeof(int));

    EXPECT_EQ(a == b, a2 == b2);
    EXPECT_EQ(b != c, b2 != c2);
    EXPECT_EQ(b < c, b2 < c2);
    EXPECT_EQ(c > b, c2 > b2);
    EXPECT_EQ(a <= b, a2 <= b2);
    EXPECT_EQ(a >= b, a2 >= b2);
}

TEST(Vector_NonMember_Fuction_Overloads, swap) {
    std::vector<int> foo (3,100);
    std::vector<int> bar (5,200);
    std::swap(foo, bar);

    ft::vector<int> foo2 (3,100);
    ft::vector<int> bar2 (5,200);
    ft::swap(foo2,bar2);

    checkTwoVectors(foo, foo2);
    checkTwoVectors(bar, bar2);
}
