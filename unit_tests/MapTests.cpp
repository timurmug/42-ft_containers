//
// Created by Quaro Tamarillo on 1/25/21.
//

#include "map.hpp"
#include "gtest/gtest.h"
#include <map>

TEST(Map_Base, empty_constructor) {
    std::map<std::string, int> std_map;
    std_map["twenty one"] = 21;
    std_map["five"] = 5;
    std_map["one"] = 1;
    std_map["null"] = 0;
    std_map["two"] = 2;

    std::map<std::string, int>::iterator it = std_map.begin();
    std::map<std::string, int>::iterator ite = std_map.end();

    while(it != ite) {
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }

    FAIL();
}

