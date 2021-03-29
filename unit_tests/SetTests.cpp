#include "set.hpp"
#include "gtest/gtest.h"
#include <set>

template <typename T, typename S>
void checkTwoSets(T & std_set, S & ft_set) {
    typename T::iterator std_it = std_set.begin();
    typename T::iterator std_ite = std_set.end();
    typename S::iterator ft_it = ft_set.begin();
    typename S::iterator ft_ite = ft_set.end();
    EXPECT_EQ(std_set.size(), ft_set.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

template <typename T, typename S>
void checkTwoSets_const_iterator(T & std_set, S & ft_set) {
    typename T::const_iterator std_it = std_set.begin();
    typename T::const_iterator std_ite = std_set.end();
    typename S::const_iterator ft_it = ft_set.begin();
    typename S::const_iterator ft_ite = ft_set.end();
    EXPECT_EQ(std_set.size(), ft_set.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}
template <typename T, typename S>
void checkTwoSets_reverse_iterator(T & std_set, S & ft_set) {
    typename T::reverse_iterator std_it = std_set.rbegin();
    typename T::reverse_iterator std_ite = std_set.rend();
    typename S::reverse_iterator ft_it = ft_set.rbegin();
    typename S::reverse_iterator ft_ite = ft_set.rend();
    EXPECT_EQ(std_set.size(), ft_set.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}
template <typename T, typename S>
void checkTwoSets_const_reverse_iterator(T & std_set, S & ft_set) {
    typename T::const_reverse_iterator std_it = std_set.rbegin();
    typename T::const_reverse_iterator std_ite = std_set.rend();
    typename S::const_reverse_iterator ft_it = ft_set.rbegin();
    typename S::const_reverse_iterator ft_ite = ft_set.rend();
    EXPECT_EQ(std_set.size(), ft_set.size());
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
    while (std_it != std_ite && ft_it != ft_ite) {
        EXPECT_EQ(*std_it, *ft_it);
        std_it++;
        ft_it++;
    }
    ASSERT_EQ((std_it == std_ite), (ft_it == ft_ite));
}

struct classcomp {
    bool operator() (const int& lhs, const int& rhs) const
    {return lhs<rhs;}
};


TEST(Set_Base, empty_constructor1) {
    std::set<int> std_set;
    ft::set<int> ft_map;

    EXPECT_EQ(std_set.size(), ft_map.size());
    checkTwoSets(std_set, ft_map);

    for (int i = 0; i < 10; i++) {
        std_set.insert(i);
        ft_map.insert(i);
    }

    checkTwoSets(std_set, ft_map);
}

TEST(Set_Base, empty_constructor2) {
    std::set<std::string> std_set;
    ft::set<std::string> ft_set;

    EXPECT_EQ(std_set.size(), ft_set.size());

    std_set.insert("1");
    ft_set.insert("1");

    std_set.insert("1sdfsdfsdfs");
    ft_set.insert("1sdfsdfsdfs");

    std_set.insert("12");
    ft_set.insert("12");

    std_set.insert("dvxc1");
    ft_set.insert("dvxc1");

    checkTwoSets(std_set, ft_set);
}

TEST(Set_Base, range_constructor) {
    std::set<char> a;
    ft::set<char> b;

    for (char symbol = 'a'; symbol < 'm'; symbol++) {
        a.insert(symbol);
        b.insert(symbol);
    }

    std::set<char, classcomp> a2 (++a.begin(), a.end());
    ft::set<char, classcomp> b2 (++a.begin(), a.end());
    checkTwoSets(a, b);
    checkTwoSets(a2, b2);
}

TEST(Set_Base, copy_constructor) {
    std::set<char> a;
    ft::set<char> b;

    for (char symbol = 'm'; symbol < 'w'; symbol++) {
        a.insert(symbol);
        b.insert(symbol);
    }

    std::set<char> a2(a);
    ft::set<char> b2(b);
    checkTwoSets(a, b);
    checkTwoSets(a2, b2);

    a.insert('.');
    b.insert('.');

    checkTwoSets(a, b);
    checkTwoSets(a2, b2);
}

TEST(Set_Base, operator_equal) {
    std::set<char> a;
    ft::set<char> b;

    for (char symbol = 'm'; symbol < 'w'; symbol++) {
        a.insert(symbol);
        b.insert(symbol);
    }

    std::set<char> a2 = a;
    ft::set<char> b2 = b;
    checkTwoSets(a, b);
    checkTwoSets(a2, b2);
}


/////* Iterators */
TEST(Set_Iterators, iterator) {
    std::set<char> a;
    ft::set<char> b;

    for (char key = 'a'; key != 'm'; key++) {
        a.insert(key);
        b.insert(key);
    }
    checkTwoSets(a, b);

    std::set<char>::iterator std_it = a.begin();
    ft::set<char>::iterator ft_it = b.begin();
    std::set<char>::iterator std_ite = a.end();
    ft::set<char>::iterator ft_ite = b.end();

    EXPECT_EQ((*std_it), (*ft_it));

    ++std_it;
    ++ft_it;
    EXPECT_EQ((*std_it), (*ft_it));
    std_it++;
    ft_it++;
    EXPECT_EQ((*std_it), (*ft_it));
    std_it--;
    ft_it--;
    EXPECT_EQ((*std_it), (*ft_it));
    --std_it;
    --ft_it;
    EXPECT_EQ((*std_it), (*ft_it));
    std_it++;
    ft_it++;
    EXPECT_EQ((*std_it), (*ft_it));

    --std_ite;
    --ft_ite;
    EXPECT_EQ((*std_it), (*ft_it));
    std_ite--;
    ft_ite--;
    EXPECT_EQ((*std_it), (*ft_it));
    ++std_ite;
    ++ft_ite;
    EXPECT_EQ((*std_it), (*ft_it));
    std_ite++;
    ft_ite++;
    //здесь нельзя разыменовывать
    --std_ite;
    --ft_ite;
    EXPECT_EQ((*std_it), (*ft_it));

    EXPECT_EQ((*std_it), (*ft_it));

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoSets(a, b);
}

TEST(Set_Iterators, const_iterator) {
    std::set<int> a;
    ft::set<int> b;

    checkTwoSets_const_iterator(a, b);

    for (int key = 12; key != 45; key++) {
        a.insert(key);
        b.insert(key);
    }
    checkTwoSets_const_iterator(a, b);

    std::set<int>::const_iterator std_it = a.begin();
    ft::set<int>::const_iterator ft_it = b.begin();
    std::set<int>::const_iterator std_ite = a.end();
    ft::set<int>::const_iterator ft_ite = b.end();

    EXPECT_EQ((*std_it), (*ft_it));

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

    EXPECT_EQ((*std_it), (*ft_it));

    EXPECT_EQ(std_it == std_ite, std_it == std_ite);
    EXPECT_EQ(std_it != std_ite, std_it != std_ite);

    checkTwoSets_const_iterator(a, b);
}

TEST(Set_Iterators, reverse_iterator) {
    std::set<int> a;
    ft::set<int> b;

    checkTwoSets_const_reverse_iterator(a, b);
    for (int key = 12; key != 45; key++) {
        a.insert(key);
        b.insert(key);
    }

    std::set<int>::reverse_iterator std_it = a.rbegin();
    ft::set<int>::reverse_iterator ft_it = b.rbegin();
    std::set<int>::reverse_iterator std_ite = a.rend();
    ft::set<int>::reverse_iterator ft_ite = b.rend();

    EXPECT_EQ((*std_it), (*ft_it));

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

    checkTwoSets_const_reverse_iterator(a, b);
}

TEST(Set_Iterators, const_reverse_iterator) {
    std::set<int> a;
    ft::set<int> b;

    checkTwoSets_const_reverse_iterator(a, b);
    for (int key = 12; key != 45; key++) {
        a.insert(key);
        b.insert(key);
    }
    checkTwoSets_const_reverse_iterator(a, b);

    std::set<int>::const_reverse_iterator std_it = a.rbegin();
    ft::set<int>::const_reverse_iterator ft_it = b.rbegin();
    std::set<int>::const_reverse_iterator std_ite = a.rend();
    ft::set<int>::const_reverse_iterator ft_ite = b.rend();

    EXPECT_EQ(*std_it, *ft_it);

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

    checkTwoSets_const_reverse_iterator(a, b);
}


///* Capacity and Element access */
TEST(Set_Capacity_Element_Access, empty) {
    std::set<std::string> std_set;
    ft::set<std::string> ft_set;

    EXPECT_EQ(std_set.empty(), ft_set.empty());

    std_set.insert ("value");
    ft_set.insert ("value");
    EXPECT_EQ(std_set.size(), ft_set.size());

    std::set<char> std_set2;
    ft::set<char> ft_set2;

    std_set2.insert('a');
    std_set2.insert('b');
    std_set2.insert('c');
    ft_set2.insert('a');
    ft_set2.insert('b');
    ft_set2.insert('c');
    while (!std_set.empty()) {
        checkTwoSets(std_set, ft_set);
        std_set.erase(std_set.begin());
        ft_set.erase(ft_set.begin());
    }
    EXPECT_EQ(std_set.empty(), ft_set.empty());
}

TEST(Set_Capacity_Element_Access, size) {
    std::set<std::string> std_set;
    ft::set<std::string> ft_set;

    EXPECT_EQ(std_set.size(), ft_set.size());

    std_set.insert ( "value" );
    ft_set.insert ( "value" );
    EXPECT_EQ(std_set.size(), ft_set.size());

    std_set.insert ( "value2");
    ft_set.insert ( "value2");
    EXPECT_EQ(std_set.size(), ft_set.size());

    std_set.insert ( "value3" );
    ft_set.insert ("value3" );
    EXPECT_EQ(std_set.size(), ft_set.size());
}


/* Modifiers */
TEST(Set_Modifiers, insert) {
    std::set<char> std_set;
    ft::set<char> ft_set;

    std::pair<std::set<char>::iterator,bool> std_ret;
    std::pair<ft::set<char>::iterator,bool> ft_ret;
    for (char key = 'a'; key != 'm'; key++) {
        std_ret = std_set.insert (key);
        ft_ret = ft_set.insert (key );
        EXPECT_EQ(*std_ret.first, *ft_ret.first);
        EXPECT_EQ(std_ret.second, ft_ret.second);
    }
    checkTwoSets(std_set, ft_set);

    std::set<char>::iterator std_it = std_set.begin();
    ft::set<char>::iterator ft_it = ft_set.begin();
    std::set<char>::iterator std_it2 = std_set.insert (std_it, '!');
    ft::set<char>::iterator ft_it2 = ft_set.insert (ft_it, '!');
    EXPECT_EQ(*std_it2, *ft_it2);
    checkTwoSets(std_set, ft_set);

    std::set<char> std_map2;
    std_map2.insert(std_set.begin(), std_set.end()--);
    ft::set<char> ft_map2;
    ft_map2.insert(ft_set.begin(), ft_set.end()--);
    checkTwoSets(std_map2, ft_map2);
}

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkMapsAreEqualIt(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe) {
    for (; itS != itSe; ) {
        EXPECT_EQ(*itS++, *itF++);
    }
    EXPECT_EQ(itF, itFe);
}

class Set_Modifiers_Erase : public testing::Test {
protected:
    virtual void SetUp() {
        s.insert("a");
        s.insert("b");
        s.insert("c");
        f.insert("a");
        f.insert("b");
        f.insert("c");
    }

    std::set<std::string> s;
    ft::set<std::string>  f;
};

void	MapEraseSimpleTestFunc(ft::set<std::string> & ft_set, std::set<std::string> & std_set,
                               std::string s1, std::string s2, std::string s3) {
    size_t retf;
    size_t rets;

    rets = std_set.erase(s1 + s2 + s3);
    retf = ft_set.erase(s1 + s2 + s3);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_set.begin(), *ft_set.begin());
    EXPECT_EQ(*--std_set.end(), *--ft_set.end());
    checkTwoSets(ft_set, std_set);

    rets = std_set.erase(s1);
    retf = ft_set.erase(s1);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_set.begin(), *ft_set.begin());
    EXPECT_EQ(*--std_set.end(), *--ft_set.end());
    checkTwoSets(ft_set, std_set);

    rets = std_set.erase(s2);
    retf = ft_set.erase(s2);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(*std_set.begin(), *ft_set.begin());
    EXPECT_EQ(*--std_set.end(), *--ft_set.end());
    checkTwoSets(ft_set, std_set);

    rets = std_set.erase(s3);
    retf = ft_set.erase(s3);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(std_set.begin(), std_set.end());
    EXPECT_EQ(ft_set.begin(), ft_set.end());
    checkTwoSets(ft_set, std_set);

    rets = std_set.erase(s1);
    retf = ft_set.erase(s1);
    EXPECT_EQ(retf, rets);
    EXPECT_EQ(std_set.begin(), std_set.end());
    EXPECT_EQ(ft_set.begin(), ft_set.end());
    checkTwoSets(ft_set, std_set);
}

TEST_F(Set_Modifiers_Erase, erase1) {
    MapEraseSimpleTestFunc(f, s, "a", "b", "c");
}

TEST_F(Set_Modifiers_Erase, erase2) {
    MapEraseSimpleTestFunc(f, s, "a", "c", "b");
}

TEST_F(Set_Modifiers_Erase, erase3) {
    MapEraseSimpleTestFunc(f, s, "b", "a", "c");
}

TEST_F(Set_Modifiers_Erase, erase4) {
    MapEraseSimpleTestFunc(f, s, "b", "c", "a");
}

TEST_F(Set_Modifiers_Erase, erase5) {
    MapEraseSimpleTestFunc(f, s, "c", "a", "b");
}

TEST_F(Set_Modifiers_Erase, erase6) {
    MapEraseSimpleTestFunc(f, s, "c", "b", "a");
}

class Set_Erase_No_Contain_Test : public testing::Test {
protected:
    virtual void SetUp() {
        for (char i = 'b'; i < 'z' ; ++i) {
            ss << i << i;
            s.insert(ss.str());
            f.insert(ss.str());
            ss.str("");
        }
    }

    std::stringstream ss;

    std::set<std::string> s;
    ft::set<std::string>  f;

    size_t retf;
    size_t rets;
};

TEST_F(Set_Erase_No_Contain_Test, erase7) {
    for (char i = 'a'; i <= 'z' ; ++i) {
        ss << i << i << i;
        rets = s.erase(ss.str());
        retf = f.erase(ss.str());
        EXPECT_EQ(retf, rets);
        EXPECT_EQ(*s.begin(), *f.begin());
        EXPECT_EQ(*--s.end(), *--f.end());
        checkTwoSets(f, s);
        ss.str("");
    }

    for (char i = 'a'; i <= 'z' ; ++i) {
        ss << i;
        rets = s.erase(ss.str());
        retf = f.erase(ss.str());
        EXPECT_EQ(retf, rets);
        EXPECT_EQ(*s.begin(), *f.begin());
        EXPECT_EQ(*--s.end(), *--f.end());
        checkTwoSets(f, s);
        ss.str("");
    }
}

class Set_Erase_By_Iterator_Test : public testing::Test {
protected:
    virtual void SetUp() {
        for (char i = 'b'; i < 'z' ; ++i) {
            ss << i << i;
            s.insert(ss.str());
            f.insert(ss.str());
            ss.str("");
        }
    }

    std::stringstream ss;

    std::set<std::string>::iterator its;
    ft::set<std::string>::iterator itf;
    std::set<std::string>::iterator itse;
    ft::set<std::string>::iterator itfe;

    std::set<std::string> s;
    ft::set<std::string>  f;
};

TEST_F(Set_Erase_By_Iterator_Test, erase8) {

    its = s.begin();
    itse = s.end();
    itf = f.begin();
    itfe = f.end();

    for (; s.begin() != itse; ) {
        s.erase(s.begin());
        f.erase(f.begin());
        checkTwoSets(f, s);
    }
    EXPECT_EQ(f.begin(), itfe);
}

TEST_F(Set_Erase_By_Iterator_Test, erase9) {

    its = s.begin();
    itse = s.end();
    itf = f.begin();
    itfe = f.end();

    while (s.size() != 0) {
        s.erase(--s.end());
        f.erase(--f.end());
        checkTwoSets(f, s);
    }
    EXPECT_EQ(f.size(), 0);
}

TEST_F(Set_Erase_By_Iterator_Test, erase10) {
    its = s.begin();
    itf = f.begin();

    for (int i = 0; i < 10; ++i) {
        s.erase(++s.begin());
        f.erase(++f.begin());
        EXPECT_EQ(s.size(), f.size());
        checkMapsAreEqualIt(itf, f.end(), its, s.end());
    }
}

TEST_F(Set_Erase_By_Iterator_Test, erase11) {
    ft::set<char> ft_set;
    ft::set<char>::iterator std_it;
    std::set<char> std_set;
    std::set<char>::iterator ft_it;

    ft_set.insert('a');		std_set.insert('a');
    ft_set.insert('b');		std_set.insert('b');
    ft_set.insert('c');		std_set.insert('c');
    ft_set.insert('d');		std_set.insert('d');
    ft_set.insert('e');		std_set.insert('e');
    ft_set.insert('f');		std_set.insert('f');
    ft_set.insert('g');		std_set.insert('g');
    ft_set.insert('h');		std_set.insert('h');
    ft_set.insert('j');		std_set.insert('j');
    ft_set.insert('k');		std_set.insert('k');

    std_it = ft_set.find('c'); ft_it = std_set.find('c');
    ft_set.erase('b');		std_set.erase('b');

    checkMapsAreEqualIt(std_it, ft_set.end(), ft_it, std_set.end());
}

TEST(Set_Modifiers, swap) {
    std::set<char> foo, bar;
    foo.insert('x');
    foo.insert('y');
    bar.insert('a');
    bar.insert('b');
    bar.insert('c');
    foo.swap(bar);

    ft::set<char> foo2, bar2;
    foo2.insert('x');
    foo2.insert('y');
    bar2.insert('a');
    bar2.insert('b');
    bar2.insert('c');
    foo2.swap(bar2);

    checkTwoSets(foo, foo2);
    checkTwoSets(bar, bar2);
}

TEST(Set_Modifiers, clear) {
    std::set<char>  std_set;
    ft::set<char>   ft_set;

    std_set.insert('x');
    std_set.insert('y');
    std_set.insert('z');
    ft_set.insert('x');
    ft_set.insert('y');
    ft_set.insert('z');
    checkTwoSets(std_set, ft_set);

    std_set.clear();
    ft_set.clear();
    checkTwoSets(std_set, ft_set);
}


/* Observers */
TEST(Set_Observers, key_comp) {
    std::set<char> std_set;
    std::set<char>::key_compare std_compare = std_set.key_comp();
    ft::set<char> ft_set;
    ft::set<char>::key_compare ft_compare = ft_set.key_comp();

    std_set.insert('x');
    std_set.insert('y');
    std_set.insert('z');
    ft_set.insert('x');
    ft_set.insert('y');
    ft_set.insert('z');

    char highest = *std_set.rbegin();
    char highest2 = *ft_set.rbegin();

    std::set<char>::iterator it = std_set.begin();
    ft::set<char>::iterator it2 = ft_set.begin();

    while ( std_compare((*it), highest) && ft_compare((*it), highest2)) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }
    EXPECT_EQ(*(--it), *(--it2));
}

TEST(Set_Observers, value_comp) {
    std::set<char> std_set;
    ft::set<char> ft_set;

    std_set.insert('x');
    std_set.insert('y');
    std_set.insert('z');
    ft_set.insert('x');
    ft_set.insert('y');
    ft_set.insert('z');

    std::set<char>::iterator it = std_set.begin();
    ft::set<char>::iterator it2 = ft_set.begin();

    while ( std_set.value_comp()(*it, *std_set.rbegin()) && ft_set.value_comp()(*it, *ft_set.rbegin())) {
        EXPECT_EQ(*it, *it2);
        it++;
        it2++;
    }
    EXPECT_EQ(*(--it), *(--it2));
}


/* Operations */
TEST(Set_Operations, find) {
    std::set<char> std_set;
    ft::set<char> ft_set;
    std::set<char>::iterator std_it;
    ft::set<char>::iterator ft_it;

    std_set.insert('x');
    std_set.insert('y');
    std_set.insert('z');
    ft_set.insert('x');
    ft_set.insert('y');
    ft_set.insert('z');

    for (char symbol = 'x'; symbol != 'z'; symbol++) {
        std_it = std_set.find(symbol);
        ft_it = ft_set.find(symbol);
        EXPECT_EQ(*std_it, *ft_it);
    }
    std_it = std_set.find('a');
    ft_it = ft_set.find('a');

    EXPECT_EQ(std_it, std_set.end());
    EXPECT_EQ(ft_it, ft_set.end());

}

TEST(Set_Operations, count) {
    std::set<char> std_set;
    ft::set<char> ft_set;
    std::set<char>::iterator std_it;
    ft::set<char>::iterator ft_it;

    std_set.insert('a');
    std_set.insert('b');
    std_set.insert('c');
    ft_set.insert('a');
    ft_set.insert('b');
    ft_set.insert('c');

    for (char symbol = 'a'; symbol < 'h'; symbol++)
        EXPECT_EQ(std_set.count(symbol), ft_set.count(symbol));
}

TEST(Set_Operations, lower_bound) {
    std::set<std::string> std_set;
    ft::set<std::string> ft_set;

    ft_set.insert("10");
    ft_set.insert("20");
    ft_set.insert("30");
    ft_set.insert("30");
    ft_set.insert("30");

    std_set.insert("10");
    std_set.insert("20");
    std_set.insert("30");
    std_set.insert("30");
    std_set.insert("30");

    std::set<std::string>::iterator std_ret;
    ft::set<std::string>::iterator ft_ret;

    //первый элемент
    std_ret = std_set.lower_bound("10");
    ft_ret = ft_set.lower_bound("10");
    EXPECT_EQ(*std_ret, *ft_ret);

    //элемент по середине
    std_ret = std_set.lower_bound("20");
    ft_ret = ft_set.lower_bound("20");
    EXPECT_EQ(*std_ret, *ft_ret);


    //последний элемент
    std_ret = std_set.lower_bound("30");
    ft_ret = ft_set.lower_bound("30");
    EXPECT_EQ(*std_ret, *ft_ret);

    //не существующий элемент
    std_ret = std_set.lower_bound("q");
    ft_ret = ft_set.lower_bound("q");
    EXPECT_EQ(ft_ret, ft_set.end());
    EXPECT_EQ(std_ret, std_set.end());
}

TEST(Set_Operations, upper_bound) {
    std::set<std::string> std_set;
    ft::set<std::string> ft_set;

    ft_set.insert("10");
    ft_set.insert("20");
    ft_set.insert("30");
    ft_set.insert("30");
    ft_set.insert("30");

    std_set.insert("10");
    std_set.insert("20");
    std_set.insert("30");
    std_set.insert("30");
    std_set.insert("30");

    std::set<std::string>::iterator std_ret;
    ft::set<std::string>::iterator ft_ret;

    //первый элемент
    std_ret = std_set.upper_bound("10");
    ft_ret = ft_set.upper_bound("10");
    EXPECT_EQ(*std_ret, *ft_ret);

    //элемент по середине
    std_ret = std_set.upper_bound("20");
    ft_ret = ft_set.upper_bound("20");
    EXPECT_EQ(*std_ret, *ft_ret);

    //последний элемент
    std_ret = std_set.upper_bound("30");
    ft_ret = ft_set.upper_bound("30");
    EXPECT_EQ(ft_ret, ft_set.end());
    EXPECT_EQ(std_ret, std_set.end());

    //не существующий элемент
    std_ret = std_set.upper_bound("q");
    ft_ret = ft_set.upper_bound("q");
    EXPECT_EQ(ft_ret, ft_set.end());
    EXPECT_EQ(std_ret, std_set.end());
}

TEST(Set_Operations, equal_range) {
    std::set<char> std_set;
    ft::set<char> ft_set;

    std_set.insert('a');
    std_set.insert('b');
    std_set.insert('c');
    ft_set.insert('a');
    ft_set.insert('b');
    ft_set.insert('c');

    std::pair<std::set<char>::iterator,std::set<char>::iterator> std_ret;
    std::pair<ft::set<char>::iterator, ft::set<char>::iterator> ft_ret;

    //первыйы элемент
    std_ret = std_set.equal_range('a');
    ft_ret = ft_set.equal_range('a');
    EXPECT_EQ(*std_ret.first, *ft_ret.first);
    EXPECT_EQ(*std_ret.second, *ft_ret.second);

    //элемент по середине
    std_ret = std_set.equal_range('b');
    ft_ret = ft_set.equal_range('b');
    EXPECT_EQ(*std_ret.first, *ft_ret.first);
    EXPECT_EQ(*std_ret.second, *ft_ret.second);

    //последний элемент
    std_ret = std_set.equal_range('c');
    ft_ret = ft_set.equal_range('c');
    EXPECT_EQ(*std_ret.first, *ft_ret.first);
    EXPECT_EQ(std_ret.second, std_set.end());
    EXPECT_EQ(ft_ret.second, ft_set.end());

    //не существующий элемент
    std_ret = std_set.equal_range('g');
    ft_ret = ft_set.equal_range('g');
    EXPECT_EQ(std_ret.first, std_set.end());
    EXPECT_EQ(ft_ret.first, ft_set.end());
    EXPECT_EQ(std_ret.second, std_set.end());
    EXPECT_EQ(ft_ret.second, ft_set.end());
}

//TEST(sdf, ssdfsf) {
//    while (1);
//}

