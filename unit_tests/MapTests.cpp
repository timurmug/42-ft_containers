//
// Created by Quaro Tamarillo on 1/25/21.
//

#include "map.hpp"
#include "gtest/gtest.h"
#include <map>

static const char alphabet[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

std::string getRandomStr() {
    const int len = rand() % 10;
    std::string randomStr;
    randomStr.reserve(len);
    for (int i = 0; i < len; ++i)
        randomStr += alphabet[rand() % (sizeof(alphabet) - 1)];
    return randomStr;
}
int         getRandomInt() {
    int randomInt = randomInt = rand();
    if (rand() % 2 == 1)
        randomInt *= -1;
    return randomInt;
}
char        getRandomChar() {
    return alphabet[rand() % (sizeof(alphabet) - 1)];
}

template <typename T, typename S>
void checkTwoMaps(T & std_map, S & ft_map) {
    typename T::iterator std_it = std_map.begin();
    typename T::iterator std_ite = std_map.end();
    typename S::iterator ft_it = ft_map.begin();
    typename S::iterator ft_ite = ft_map.end();
    EXPECT_EQ(std_map.size(), ft_map.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(std_it->first, ft_it->first);
        EXPECT_EQ(std_it->second, ft_it->second);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}
template <typename T, typename S>
void checkTwoMaps_const_iterator(T & std_map, S & ft_map) {
    typename T::const_iterator std_it = std_map.begin();
    typename T::const_iterator std_ite = std_map.end();
    typename S::const_iterator ft_it = ft_map.begin();
    typename S::const_iterator ft_ite = ft_map.end();
    EXPECT_EQ(std_map.size(), ft_map.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(std_it->first, ft_it->first);
        EXPECT_EQ(std_it->second, ft_it->second);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}
template <typename T, typename S>
void checkTwoMaps_reverse_iterator(T & std_map, S & ft_map) {
    typename T::reverse_iterator std_it = std_map.rbegin();
    typename T::reverse_iterator std_ite = std_map.rend();
    typename S::reverse_iterator ft_it = ft_map.rbegin();
    typename S::reverse_iterator ft_ite = ft_map.rend();
    EXPECT_EQ(std_map.size(), ft_map.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(std_it->first, ft_it->first);
        EXPECT_EQ(std_it->second, ft_it->second);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}
template <typename T, typename S>
void checkTwoMaps_const_reverse_iterator(T & std_map, S & ft_map) {
    typename T::const_reverse_iterator std_it = std_map.rbegin();
    typename T::const_reverse_iterator std_ite = std_map.rend();
    typename S::const_reverse_iterator ft_it = ft_map.rbegin();
    typename S::const_reverse_iterator ft_ite = ft_map.rend();
    EXPECT_EQ(std_map.size(), ft_map.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(std_it->first, ft_it->first);
        EXPECT_EQ(std_it->second, ft_it->second);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

template <typename T, typename S>
void printTwoMaps(T & std_map, S & ft_map) {
    typename T::iterator std_it = std_map.begin();
    typename T::iterator std_ite = std_map.end();
    typename S::iterator ft_it = ft_map.begin();
    typename S::iterator ft_ite = ft_map.end();
    std::cout << "std_map: |"<< std::setw(15) << "key| |"<< std::setw(15) << "value|" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    while (std_it != std_ite) {
        std::cout << "\t\t |" << std::setw(12) << std_it->first << "| |" << std::setw(14) << std_it->second << "|" << std::endl;
        std_it++;
    }
    std::cout << std::endl <<"ft_map: |"<< std::setw(15) << "key| |"<< std::setw(15) << "value|" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    while (ft_it != ft_ite) {
        std::cout << "\t\t |" << std::setw(12) << ft_it->first << "| |" << std::setw(14) << ft_it->second << "|" << std::endl;
        ft_it++;
    }
}

bool fncomp (char lhs, char rhs) {
    return lhs<rhs;
}
struct classcomp {
    bool operator() (const char& lhs, const char& rhs) const {
        return lhs<rhs;
    }
};

TEST(Map_Base, empty_constructor1) {
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    EXPECT_EQ(std_map.size(), ft_map.size());
    checkTwoMaps(std_map, ft_map);

//    std_res = std_map.insert ( std::pair<int, std::string>(10, "value" ) );
//    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "value" ) );
//    EXPECT_EQ(std_map.size(), ft_map.size());
//
//    EXPECT_EQ(std_res.first->first, ft_res.first->first);
//    EXPECT_EQ(std_res.first->second, ft_res.first->second);
//    EXPECT_EQ(std_res.second, ft_res.second);
//
//    srand(time(0));
//    int n = 10;
//    int key;
//    std::string value;
//    while (n--) {
//        key = getRandomInt();
//        value = getRandomStr();
//        std_res = std_map.insert ( std::pair<int, std::string>(key, value ) );
//        ft_res = ft_map.insert ( std::pair<int, std::string>(key, value ) );
//        EXPECT_EQ(std_map.size(), ft_map.size());
//
//        EXPECT_EQ(std_res.first->first, ft_res.first->first);
//        EXPECT_EQ(std_res.first->second, ft_res.first->second);
//        EXPECT_EQ(std_res.second, ft_res.second);
//    }
//    checkTwoMaps(std_map, ft_map);
}

TEST(Map_Base, empty_constructor2) {
    std::map<std::string, int> std_map;
    ft::map<std::string, int> ft_map;
    std::pair<std::map<std::string, int>::iterator, bool> std_res;
    std::pair<ft::map<std::string, int>::iterator, bool> ft_res;

    EXPECT_EQ(std_map.size(), ft_map.size());

    srand(time(0));
    int n = 10;
    std::string key;
    int value;
    while (n--) {
        key = getRandomStr();
        value = getRandomInt();
        std_res = std_map.insert ( std::pair<std::string, int>(key, value ) );
        ft_res = ft_map.insert ( std::pair<std::string, int>(key, value ) );
        EXPECT_EQ(std_map.size(), ft_map.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }

    checkTwoMaps(std_map, ft_map);
}

TEST(Map_Base, range_constructor) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    srand(time(0));
    int n = 10;
    char key;
    int value;
    while (n--) {
        key = getRandomChar();
        value = getRandomInt();
        std_res = a.insert(std::pair<char, int>(key, value ));
        ft_res = b.insert(std::pair<char, int>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }

    std::map<char, int, classcomp> a2 (++a.begin(), a.end());
    ft::map<char, int, classcomp> b2 (++a.begin(), a.end());
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);

    bool(*fn_pt)(char,char) = fncomp;
    std::map<char,int,bool(*)(char,char)> c (fn_pt);
    ft::map<char,int,bool(*)(char,char)> c2 (fn_pt);
    checkTwoMaps(c, c2);
}

TEST(Map_Base, copy_constructor) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    srand(time(0));
    int n = 10;
    char key;
    int value;
    while (n--) {
        key = getRandomChar();
        value = getRandomInt();
        std_res = a.insert(std::pair<char, int>(key, value ));
        ft_res = b.insert(std::pair<char, int>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }

    std::map<char, int> a2(a);
    ft::map<char, int> b2(b);
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);

    std_res = a.insert(std::pair<char, int>('.', value ));
    ft_res = b.insert(std::pair<char, int>('.', value ));

    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);
}

TEST(Map_Base, operator_equal) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    srand(time(0));
    int n = 10;
    char key;
    int value;
    while (n--) {
        key = getRandomChar();
        value = getRandomInt();
        std_res = a.insert(std::pair<char, int>(key, value ));
        ft_res = b.insert(std::pair<char, int>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }

    std::map<char, int> a2 = a;
    ft::map<char, int> b2 = b;
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);

    std_res = a.insert(std::pair<char, int>('.', value ));
    ft_res = b.insert(std::pair<char, int>('.', value ));

    a2 = a;
    b2 = b;

    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);
}


///* Iterators */
TEST(Map_Iterators, iterator) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    checkTwoMaps(a, b);

    srand(time(0));
    int n = 10;
    char key;
    int value;
    while (n--) {
        key = getRandomChar();
        value = getRandomInt();
        std_res = a.insert(std::pair<char, int>(key, value ));
        ft_res = b.insert(std::pair<char, int>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }
    checkTwoMaps(a, b);

    std::map<char, int>::iterator std_it = a.begin();
    ft::map<char, int>::iterator ft_it = b.begin();
    std::map<char, int>::iterator std_ite = a.end();
    ft::map<char, int>::iterator ft_ite = b.end();

    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);

    ++std_it;
    ++ft_it;
    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);
    std_it++;
    ft_it++;
    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);
    std_it--;
    ft_it--;
    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);
    --std_it;
    --ft_it;
    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);
    std_it++;
    ft_it++;
    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);

    --std_ite;
    --ft_ite;
    EXPECT_EQ((*std_ite).first, (*ft_ite).first);
    EXPECT_EQ(std_ite->second, ft_ite->second);
    std_ite--;
    ft_ite--;
    EXPECT_EQ((*std_ite).first, (*ft_ite).first);
    EXPECT_EQ(std_ite->second, ft_ite->second);
    ++std_ite;
    ++ft_ite;
    EXPECT_EQ((*std_ite).first, (*ft_ite).first);
    EXPECT_EQ(std_ite->second, ft_ite->second);
    std_ite++;
    ft_ite++;
    //здесь нельзя разыменовывать
    --std_ite;
    --ft_ite;
    EXPECT_EQ((*std_ite).first, (*ft_ite).first);
    EXPECT_EQ(std_ite->second, ft_ite->second);

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoMaps(a, b);
}
//
TEST(Map_Iterators, const_iterator) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::const_iterator, bool> std_res;
    std::pair<ft::map<char, int>::const_iterator, bool> ft_res;

    checkTwoMaps_const_iterator(a, b);

    srand(time(0));
    int n = 10;
    char key;
    int value;
    while (n--) {
        key = getRandomChar();
        value = getRandomInt();
        std_res = a.insert(std::pair<char, int>(key, value ));
        ft_res = b.insert(std::pair<char, int>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }
    checkTwoMaps_const_iterator(a, b);

    std::map<char, int>::const_iterator std_it = a.begin();
    ft::map<char, int>::const_iterator ft_it = b.begin();
    std::map<char, int>::const_iterator std_ite = a.end();
    ft::map<char, int>::const_iterator ft_ite = b.end();

    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);

    ++std_it;
    ++ft_it;
    std_it++;
    ft_it++;
    std_it--;
    ft_it--;
    --std_it;
    --ft_it;
    std_it++;
    ft_it++;


    --std_ite;
    --ft_ite;
    std_ite--;
    ft_ite--;
    ++std_ite;
    ++ft_ite;
    std_ite++;
    ft_ite++;
    --std_ite;
    --ft_ite;

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoMaps_const_iterator(a, b);
}
//
TEST(Map_Iterators, reverse_iterator) {
    std::map<int, std::string> a;
    ft::map<int, std::string> b;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    checkTwoMaps_reverse_iterator(a, b);

    srand(time(0));
    int n = 10;
    int key;
    std::string value;
    while (n--) {
        key = getRandomInt();
        value = getRandomStr();
        std_res = a.insert(std::pair<int, std::string>(key, value ));
        ft_res = b.insert(std::pair<int, std::string>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }
    checkTwoMaps_reverse_iterator(a, b);

    std::map<int, std::string>::reverse_iterator std_it = a.rbegin();
    std::map<int, std::string>::reverse_iterator std_ite = a.rend();
    ft::map<int, std::string>::reverse_iterator ft_it = b.rbegin();
    ft::map<int, std::string>::reverse_iterator ft_ite = b.rend();

    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);

    ++std_it;
    ++ft_it;
    std_it++;
    ft_it++;
    std_it--;
    ft_it--;
    --std_it;
    --ft_it;
    std_it++;
    ft_it++;


    --std_ite;
    --ft_ite;
    std_ite--;
    ft_ite--;
    ++std_ite;
    ++ft_ite;
    std_ite++;
    ft_ite++;
    --std_ite;
    --ft_ite;

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoMaps_reverse_iterator(a, b);
}

TEST(Map_Iterators, const_reverse_iterator) {
    std::map<int, std::string> a;
    ft::map<int, std::string> b;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    checkTwoMaps_const_reverse_iterator(a, b);

    srand(time(0));
    int n = 10;
    int key;
    std::string value;
    while (n--) {
        key = getRandomInt();
        value = getRandomStr();
        std_res = a.insert(std::pair<int, std::string>(key, value ));
        ft_res = b.insert(std::pair<int, std::string>(key, value ));
        EXPECT_EQ(a.size(), b.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }
    checkTwoMaps_const_reverse_iterator(a, b);

    std::map<int, std::string>::const_reverse_iterator std_it = a.rbegin();
    std::map<int, std::string>::const_reverse_iterator std_ite = a.rend();
    ft::map<int, std::string>::const_reverse_iterator ft_it = b.rbegin();
    ft::map<int, std::string>::const_reverse_iterator ft_ite = b.rend();

    EXPECT_EQ((*std_it).first, (*ft_it).first);
    EXPECT_EQ(std_it->second, ft_it->second);

    ++std_it;
    ++ft_it;
    std_it++;
    ft_it++;
    std_it--;
    ft_it--;
    --std_it;
    --ft_it;
    std_it++;
    ft_it++;


    --std_ite;
    --ft_ite;
    std_ite--;
    ft_ite--;
    ++std_ite;
    ++ft_ite;
    std_ite++;
    ft_ite++;
    --std_ite;
    --ft_ite;

    EXPECT_EQ(*std_it, *ft_it);
    EXPECT_EQ(*std_ite, *ft_ite);

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoMaps_const_reverse_iterator(a, b);
}


/* Capacity and Element access */
TEST(Map_Capacity_Element_Access, empty) {
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    EXPECT_EQ(std_map.empty(), ft_map.empty());

    std_res = std_map.insert ( std::pair<int, std::string>(10, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "value" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    std::map<char,int> std_map2;
    ft::map<char,int> ft_map2;

    std_map2['a']=10;
    std_map2['b']=20;
    std_map2['c']=30;
    ft_map2['a']=10;
    ft_map2['b']=20;
    ft_map2['c']=30;

    while (!std_map2.empty()) {
        checkTwoMaps(std_map2, ft_map2);
        std_map2.erase(std_map2.begin());
        ft_map2.erase(ft_map2.begin());
    }
    EXPECT_EQ(std_map2.empty(), ft_map2.empty());
}

TEST(Map_Capacity_Element_Access, size) {
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    EXPECT_EQ(std_map.size(), ft_map.size());

    std_res = std_map.insert ( std::pair<int, std::string>(10, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "value" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    std_res = std_map.insert ( std::pair<int, std::string>(12, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(12, "value" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    std_res = std_map.insert ( std::pair<int, std::string>(1, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(1, "value" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());
}

TEST(Map_Capacity_Element_Access, max_size) {
    std::map<int, std::string> std_map;
    ft::map<int, std::string> ft_map;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    EXPECT_EQ(std_map.max_size(), ft_map.max_size());

    std_res = std_map.insert ( std::pair<int, std::string>(10, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "value" ) );
    EXPECT_EQ(std_map.max_size(), ft_map.max_size());

    std_res = std_map.insert ( std::pair<int, std::string>(12, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(12, "value" ) );
    EXPECT_EQ(std_map.max_size(), ft_map.max_size());
}

TEST(Map_Capacity_Element_Access, operator_) {
    std::map<char,std::string> std_map;
    ft::map<char,std::string> ft_map;

    std_map['a'] = "an element";
    ft_map['a'] = "an element";

    std_map['b'] = "another element";
    std_map['b'] = "another element";
    ft_map['b'] = "another element";
    ft_map['b'] = "another element";

    std_map['c'] = std_map['b'];
    ft_map['c'] = ft_map['b'];

    EXPECT_EQ(std_map['d'], ft_map['d']);

    checkTwoMaps(std_map, ft_map);
}


/* Modifiers */
TEST(Map_Modifiers, insert) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    std::pair<std::map<char,int>::iterator,bool> std_ret;
    std::pair<ft::map<char,int>::iterator,bool> ft_ret;
    int value;
    char key;
    for (int i = 0; i != 10; i++) {
        key = getRandomChar();
        value = getRandomInt();
        std_ret = std_map.insert ( std::pair<char,int>(key, value) );
        ft_ret = ft_map.insert ( std::pair<char,int>(key, value) );
        EXPECT_EQ((*std_ret.first).first, (*ft_ret.first).first);
        EXPECT_EQ((*std_ret.first).second, (*ft_ret.first).second);
        EXPECT_EQ(std_ret.second, ft_ret.second);
    }
    checkTwoMaps(std_map, ft_map);

    std::map<char,int>::iterator std_it = std_map.begin();
    ft::map<char,int>::iterator ft_it = ft_map.begin();
    std::map<char,int>::iterator std_it2 = std_map.insert (std_it,  std::pair<char,int>(key, value) );
    ft::map<char,int>::iterator ft_it2 = ft_map.insert (ft_it, std::pair<char,int>(key, value) );
    EXPECT_EQ(std_it2->first, ft_it2->first);
    EXPECT_EQ(std_it2->second, ft_it2->second);
    checkTwoMaps(std_map, ft_map);

    std::map<char,int> std_map2;
    std_map2.insert(std_map.begin(),std_map.end()--);
    ft::map<char,int> ft_map2;
    ft_map2.insert(ft_map.begin(),ft_map.end()--);
    checkTwoMaps(std_map2, ft_map2);
}

TEST(Map_Modifiers, erase) {
    std::map<char,int>              std_map;
    std::map<char,int>::iterator    std_it;

    std::cout << std_map.erase('q') << std::endl;

//    std_map['a']=10;
//    std_map['a']=10;
//    std_map['b']=20;
//    std_map['c']=30;
//    std_map['d']=40;
//    std_map['e']=50;
//    std_map['f']=60;

    std::cout << std_map.erase('q') << std::endl;
    std::cout << std_map.erase('a') << std::endl;

    FAIL();
}

TEST(Map_Modifiers, swap) {
    std::map<char,char> std_map;
    ft::map<char,char> ft_map;

    std_map['a'] = '2';
    ft_map['a'] = '2';

    std::map<char,int> foo, bar;
    foo['x']=100;
    foo['y']=200;
    bar['a']=11;
    bar['b']=22;
    bar['c']=33;
    foo.swap(bar);

    ft::map<char,int> foo2, bar2;
    foo2['x']=100;
    foo2['y']=200;
    bar2['a']=11;
    bar2['b']=22;
    bar2['c']=33;
    foo2.swap(bar2);

    checkTwoMaps(foo, foo2);
    checkTwoMaps(bar, bar2);
}

TEST(Map_Modifiers, clear) {
    FAIL();
}


/* Observers */
TEST(Map_Observers, key_comp) {
    std::map<char,int> std_map;
    std::map<char,int>::key_compare std_compare = std_map.key_comp();
    ft::map<char,int> ft_map;
    ft::map<char,int>::key_compare ft_compare = ft_map.key_comp();

    std_map['a']=100;
    std_map['b']=200;
    std_map['c']=300;
    ft_map['a']=100;
    ft_map['b']=200;
    ft_map['c']=300;

    char highest = std_map.rbegin()->first;
    char highest2 = ft_map.rbegin()->first;

    std::map<char,int>::iterator it = std_map.begin();
    ft::map<char,int>::iterator it2 = ft_map.begin();

    while ( std_compare((*it).first, highest) && ft_compare((*it).first, highest2)) {
        EXPECT_EQ(it->first, it2->first);
        EXPECT_EQ(it->second, it2->second);
        it++;
        it2++;
    }
    EXPECT_EQ((--it)->first, (--it2)->first);
}

TEST(Map_Observers, value_comp) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    std_map['a']=100;
    std_map['b']=200;
    std_map['c']=300;
    ft_map['a']=100;
    ft_map['b']=200;
    ft_map['c']=300;

    std::map<char,int>::iterator it = std_map.begin();
    ft::map<char,int>::iterator it2 = ft_map.begin();

    while ( std_map.value_comp()(*it, *std_map.rbegin()) && ft_map.value_comp()(*it, *ft_map.rbegin())) {
        EXPECT_EQ(it->first, it2->first);
        EXPECT_EQ(it->second, it2->second);
        std::cout << it->first << " => " << it->second << '\n';
        std::cout << it2->first << " => " << it2->second << "\n\n";
        it++;
        it2++;
    }
    EXPECT_EQ((--it)->first, (--it2)->first);
}


/* Operations */
TEST(Map_Operations, find) {
    std::map<char, int> std_map;
    std::map<char, int>::iterator std_it;
    ft::map<char, int> ft_map;
    ft::map<char, int>::iterator ft_it;

    std_map['a'] = 50;
    std_map['b'] = 100;
    std_map['c'] = 150;
    std_map['d'] = 200;
    ft_map['a'] = 50;
    ft_map['b'] = 100;
    ft_map['c'] = 150;
    ft_map['d'] = 200;

    for (char symbol = 'a'; symbol != 'e'; symbol++) {
        std_it = std_map.find(symbol);
        ft_it = ft_map.find(symbol);
        EXPECT_EQ(std_it->first, ft_it->first);
        EXPECT_EQ(std_it->second, ft_it->second);
    }

    std_it = std_map.find('n');
    ft_it = ft_map.find('n');
    EXPECT_EQ(std_it, std_map.end());
    EXPECT_EQ(ft_it, ft_map.end());


    std::map<char, int> std_map2;
    std::map<char, int>::const_iterator std_it2;
    ft::map<char, int> ft_map2;
    ft::map<char, int>::const_iterator ft_it2;

    std_map2['a'] = 50;
    std_map2['b'] = 100;
    std_map2['c'] = 150;
    std_map2['d'] = 200;
    ft_map2['a'] = 50;
    ft_map2['b'] = 100;
    ft_map2['c'] = 150;
    ft_map2['d'] = 200;

    for (char symbol = 'a'; symbol != 'e'; symbol++) {
        std_it2 = std_map2.find(symbol);
        ft_it2 = ft_map2.find(symbol);
        EXPECT_EQ(std_it2->first, ft_it2->first);
        EXPECT_EQ(std_it2->second, ft_it2->second);
    }

    std_it2 = std_map2.find('n');
    ft_it2 = ft_map2.find('n');
    EXPECT_EQ(std_it2, std_map2.end());
    EXPECT_EQ(ft_it2, ft_map2.end());
}

TEST(Map_Operations, count) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    std_map ['a']=101;
    std_map ['c']=202;
    std_map ['f']=303;
    ft_map ['a']=101;
    ft_map ['c']=202;
    ft_map ['f']=303;

    for (char symbol = 'a'; symbol < 'h'; symbol++)
        EXPECT_EQ(std_map.count(symbol), ft_map.count(symbol));
}

TEST(Map_Operations, lower_bound) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    ft_map['a']=10;
    ft_map['b']=20;
    ft_map['c']=30;
    ft_map['d']=30;
    ft_map['e']=30;
    std_map['a']=10;
    std_map['b']=20;
    std_map['c']=30;
    std_map['d']=30;
    std_map['e']=30;

    std::map<char,int>::iterator std_ret;
    ft::map<char,int>::iterator ft_ret;

    //первый элемент
    std_ret = std_map.lower_bound('a');
    ft_ret = ft_map.lower_bound('a');
    EXPECT_EQ(std_ret->first, ft_ret->first);
    EXPECT_EQ(std_ret->second, ft_ret->second);

    //элемент по середине
    std_ret = std_map.lower_bound('b');
    ft_ret = ft_map.lower_bound('b');
    EXPECT_EQ(std_ret->first, ft_ret->first);
    EXPECT_EQ(std_ret->second, ft_ret->second);

    //последний элемент
    std_ret = std_map.lower_bound('e');
    ft_ret = ft_map.lower_bound('e');
    EXPECT_EQ(std_ret->first, ft_ret->first);
    EXPECT_EQ(std_ret->second, ft_ret->second);

    //не существующий элемент
    std_ret = std_map.lower_bound('q');
    ft_ret = ft_map.lower_bound('q');
    EXPECT_EQ(std_ret, std_map.end());
    EXPECT_EQ(ft_ret, ft_map.end());

    //const
    std::map<char,int>::const_iterator std_ret2 = std_map.lower_bound('b');
    ft::map<char,int>::const_iterator ft_ret2= ft_map.lower_bound('b');
    EXPECT_EQ(std_ret2->first, ft_ret2->first);
    EXPECT_EQ(std_ret2->second, ft_ret2->second);

}

TEST(Map_Operations, upper_bound) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    ft_map['a']=10;
    ft_map['b']=20;
    ft_map['c']=30;
    ft_map['d']=30;
    ft_map['e']=30;
    std_map['a']=10;
    std_map['b']=20;
    std_map['c']=30;
    std_map['d']=30;
    std_map['e']=30;

    std::map<char,int>::iterator std_ret;
    ft::map<char,int>::iterator ft_ret;

    //первый элемент
    std_ret = std_map.upper_bound('a');
    ft_ret = ft_map.upper_bound('a');
    EXPECT_EQ(std_ret->first, ft_ret->first);
    EXPECT_EQ(std_ret->second, ft_ret->second);

    //элемент по середине
    std_ret = std_map.upper_bound('b');
    ft_ret = ft_map.upper_bound('b');
    EXPECT_EQ(std_ret->first, ft_ret->first);
    EXPECT_EQ(std_ret->second, ft_ret->second);

    //последний элемент
    std_ret = std_map.upper_bound('e');
    ft_ret = ft_map.upper_bound('e');
    EXPECT_EQ(std_ret, std_map.end());
    EXPECT_EQ(ft_ret, ft_map.end());

    //не существующий элемент
    std_ret = std_map.upper_bound('q');
    ft_ret = ft_map.upper_bound('q');
    EXPECT_EQ(std_ret, std_map.end());
    EXPECT_EQ(ft_ret, ft_map.end());

    //const
    std::map<char,int>::const_iterator std_ret2 = std_map.upper_bound('b');
    ft::map<char,int>::const_iterator ft_ret2 = ft_map.upper_bound('b');
    EXPECT_EQ(std_ret2->first, ft_ret2->first);
    EXPECT_EQ(std_ret2->second, ft_ret2->second);
}

TEST(Map_Operations, equal_range) {
    std::map<char,int> std_map;
    ft::map<char,int> ft_map;

    ft_map['a']=10;
    ft_map['b']=20;
    ft_map['c']=30;
    std_map['a']=10;
    std_map['b']=20;
    std_map['c']=30;

    std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> std_ret;
    std::pair<ft::map<char,int>::iterator, ft::map<char,int>::iterator> ft_ret;

    //первыйы элемент
    std_ret = std_map.equal_range('a');
    ft_ret = ft_map.equal_range('a');

    EXPECT_EQ(std_ret.first->first, ft_ret.first->first);
    EXPECT_EQ(std_ret.first->second, ft_ret.first->second);

    EXPECT_EQ(std_ret.second->first, ft_ret.second->first);
    EXPECT_EQ(std_ret.second->second, ft_ret.second->second);


    //элемент по середине
    std_ret = std_map.equal_range('b');
    ft_ret = ft_map.equal_range('b');

    EXPECT_EQ(std_ret.first->first, ft_ret.first->first);
    EXPECT_EQ(std_ret.first->second, ft_ret.first->second);

    EXPECT_EQ(std_ret.second->first, ft_ret.second->first);
    EXPECT_EQ(std_ret.second->second, ft_ret.second->second);

    //последний элемент
    std_ret = std_map.equal_range('c');
    ft_ret = ft_map.equal_range('c');

    EXPECT_EQ(std_ret.first->first, ft_ret.first->first);
    EXPECT_EQ(std_ret.first->second, ft_ret.first->second);

    EXPECT_EQ(std_ret.second, std_map.end());
    EXPECT_EQ(ft_ret.second, ft_map.end());

    //не существующий элемент
    std_ret = std_map.equal_range('g');
    ft_ret = ft_map.equal_range('g');

    EXPECT_EQ(std_ret.first, std_map.end());
    EXPECT_EQ(std_ret.first, std_map.end());

    EXPECT_EQ(std_ret.second, std_map.end());
    EXPECT_EQ(ft_ret.second, ft_map.end());


    // const
    std::pair<std::map<char,int>::const_iterator,std::map<char,int>::const_iterator> std_ret2;
    std::pair<ft::map<char,int>::const_iterator, ft::map<char,int>::const_iterator> ft_ret2;

    std_ret2 = std_map.equal_range('b');
    ft_ret2 = ft_map.equal_range('b');

    EXPECT_EQ(std_ret2.first->first, ft_ret2.first->first);
    EXPECT_EQ(std_ret2.first->second, ft_ret2.first->second);

    EXPECT_EQ(std_ret2.second->first, ft_ret2.second->first);
    EXPECT_EQ(std_ret2.second->second, ft_ret2.second->second);
}

