#include <gtest/gtest.h>
#include <list>
#include "list.hpp"

template <typename T, typename S>
void checkTwoListsAndDelete(T *std_list, S *ft_list) {
    typename T::iterator std_it = std_list->begin();
    typename T::iterator std_ite = std_list->end();
    typename S::iterator ft_it = ft_list->begin();
    typename S::iterator ft_ite = ft_list->end();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    delete std_list;
    delete ft_list;
}

template <typename T, typename S>
void checkTwoLists(T & std_list, S & ft_list) {
    typename T::iterator std_it = std_list.begin();
    typename T::iterator std_ite = std_list.end();
    typename S::iterator ft_it = ft_list.begin();
    typename S::iterator ft_ite = ft_list.end();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}


/* Constructor, destructor, operator= */
TEST(ListBase, empty_constructor) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor2) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    std_list->push_back(1);
    ft_list->push_back(1);
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor3) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    for (int i = 0; i < 5; i++) {
        std_list->push_back(i);
        ft_list->push_back(i);
    }
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor4) {

    std::list<char> *std_list = new std::list<char>();
    ft::list<char> *ft_list = new ft::list<char>();
    std_list->push_back('a');
    ft_list->push_back('a');
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor5) {
    std::list<char> *std_list = new std::list<char>();
    ft::list<char> *ft_list = new ft::list<char>();
    for (char i = 'a'; i < 'e'; i++) {
        std_list->push_back(i);
        ft_list->push_back(i);
    }
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor6) {
    std::list<std::string> *std_list = new std::list<std::string>();
    ft::list<std::string> *ft_list = new ft::list<std::string>();
    std_list->push_back("abc");
    ft_list->push_back("abc");
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, empty_constructor7) {
    std::list<std::string> *std_list = new std::list<std::string>();
    ft::list<std::string> *ft_list = new ft::list<std::string>();
    int n = 4;
    while (n--) {
        std_list->push_back("abc");
        ft_list->push_back("abc");
    }
    checkTwoListsAndDelete(std_list, ft_list);
}

TEST(ListBase, fill_constructor1) {
    std::list<int> *std_list = new std::list<int>(4);
    ft::list<int> *ft_list = new ft::list<int>(4);
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(ListBase, fill_constructor2) {
    std::list<std::string> *std_list = new std::list<std::string>(10, "abc");
    ft::list<std::string> *ft_list = new ft::list<std::string>(10, "abc");
    checkTwoListsAndDelete(std_list, ft_list);
}

TEST(ListBase, range_constructor) {
    std::list<std::string> *std_list = new std::list<std::string>(10, "abc");
    ft::list<std::string> *ft_list = new ft::list<std::string>(10, "abc");
    std::list<std::string> *std_list2 = new std::list<std::string> (std_list->begin(), --std_list->end());
    ft::list<std::string> *ft_list2 = new ft::list<std::string> (ft_list->begin(), --ft_list->end());
    checkTwoListsAndDelete(std_list2, ft_list2);
    delete std_list;
    delete ft_list;
}

TEST(ListBase, copy_constructor) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    std::list<int> std_list2(std_list);
    ft::list<int> ft_list2(ft_list);
    checkTwoLists(std_list2, ft_list2);
}
TEST(ListBase, copy_constructor2) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    for (int i = 0; i < 4; i++) {
        std_list.push_back(i);
        ft_list.push_back(i);
    }
    std::list<int> std_list2(std_list);
    ft::list<int> ft_list2(ft_list);
    checkTwoLists(std_list2, ft_list2);
}

TEST(ListBase, construct_from_arrays) {
    double mydoubles[] = {16.3, 2, 77.5, 29};
    double mydoubles2[] = {16.3, 2, 77.5, 29};
    std::list<double> std_list (mydoubles, mydoubles + sizeof(mydoubles) / sizeof(double) );
    ft::list<double> ft_list (mydoubles2, mydoubles2 + sizeof(mydoubles2) / sizeof(double) );
    checkTwoLists(std_list, ft_list);
}
TEST(ListBase, operator_equal) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    std_list.push_back(1);
    ft_list.push_back(1);

    std::list<int> std_list2;
    ft::list<int> ft_list2;
    std_list.push_back(2);
    ft_list.push_back(2);
    std_list2 = std_list;
    ft_list2 = ft_list;
    checkTwoLists(std_list2, ft_list2);
}


/* Iterators */
TEST(ListIterators, iterator) {

    int n = 10;
    std::list<std::string> std_list;
    ft::list<std::string> ft_list;
    while (n--) {
        std_list.push_back("abc");
        ft_list.push_back("abc");
    }
    std::list<std::string>::iterator std_it = std_list.begin();
    std::list<std::string>::iterator std_ite = std_list.end();
    ft::list<std::string>::iterator ft_it = ft_list.begin();
    ft::list<std::string>::iterator ft_ite = ft_list.end();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

TEST(ListIterators, const_iterator) {
    int n = 'a';
    std::list<char> std_list;
    ft::list<char> ft_list;
    while (n++ != 'm') {
        std_list.push_back(n);
        ft_list.push_back(n);
    }
    std::list<char>::const_iterator std_it = std_list.begin();
    std::list<char>::const_iterator std_ite = std_list.end();
    ft::list<char>::const_iterator ft_it = ft_list.begin();
    ft::list<char>::const_iterator ft_ite = ft_list.end();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

TEST(ListIterators, reverse_iterator) {
    int n = 10;
    std::list<int> std_list;
    ft::list<int> ft_list;
    while (n--) {
        std_list.push_back(n);
        ft_list.push_back(n);
    }
    std::list<int>::reverse_iterator std_it = std_list.rbegin();
    std::list<int>::reverse_iterator std_ite = std_list.rend();
    ft::list<int>::reverse_iterator ft_it = ft_list.rbegin();
    ft::list<int>::reverse_iterator ft_ite = ft_list.rend();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

TEST(ListIterators, const_reverse_iterator) {
    int n = 7;
    std::list<int> std_list;
    ft::list<int> ft_list;
    while (n--) {
        std_list.push_back(n);
        ft_list.push_back(n);
    }
    std::list<int>::const_reverse_iterator std_it = std_list.rbegin();
    std::list<int>::const_reverse_iterator std_ite = std_list.rend();
    ft::list<int>::const_reverse_iterator ft_it = ft_list.rbegin();
    ft::list<int>::const_reverse_iterator ft_ite = ft_list.rend();
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}


/* Capacity */