#include "interval_map.hh"
#include "interval_map.cc"
#include <cstdio>
#include <cassert>
// Trivial check: no allocations == zero statistics.

/*struct TestKeyType
{
    unsigned int val;
    constexpr int(unsigned int val) : val(val) {}
    constexpr bool operator<(const int& other) const { return val < other.val; }
};*/

/*namespace std {
    template<> class numeric_limits<int> {
    public:
        static constexpr int lowest() { return int(numeric_limits<unsigned int>::lowest()); }
        //static constexpr int lowest() { return int(-250); }
    };
}*/

using TestValueType = char;

/*struct TestFloatKeyType
{
    float val;

    TestFloatKeyType() = default;

    TestFloatKeyType(float val) : val(val) {}
    bool operator< (TestFloatKeyType other) const
    {
        return other.val - val > 1.e-4f;
    }
};

namespace std {
    template<> class numeric_limits<TestFloatKeyType> {
    public:
        static TestFloatKeyType lowest() { return TestFloatKeyType(numeric_limits<float>::lowest()); }
    };
}*/

static void TEST_CASE_1()
{
    interval_map<int, TestValueType> m('A');
    m.assign(3, 3, 'B');
    assert(m.m_map.count(3) == 0);

    m.assign(3, 2, 'B');
    assert(m.m_map.count(2) == 0);
    assert(m.m_map.count(3) == 0);
}


static void TEST_CASE_2()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 10, 'B');
    assert(m[0] == 'A');
    for (int i = 1; i < 10; i++)
    {
        assert(m[i] == 'B');
    }
    assert(m[10] == 'A');
}

static void TEST_CASE_3()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 3, 'B');
    m.assign(6, 8, 'C');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'A');
    assert(m[4] == 'A');
    assert(m[5] == 'A');
    assert(m[6] == 'C');
    assert(m[7] == 'C');
    assert(m[8] == 'A');
}

static void TEST_CASE_4()
{
    interval_map<int, TestValueType> m('A');
    m.assign(std::numeric_limits<int>::lowest(), 10000, 'B');
    assert(m[0] == 'B');
    assert(m[9999] == 'B');
    assert(m[10000] == 'A');
}

static void TEST_CASE_5()
{
    interval_map<int, TestValueType> m('A');
    m.assign(std::numeric_limits<int>::lowest(), 10, 'B');
    m.assign(10, 20, 'B');
    assert(m[0] == 'B');
    assert(m[10] == 'B');
    assert(m[19] == 'B');
    assert(m[20] == 'A');
}

static void TEST_CASE_6()
{
    interval_map<float, TestValueType> m('A');
    m.assign(1.f, 5.f, 'B');
    assert(m[0.f] == 'A');
    assert(m[.999999999f] == 'B');
    assert(m[1.f] == 'B');
    assert(m[4.999f] == 'B');
    assert(m[5.f] == 'A');

}

static void TEST_CASE_7()
{
    interval_map<int, TestValueType> m('A');
    m.assign(3, 5, 'B');
    m.assign(1, 6, 'C');
    assert(m[0] == 'A');
    assert(m[1] == 'C');
    assert(m[2] == 'C');
    assert(m[3] == 'C');
    assert(m[4] == 'C');
    assert(m[5] == 'C');
    assert(m[6] == 'A');
}

static void TEST_CASE_8()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 6, 'C');
    m.assign(3, 5, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'C');
    assert(m[2] == 'C');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'C');
    assert(m[6] == 'A');
}

static void TEST_CASE_9()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'C');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'C');
    assert(m[4] == 'C');
    assert(m[5] == 'C');
    assert(m[6] == 'A');
}

static void TEST_CASE_10()
{
    interval_map<int, TestValueType> m('A');
    m.assign(3, 6, 'C');
    m.assign(1, 5, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'C');
    assert(m[6] == 'A');
}

static void TEST_CASE_11()
{
    interval_map<int, TestValueType> m('A');
    m.assign(3, 5, 'B');
    m.assign(1, 4, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'A');
}

static void TEST_CASE_12()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(3, 6, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'B');
    assert(m[6] == 'A');
}

static void TEST_CASE_13()
{
    interval_map<int, TestValueType> m('A');
    m.assign(2, 3, 'B');
    m.assign(1, 5, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'A');
}

static void TEST_CASE_14()
{
    interval_map<int, TestValueType> m('A');
    m.assign(2, 5, 'B');
    m.assign(5, 8, 'C');
    m.assign(4, 5, 'A');
    assert(m[0] == 'A');
    assert(m[1] == 'A');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'A');
    assert(m[5] == 'C');
    assert(m[6] == 'C');
    assert(m[7] == 'C');
    assert(m[8] == 'A');
}

static void TEST_CASE_15()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(2, 3, 'B');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'B');
    assert(m[5] == 'A');
}

static void TEST_CASE_16()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(4, 6, 'A');
    assert(m[0] == 'A');
    assert(m[1] == 'B');
    assert(m[2] == 'B');
    assert(m[3] == 'B');
    assert(m[4] == 'A');
    assert(m[5] == 'A');
}

static void TEST_CASE_17()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(1, 5, 'A');

    assert(m[0] == 'A');
    assert(m[1] == 'A');
    assert(m[2] == 'A');
    assert(m[3] == 'A');
    assert(m[4] == 'A');
    assert(m[5] == 'A');
}

static void TEST_CASE_18()
{
    interval_map<int, TestValueType> m('A');
    m.assign(1, 5, 'B');
    m.assign(0, 7, 'A');
    assert(m[0] == 'A');
    assert(m[1] == 'A');
    assert(m[2] == 'A');
    assert(m[3] == 'A');
    assert(m[4] == 'A');
    assert(m[5] == 'A');
}

static void TEST_CASE_19()
{
    interval_map<int, TestValueType> m('A');
    m.assign(3, 6, 'B');
    m.assign(2, 5, 'C');
    m.assign(4, 7, 'A');

    assert(m[1] == 'A');
    assert(m[2] == 'C');
    assert(m[3] == 'C');
    assert(m[4] == 'A');
    assert(m[5] == 'A');
    assert(m[6] == 'A');
    assert(m[7] == 'A');
}

static void TEST_CASE_20()
{
    interval_map<int,char> m('A');
    m.assign(3,17,'B');

    assert(m[0] ==  'A');
    assert(m[1] ==  'A');
    assert(m[2] ==  'A');
    assert(m[3] ==  'B');
    assert(m[4] ==  'B');
    assert(m[5] ==  'B');
    assert(m[6] ==  'B');
    assert(m[7] ==  'B');
    assert(m[8] ==  'B');
    assert(m[9] ==  'B');
    assert(m[10] == 'B');
    assert(m[11] == 'B');
    assert(m[12] == 'B');
    assert(m[13] == 'B');
    assert(m[14] == 'B');
    assert(m[15] == 'B');
    assert(m[16] == 'B');
    assert(m[17] == 'A');
    assert(m[18] == 'A');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(8,11,'C');
    assert(m[0] ==  'A');
    assert(m[1] ==  'A');
    assert(m[2] ==  'A');
    assert(m[3] ==  'B');
    assert(m[4] ==  'B');
    assert(m[5] ==  'B');
    assert(m[6] ==  'B');
    assert(m[7] ==  'B');
    assert(m[8] ==  'C');
    assert(m[9] ==  'C');
    assert(m[10] == 'C');
    assert(m[11] == 'B');
    assert(m[12] == 'B');
    assert(m[13] == 'B');
    assert(m[14] == 'B');
    assert(m[15] == 'B');
    assert(m[16] == 'B');
    assert(m[17] == 'A');
    assert(m[18] == 'A');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(5,9,'D');
    assert(m[0] ==  'A');
    assert(m[1] ==  'A');
    assert(m[2] ==  'A');
    assert(m[3] ==  'B');
    assert(m[4] ==  'B');
    assert(m[5] ==  'D');
    assert(m[6] ==  'D');
    assert(m[7] ==  'D');
    assert(m[8] ==  'D');
    assert(m[9] ==  'C');
    assert(m[10] == 'C');
    assert(m[11] == 'B');
    assert(m[12] == 'B');
    assert(m[13] == 'B');
    assert(m[14] == 'B');
    assert(m[15] == 'B');
    assert(m[16] == 'B');
    assert(m[17] == 'A');
    assert(m[18] == 'A');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(13,14,'E');
    assert(m[0] ==  'A');
    assert(m[1] ==  'A');
    assert(m[2] ==  'A');
    assert(m[3] ==  'B');
    assert(m[4] ==  'B');
    assert(m[5] ==  'D');
    assert(m[6] ==  'D');
    assert(m[7] ==  'D');
    assert(m[8] ==  'D');
    assert(m[9] ==  'C');
    assert(m[10] == 'C');
    assert(m[11] == 'B');
    assert(m[12] == 'B');
    assert(m[13] == 'E');
    assert(m[14] == 'B');
    assert(m[15] == 'B');
    assert(m[16] == 'B');
    assert(m[17] == 'A');
    assert(m[18] == 'A');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(2,19,'F');
    assert(m[0] ==  'A');
    assert(m[1] ==  'A');
    assert(m[2] ==  'F');
    assert(m[3] ==  'F');
    assert(m[4] ==  'F');
    assert(m[5] ==  'F');
    assert(m[6] ==  'F');
    assert(m[7] ==  'F');
    assert(m[8] ==  'F');
    assert(m[9] ==  'F');
    assert(m[10] == 'F');
    assert(m[11] == 'F');
    assert(m[12] == 'F');
    assert(m[13] == 'F');
    assert(m[14] == 'F');
    assert(m[15] == 'F');
    assert(m[16] == 'F');
    assert(m[17] == 'F');
    assert(m[18] == 'F');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(1,7,'H');
    assert(m[0] ==  'A');
    assert(m[1] ==  'H');
    assert(m[2] ==  'H');
    assert(m[3] ==  'H');
    assert(m[4] ==  'H');
    assert(m[5] ==  'H');
    assert(m[6] ==  'H');
    assert(m[7] ==  'F');
    assert(m[8] ==  'F');
    assert(m[9] ==  'F');
    assert(m[10] == 'F');
    assert(m[11] == 'F');
    assert(m[12] == 'F');
    assert(m[13] == 'F');
    assert(m[14] == 'F');
    assert(m[15] == 'F');
    assert(m[16] == 'F');
    assert(m[17] == 'F');
    assert(m[18] == 'F');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(3,8,'I');
    assert(m[0] ==  'A');
    assert(m[1] ==  'H');
    assert(m[2] ==  'H');
    assert(m[3] ==  'I');
    assert(m[4] ==  'I');
    assert(m[5] ==  'I');
    assert(m[6] ==  'I');
    assert(m[7] ==  'I');
    assert(m[8] ==  'F');
    assert(m[9] ==  'F');
    assert(m[10] == 'F');
    assert(m[11] == 'F');
    assert(m[12] == 'F');
    assert(m[13] == 'F');
    assert(m[14] == 'F');
    assert(m[15] == 'F');
    assert(m[16] == 'F');
    assert(m[17] == 'F');
    assert(m[18] == 'F');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

    m.assign(4,5,'O');
    assert(m[0] ==  'A');
    assert(m[1] ==  'H');
    assert(m[2] ==  'H');
    assert(m[3] ==  'I');
    assert(m[4] ==  'O');
    assert(m[5] ==  'I');
    assert(m[6] ==  'I');
    assert(m[7] ==  'I');
    assert(m[8] ==  'F');
    assert(m[9] ==  'F');
    assert(m[10] == 'F');
    assert(m[11] == 'F');
    assert(m[12] == 'F');
    assert(m[13] == 'F');
    assert(m[14] == 'F');
    assert(m[15] == 'F');
    assert(m[16] == 'F');
    assert(m[17] == 'F');
    assert(m[18] == 'F');
    assert(m[19] == 'A');
    assert(m[20] == 'A');

}

int main() {

    printf("STARTING UNIT TESTS\n");
    TEST_CASE_1();
    TEST_CASE_2();
    TEST_CASE_3();
    TEST_CASE_4();
    TEST_CASE_5();
    TEST_CASE_6();
    TEST_CASE_7();
    TEST_CASE_8();
    TEST_CASE_9();
    TEST_CASE_10();
    TEST_CASE_11();
    TEST_CASE_12();
    TEST_CASE_13();
    TEST_CASE_14();
    TEST_CASE_15();
    TEST_CASE_16();
    TEST_CASE_17();
    TEST_CASE_18();
    TEST_CASE_19();
    TEST_CASE_20();
    printf("FINISHED UNIT TESTS. Result: OK\n");
}

// Lines starting with "//!" define the expected output for this test.

//! STARTING UNIT TESTS
//! FINISHED UNIT TESTS. Result: OK
