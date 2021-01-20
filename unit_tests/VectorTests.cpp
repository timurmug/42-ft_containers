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
    for (size_t i = 0; i <= std_vector.size(); i++)
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

//TEST(Vector_tests, unknown) {
//    std::string myints2[] = {"asfasd","second","thrid"};
//    std::vector<std::string> fifth2 (myints2, myints2 + sizeof(myints2) / sizeof(std::string) );
//    for (size_t i = 0 ; i < fifth2.size(); i++)
//        std::cout << fifth2[i] << " ";
//    std::cout << std::endl;
//    std::string *pointer = &fifth2[0];
//    pointer++;
//    pointer++;
//    pointer--;
//    std::cout << *pointer << " ";
//    FAIL();
//}