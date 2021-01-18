//
// Created by Quaro Tamarillo on 1/18/21.
//
#include <gtest/gtest.h>
#include <stack>
#include <deque>
#include <vector>
#include "stack.hpp"

TEST(Stack, constructor) {
    std::deque<int> mydeque (3,100);
    std::vector<int> myvector (2,200);

    std::stack<int> std_stack;
    std::stack<int> std_stack2(mydeque);

    std::stack<int, std::vector<int> > std_stack3;
    std::stack<int, std::vector<int> > std_stack4 (myvector);

    ft::list<int> mylist2 (3,100);
    std::vector<int> myvector2 (2,200);

    ft::stack<int> ft_stack;
    ft::stack<int> ft_stack2(mylist2);

    ft::stack<int, std::vector<int> > ft_stack3;
    ft::stack<int, std::vector<int> > ft_stack4 (myvector2);

    EXPECT_EQ(std_stack.size(), ft_stack.size());
    EXPECT_EQ(std_stack2.size(), ft_stack2.size());
    EXPECT_EQ(std_stack3.size(), ft_stack3.size());
    EXPECT_EQ(std_stack4.size(), ft_stack4.size());
}

TEST(Stack, empty) {
    std::stack<int> std_stack;
    ft::stack<int> ft_stack;
    int sum (0);
    int sum2(0);

    for (int i = 1; i <= 10; i++) {
        std_stack.push(i);
        ft_stack.push(i);
    }

    while (!std_stack.empty())
    {
        sum += std_stack.top();
        std_stack.pop();
    }
    while (!ft_stack.empty())
    {
        sum2 += ft_stack.top();
        ft_stack.pop();
    }
    EXPECT_EQ(sum, sum2);
}

TEST(Stack, size) {
    std::stack<int> std_stack;
    ft::stack<int> ft_stack;
    EXPECT_EQ(std_stack.size(), ft_stack.size());

    for (int i=0; i<5; i++) {
        std_stack.push(i);
        ft_stack.push(i);
    }
    EXPECT_EQ(std_stack.size(), ft_stack.size());

    std_stack.pop();
    ft_stack.pop();
    EXPECT_EQ(std_stack.size(), ft_stack.size());
}

TEST(Stack, top) {
    std::stack<int> std_stack;
    std_stack.push(10);
    std_stack.push(20);
    std_stack.top() -= 5;

    ft::stack<int> ft_stack;
    ft_stack.push(10);
    ft_stack.push(20);
    ft_stack.top() -= 5;

    EXPECT_EQ(std_stack.top(), ft_stack.top());
}

TEST(Stack, push_pop) {
    std::stack<int> std_stack;
    ft::stack<int> ft_stack;

    for (int i=0; i<5; ++i) {
        std_stack.push(i);
        ft_stack.push(i);
    }

    while (!std_stack.empty())
    {
        if (ft_stack.empty())
            FAIL();
        EXPECT_EQ(std_stack.top(), ft_stack.top());
        std_stack.pop();
        ft_stack.pop();
    }
    EXPECT_EQ(std_stack.size(), ft_stack.size());
}

TEST(Stack, relational_operators) {
    std::stack<int> std_stack;
    std_stack.push(10);
    std_stack.push(20);
    std_stack.top() -= 5;
    std::stack<int> std_stack2;
    std_stack2.push(15);

    ft::stack<int> ft_stack;
    ft_stack.push(10);
    ft_stack.push(20);
    ft_stack.top() -= 5;
    ft::stack<int> ft_stack2;
    ft_stack2.push(15);

    EXPECT_EQ(std_stack == std_stack2, ft_stack == ft_stack2);
    EXPECT_EQ(std_stack != std_stack2, ft_stack != ft_stack2);
    EXPECT_EQ(std_stack < std_stack2, ft_stack < ft_stack2);
    EXPECT_EQ(std_stack <= std_stack2, ft_stack <= ft_stack2);
    EXPECT_EQ(std_stack > std_stack2, ft_stack > ft_stack2);
    EXPECT_EQ(std_stack >= std_stack2, ft_stack >= ft_stack2);
}
