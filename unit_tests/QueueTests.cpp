//
// Created by Quaro Tamarillo on 1/18/21.
//
#include <gtest/gtest.h>
#include <queue>
#include <deque>
#include <list>
#include <vector>
#include "queue.hpp"

TEST(Queue, constructor) {
    std::deque<int> mydeck (3,100);        // deque with 3 elements
    std::vector<int> myvector (2,200);         // list with 2 elements

    std::queue<int> std_queue;                 // empty queue
    std::queue<int> std_queue2 (mydeck);       // queue initialized to copy of deque

    std::queue<int,std::list<int> > std_queue3; // empty queue with list as underlying container
    std::queue<int,std::vector<int> > std_queue4 (myvector);

    ft::list<int> ft_list (3,100);        // deque with 3 elements
    std::vector<int> myvector2 (2,200);         // list with 2 elements

    ft::queue<int> ft_queue;                 // empty queue
    ft::queue<int> ft_queue2 (ft_list);       // queue initialized to copy of deque

    ft::queue<int,std::list<int> > ft_queue3; // empty queue with list as underlying container
    ft::queue<int,std::vector<int> > ft_queue4 (myvector2);

    EXPECT_EQ(std_queue.size(), ft_queue.size());
    EXPECT_EQ(std_queue2.size(), ft_queue2.size());
    EXPECT_EQ(std_queue3.size(), ft_queue3.size());
    EXPECT_EQ(std_queue4.size(), ft_queue4.size());
}

TEST(Queue, empty) {
    std::queue<int> std_queue;
    ft::queue<int> ft_queue;
    int sum (0);
    int sum2 (0);

    for (int i = 1;i <= 10;i++) {
        std_queue.push(i);
        ft_queue.push(i);
    }

    while (!std_queue.empty())
    {
        sum += std_queue.front();
        std_queue.pop();
    }
    while (!ft_queue.empty())
    {
        sum2 += ft_queue.front();
        ft_queue.pop();
    }
    EXPECT_EQ(sum, sum2);
}

TEST(Queue, size) {
    std::queue<int> std_queue;
    ft::queue<int> ft_queue;
    EXPECT_EQ(std_queue.size(), ft_queue.size());

    for (int i = 0; i < 5; i++) {
        std_queue.push(i);
        ft_queue.push(i);
    }
    EXPECT_EQ(std_queue.size(), ft_queue.size());

    std_queue.pop();
    ft_queue.pop();
    EXPECT_EQ(std_queue.size(), ft_queue.size());
}

TEST(Queue, front) {
    std::queue<int> std_queue;
    ft::queue<int> ft_queue;

    std_queue.push(77);
    std_queue.push(16);
    ft_queue.push(77);
    ft_queue.push(16);

    std_queue.front() -= std_queue.back();
    ft_queue.front() -= ft_queue.back();

    EXPECT_EQ(std_queue.front(), ft_queue.front());
}

TEST(Queue, back) {
    std::queue<int> std_queue;
    ft::queue<int> ft_queue;

    std_queue.push(12);
    std_queue.push(75);
    ft_queue.push(12);
    ft_queue.push(75);

    std_queue.back() -= std_queue.front();
    ft_queue.back() -= ft_queue.front();

    EXPECT_EQ(std_queue.back(), ft_queue.back());
}

TEST(Queue, push_pop) {
    std::queue<int> std_queue;
    ft::queue<int> ft_queue;

    for (int i = 0; i < 10; i++) {
        std_queue.push (i);
        ft_queue.push (i);
    }

    while (!std_queue.empty())
    {
        if (ft_queue.empty())
            FAIL();
        EXPECT_EQ(std_queue.front(), ft_queue.front());
        std_queue.pop();
        ft_queue.pop();
    }
    EXPECT_EQ(std_queue.size(), ft_queue.size());
}

TEST(Queue, relational_operators) {
    std::queue<int> std_queue;
    std_queue.push(10);
    std_queue.push(20);
//    std_queue.back() -= 5;
    std::queue<int> std_stack2;
    std_stack2.push(15);

    ft::queue<int> ft_queue;
    ft_queue.push(10);
    ft_queue.push(20);
//    ft_queue.back() -= 5;
    ft::queue<int> ft_stack2;
    ft_stack2.push(15);

    EXPECT_EQ(std_queue == std_stack2, ft_queue == ft_stack2);
    EXPECT_EQ(std_queue != std_stack2, ft_queue != ft_stack2);
    EXPECT_EQ(std_queue < std_stack2, ft_queue < ft_stack2);
    EXPECT_EQ(std_queue <= std_stack2, ft_queue <= ft_stack2);
    EXPECT_EQ(std_queue > std_stack2, ft_queue > ft_stack2);
    EXPECT_EQ(std_queue >= std_stack2, ft_queue >= ft_stack2);
}

