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

    std_res = std_map.insert ( std::pair<int, std::string>(10, "value" ) );
    ft_res = ft_map.insert ( std::pair<int, std::string>(10, "value" ) );
    EXPECT_EQ(std_map.size(), ft_map.size());

    EXPECT_EQ(std_res.first->first, ft_res.first->first);
    EXPECT_EQ(std_res.first->second, ft_res.first->second);
    EXPECT_EQ(std_res.second, ft_res.second);

    srand(time(0));
    int n = 10;
    int key;
    std::string value;
    while (n--) {
        key = getRandomInt();
        value = getRandomStr();
        std_res = std_map.insert ( std::pair<int, std::string>(key, value ) );
        ft_res = ft_map.insert ( std::pair<int, std::string>(key, value ) );
        EXPECT_EQ(std_map.size(), ft_map.size());

        EXPECT_EQ(std_res.first->first, ft_res.first->first);
        EXPECT_EQ(std_res.first->second, ft_res.first->second);
        EXPECT_EQ(std_res.second, ft_res.second);
    }
    checkTwoMaps(std_map, ft_map);
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

    FAIL();
    std::map<char,int> mymap;

    mymap['a']=10;
    mymap['b']=20;
    mymap['c']=30;

    while (!mymap.empty())
    {
        std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
        mymap.erase(mymap.begin());
    }
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

    std::map<char,std::string> mymap;

    mymap['a'] = "an element";
    mymap['b'] = "another element";
//    mymap['b'] = "another element";
//    mymap['c']=mymap['b'];
    mymap['c'] = mymap['b'];

    std::cout << "mymap['a'] is " << mymap['a'] << '\n';
    std::cout << "mymap['b'] is " << mymap['b'] << '\n';
    std::cout << "mymap['c'] is " << mymap['c'] << '\n';
    std::cout << "mymap['d'] is " << mymap['d'] << '\n';

    std::cout << "mymap now contains " << mymap.size() << " elements.\n";

    FAIL();
}

//TEST(test, test) {
//
//    while (1) ;
//}
