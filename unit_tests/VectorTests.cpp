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
    EXPECT_EQ(std_vector.capacity(), ft_vector.capacity());
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
    printTwoVectors(std_vector2, ft_vector2);


//    std::list<int> *std_list3 = new std::list<int>(10, 12);
//    ft::list<int> *ft_list3 = new ft::list<int>(10, 12);
//    std::list<int> *std_list4 = new std::list<int> (std_list3->begin(), --std_list3->end());
//    ft::list<int> *ft_list4 = new ft::list<int> (ft_list3->begin(), --ft_list3->end());
//    checkTwoListsAndDelete(std_list4, ft_list4);
//    delete std_list3;
//    delete ft_list3;
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