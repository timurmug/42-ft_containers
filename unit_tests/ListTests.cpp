#include <gtest/gtest.h>
#include <list>
#include "list.hpp"
#include <cmath>
#include <iostream>

template <typename T, typename S>
void checkTwoListsAndDelete(T *std_list, S *ft_list) {
    typename T::iterator std_it = std_list->begin();
    typename T::iterator std_ite = std_list->end();
    typename S::iterator ft_it = ft_list->begin();
    typename S::iterator ft_ite = ft_list->end();
    EXPECT_EQ(std_list->size(), ft_list->size());
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
    EXPECT_EQ(std_list.size(), ft_list.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

template <typename T, typename S>
void printTwoLists(T & std_list, S & ft_list)  {
    typename T::iterator std_it = std_list.begin();
    typename T::iterator std_ite = std_list.end();
    typename S::iterator ft_it = ft_list.begin();
    typename S::iterator ft_ite = ft_list.end();
    std::cout << "std_list:\t";
    while (std_it != std_ite)
        std::cout << ' ' << *std_it++;
    std::cout << std::endl;
    std::cout << "ft_list:\t";
    while (ft_it != ft_ite)
        std::cout << ' ' << *ft_it++;
    std::cout << std::endl;
}

/* Constructor, destructor, operator= */
TEST(List_Base, empty_constructor) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor2) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    std_list->push_back(1);
    ft_list->push_back(1);
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor3) {
    std::list<int> *std_list = new std::list<int>();
    ft::list<int> *ft_list = new ft::list<int>();
    for (int i = 0; i < 5; i++) {
        std_list->push_back(i);
        ft_list->push_back(i);
    }
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor4) {
    std::list<char> *std_list = new std::list<char>();
    ft::list<char> *ft_list = new ft::list<char>();
    std_list->push_back('a');
    ft_list->push_back('a');
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor5) {
    std::list<char> *std_list = new std::list<char>();
    ft::list<char> *ft_list = new ft::list<char>();
    for (char i = 'a'; i < 'e'; i++) {
        std_list->push_back(i);
        ft_list->push_back(i);
    }
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor6) {
    std::list<std::string> *std_list = new std::list<std::string>();
    ft::list<std::string> *ft_list = new ft::list<std::string>();
    std_list->push_back("abc");
    ft_list->push_back("abc");
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, empty_constructor7) {
    std::list<std::string> *std_list = new std::list<std::string>();
    ft::list<std::string> *ft_list = new ft::list<std::string>();
    int n = 4;
    while (n--) {
        std_list->push_back("abc");
        ft_list->push_back("abc");
    }
    checkTwoListsAndDelete(std_list, ft_list);
}

TEST(List_Base, fill_constructor1) {
    std::list<int> *std_list = new std::list<int>(4);
    ft::list<int> *ft_list = new ft::list<int>(4);
    checkTwoListsAndDelete(std_list, ft_list);
}
TEST(List_Base, fill_constructor2) {
    std::list<std::string> *std_list = new std::list<std::string>(10, "abc");
    ft::list<std::string> *ft_list = new ft::list<std::string>(10, "abc");
    checkTwoListsAndDelete(std_list, ft_list);
}

TEST(List_Base, range_constructor) {
    std::list<std::string> *std_list = new std::list<std::string>(10, "abc");
    ft::list<std::string> *ft_list = new ft::list<std::string>(10, "abc");
    std::list<std::string> *std_list2 = new std::list<std::string> (std_list->begin(), --std_list->end());
    ft::list<std::string> *ft_list2 = new ft::list<std::string> (ft_list->begin(), --ft_list->end());
    checkTwoListsAndDelete(std_list2, ft_list2);
    delete std_list;
    delete ft_list;

    std::list<int> *std_list3 = new std::list<int>(10, 12);
    ft::list<int> *ft_list3 = new ft::list<int>(10, 12);
    std::list<int> *std_list4 = new std::list<int> (std_list3->begin(), --std_list3->end());
    ft::list<int> *ft_list4 = new ft::list<int> (ft_list3->begin(), --ft_list3->end());
    checkTwoListsAndDelete(std_list4, ft_list4);
    delete std_list3;
    delete ft_list3;
}

TEST(List_Base, copy_constructor) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    std::list<int> std_list2(std_list);
    ft::list<int> ft_list2(ft_list);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
}
TEST(List_Base, copy_constructor2) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    for (int i = 0; i < 4; i++) {
        std_list.push_back(i);
        ft_list.push_back(i);
    }
    std::list<int> std_list2(std_list);
    ft::list<int> ft_list2(ft_list);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
}

TEST(List_Base, construct_from_arrays) {
    double mydoubles[] = {16.3, 2, 77.5, 29};
    double mydoubles2[] = {16.3, 2, 77.5, 29};
    std::list<double> std_list (mydoubles, mydoubles + sizeof(mydoubles) / sizeof(double) );
    ft::list<double> ft_list (mydoubles2, mydoubles2 + sizeof(mydoubles2) / sizeof(double) );
    checkTwoLists(std_list, ft_list);
}
TEST(List_Base, operator_equal) {
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
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
}


/* Iterators */
TEST(List_Iterators, iterator) {
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

TEST(List_Iterators, const_iterator) {
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

TEST(List_Iterators, reverse_iterator) {
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

TEST(List_Iterators, const_reverse_iterator) {
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


/* Capacity and Element access */
TEST(List_Capacity_And_Element_Access, empty) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    EXPECT_EQ(std_list.empty(), ft_list.empty());

    std::list<char> std_list2(2, 'a');
    ft::list<char> ft_list2(2, 'a');
    EXPECT_EQ(std_list2.empty(), ft_list2.empty());

    int n = 5;
    std::list<char> std_list3(n, 'a');
    ft::list<char> ft_list3(n, 'a');
    std_list3.remove('a');
    ft_list3.remove('a');
    EXPECT_EQ(std_list3.empty(), ft_list3.empty());

    std::list<int> std_list4;
    ft::list<int> ft_list4;
    int sum1(0);
    int sum2(0);

    for (int i = 1;i <= 10; ++i) {
        std_list4.push_back(i);
        ft_list4.push_back(i);
    }

    while (!std_list4.empty() && !ft_list4.empty())
    {
        sum1 += std_list4.front();
        sum2 += ft_list4.front();
        std_list4.pop_front();
        ft_list4.pop_front();
        checkTwoLists(std_list4, ft_list4);
    }
    ASSERT_EQ(sum1, sum2);
    checkTwoLists(std_list4, ft_list4);
}

TEST(List_Capacity_And_Element_Access, size) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    ASSERT_EQ(std_list.size(), ft_list.size());

    std::list<char> std_list2(20, 'a');
    ft::list<char> ft_list2(20, 'a');
    ASSERT_EQ(std_list2.size(), ft_list2.size());

    std::list<char> std_list3(5, 'a');
    ft::list<char> ft_list3(5, 'a');
    ASSERT_EQ(std_list3.size(), ft_list3.size());

    std::list<int> std_list4(100);
    ft::list<int> ft_list4(100);
    ASSERT_EQ(std_list4.size(), ft_list4.size());
}

TEST(List_Capacity_And_Element_Access, max_size) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    EXPECT_EQ(std_list.max_size(), ft_list.max_size());

    std::list<char> std_list2(20, 'a');
    ft::list<char> ft_list2(20, 'a');
    EXPECT_EQ(std_list2.max_size(), ft_list2.max_size());

    std::list<double> std_list3(5);
    ft::list<double> ft_list3(5);
    ASSERT_EQ(std_list3.max_size(), ft_list3.max_size());
}

TEST(List_Capacity_And_Element_Access, front) {
    std::list<int> std_list;
    ft::list<int> ft_list;

    std_list.push_back(77);
    ft_list.push_back(77);
    std_list.push_back(22);
    ft_list.push_back(22);

    int const std_front_const = std_list.front();
    int const ft_front_const = ft_list.front();
    EXPECT_EQ(std_front_const, ft_front_const);
    std_list.front() -= std_list.back();
    ft_list.front() -= ft_list.back();
    EXPECT_EQ(std_list.front(), ft_list.front());
}

TEST(List_Capacity_And_Element_Access, back) {
    std::list<int> std_list;
    ft::list<int> ft_list;

    std_list.push_back(10);
    while (std_list.back() != 0) {
        std_list.push_back ( std_list.back() - 1 );
    }
    ft_list.push_back(10);
    while (ft_list.back() != 0)
        ft_list.push_back ( ft_list.back() - 1 );
    int const std_back_const = std_list.back();
    int const ft_back_const = ft_list.back();
    EXPECT_EQ(std_back_const, ft_back_const);
    checkTwoLists(std_list, ft_list);
}


/* Modifiers */
TEST(List_Modifiers, assign) {
    std::list<char> std_list;
    std::list<char> std_list2;
    ft::list<char> ft_list;
    ft::list<char> ft_list2;

    std_list.assign(7,'a');
    ft_list.assign(7,'a');
    checkTwoLists(std_list, ft_list);

    std_list2.assign (std_list.begin(), std_list.end());
    ft_list2.assign (ft_list.begin(), ft_list.end());
    checkTwoLists(std_list2, ft_list2);

    int myints[] = {1776, 7, 4};
    std_list.assign(myints,myints + 3);
    ft_list.assign(myints,myints + 3);
    checkTwoLists(std_list, ft_list);
}

TEST(List_Modifiers, push_front) {
    std::list<int> std_list(2);
    ft::list<int> ft_list(2);
    std_list.push_front(200);
    std_list.push_front(300);
    ft_list.push_front(200);
    ft_list.push_front(300);
    checkTwoLists(std_list, ft_list);

    char symbol = 'a';
    std::list<char> std_list2(symbol);
    std::list<char> ft_list2(symbol);
    while (symbol != 'e') {
        std_list2.push_front(symbol);
        ft_list2.push_front(symbol);
        symbol++;
    }
    checkTwoLists(std_list2, ft_list2);
}

TEST(List_Modifiers, pop_front) {
    std::list<int> std_list(5);
    ft::list<int> ft_list(5);

    while (!std_list.empty() && !ft_list.empty()){
        std_list.pop_front();
        ft_list.pop_front();
        checkTwoLists(std_list, ft_list);
    }
    checkTwoLists(std_list, ft_list);
}

TEST(List_Modifiers, push_back) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    int n = 10;
    while (n--) {
        std_list.push_back(n);
        ft_list.push_back(n);
        checkTwoLists(std_list, ft_list);
    }
    checkTwoLists(std_list, ft_list);
}

TEST(List_Modifiers, pop_back) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    int n = 100;
    while (n != 400) {
        std_list.push_back (n);
        ft_list.push_back (n);
        n += 100;
    }

    int sum1 (0);
    int sum2 (0);
    while (!std_list.empty() && !ft_list.empty())
    {
        sum1 += std_list.back();
        sum2 += ft_list.back();
        std_list.pop_back();
        ft_list.pop_back();
        checkTwoLists(std_list, ft_list);
    }
    checkTwoLists(std_list, ft_list);
    ASSERT_EQ(sum1, sum2);
}

TEST(List_Modifiers, insert) {
    std::list<char> std_list;
    ft::list<char> ft_list;
    std::list<char>::iterator std_it;
    ft::list<char>::iterator ft_it;

    for (char i = 'a'; i <= 'e'; ++i) {
        std_list.push_back(i);
        ft_list.push_back(i);
    }

    std_it = std_list.begin();
    ft_it = ft_list.begin();
    ++std_it;
    ++ft_it;
    ASSERT_EQ(*std_list.insert (std_it, 'w'), *ft_list.insert (ft_it, 'w'));

    std_list.insert (std_it, 2, 'r');
    ft_list.insert(ft_it, 2, 'r');

    --std_it;
    --ft_it;

    std::list<char> std_list_to_copy;
    ft::list<char> ft_list_to_copy;
    for (char i = '1'; i <= '4'; ++i) {
        std_list_to_copy.push_back(i);
        ft_list_to_copy.push_back(i);
    }
    std_list.insert (std_it, std_list_to_copy.begin(), std_list_to_copy.end());
    ft_list.insert (ft_it, ft_list_to_copy.begin(), ft_list_to_copy.end());
    checkTwoLists(std_list, ft_list);
}

TEST(List_Modifiers, erase) {
    std::list<int> std_list;
    ft::list<int> ft_list;

    for (int i = 1; i < 10; ++i) {
        std_list.push_back(i * 10);
        ft_list.push_back(i * 10);
    }
    // 10 20 30 40 50 60 70 80 90

    std::list<int>::iterator std_it = std_list.begin();
    std::list<int>::iterator std_ite = std_list.end();
    ft::list<int>::iterator ft_it = ft_list.begin();
    ft::list<int>::iterator ft_ite = ft_list.end();
    std_it++;
    ft_it++;
    int n = 3;
    while (n--) {
        std_ite--;
        ft_ite--;
    }
    std::list<int>::iterator std_it2 = std_list.erase(std_it);
    ft::list<int>::iterator ft_it2 = ft_list.erase(ft_it);
    std::list<int>::iterator std_ite2 = std_list.erase(std_ite);
    ft::list<int>::iterator ft_ite2 = ft_list.erase(ft_ite);
    EXPECT_EQ(*std_it2, *ft_it2);
    EXPECT_EQ(*std_ite2, *ft_ite2);
    checkTwoLists(std_list, ft_list);
    // 10 30 40 50 60 80 90

    ++std_it2;
    ft_it2++;
    --std_ite2;
    --ft_ite2;
    EXPECT_EQ(*std_list.erase(std_it2, std_ite2), *ft_list.erase(ft_it2, ft_ite2));
    checkTwoLists(std_list, ft_list);
    // 10 30 60 80 90
}

TEST(List_Modifiers, swap) {
    std::list<char> std_first (3,'a');
    ft::list<char> ft_first (3,'a');
    std::list<char> std_second (5,'b');
    ft::list<char> ft_second (5,'b');

    std_first.swap(std_second);
    ft_first.swap(ft_second);
    checkTwoLists(std_first, ft_first);
    checkTwoLists(std_second, ft_second);
}

TEST(List_Modifiers, resize) {
    std::list<int>  std_list;
    ft::list<int>   ft_list;

    for (int i = 1; i < 10; ++i) {
        std_list.push_back(i);
        ft_list.push_back(i);
    }

    std_list.resize(5);
    ft_list.resize(5);
    std_list.resize(8, 100);
    ft_list.resize(8, 100);
    std_list.resize(12);
    ft_list.resize(12);

    checkTwoLists(std_list, ft_list);
}

TEST(List_Modifiers, clear) {
    std::list<int> std_list;
    ft::list<int> ft_list;

    std_list.push_back (100);
    std_list.push_back (200);
    std_list.push_back (300);
    ft_list.push_back (100);
    ft_list.push_back (200);
    ft_list.push_back (300);

    std_list.clear();
    ft_list.clear();
    checkTwoLists(std_list, ft_list);

    std_list.push_back (1101);
    std_list.push_back (2202);
    ft_list.push_back (1101);
    ft_list.push_back (2202);
    checkTwoLists(std_list, ft_list);
}


/* Operations */
TEST(List_Operations, splice1) {
    std::list<int> std_list;
    std::list<int> std_list2;
    ft::list<int> ft_list;
    ft::list<int> ft_list2;

    std::list<int>::iterator std_it = std_list.begin();
    ft::list<int>::iterator ft_it = ft_list.begin();
    std_list.splice (std_it, std_list);
    ft_list.splice (ft_it, ft_list);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std_it, *ft_it);

    for (int i=1; i<=3; ++i) {
        std_list2.push_back(i * 10);
        ft_list2.push_back(i * 10);
    }
    std_list.splice (std_it, std_list2);
    ft_list.splice (ft_it, ft_list2);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    std_it = std_list.begin();
    ft_it = ft_list.begin();
    std_it++;
    ft_it++;
    std_list.splice (std_it, std_list2);
    ft_list.splice (ft_it, ft_list2);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std_it, *ft_it);

    for (int i=1; i<=3; ++i) {
        std_list2.push_back(i * 10);
        ft_list2.push_back(i * 10);
    }
    std_list.splice (std_list.begin(), std_list2);
    ft_list.splice (ft_list.begin(), ft_list2);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std_it, *ft_it);

    for (int i=1; i<=3; ++i) {
        std_list2.push_back(i * 10);
        ft_list2.push_back(i * 10);
    }
    std_list.splice (std_list.end(), std_list2);
    ft_list.splice (ft_list.end(), ft_list2);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std_it, *ft_it);
}
TEST(List_Operations, splice2) {
    std::list<int> std_list;
    std::list<int> std_list2;
    ft::list<int> ft_list;
    ft::list<int> ft_list2;

    std::list<int>::iterator std_it = std_list.begin();
    ft::list<int>::iterator ft_it = ft_list.begin();
    std_list.splice (std_it, std_list, std_it);
    ft_list.splice (ft_it, ft_list, ft_it);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std_it, *ft_it);

    for (int i=1; i<=5; ++i) {
        std_list2.push_back(i * 10);
        ft_list2.push_back(i * 10);
    }
    std::list<int>::iterator std2_ite = std_list2.end();
    ft::list<int>::iterator ft2_ite = ft_list2.end();
    int n = 3;
    while (n--) {
        std2_ite--;
        ft2_ite--;
    }
    std_list.splice (std_it, std_list2, std2_ite);
    ft_list.splice (ft_it, ft_list2, ft2_ite);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std2_ite, *ft2_ite);

    std_it = std_list.begin();
    ft_it = ft_list.begin();
    std_it++;
    ft_it++;
    std_list.splice (std_it, std_list2, std_list2.begin());
    ft_list.splice (ft_it, ft_list2, ft_list2.begin());
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    for (int i=1; i<=3; ++i) {
        std_list2.push_back(i * 10);
        ft_list2.push_back(i * 10);
    }
    std2_ite = std_list2.end();
    ft2_ite = ft_list2.end();
    n = 2;
    while (n--) {
        std2_ite--;
        ft2_ite--;
    }
    std_list.splice (std_list.begin(), std_list2, std2_ite);
    ft_list.splice (ft_list.begin(), ft_list2, ft2_ite);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std2_ite, *ft2_ite);
}
TEST(List_Operations, splice3) {
    std::list<int> std_list;
    std::list<int> std_list2;
    ft::list<int> ft_list;
    ft::list<int> ft_list2;

    std_list.splice (std_list.begin(), std_list, std_list.begin(), std_list.end());
    ft_list.splice (ft_list.begin(), ft_list, ft_list.begin(), ft_list.end());
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    std_list.splice (std_list.begin(), std_list2, std_list2.begin(), std_list2.end());
    ft_list.splice (ft_list.begin(), ft_list2, ft_list2.begin(), ft_list2.end());
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    for (int i = 0; i < 5; i++) {
        std_list2.push_back(i);
        ft_list2.push_back(i);
    }
    std_list.splice (std_list.begin(), std_list2, std_list2.begin(), std_list2.end());
    ft_list.splice (ft_list.begin(), ft_list2, ft_list2.begin(), ft_list2.end());
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    for (int i = 0; i < 5; i++) {
        std_list2.push_back(i);
        ft_list2.push_back(i);
    }
    std::list<int>::iterator std2_it = std_list2.begin();
    std2_it++;
    ft::list<int>::iterator ft2_it = ft_list2.begin();
    ft2_it++;
    std::list<int>::iterator std2_ite = std_list2.end();
    std2_ite--;
    ft::list<int>::iterator ft2_ite = ft_list2.end();
    ft2_ite--;
    std_list.splice (std_list.begin(), std_list2, std2_it, std2_ite);
    ft_list.splice (ft_list.begin(), ft_list2, ft2_it, ft2_ite);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
    EXPECT_EQ(*std2_it, *ft2_it);
    EXPECT_EQ(*std2_ite, *ft2_ite);
}

TEST(List_Operations, remove) {
    int myints[] = {17, 13,89,7,14, 13, 13};
    std::list<int> std_list (myints,myints + 4);
    ft::list<int> ft_list (myints,myints + 4);

    std_list.remove(89);
    ft_list.remove(89);
    std_list.remove(15);
    ft_list.remove(15);
    std_list.remove(89);
    ft_list.remove(89);
    checkTwoLists(std_list, ft_list);
}

bool single_digit (const int& value) { return (value < 10); }
struct is_odd {
    bool operator() (const int& value) { return (value % 2) == 1; }
};
TEST(List_Operations, remove_if) {
    int myints[] = {15,36,7,17,20,39,4,1};
    std::list<int> std_list (myints, myints + 8);   // 15 36 7 17 20 39 4 1
    ft::list<int> ft_list (myints, myints + 8);   // 15 36 7 17 20 39 4 1

    std_list.remove_if(single_digit);           // 15 36 17 20 39
    ft_list.remove_if(single_digit);           // 15 36 17 20 39

    std_list.remove_if (is_odd());               // 36 20
    ft_list.remove_if (is_odd());               // 36 20
    checkTwoLists(std_list, ft_list);
}

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }
struct is_near {
    bool operator() (double first, double second)
    { return (fabs(first-second)<5.0); }
};
TEST(List_Operations, unique) {
    double mydoubles[] = { 2.72,  3.14, 12.15, 12.77, 12.77, 15.3,  72.25, 72.25, 73.0,  73.35 };
    std::list<double> std_list (mydoubles,mydoubles + 10);
    ft::list<double> ft_list (mydoubles, mydoubles + 10);

    std_list.unique();
    ft_list.unique();

    std_list.unique (same_integral_part);
    ft_list.unique (same_integral_part);

    std_list.unique (is_near());
    ft_list.unique (is_near());
    checkTwoLists(std_list, ft_list);
}

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }
TEST(List_Operations, merge) {
    std::list<double> std_list, std_list2;
    std_list.push_back (3.1);
    std_list.push_back (2.2);
    std_list.push_back (2.9);
    std_list2.push_back (3.7);
    std_list2.push_back (7.1);
    std_list2.push_back (1.4);
    ft::list<double> ft_list, ft_list2;
    ft_list.push_back (3.1);
    ft_list.push_back (2.2);
    ft_list.push_back (2.9);
    ft_list2.push_back (3.7);
    ft_list2.push_back (7.1);
    ft_list2.push_back (1.4);
    std_list.sort();
    std_list2.sort();
    ft_list.sort();
    ft_list2.sort();

    std_list.merge(std_list2);
    ft_list.merge(ft_list2);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);

    std_list2.push_back (2.1);
    std_list.merge(std_list2, mycomparison);
    ft_list2.push_back (2.1);
    ft_list.merge(ft_list2, mycomparison);
    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
}

bool compare_nocase (const std::string& first, const std::string& second)
{
    unsigned int i=0;
    while ( (i<first.length()) && (i<second.length()) )
    {
        if (tolower(first[i])<tolower(second[i])) return true;
        else if (tolower(first[i])>tolower(second[i])) return false;
        ++i;
    }
    return ( first.length() < second.length() );
}
TEST(List_Operations, sort) {
    std::list<std::string> std_list;
    ft::list<std::string> ft_list;
    std_list.push_back ("one");
    std_list.push_back ("two");
    std_list.push_back ("Three");
    std_list.push_back ("abc");
    std_list.sort();
    ft_list.push_back ("one");
    ft_list.push_back ("two");
    ft_list.push_back ("Three");
    ft_list.push_back ("abc");
    ft_list.sort();
    checkTwoLists(std_list, ft_list);

    std_list.sort(compare_nocase);
    ft_list.sort(compare_nocase);
    checkTwoLists(std_list, ft_list);

    double mydoubles[] = {500, 16.3, 345, -10, 2, 77.5, 29, 0, -100, 321};
    double mydoubles2[] = {500, 16.3, 345, -10, 2, 77.5, 29, 0, -100, 321};
    std::list<double> std_list2 (mydoubles, mydoubles + sizeof(mydoubles) / sizeof(double) );
    ft::list<double> ft_list2 (mydoubles2, mydoubles2 + sizeof(mydoubles2) / sizeof(double) );
    std_list2.sort();
    ft_list2.sort();
    checkTwoLists(std_list2, ft_list2);
}

TEST(List_Operations, reverse) {
    std::list<int> std_list;
    for (int i = 1; i < 10; ++i)
        std_list.push_back(i);
    ft::list<int> ft_list;
    for (int i = 1; i < 10; ++i)
        ft_list.push_back(i);

    std_list.reverse();
    ft_list.reverse();
    checkTwoLists(std_list, ft_list);
}


/* Non-member function overloads */
TEST(List_NonMember_Fuction_Overloads, relational_operators) {
    int std_ints[] = {10, 20, 30};
    std::list<int> a(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    std::list<int> b(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    int std_ints2[] = {10, 20};
    std::list<int> c(std_ints2, std_ints2 + sizeof(std_ints2) / sizeof(int) );

    int ft_ints[] = {10, 20, 30};
    ft::list<int> a2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int) );
    ft::list<int> b2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int));
    int ft_ints2[] = {10, 20};
    ft::list<int> c2(ft_ints2, ft_ints2 + sizeof(ft_ints2) / sizeof(int));

    EXPECT_EQ(a == b, a2 == b2);
    EXPECT_EQ(b != c, b2 != c2);
    EXPECT_EQ(b < c, b2 < c2);
    EXPECT_EQ(c > b, c2 > b2);
    EXPECT_EQ(a <= b, a2 <= b2);
    EXPECT_EQ(a >= b, a2 >= b2);
}

TEST(List_NonMember_Fuction_Overloads, swap) {
    std::list<char> std_list (3, 'a');
    std::list<char> std_list2 (5, 'b');
    std::swap(std_list, std_list2);

    ft::list<char> ft_list (3,'a');
    ft::list<char> ft_list2 (5,'b');
    ft::swap(ft_list, ft_list2);

    checkTwoLists(std_list, ft_list);
    checkTwoLists(std_list2, ft_list2);
}
