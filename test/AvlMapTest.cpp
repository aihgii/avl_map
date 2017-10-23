#include "gtest/gtest.h"
#include "../include/avl_map.h"

class AvlMapTest : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}
};

TEST_F(AvlMapTest, IsEmptyInitially) {
    typedef not_std::map<int, double> M;
    M m;

    EXPECT_TRUE(m.empty());
    EXPECT_EQ(0, m.size());
}

TEST_F(AvlMapTest, InsertAndClear) {
    typedef not_std::map<int, double> M;
    M m;

    assert(m.empty());
    m.insert(M::value_type(1, 1.5));
    assert(!m.empty());
    m.clear();
    assert(m.empty());
}

TEST_F(AvlMapTest, At) {
    typedef std::pair<const int, double> V;
    V ar[] =
            {
                    V(1, 1.5),
                    V(2, 2.5),
                    V(3, 3.5),
                    V(4, 4.5),
                    V(5, 5.5),
                    V(7, 7.5),
                    V(8, 8.5),
            };

    not_std::map<int, double> m(ar, ar+sizeof(ar)/sizeof(ar[0]));
    assert(m.size() == 7);
    assert(m.at(1) == 1.5);
    m.at(1) = -1.5;
    assert(m.at(1) == -1.5);
    assert(m.at(2) == 2.5);
    assert(m.at(3) == 3.5);
    assert(m.at(4) == 4.5);
    assert(m.at(5) == 5.5);

    try
    {
        m.at(6);
        assert(false);
    }
    catch (std::out_of_range&)
    { }

    assert(m.at(7) == 7.5);
    assert(m.at(8) == 8.5);
    assert(m.size() == 7);
}

TEST_F(AvlMapTest, Index) {
    typedef std::pair<const int, double> V;
    V ar[] =
            {
                    V(1, 1.5),
                    V(2, 2.5),
                    V(3, 3.5),
                    V(4, 4.5),
                    V(5, 5.5),
                    V(7, 7.5),
                    V(8, 8.5),
            };

    not_std::map<int, double> m(ar, ar+sizeof(ar)/sizeof(ar[0]));
    assert(m.size() == 7);
    assert(m[1] == 1.5);
    assert(m.size() == 7);
    m[1] = -1.5;
    assert(m[1] == -1.5);
    assert(m.size() == 7);
    assert(m[6] == 0);
    assert(m.size() == 8);
    m[6] = 6.5;
    assert(m[6] == 6.5);
    assert(m.size() == 8);
}

TEST_F(AvlMapTest, TupleIndex) {
    using namespace std;
    not_std::map<tuple<int,int>, size_t> m;
    m[make_tuple(2,3)]=7;
}

TEST_F(AvlMapTest, Iterator) {
    {
        typedef std::pair<const int, double> V;
        V ar[] =
                {
                        V(1, 1),
                        V(1, 1.5),
                        V(1, 2),
                        V(2, 1),
                        V(2, 1.5),
                        V(2, 2),
                        V(3, 1),
                        V(3, 1.5),
                        V(3, 2),
                        V(4, 1),
                        V(4, 1.5),
                        V(4, 2),
                        V(5, 1),
                        V(5, 1.5),
                        V(5, 2),
                        V(6, 1),
                        V(6, 1.5),
                        V(6, 2),
                        V(7, 1),
                        V(7, 1.5),
                        V(7, 2),
                        V(8, 1),
                        V(8, 1.5),
                        V(8, 2)
                };
        not_std::map<int, double> m(ar, ar+sizeof(ar)/sizeof(ar[0]));
        assert(static_cast<std::size_t>(std::distance(m.begin(), m.end())) == m.size());
        assert(static_cast<std::size_t>(std::distance(m.rbegin(), m.rend())) == m.size());
        not_std::map<int, double>::iterator i;
        i = m.begin();
        not_std::map<int, double>::const_iterator k = i;
        assert(i == k);
        for (int j = 1; static_cast<std::size_t>(j) <= m.size(); ++j, ++i)
        {
            assert(i->first == j);
            assert(i->second == 1);
            i->second = 2.5;
            assert(i->second == 2.5);
        }
    }
    {
        typedef std::pair<const int, double> V;
        V ar[] =
                {
                        V(1, 1),
                        V(1, 1.5),
                        V(1, 2),
                        V(2, 1),
                        V(2, 1.5),
                        V(2, 2),
                        V(3, 1),
                        V(3, 1.5),
                        V(3, 2),
                        V(4, 1),
                        V(4, 1.5),
                        V(4, 2),
                        V(5, 1),
                        V(5, 1.5),
                        V(5, 2),
                        V(6, 1),
                        V(6, 1.5),
                        V(6, 2),
                        V(7, 1),
                        V(7, 1.5),
                        V(7, 2),
                        V(8, 1),
                        V(8, 1.5),
                        V(8, 2)
                };
        const not_std::map<int, double> m(ar, ar+sizeof(ar)/sizeof(ar[0]));
        assert(static_cast<std::size_t>(std::distance(m.begin(), m.end())) == m.size());
        assert(static_cast<std::size_t>(std::distance(m.cbegin(), m.cend())) == m.size());
        assert(static_cast<std::size_t>(std::distance(m.rbegin(), m.rend())) == m.size());
        assert(static_cast<std::size_t>(std::distance(m.crbegin(), m.crend())) == m.size());
        not_std::map<int, double>::const_iterator i;
        i = m.begin();
        for (int j = 1; static_cast<std::size_t>(j) <= m.size(); ++j, ++i)
        {
            assert(i->first == j);
            assert(i->second == 1);
        }
    }
}

TEST_F(AvlMapTest, Size){
    typedef not_std::map<int, double> M;
    M m;
    assert(m.size() == 0);
    m.insert(M::value_type(2, 1.5));
    assert(m.size() == 1);
    m.insert(M::value_type(1, 1.5));
    assert(m.size() == 2);
    m.insert(M::value_type(3, 1.5));
    assert(m.size() == 3);
    m.erase(m.begin());
    assert(m.size() == 2);
    m.erase(m.begin());
    assert(m.size() == 1);
    m.erase(m.begin());
    assert(m.size() == 0);
}
