//
// Created by Quaro Tamarillo on 1/25/21.
//

#include "map.hpp"
#include "gtest/gtest.h"
#include <map>

TEST(Map_Base, empty_constructor) {
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;

    EXPECT_EQ(std_map.size(), ft_map.size());
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

//    srand(time(0));
//    int n = 10;
//    int key;
//    while (n--) {
//        key = rand();
//        if (rand() % 2 == 1)
//            key *= -1;
//        std_res = std_map.insert ( std::pair<int, std::string>(key, "ten" ) );
//        ft_res = ft_map.insert ( std::pair<int, std::string>(key, "ten" ) );
//        EXPECT_EQ(std_map.size(), ft_map.size());
//
//        EXPECT_EQ(std_res.first->first, ft_res.first->first);
//        EXPECT_EQ(std_res.first->second, ft_res.first->second);
//        EXPECT_EQ(std_res.second, ft_res.second);
//    }

//    std_res = std_map.insert ( std::pair<int, std::string>(key, "ыфва" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(key, "ыфва" ) );
//    EXPECT_EQ(std_map.size(), ft_map.size());

    std_res = std_map.insert ( std::pair<int, std::string>(5, "ten" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(5, "ten" ) );

    std_res = std_map.insert ( std::pair<int, std::string>(7, "ten" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(7, "ten" ) );

//    std_res = std_map.insert ( std::pair<int, std::string>(8, "ten" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(8, "ten" ) );
//////
//    std_res = std_map.insert ( std::pair<int, std::string>(6, "ten" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(6, "ten" ) );
////
//    std_res = std_map.insert ( std::pair<int, std::string>(3, "ten" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(3, "ten" ) );
////
//    std_res = std_map.insert ( std::pair<int, std::string>(4, "ten" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(4, "ten" ) );

    EXPECT_EQ(std_res.first->first, ft_res.first->first);
    EXPECT_EQ(std_res.first->second, ft_res.first->second);
    EXPECT_EQ(std_res.second, ft_res.second);

    std::map<int, std::string>::iterator std_it = std_map.begin();
    std::map<int, std::string>::iterator std_ite = std_map.end();
    while (std_it != std_ite) {
        std::cout << std_it->first << " " << std_it->second << std::endl;
        std_it++;
    }

    std::cout << std::endl;

    ft::map<int, std::string>::iterator ft_it = ft_map.begin();
    ft::map<int, std::string>::iterator ft_ite = ft_map.end();
    while (ft_it != ft_ite) {
        std::cout << ft_it->first << " " << ft_it->second << std::endl;
        ft_it++;
    }

//    std::cout << std_res.first->first << " " << std_res.first->second << std::endl;
//    std::cout << std_res.second << std::endl;
//    std::cout << ft_res.first->first << " " << ft_res.first->second << std::endl;
//    std::cout << ft_res.second << std::endl;
}



//TEST(Map_Base, test) {
//    std::map<int, std::string> std_map;
//    std::cout << "size: " << std_map.size() << std::endl;
//
//    std_map.insert ( std::pair<int, std::string>(21, "twenty one" ) );
//    std_map.insert ( std::pair<int, std::string>(5, "five") );
//    std_map.insert ( std::pair<int, std::string>(1, "one") );
//    std_map.insert ( std::pair<int, std::string>(1, "one") );
//    std_map.insert ( std::pair<int, std::string>(0, "null") );
//    std_map.insert ( std::pair<int, std::string>(2, "two") );
////    std_map["twenty one"] = 21;
////    std_map["five"] = 5;
////    std_map["one"] = 1;
////    std_map["null"] = 0;
////    std_map["two"] = 2;
//
//    std::map<int, std::string>::iterator it = std_map.begin();
//    std::map<int, std::string>::iterator ite = std_map.end();
//
//    std::cout << "\n";
//    while(it != ite) {
//        std::cout << it->first << " " << it->second << std::endl;
//        it++;
//    }
//    std::cout << "\n";
//
//    std::cout << "size: " << std_map.size() << std::endl;
//    std::pair<int, std::string> pair(2, "two");
//    std::cout << "\n" << pair.first << " " << pair.second << "\n";
//    FAIL();
//}

