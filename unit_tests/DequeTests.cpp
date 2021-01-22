//
// Created by Quaro Tamarillo on 1/22/21.
//

#include "deque.hpp"
#include <deque>
#include "gtest/gtest.h"

template <typename T, typename S>
void checkTwoDeque(T & std_deque, S & dt_deque) {
    typename T::iterator std_it = std_deque.begin();
    typename T::iterator std_ite = std_deque.end();
    typename S::iterator ft_it = dt_deque.begin();
    typename S::iterator ft_ite = dt_deque.end();
    EXPECT_EQ(std_deque.size(), dt_deque.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite)
        EXPECT_EQ(*std_it++, *ft_it++);
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

template <typename T, typename S>
void printTwoDeque(T & std_deque, S & ft_deque) {
    typename T::iterator std_it = std_deque.begin();
    typename T::iterator std_ite = std_deque.end();
    typename S::iterator ft_it = ft_deque.begin();
    typename S::iterator ft_ite = ft_deque.end();
    std::cout << "std_deque:\t";
    while (std_it != std_ite)
        std::cout << ' ' << *std_it++;
    std::cout << std::endl;
    std::cout << "ft_deque:\t";
    while (ft_it != ft_ite)
        std::cout << ' ' << *ft_it++;
    std::cout << std::endl;
}

TEST(Deque_Base, empty_constructor) {
    std::deque<int>           std_deque;
    ft::deque<int>            ft_deque;
    checkTwoDeque(std_deque, ft_deque);
    for (int i = 0; i < 5; i++) {
        std_deque.push_back(1);
        ft_deque.push_back(1);
        checkTwoDeque(std_deque, ft_deque);
    }
    checkTwoDeque(std_deque, ft_deque);

    std::deque<char>           std_deque2;
    ft::deque<char>            ft_deque2;
    checkTwoDeque(std_deque2, ft_deque2);
    for (char i = 'a'; i < 'e'; i++) {
        std_deque2.push_back(i);
        ft_deque2.push_back(i);
        checkTwoDeque(std_deque2, ft_deque2);
    }
    checkTwoDeque(std_deque2, ft_deque2);

    std::deque<std::string>    std_deque3;
    ft::deque<std::string>     ft_deque3;
    checkTwoDeque(std_deque3, ft_deque3);
    int n = 4;
    while (n--) {
        std_deque3.push_back("abc");
        ft_deque3.push_back("abc");
    }
    checkTwoDeque(std_deque3, ft_deque3);

    std::deque<double>            std_deque5;
    ft::deque<double>             ft_deque5;
    checkTwoDeque(std_deque5, ft_deque5);
    for (int i = 0; i < 10; i++) {
        std_deque5.push_back(1);
        ft_deque5.push_back(1);
        checkTwoDeque(std_deque5, ft_deque5);
    }
    checkTwoDeque(std_deque5, ft_deque5);
}

TEST(Deque_Base, fill_constructor) {
    std::deque<int> a(4);
    ft::deque<int> b(4);
    checkTwoDeque(a, b);
    for (int i = 0; i < 10; i++) {
        a.push_back(1);
        b.push_back(1);
        checkTwoDeque(a, b);
    }
    checkTwoDeque(a, b);

    std::deque<std::string> a2(10, "abc");
    ft::deque<std::string> b2(10, "abc");
    checkTwoDeque(a2, b2);

    std::deque<char> a3(0);
    ft::deque<char> b3(0 );
    checkTwoDeque(a3, b3);
}

TEST(Deque_Base, range_constructor) {
    std::deque<std::string> a(10, "abc");
    ft::deque<std::string> b(10, "abc");
    checkTwoDeque(a, b);

    std::deque<std::string> a2(a.begin(), (a.end()));
    ft::deque<std::string> b2(b.begin(), (b.end()));
    checkTwoDeque(a, b);
    checkTwoDeque(a2, b2);

    std::deque<int> a3(10, 12);
    ft::deque<int> b3(10, 12);
    std::deque<int> a4(a3.begin(), --a3.end());
    ft::deque<int> b4(b3.begin(), --b3.end());
    checkTwoDeque(a3, b3);
    checkTwoDeque(a4, b4);
}

TEST(Deque_Base, copy_constructor) {
    std::deque<int> std_to_copy (4, 100);
    std::deque<int> a (std_to_copy);
    ft::deque<int> ft_to_copy (4, 100);
    ft::deque<int> b (ft_to_copy);
    checkTwoDeque(a, b);

    std::deque<int> a2;
    ft::deque<int> b2;
    for (int i = 0; i < 4; i++) {
        a2.push_back(i);
        b2.push_back(i);
    }
    std::deque<int> a3(a2);
    ft::deque<int> b3(b2);
    checkTwoDeque(a3, b3);
    checkTwoDeque(a2, b2);
}

TEST(Deque_Base, construct_from_arrays) {
    int myints[] = {16,2,77,29};
    std::deque<int> a (myints, myints + sizeof(myints) / sizeof(int) );
    ft::deque<int> b (myints, myints + sizeof(myints) / sizeof(int) );
    checkTwoDeque(a, b);
}

TEST(Deque_Base, operator_equal) {
    std::deque<int> a (3, 0);
    std::deque<int> a2 (5, 0);
    ft::deque<int> b (3, 0);
    ft::deque<int> b2 (5, 0);

    a = a2;
    a2 = std::deque<int>();
    b = b2;
    b2 = ft::deque<int>();
    checkTwoDeque(a, b);
    checkTwoDeque(a2, b2);

    std::deque<char> a3;
    ft::deque<char> b3;
    a3.push_back('1');
    b3.push_back('1');

    std::deque<char> a4;
    ft::deque<char> b4;
    a3.push_back('2');
    b3.push_back('2');
    a4 = a3;
    b4 = b3;
    checkTwoDeque(a3, b3);
    checkTwoDeque(a4, b4);
}


/* Iterators */
TEST(Deque_Iterators, iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::deque<std::string> a (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::deque<std::string> b (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoDeque(a, b);

    std::deque<std::string>::iterator std_it = a.begin();
    std::deque<std::string>::iterator std_ite = a.end();
    ft::deque<std::string>::iterator ft_it = b.begin();
    ft::deque<std::string>::iterator ft_ite = b.end();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.begin();
    ft_it = b.begin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.begin();
    ft_it = b.begin();
    std_ite = a.end();
    ft_ite = b.end();
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

    std_it = a.begin();
    ft_it = b.begin();
    for (size_t i = 0; i < a.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);
}

TEST(Deque_Iterators, const_iterator) {
    char chars[] = {'a','b','c', 'd', 'e', 'f', 'g', 'h', 'k'};
    std::deque<char> a (chars, chars + sizeof(chars) / sizeof(char) );
    ft::deque<char> b (chars, chars + sizeof(chars) / sizeof(char) );
    checkTwoDeque(a, b);

    std::deque<char>::const_iterator std_it = a.begin();
    std::deque<char>::const_iterator std_ite = a.end();
    ft::deque<char>::const_iterator ft_it = b.begin();
    ft::deque<char>::const_iterator ft_ite = b.end();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.begin();
    ft_it = b.begin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.begin();
    ft_it = b.begin();
    std_ite = a.end();
    ft_ite = b.end();
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

    std_it = a.begin();
    ft_it = b.begin();
    for (size_t i = 0; i < a.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);
}

TEST(Deque_Iterators, reverse_iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::deque<std::string> a (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::deque<std::string> b (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoDeque(a, b);

    std::deque<std::string>::reverse_iterator std_it = a.rbegin();
    std::deque<std::string>::reverse_iterator std_ite = a.rend();
    ft::deque<std::string>::reverse_iterator ft_it = b.rbegin();
    ft::deque<std::string>::reverse_iterator ft_ite = b.rend();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));
    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.rbegin();
    ft_it = b.rbegin();

    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_ite--;
        --std_ite;
        ft_ite--;
        --ft_ite;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

    std_it = a.rbegin();
    ft_it = b.rbegin();
    std_ite = a.rend();
    ft_ite = b.rend();
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

    std_it = a.rbegin();
    ft_it = b.rbegin();
    for (size_t i = 0; i < a.size(); i++)
        EXPECT_EQ(std_it[i], ft_it[i]);

    std::deque<int> a2 (5);
    ft::deque<int> b2 (5);
    std::deque<int>::reverse_iterator std_it2 = a2.rbegin();
    ft::deque<int>::reverse_iterator ft_it2 = b2.rbegin();
    int i = 0;
    int i2 = 0;
    for (std_it2 = a2.rbegin(); std_it2 != a2.rend(); ++std_it2)
        *std_it2 = ++i;
    for (ft_it2 = b2.rbegin(); ft_it2 != b2.rend(); ++ft_it2)
        *ft_it2 = ++i2;
    checkTwoDeque(a2, b2);

    std::deque<int> a3 (5);
    ft::deque<int> b3 (5);
    std::deque<int>::reverse_iterator std_it3 = a3.rbegin();
    ft::deque<int>::reverse_iterator ft_it3 = b3.rbegin();
    for (; std_it3 != a3.rend(); ++std_it3)
        *std_it3 = ++i;
    for (; ft_it3 != b3.rend(); ++ft_it3)
        *ft_it3 = ++i2;
    checkTwoDeque(a3, b3);
}

TEST(Deque_Iterators, const_reverse_iterator) {
    std::string strings[] = {"one","two","three", "four", "five", "six", "seven", "eight", "nine"};
    std::deque<std::string> a (strings, strings + sizeof(strings) / sizeof(std::string) );
    ft::deque<std::string> b (strings, strings + sizeof(strings) / sizeof(std::string) );
    checkTwoDeque(a, b);

    std::deque<std::string>::const_reverse_iterator std_it = a.rbegin();
    std::deque<std::string>::const_reverse_iterator std_ite = a.rend();
    ft::deque<std::string>::const_reverse_iterator ft_it = b.rbegin();
    ft::deque<std::string>::const_reverse_iterator ft_ite = b.rend();

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*(--std_ite), *(--ft_ite));
    while (std_it != std_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);

//    std_it = a.rbegin();
//    ft_it = b.rbegin();
//
//    while (std_it != std_ite) {
//        EXPECT_EQ(*std_it, *ft_it);
//        std_ite--;
//        --std_ite;
//        ft_ite--;
//        --ft_ite;
//    }
//    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
//
//    std_it = a.rbegin();
//    ft_it = b.rbegin();
//    std_ite = a.rend();
//    ft_ite = b.rend();
//    EXPECT_EQ(*(std_it + 3), *(ft_it + 3));
//    EXPECT_EQ(*(std_ite - 4), *(ft_ite - 4));
//
//    std_it += 2;
//    ft_it += 2;
//    std_ite -= 3;
//    ft_ite -= 3;
//    EXPECT_EQ(*std_it, *ft_it);
//    EXPECT_EQ(*std_ite, *ft_ite);
//    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
//    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
//    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
//    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
//    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
//    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);
//
//    std_it = std_ite;
//    ft_it = ft_ite;
//    EXPECT_EQ(*std_it, *ft_it);
//    EXPECT_EQ(*std_ite, *ft_ite);
//    EXPECT_EQ(std_it == std_ite, ft_it == ft_ite);
//    EXPECT_EQ(std_it != std_ite, ft_it != ft_ite);
//    EXPECT_EQ(std_it <= std_ite, ft_it <= ft_ite);
//    EXPECT_EQ(std_it >= std_ite, ft_it >= ft_ite);
//    EXPECT_EQ(std_it < std_ite, ft_it < ft_ite);
//    EXPECT_EQ(std_it > std_ite, ft_it > ft_ite);
//
//    std_it = a.rbegin();
//    ft_it = b.rbegin();
//    for (size_t i = 0; i < a.size(); i++)
//        EXPECT_EQ(std_it[i], ft_it[i]);
}


/* Capacity */
TEST(Deque_Capacity, size) {
    std::deque<int> a;
    ft::deque<int> b;
    EXPECT_EQ(a.size(), b.size());

    for (int i = 0; i < 10; i++) {
        a.push_back(i);
        b.push_back(i);
    }
    EXPECT_EQ(a.size(), b.size());
}

TEST(Deque_Capacity, max_size) {
    std::deque<int> a;
    ft::deque<int> b;
    EXPECT_EQ(a.max_size(), b.max_size());

    std::deque<int> a2(20, 2);
    ft::deque<int> b2(20, 2);
    EXPECT_EQ(a2.max_size(), b2.max_size());

    std::deque<double> a3(5);
    ft::deque<double> b3(5);
    for (int i=0; i<100; i++) {
        a3.push_back(i);
        b3.push_back(i);
    }
    EXPECT_EQ(a3.max_size(), b3.max_size());
}

TEST(Deque_Capacity, resize) {
    std::deque<int> a;
    ft::deque<int> b;
    for (int i = 1;i < 10; i++) {
        a.push_back(i);
        b.push_back(i);
    }

    a.resize(5);
    a.resize(8, 100);
    a.resize(12);
    a.resize(12);
    a.resize(11);
    b.resize(5);
    b.resize(8, 100);
    b.resize(12);
    b.resize(12);
    b.resize(11);
    checkTwoDeque(a, b);

    a.resize(0);
    b.resize(0);
    checkTwoDeque(a, b);
    EXPECT_EQ(a.empty(), b.empty());
}

TEST(Deque_Capacity, empty) {
    std::deque<int> a;
    ft::deque<int> b;
    EXPECT_EQ(a.empty(), b.empty());

    a.push_back(12);
    b.push_back(12);
    EXPECT_EQ(a.empty(), b.empty());
}


/* Element access */
TEST(Deque_Element_acces, operator_) {
    std::deque<int> a (10);
    std::deque<int>::size_type sz = a.size();
    ft::deque<int> b (10);
    ft::deque<int>::size_type sz2 = b.size();

    for (unsigned i = 0; i < sz; i++) {
        a[i] = i;
        b[i] = i;
    }

    for (unsigned i = 0; i < sz / 2; i++)
    {
        int temp;
        temp = a[sz - 1 - i];
        a[sz - 1 - i] = a[i];
        a[i] = temp;
    }
    for (unsigned i = 0; i < sz2 / 2; i++)
    {
        int temp;
        temp = b[sz2 - 1 - i];
        b[sz2 - 1 - i] = b[i];
        b[i] = temp;
    }
    checkTwoDeque(a, b);

    std::string myints2[] = {"asfasd","second","thrid"};
    std::deque<std::string> a2 (myints2, myints2 + sizeof(myints2) / sizeof(std::string) );
    ft::deque<std::string> b2 (myints2, myints2 + sizeof(myints2) / sizeof(std::string) );

    std::string *pointer = &a2[0];
    pointer++;
    pointer++;
    pointer--;
    std::string *pointer2 = &b2[0];
    pointer2++;
    pointer2++;
    pointer2--;

    EXPECT_EQ(*pointer, *pointer2);
}

TEST(Deque_Element_acces, at) {
    std::deque<int> a (10);
    ft::deque<int> b (10);

    std::string result = "";
    std::string result2 = "";

    try {
        for (unsigned i = 0; i < 100; i++) {
            a.at(i) = i;
        }
    }
    catch (std::exception &e) {
        result = e.what();
    }
    ASSERT_THROW(a.at(30), std::out_of_range);
    try {
        for (unsigned i = 0; i < 100; i++) {
            b.at(i) = i;
        }
    }
    catch (std::exception &e) {
        result2 = e.what();
    }
    ASSERT_THROW(b.at(30), std::out_of_range);
    checkTwoDeque(a, b);
    EXPECT_EQ(result, result2);
}

TEST(Deque_Element_acces, front_back) {
    std::deque<int> a;
    a.push_back(78);
    a.push_back(16);
    a.front() -= a.back();

    ft::deque<int> b;
    b.push_back(78);
    b.push_back(16);
    b.front() -= b.back();

    EXPECT_EQ(a.front(), b.front());
    EXPECT_EQ(a.back(), b.back());

    a.push_back(10);
    while (a.back() != 0)
        a.push_back (a.back() - 1 );
    b.push_back(10);
    while (b.back() != 0)
        b.push_back (b.back() - 1 );
    EXPECT_EQ(a.front(), b.front());
    EXPECT_EQ(a.back(), b.back());

    checkTwoDeque(a, b);
}


/* Modifiers */
TEST(Deque_Modifiers, assign) {
    std::deque<int> std_first;
    std::deque<int> std_second;
    std::deque<int> std_third;

    std_first.assign (7, 100);

    std::deque<int>::iterator std_it;
    std_it= std_first.begin() + 1;

    std_second.assign (std_it, std_first.end() - 1);

    int myints[] = { 1776, 7, 4};
    std_third.assign (myints, myints + 3);

    ft::deque<int> ft_first;
    ft::deque<int> ft_second;
    ft::deque<int> ft_third;

    ft_first.assign (7, 100);

    ft::deque<int>::iterator ft_it;
    ft_it = ft_first.begin() + 1;

    ft_second.assign (ft_it, ft_first.end() - 1);

    ft_third.assign (myints, myints + 3);

    checkTwoDeque(std_first, ft_first);
    checkTwoDeque(std_second, ft_second);
    checkTwoDeque(std_third, ft_third);
}

TEST(Deque_Modifiers, push_back) {
    std::deque<int> a;
    ft::deque<int> b;
    for (int i = 0; i < 100; i++){
        a.push_back (i);
        b.push_back (i);
    }
    checkTwoDeque(a, b);

    std::deque<std::string> a2;
    ft::deque<std::string> b2;
    a2.push_back("first");
    a2.push_back("second");
    a2.push_back("123");
    a2.push_back("567");
    b2.push_back("first");
    b2.push_back("second");
    b2.push_back("123");
    b2.push_back("567");
    checkTwoDeque(a2, b2);
}

TEST(Deque_Modifiers, push_front) {
    FAIL();
}

TEST(Deque_Modifiers, pop_back) {
    std::deque<int> a(1, 4);
    ft::deque<int> b(1, 4);
    int sum (0);
    int sum2 (0);

    sum += a.back();
    sum2 += b.back();
    a.pop_back();
    b.pop_back();
    a.push_back (100);
    a.push_back (200);
    a.push_back (300);
    b.push_back (100);
    b.push_back (200);
    b.push_back (300);

    while (!a.empty() && !b.empty())
    {
        sum += a.back();
        sum2 += b.back();
        a.pop_back();
        b.pop_back();
    }
    EXPECT_EQ(a.empty(), b.empty());
    checkTwoDeque(a, b);
    EXPECT_EQ(sum, sum2);
}

TEST(Deque_Modifiers, pop_front) {
    std::deque<int> *a = new std::deque<int>();
//    ft::deque<int> *b = new ft::deque<int>();

//    a->push_back (100);
//    a->push_back (200);
//    a->push_back (300);
//    b->push_back (100);
//    b->push_back (200);
//    b->push_back (300);

//    while (!a->empty() && !b->empty())
//    {
//        EXPECT_EQ(a->front(), b->front());
        a->pop_front();
//        b->pop_front();
//        checkTwoDeque(*a, *b);
//        printTwoDeque(*a, *b);
//    }
//    EXPECT_EQ(a->empty(), b->empty());
//    checkTwoDeque(*a, *b);

    delete a;
//    delete b;
}

TEST(Deque_Modifiers, insert) {
    int array[] = {1, 2, 3, 4 };
    std::deque<int> a(array, array + sizeof(array) / sizeof(int));
    ft::deque<int> b(array, array + sizeof(array) / sizeof(int));
    EXPECT_EQ(*a.insert(a.begin() + 2, 12),
              *b.insert(b.begin() + 2, 12));
    checkTwoDeque(a, b);
    EXPECT_EQ(*a.insert(a.end(), 14),
              *b.insert(b.end(), 14));
    checkTwoDeque(a, b);

    std::deque<int> a2;
    ft::deque<int> b2;
    EXPECT_EQ(*a2.insert(a2.begin(), 12),
              *b2.insert(b2.begin(), 12));
    checkTwoDeque(a2, b2);

    EXPECT_EQ(*a2.insert(a2.begin(), 13),
              *b2.insert(b2.begin(), 13));
    checkTwoDeque(a2, b2);

    std::deque<int> a3 (3, 100);
    std::deque<int>::iterator std_it;
    std_it = a3.begin();
    std_it = a3.insert (std_it , 200 );

    ft::deque<int> b3 (3, 100);
    ft::deque<int>::iterator ft_it;
    ft_it = b3.begin();
    ft_it = b3.insert (ft_it , 200 );

    a3.insert (std_it, 2, 300);
    b3.insert (ft_it, 2, 300);
    checkTwoDeque(a3, b3);

    std_it = a3.begin();
    ft_it = b3.begin();
    EXPECT_EQ(*std_it, *ft_it);

    std::deque<int> anothervector (2,400);
    ft::deque<int> anothervector2 (2,400);
    checkTwoDeque(anothervector, anothervector2);
    a3.insert (std_it + 2, anothervector.begin(), anothervector.end());
    b3.insert (ft_it + 2, anothervector2.begin(), anothervector2.end());
    checkTwoDeque(a3, b3);

    int myarray [] = { 501,502,503 };
    a3.insert (a3.begin(), myarray, myarray + 3);
    b3.insert (b3.begin(), myarray, myarray + 3);
    checkTwoDeque(a3, b3);
}

TEST(Deque_Modifiers, erase) {
    std::deque<int> a;
    ft::deque<int> b;

    for (int i = 1; i <= 12; i++) {
        a.push_back(i);
        b.push_back(i);
    }

    EXPECT_EQ(*a.erase (a.begin() + 5),
              *b.erase(b.begin() + 5));
    checkTwoDeque(a, b);

    EXPECT_EQ(*a.erase (a.begin() + 3),
              *b.erase(b.begin() + 3));
    checkTwoDeque(a, b);

    EXPECT_EQ(*a.erase (a.begin()),
              *b.erase(b.begin()));
    checkTwoDeque(a, b);

    EXPECT_EQ(*a.erase (a.end() - 2),
              *b.erase(b.end() - 2));
    checkTwoDeque(a, b);

    EXPECT_EQ(*a.erase (a.begin(), a.begin() + 6),
              *b.erase (b.begin(), b.begin() + 6));
    checkTwoDeque(a, b);
}

TEST(Deque_Modifiers, swap) {
    std::deque<int> foo (3,100);
    std::deque<int> bar (5,200);
    foo.swap(bar);

    ft::deque<int> foo2 (3,100);
    ft::deque<int> bar2 (5,200);
    foo2.swap(bar2);

    checkTwoDeque(foo, foo2);
    checkTwoDeque(bar, bar2);
}

TEST(Deque_Modifiers, clear) {
    std::deque<int> std_deque;
    std_deque.push_back (100);
    std_deque.push_back (200);
    std_deque.push_back (300);

    ft::deque<int> ft_deque;
    ft_deque.push_back (100);
    ft_deque.push_back (200);
    ft_deque.push_back (300);

    checkTwoDeque(std_deque, ft_deque);

    std_deque.clear();
    std_deque.push_back (1101);
    std_deque.push_back (2202);

    ft_deque.clear();
    ft_deque.push_back (1101);
    ft_deque.push_back (2202);

    checkTwoDeque(std_deque, ft_deque);
}


/* Non-member function overloads */
TEST(Deque_NonMember_Fuction_Overloads, relational_operators) {
    int std_ints[] = {10, 20, 30};
    std::vector<int> a(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    std::vector<int> b(std_ints, std_ints + sizeof(std_ints) / sizeof(int) );
    int std_ints2[] = {10, 20};
    std::vector<int> c(std_ints2, std_ints2 + sizeof(std_ints2) / sizeof(int) );

    int ft_ints[] = {10, 20, 30};
    ft::deque<int> a2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int) );
    ft::deque<int> b2(ft_ints, ft_ints + sizeof(ft_ints) / sizeof(int));
    int ft_ints2[] = {10, 20};
    ft::deque<int> c2(ft_ints2, ft_ints2 + sizeof(ft_ints2) / sizeof(int));

    EXPECT_EQ(a == b, a2 == b2);
    EXPECT_EQ(b != c, b2 != c2);
    EXPECT_EQ(b < c, b2 < c2);
    EXPECT_EQ(c > b, c2 > b2);
    EXPECT_EQ(a <= b, a2 <= b2);
    EXPECT_EQ(a >= b, a2 >= b2);
}

TEST(Deque_NonMember_Fuction_Overloads, swap) {
    std::deque<int> foo (3,100);
    std::deque<int> bar (5,200);
    std::swap(foo, bar);

    ft::deque<int> foo2 (3,100);
    ft::deque<int> bar2 (5,200);
    ft::swap(foo2,bar2);

    checkTwoDeque(foo, foo2);
    checkTwoDeque(bar, bar2);
}