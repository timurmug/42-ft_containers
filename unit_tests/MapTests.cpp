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

    std::pair<std::map<int, std::string>::iterator, bool> std_res =
            std_map.insert ( std::pair<int, std::string>(21, "twenty one" ) );
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res =
            ft_map.insert ( std::pair<int, std::string>(21, "twenty one" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    EXPECT_EQ(std_res.first->first, ft_res.first->first);
    EXPECT_EQ(std_res.first->second, ft_res.first->second);
    EXPECT_EQ(std_res.second, ft_res.second);

//    std_res = std_map.insert ( std::pair<int, std::string>(21, "twenty one" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(21, "twenty one" ) );
//    EXPECT_EQ(std_map.size(), ft_map.size());
//
//    EXPECT_EQ(std_res.first->first, ft_res.first->first);
//    EXPECT_EQ(std_res.first->second, ft_res.first->second);
//    EXPECT_EQ(std_res.second, ft_res.second);

    std_res = std_map.insert ( std::pair<int, std::string>(22, "twenty two" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(22, "twenty two" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    EXPECT_EQ(std_res.first->first, ft_res.first->first);
    EXPECT_EQ(std_res.first->second, ft_res.first->second);
    EXPECT_EQ(std_res.second, ft_res.second);

    std_res = std_map.insert ( std::pair<int, std::string>(10, "ten" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "ten" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    EXPECT_EQ(std_res.first->first, ft_res.first->first);
    EXPECT_EQ(std_res.first->second, ft_res.first->second);
    EXPECT_EQ(std_res.second, ft_res.second);


    std::cout << std_res.first->first << " " << std_res.first->second << std::endl;
    std::cout << std_res.second << std::endl;
    std::cout << ft_res.first->first << " " << ft_res.first->second << std::endl;
    std::cout << ft_res.second << std::endl;
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

