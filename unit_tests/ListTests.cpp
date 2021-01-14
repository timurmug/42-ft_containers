#include <gtest/gtest.h>
#include <list>
#include "list.hpp"

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
    std::cout << "std_list: ";
    while (std_it != std_ite)
        std::cout << ' ' << *std_it++;
    std::cout << std::endl;
    std::cout << "ft_list: ";
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
}

TEST(List_Base, copy_constructor) {
    std::list<int> std_list;
    ft::list<int> ft_list;
    std::list<int> std_list2(std_list);
    ft::list<int> ft_list2(ft_list);
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
    while (n--) {
        std_list3.remove('a');
        ft_list3.remove('a');
    }
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

}

