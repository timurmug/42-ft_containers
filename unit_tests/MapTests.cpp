//
// Created by Quaro Tamarillo on 1/25/21.
//

#include "map.hpp"
#include "gtest/gtest.h"
#include <map>

//static const char alphabet[] =
//        "0123456789"
//        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//        "abcdefghijklmnopqrstuvwxyz";
//
//std::string getRandomStr() {
//    const int len = rand() % 10;
//    std::string randomStr;
//    randomStr.reserve(len);
//    for (int i = 0; i < len; ++i)
//        randomStr += alphabet[rand() % (sizeof(alphabet) - 1)];
//    return randomStr;
//}
//int         getRandomInt() {
//    int randomInt = randomInt = rand();
//    if (rand() % 2 == 1)
//        randomInt *= -1;
//    return randomInt;
//}
//char        getRandomChar() {
//    return alphabet[rand() % (sizeof(alphabet) - 1)];
//}

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

    std_map.insert ( std::pair<int, std::string>(1, "value" ) );
    ft_map.insert ( std::pair<int, std::string>(1, "value" ) );
    std_map.insert ( std::pair<int, std::string>(2, "value" ) );
    ft_map.insert ( std::pair<int, std::string>(2, "value" ) );
    std_map.insert ( std::pair<int, std::string>(3, "value" ) );
    ft_map.insert ( std::pair<int, std::string>(3, "value" ) );

    checkTwoMaps(std_map, ft_map);
}

TEST(Map_Base, empty_constructor2) {
    std::map<std::string, int> std_map;
    ft::map<std::string, int> ft_map;

    EXPECT_EQ(std_map.size(), ft_map.size());

    std_map.insert(std::pair<std::string, int>("1", 2));
    ft_map.insert ( std::pair<std::string, int>("1", 2 ) );

    std_map.insert ( std::pair<std::string, int>("sdf", 3 ) );
    ft_map.insert ( std::pair<std::string, int>("sdf", 3) );

    std_map.insert ( std::pair<std::string, int>("fd", 5) );
    ft_map.insert ( std::pair<std::string, int>("fd", 5 ) );

    std_map.insert ( std::pair<std::string, int>("12", 5) );
    ft_map.insert ( std::pair<std::string, int>("12", 5 ) );

    checkTwoMaps(std_map, ft_map);
}

TEST(Map_Base, range_constructor) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    a.insert(std::pair<char, int>('b', 12 ));
    b.insert(std::pair<char, int>('b', 12 ));

    a.insert(std::pair<char, int>('a', 12 ));
    b.insert(std::pair<char, int>('a', 12 ));

    a.insert(std::pair<char, int>('c', 12 ));
    b.insert(std::pair<char, int>('c', 12 ));

    a.insert(std::pair<char, int>('d', 12 ));
    b.insert(std::pair<char, int>('d', 12 ));

    for (char key = 't'; key != 'z'; key++) {
        a[key] = 12;
        b[key] = 12;
    }

    std::map<char, int, classcomp> a2 (++a.begin(), a.end());
    ft::map<char, int, classcomp> b2 (++a.begin(), a.end());
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);
}

TEST(Map_Base, copy_constructor) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    a.insert ( std::pair<char, int>('c', 2 ) );
    b.insert ( std::pair<char, int>('c', 2 ) );

    a.insert ( std::pair<char, int>('1', 3 ) );
    b.insert ( std::pair<char, int>('1', 3) );

    a.insert ( std::pair<char, int>('d', 5) );
    b.insert ( std::pair<char, int>('d', 5) );

    std::map<char, int> a2(a);
    ft::map<char, int> b2(b);
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);

    a.insert(std::pair<char, int>('.', 112 ));
    b.insert(std::pair<char, int>('.', 112 ));

    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);
}

TEST(Map_Base, operator_equal) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    a.insert ( std::pair<char, int>('c', 2 ) );
    b.insert ( std::pair<char, int>('c', 2 ) );

    a.insert ( std::pair<char, int>('1', 3 ) );
    b.insert ( std::pair<char, int>('1', 3) );

    a.insert ( std::pair<char, int>('d', 5) );
    b.insert ( std::pair<char, int>('d', 5) );

    std::map<char, int> a2 = a;
    ft::map<char, int> b2 = b;
    checkTwoMaps(a, b);
    checkTwoMaps(a2, b2);
}


/////* Iterators */
TEST(Map_Iterators, iterator) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::iterator, bool> std_res;
    std::pair<ft::map<char, int>::iterator, bool> ft_res;

    for (char key = 'a'; key != 'm'; key++) {
        a[key] = 2;
        b[key] = 2;
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

TEST(Map_Iterators, const_iterator) {
    std::map<char, int> a;
    ft::map<char, int> b;
    std::pair<std::map<char, int>::const_iterator, bool> std_res;
    std::pair<ft::map<char, int>::const_iterator, bool> ft_res;

    checkTwoMaps_const_iterator(a, b);

    for (char key = 'm'; key != 'w'; key++) {
        a[key] = 2;
        b[key] = 2;
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

TEST(Map_Iterators, reverse_iterator) {
    std::map<int, std::string> a;
    ft::map<int, std::string> b;
    std::pair<std::map<int, std::string>::iterator, bool> std_res;
    std::pair<ft::map<int, std::string>::iterator, bool> ft_res;

    checkTwoMaps_reverse_iterator(a, b);
    for (int i = 0; i != 12; i++) {
        a[i] = "fdfs";
        b[i] = "fdfs";
    }

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
    for (int i = 100; i != 75; i--) {
        a[i] = "fdfs";
        b[i] = "fdfs";
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


///* Capacity and Element access */
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
    int value = 124;
    char key = ' ';
    for (int i = 0; i != 10; i++) {
        std_ret = std_map.insert ( std::pair<char,int>(key, value) );
        ft_ret = ft_map.insert ( std::pair<char,int>(key, value) );
        EXPECT_EQ((*std_ret.first).first, (*ft_ret.first).first);
        EXPECT_EQ((*std_ret.first).second, (*ft_ret.first).second);
        EXPECT_EQ(std_ret.second, ft_ret.second);
        key++;
        value++;
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

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkMapsAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
    for (; itS != itSe; ) {
        EXPECT_EQ(*itS++, *itF++);
    }
    EXPECT_EQ(itF, itFe);
}

class Map_Modifiers_Erase : public testing::Test {
protected:
    virtual void SetUp() {
        s.insert(std::make_pair("a", 1));
        s.insert(std::make_pair("b", 1));
        s.insert(std::make_pair("c", 1));
        f.insert(std::make_pair("a", 1));
        f.insert(std::make_pair("b", 1));
        f.insert(std::make_pair("c", 1));
    }

    std::map<std::string, int> s;
    ft::map<std::string, int>  f;
};

void	MapEraseSimpleTestFunc(ft::map<std::string, int> & ft_map, std::map<std::string, int> & std_map,
                               std::string s1, std::string s2, std::string s3) {
    size_t retf;
    size_t rets;

    rets = std_map.erase(s1 + s2 + s3);
    retf = ft_map.erase(s1 + s2 + s3);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_map.begin(), *ft_map.begin());
    EXPECT_EQ(*--std_map.end(), *--ft_map.end());
    checkTwoMaps(ft_map, std_map);

    rets = std_map.erase(s1);
    retf = ft_map.erase(s1);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_map.begin(), *ft_map.begin());
    EXPECT_EQ(*--std_map.end(), *--ft_map.end());
    checkTwoMaps(ft_map, std_map);

    rets = std_map.erase(s2);
    retf = ft_map.erase(s2);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_map.begin(), *ft_map.begin());
    EXPECT_EQ(*--std_map.end(), *--ft_map.end());
    checkTwoMaps(ft_map, std_map);

    rets = std_map.erase(s3);
    retf = ft_map.erase(s3);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(std_map.begin(), std_map.end());
    EXPECT_EQ(ft_map.begin(), ft_map.end());
    checkTwoMaps(ft_map, std_map);

    rets = std_map.erase(s1);
    retf = ft_map.erase(s1);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(std_map.begin(), std_map.end());
    EXPECT_EQ(ft_map.begin(), ft_map.end());
    checkTwoMaps(ft_map, std_map);
}

TEST_F(Map_Modifiers_Erase, erase1) {
    MapEraseSimpleTestFunc(f, s, "a", "b", "c");
}

TEST_F(Map_Modifiers_Erase, erase2) {
    MapEraseSimpleTestFunc(f, s, "a", "c", "b");
}

TEST_F(Map_Modifiers_Erase, erase3) {
    MapEraseSimpleTestFunc(f, s, "b", "a", "c");
}

TEST_F(Map_Modifiers_Erase, erase4) {
    MapEraseSimpleTestFunc(f, s, "b", "c", "a");
}

TEST_F(Map_Modifiers_Erase, erase5) {
    MapEraseSimpleTestFunc(f, s, "c", "a", "b");
}

TEST_F(Map_Modifiers_Erase, erase6) {
    MapEraseSimpleTestFunc(f, s, "c", "b", "a");
}


class Map_Erase_No_Contain_Test : public testing::Test {
protected:
    virtual void SetUp() {
        for (char i = 'b'; i < 'z' ; ++i) {
            ss << i << i;
            s.insert(std::make_pair(ss.str(), i));
            f.insert(std::make_pair(ss.str(), i));
            ss.str("");
        }
    }

    std::stringstream ss;

    std::map<std::string, int> s;
    ft::map<std::string, int>  f;

    size_t retf;
    size_t rets;
};

TEST_F(Map_Erase_No_Contain_Test, erase7) {
    for (char i = 'a'; i <= 'z' ; ++i) {
        ss << i << i << i;
        rets = s.erase(ss.str());
        retf = f.erase(ss.str());
        EXPECT_EQ(retf, rets);
        EXPECT_EQ(*s.begin(), *f.begin());
        EXPECT_EQ(*--s.end(), *--f.end());
        checkTwoMaps(f, s);
        ss.str("");
    }

    for (char i = 'a'; i <= 'z' ; ++i) {
        ss << i;
        rets = s.erase(ss.str());
        retf = f.erase(ss.str());
        EXPECT_EQ(retf, rets);
        EXPECT_EQ(*s.begin(), *f.begin());
        EXPECT_EQ(*--s.end(), *--f.end());
        checkTwoMaps(f, s);
        ss.str("");
    }
}

class Map_Erase_By_Iterator_Test : public testing::Test {
protected:
    virtual void SetUp() {
        for (char i = 'b'; i < 'z' ; ++i) {
            ss << i << i;
            s.insert(std::make_pair(ss.str(), i));
            f.insert(std::make_pair(ss.str(), i));
            ss.str("");
        }
    }

    std::stringstream ss;

    std::map<std::string, int>::iterator its;
    ft::map<std::string,  int>::iterator itf;
    std::map<std::string, int>::iterator itse;
    ft::map<std::string,  int>::iterator itfe;

    std::map<std::string, int> s;
    ft::map<std::string, int>  f;
};

TEST_F(Map_Erase_By_Iterator_Test, erase8) {

    its = s.begin();
    itse = s.end();
    itf = f.begin();
    itfe = f.end();

    for (; s.begin() != itse; ) {
        s.erase(s.begin());
        f.erase(f.begin());
        checkTwoMaps(f, s);
    }
    EXPECT_EQ(f.begin(), itfe);
}

TEST_F(Map_Erase_By_Iterator_Test, erase9) {

    its = s.begin();
    itse = s.end();
    itf = f.begin();
    itfe = f.end();

    while (s.size() != 0) {
        s.erase(--s.end());
        f.erase(--f.end());
        checkTwoMaps(f, s);
    }
    EXPECT_EQ(f.size(), 0);
}

TEST_F(Map_Erase_By_Iterator_Test, erase10) {
    its = s.begin();
    itf = f.begin();

    for (int i = 0; i < 10; ++i) {
        s.erase(++s.begin());
        f.erase(++f.begin());
        EXPECT_EQ(s.size(), f.size());
        checkMapsAreEqualIt(itf, f.end(), its, s.end());
    }
}

TEST_F(Map_Erase_By_Iterator_Test, erase11) {
    ft::map<char, int> ftmap;
    ft::map<char,int>::iterator itf;
    std::map<char, int> stmap;
    std::map<char, int>::iterator its;

    ftmap.insert(std::make_pair('a', 123));		stmap.insert(std::make_pair('a', 123));
    ftmap.insert(std::make_pair('b', 123));		stmap.insert(std::make_pair('b', 123));
    ftmap.insert(std::make_pair('c', 123));		stmap.insert(std::make_pair('c', 123));
    ftmap.insert(std::make_pair('d', 123));		stmap.insert(std::make_pair('d', 123));
    ftmap.insert(std::make_pair('e', 123));		stmap.insert(std::make_pair('e', 123));
    ftmap.insert(std::make_pair('f', 123));		stmap.insert(std::make_pair('f', 123));
    ftmap.insert(std::make_pair('g', 123));		stmap.insert(std::make_pair('g', 123));
    ftmap.insert(std::make_pair('h', 123));		stmap.insert(std::make_pair('h', 123));
    ftmap.insert(std::make_pair('j', 123));		stmap.insert(std::make_pair('j', 123));
    ftmap.insert(std::make_pair('k', 123));		stmap.insert(std::make_pair('k', 123));

    itf = ftmap.find('c');	its = stmap.find('c');
    ftmap.erase('b');		stmap.erase('b');

    checkMapsAreEqualIt(itf, ftmap.end(), its, stmap.end());
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
    std::map<char,int>  std_map;
    ft::map<char,int>   ft_map;

    std_map['x'] = 100;
    std_map['y'] = 200;
    std_map['z'] = 300;
    ft_map['x'] = 100;
    ft_map['y'] = 200;
    ft_map['z'] = 300;
    checkTwoMaps(std_map, ft_map);

    std_map.clear();
    ft_map.clear();
    checkTwoMaps(std_map, ft_map);
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

//TEST(sdf, ssdfsf) {
//    while (1);
//}
