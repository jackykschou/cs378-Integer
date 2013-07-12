// --------------------------------
// projects/integer/TestInteger.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Integer.c++ TestInteger.c++ -o TestInteger -lcppunit -ldl
    % valgrind TestInteger > TestInteger.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Integer.h"

// -----------
// TestInteger
// -----------

struct TestInteger : CppUnit::TestFixture {
    // -----------------
    // shift_left_digits
    // -----------------

    void test_shift_left_digits_1 () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {2, 3, 4, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 5);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }

    void test_shift_left_digits_2 () 
    {
        const int a[] = {1, 2, 3, 4, 5};
        const int b[] = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};
              int x[10];
        const int* p = shift_left_digits(a, a + 5, 5, x);
        CPPUNIT_ASSERT((p - x) == 10);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }

    void test_shift_left_digits_3 () 
    {
        const int a[] = {1};
        const int b[] = {1};
              int x[10];
        const int* p = shift_left_digits(a, a + 1, 0, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }

    void test_shift_left_digits_4 () 
    {
        const int a[] = {1, 2, 3, 4, 5};
        const int b[] = {1, 2, 3, 0, 0, 0, 4, 5};
              int x[10];
        const int* p = shift_left_digits(a, a + 3, 3, x);
        CPPUNIT_ASSERT((p - x) == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }



    // ------------------
    // shift_right_digits
    // ------------------

    void test_shift_right_digits_1 () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 3, 2, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }

    void test_shift_right_digits_2 () 
    {
        const int a[] = {2, 3, 4, 5, 6, 7};
        const int b[] = {2, 3, 4};
              int x[10];
        const int* p = shift_right_digits(a, a + 6, 3, x);
        CPPUNIT_ASSERT((p - x) == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }
    void test_shift_right_digits_3 () 
    {
        const int a[] = {2};
        const int b[] = {2};
              int x[10];
        const int* p = shift_right_digits(a, a + 1, 0, x);
        CPPUNIT_ASSERT((p - x) == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, b));
    }

    // -----------
    // plus_digits
    // -----------

    void test_plus_digits_1 () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {8, 0, 1};
              int x[10];
        const int* p = plus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_2 () 
    {
        const int a[] = {9, 9, 9, 9, 9};
        const int b[] = {1};
        const int c[] = {1, 0, 0, 0, 0, 0};
              int x[10];
        const int* p = plus_digits(a, a + 5, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_3 () 
    {
        const int a[] = {0};
        const int b[] = {0};
        const int c[] = {0};
              int x[10];
        const int* p = plus_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_4 () 
    {
        const int a[] = {6, 4};
        const int b[] = {7, 2};
        const int c[] = {1, 3, 6};
              int x[10];
        const int* p = plus_digits(a, a + 2, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_plus_digits_5 () 
    {
        const int a[] = {1, 3, 5, 7};
        const int b[] = {2, 4, 6, 8};
        const int c[] = {3, 8, 2, 5};
              int x[10];
        const int* p = plus_digits(a, a + 4, b, b + 4, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    // ------------
    // minus_digits
    // ------------

    void test_minus_digits_1 () 
    {
        const int a[] = {8, 0, 1};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = minus_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_minus_digits_2 () 
    {
        const int a[] = {1, 0, 0, 0};
        const int b[] = {3, 3};
        const int c[] = {9, 6, 7};
              int x[10];
        const int* p = minus_digits(a, a + 4, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_minus_digits_3 () 
    {
        const int a[] = {1, 0};
        const int b[] = {0};
        const int c[] = {1, 0};
              int x[10];
        const int* p = minus_digits(a, a + 2, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_minus_digits_4 () 
    {
        const int a[] = {0};
        const int b[] = {0};
        const int c[] = {0};
              int x[10];
        const int* p = minus_digits(a, a + 1, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_minus_digits_5 () 
    {
        const int a[] = {3, 6};
        const int b[] = {6};
        const int c[] = {3, 0};
              int x[10];
        const int* p = minus_digits(a, a + 2, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 2);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    // -----------------
    // multiplies_digits
    // -----------------

    void test_multiplies_digits_1 () 
    {
        const int a[] = {2, 3, 4};
        const int b[] = {5, 6, 7};
        const int c[] = {1, 3, 2, 6, 7, 8};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 6);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_multiplies_digits_2 () 
    {
        const int a[] = {9, 6, 7};
        const int b[] = {0};
        const int c[] = {0};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_multiplies_digits_3 () 
    {
        const int a[] = {0};
        const int b[] = {5, 5, 5};
        const int c[] = {0};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_multiplies_digits_4 () 
    {
        const int a[] = {1, 1, 1};
        const int b[] = {5};
        const int c[] = {5, 5, 5};
              int x[10];
        const int* p = multiplies_digits(a, a + 3, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_multiplies_digits_5 () 
    {
        const int a[] = {5};
        const int b[] = {1, 1, 1};
        const int c[] = {5, 5, 5};
              int x[10];
        const int* p = multiplies_digits(a, a + 1, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_multiplies_digits_6 () 
    {
        const int a[] = {7, 6, 3, 2, 4};
        const int b[] = {8, 8, 8};
        const int c[] = {6, 7, 7, 7, 5, 7, 1, 2};
              int x[10];
        const int* p = multiplies_digits(a, a + 5, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 8);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    // --------------
    // divides_digits
    // --------------

    void test_divides_digits_1 () 
    {
        const int a[] = {1, 3, 2, 6, 7, 8};
        const int b[] = {5, 6, 7};
        const int c[] = {2, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_divides_digits_2 () 
    {
        const int a[] = {9, 4, 9, 6, 0, 0 ,3};
        const int b[] = {3, 4, 5, 6, 7};
        const int c[] = {2, 7, 4};
              int x[10];
        const int* p = divides_digits(a, a + 7, b, b + 5, x);
        CPPUNIT_ASSERT(p - x == 3);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_divides_digits_3 () 
    {
        const int a[] = {1, 5, 3, 4};
        const int b[] = {1};
        const int c[] = {1, 5, 3, 4};
              int x[10];
        const int* p = divides_digits(a, a + 4, b, b + 1, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_divides_digits_4 () 
    {
        const int a[] = {5, 6, 7};
        const int b[] = {5, 6, 7};
        const int c[] = {1};
              int x[10];
        const int* p = divides_digits(a, a + 3, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    void test_divides_digits_5 () 
    {
        const int a[] = {0};
        const int b[] = {9, 9};
        const int c[] = {0};
              int x[10];
        const int* p = divides_digits(a, a + 1, b, b + 2, x);
        CPPUNIT_ASSERT(p - x == 1);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

     void test_divides_digits_6 () 
    {
        const int a[] = {1, 0, 0, 0, 0, 0};
        const int b[] = {1, 0, 0};
        const int c[] = {1, 0, 0, 0};
              int x[10];
        const int* p = divides_digits(a, a + 6, b, b + 3, x);
        CPPUNIT_ASSERT(p - x == 4);
        CPPUNIT_ASSERT(std::equal(const_cast<const int*>(x), p, c));
    }

    // -----------
    // constructor
    // -----------

    void test_constructor_1 () 
    {
        try {
            const Integer<int> x("abc");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::Integer(const string&)"));}
    }

    void test_constructor_2 () 
    {
        try {
            const Integer<int> x("-t33vb102");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::Integer(const string&)"));}
    }

    void test_constructor_3 () 
    {
        try {
            const Integer<int> x("7a80");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::Integer(const string&)"));}
    }

    void test_constructor_4 () 
    {
        try {
            const Integer<int> x("1.1");
            CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::Integer(const string&)"));}
    }

    void test_constructor_5 () 
    {
        try {
            const Integer<int> x("2");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_constructor_6 () {
        try {
            const Integer<int> x("-9912");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }


    void test_constructor_7 () {
        try {
            const Integer<int> x("0");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_constructor_8 () {
        try {
            const Integer<int> x(200);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_constructor_9 () {
        try {
            const Integer<int> x(-928473);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_constructor_10 () {
        try {
            const Integer<int> x(0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // ==
    // ---

    void test_equal_1 ()
    {   
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(x == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_equal_2 ()
    {
        try {
        Integer<int> x = 92800;
        Integer<int> y = 92800;
        CPPUNIT_ASSERT(x == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_equal_3 ()
    {
        try {
        Integer<int> x = -80;
        Integer<int> y = 80;
        CPPUNIT_ASSERT(!(x == y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_equal_4()
    {
        try {
        Integer<int> x = -74237;
        Integer<int> y = 3270077;
        CPPUNIT_ASSERT(!(x == y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }


     void test_equal_5 ()
    {
        try {
        Integer<int> x = -777;
        Integer<int> y = -777;
        CPPUNIT_ASSERT(x == y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // !=
    // ---

    void test_unequal_1 ()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(!(x != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_unequal_2 ()
    {
        try {
        Integer<int> x = 92800;
        Integer<int> y = 92800;
        CPPUNIT_ASSERT(!(x != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_unequal_3 ()
    {
        try {
        Integer<int> x = -80;
        Integer<int> y = 80;
        CPPUNIT_ASSERT(x != y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

     void test_unequal_4()
    {
        try {
        Integer<int> x = -74237;
        Integer<int> y = 3270077;
        CPPUNIT_ASSERT(x != y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }


     void test_unequal_5 ()
    {
        try {
        Integer<int> x = -777;
        Integer<int> y = -777;
        CPPUNIT_ASSERT(!(x != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // <
    // ---

    void test_less_1 ()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 198;
        CPPUNIT_ASSERT(x < y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_2 ()
    {
        try {
        Integer<int> x = 198;
        Integer<int> y = 100;
        CPPUNIT_ASSERT(!(x < y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_3 ()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(!(x < y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_4 ()
    {
        try {
        Integer<int> x = -100;
        Integer<int> y = 28;
        CPPUNIT_ASSERT(x < y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_5 ()
    {
        try {
        Integer<int> x = 23;
        Integer<int> y = -90972;
        CPPUNIT_ASSERT(!(x < y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // >
    // ---

    void test_greater_1 ()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 198;
        CPPUNIT_ASSERT(!(x > y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greater_2 ()
    {
        try {
        Integer<int> x = 198;
        Integer<int> y = 100;
        CPPUNIT_ASSERT(x > y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greater_3 ()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(!(x > y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greater_4 ()
    {
        try {
        Integer<int> x = -100;
        Integer<int> y = 28;
        CPPUNIT_ASSERT(!(x > y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greater_5 ()
    {
        try {
        Integer<int> x = 23;
        Integer<int> y = -90972;
        CPPUNIT_ASSERT(x > y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // <=
    // ---

    void test_less_equal_1 ()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 198;
        CPPUNIT_ASSERT(x <= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_equal_2 ()
    {
        try {
        Integer<int> x = 198;
        Integer<int> y = 100;
        CPPUNIT_ASSERT(!(x <= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_equal_3 ()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(x <= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_equal_4 ()
    {
        try {
        Integer<int> x = -100;
        Integer<int> y = 28;
        CPPUNIT_ASSERT(x <= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_less_equal_5 ()
    {
        try {
        Integer<int> x = 23;
        Integer<int> y = -90972;
        CPPUNIT_ASSERT(!(x <= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // >=
    // ---

    void test_greaters_equal_1 ()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 198;
        CPPUNIT_ASSERT(!(x >= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greaters_equal_2 ()
    {
        try {
        Integer<int> x = 198;
        Integer<int> y = 100;
        CPPUNIT_ASSERT(x >= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greaters_equal_3 ()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        CPPUNIT_ASSERT(x >= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greaters_equal_4 ()
    {
        try {
        Integer<int> x = -100;
        Integer<int> y = 28;
        CPPUNIT_ASSERT(!(x >= y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_greaters_equal_5 ()
    {
        try {
        Integer<int> x = 23;
        Integer<int> y = -90972;
        CPPUNIT_ASSERT(x >= y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // +
    // ---

    void test_plus_1()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 256;
        Integer<int> z = x + y;
        Integer<int> answer = 356;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_2()
    {
        try {
        Integer<int> x = 999;
        Integer<int> y = 1;
        Integer<int> z = x + y;
        Integer<int> answer = 1000;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_3()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        Integer<int> z = x + y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_4()
    {
        try {
        Integer<int> x = -3250;
        Integer<int> y = -12;
        Integer<int> z = x + y;
        Integer<int> answer = -3262;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_5()
    {
        try {
        Integer<int> x = -999;
        Integer<int> y = 1000;
        Integer<int> z = x + y;
        Integer<int> answer = 1;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_6()
    {
        try {
        Integer<int> x = 1250;
        Integer<int> y = -1300;
        Integer<int> z = x + y;
        Integer<int> answer = -50;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // +=
    // ---

    void test_plus_equal_1()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 256;
        x += y;
        Integer<int> answer = 356;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_2()
    {
        try {
        Integer<int> x = 999;
        Integer<int> y = 1;
        x += y;
        Integer<int> answer = 1000;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_3()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        x += y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_4()
    {
        try {
        Integer<int> x = -3250;
        Integer<int> y = -12;
        x += y;
        Integer<int> answer = -3262;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_5()
    {
        try {
        Integer<int> x = -999;
        Integer<int> y = 1000;
        x += y;
        Integer<int> answer = 1;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_plus_equal_6()
    {
        try {
        Integer<int> x = 1250;
        Integer<int> y = -1300;
        x += y;
        Integer<int> answer = -50;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // -
    // ---

    void test_minus_1()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 256;
        Integer<int> z = x - y;
        Integer<int> answer = -156;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_2()
    {
        try {
        Integer<int> x = 999;
        Integer<int> y = 1;
        Integer<int> z = x - y;
        Integer<int> answer = 998;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_3()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        Integer<int> z = x - y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_4()
    {
        try {
        Integer<int> x = -3250;
        Integer<int> y = -12;
        Integer<int> z = x - y;
        Integer<int> answer = -3238;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_5()
    {
        try {
        Integer<int> x = -999;
        Integer<int> y = 1000;
        Integer<int> z = x - y;
        Integer<int> answer = -1999;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_6()
    {
        try {
        Integer<int> x = 1250;
        Integer<int> y = -1300;
        Integer<int> z = x - y;
        Integer<int> answer = 2550;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // -=
    // ---

    void test_minus_equal_1()
    {
        try {
        Integer<int> x = 100;
        Integer<int> y = 256;
        x -= y;
        Integer<int> answer = -156;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_2()
    {
        try {
        Integer<int> x = 999;
        Integer<int> y = 1;
        x -= y;
        Integer<int> answer = 998;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_3()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        x -= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_4()
    {
        try {
        Integer<int> x = -3250;
        Integer<int> y = -12;
        x -= y;
        Integer<int> answer = -3238;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_5()
    {
        try {
        Integer<int> x = -999;
        Integer<int> y = 1000;
        x -= y;
        Integer<int> answer = -1999;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_minus_equal_6()
    {
        try {
        Integer<int> x = 1250;
        Integer<int> y = -1300;
        x -= y;
        Integer<int> answer = 2550;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // *
    // ---

    void test_mult_1()
    {
        try {
        Integer<int> x = 120;
        Integer<int> y = 5;
        Integer<int> z = x * y;
        Integer<int> answer = 600;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_2()
    {
        try {
        Integer<int> x = -728;
        Integer<int> y = 2;
        Integer<int> z = x * y;
        Integer<int> answer = -1456;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_3()
    {
        try {
        Integer<int> x = 9999;
        Integer<int> y = 0;
        Integer<int> z = x * y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_4()
    {
        try {
        Integer<int> x = -555;
        Integer<int> y = -100;
        Integer<int> z = x * y;
        Integer<int> answer = 55500;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_5()
    {
        try {
        Integer<int> x = 78;
        Integer<int> y = -3;
        Integer<int> z = x * y;
        Integer<int> answer = -234;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_6()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        Integer<int> z = x * y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // *=
    // ---

    void test_mult_equal_1()
    {
        try {
        Integer<int> x = 120;
        Integer<int> y = 5;
        x *= y;
        Integer<int> answer = 600;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_equal_2()
    {
        try {
        Integer<int> x = -728;
        Integer<int> y = 2;
        x *= y;
        Integer<int> answer = -1456;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_equal_3()
    {
        try {
        Integer<int> x = 9999;
        Integer<int> y = 0;
        x *= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_equal_4()
    {
        try {
        Integer<int> x = -555;
        Integer<int> y = -100;
        x *= y;
        Integer<int> answer = 55500;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_equal_5()
    {
        try {
        Integer<int> x = 78;
        Integer<int> y = -3;
        x *= y;
        Integer<int> answer = -234;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mult_equal_6()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 0;
        x *= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // /
    // ---

    void test_divide_1()
    {
        try {
        Integer<int> x = 12603;
        Integer<int> y = 342;
        Integer<int> z = x / y;
        Integer<int> answer = 36;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_2()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 999;
        Integer<int> z = x / y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_3()
    {
        try {
        Integer<int> x = 10001;
        Integer<int> y = -100;
        Integer<int> z = x / y;
        Integer<int> answer = -100;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_4()
    {
        try {
        Integer<int> x = -334422;
        Integer<int> y = -111;
        Integer<int> z = x / y;
        Integer<int> answer = 3012;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_5()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = -3;
        Integer<int> z = x / y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_6()
    {
        try {
        Integer<int> x = 12603;
        Integer<int> y = 0;
        Integer<int> z = x / y;
        Integer<int> answer = 36;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator / (Integer,const Integer&)"));}
    }

    // ---
    // /=
    // ---

    void test_divide_equal_1()
    {
        try {
        Integer<int> x = 12603;
        Integer<int> y = 342;
        x /= y;
        Integer<int> answer = 36;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_equal_2()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 999;
        x /= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_equal_3()
    {
        try {
        Integer<int> x = 10001;
        Integer<int> y = -100;
        x /= y;
        Integer<int> answer = -100;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_equal_4()
    {
        try {
        Integer<int> x = -334422;
        Integer<int> y = -111;
        x /= y;
        Integer<int> answer = 3012;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_equal_5()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = -3;
        x /= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_divide_equal_6()
    {
        try {
        Integer<int> x = 12603;
        Integer<int> y = 0;
        x /= y;
        Integer<int> answer = 36;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator /= (const Integer&)"));}
    }

    // ---
    // %
    // ---

    void test_mod_1()
    {
        try {
        Integer<int> x = 10234;
        Integer<int> y = 36;
        Integer<int> z = x % y;
        Integer<int> answer = 10;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_2()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 100;
        Integer<int> z = x % y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_3()
    {
        try {
        Integer<int> x = 100000000;
        Integer<int> y = 10;
        Integer<int> z = x % y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_4()
    {
        try {
        Integer<int> x = 10234;
        Integer<int> y = 0;
        Integer<int> z = x % y;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator % (Integer,const Integer&)"));}
    }

    // ---
    // %=
    // ---

    void test_mod_equal_1()
    {
        try {
        Integer<int> x = 10234;
        Integer<int> y = 36;
        x %= y;
        Integer<int> answer = 10;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_equal_2()
    {
        try {
        Integer<int> x = 0;
        Integer<int> y = 100;
        x %= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_equal_3()
    {
        try {
        Integer<int> x = 100000000;
        Integer<int> y = 10;
        x %= y;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_mod_equal_4()
    {
        try {
        Integer<int> x = 10234;
        Integer<int> y = 0;
        x %= y;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator %= (const Integer&)"));}
    }

    // ---
    // <<= (shift)
    // ---

    void test_l_shift_equal_1()
    {
        try {
        Integer<int> x = 99999;
        x <<= 3;
        Integer<int> answer = 99999000;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_l_shift_equal_2()
    {
        try {
        Integer<int> x = 99999;
        x <<= 0;
        Integer<int> answer = 99999;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_l_shift_equal_3()
    {
        try {
        Integer<int> x = 99999;
        x <<= -19;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator <<= (int)"));}
    }

    // ---
    // << (shift)
    // ---

    void test_l_shift_1()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x << 3;
        Integer<int> answer = 99999000;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_l_shift_2()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x << 0;
        Integer<int> answer = 99999;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_l_shift_3()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x << -19;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator << (Integer, int)"));}
    }

    // ---
    // >>= (shift)
    // ---

    void test_r_shift_equal_1()
    {
        try {
        Integer<int> x = 99999;
        x >>= 3;
        Integer<int> answer = 99;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_r_shift_equal_2()
    {
        try {
        Integer<int> x = 99999;
        x >>= 0;
        Integer<int> answer = 99999;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_r_shift_equal_3()
    {
        try {
        Integer<int> x = 99999;
        x >>= -19;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator >>= (int)"));}
    }

    void test_r_shift_equal_4()
    {
        try {
        Integer<int> x = 99999;
        x >>= 1000;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(x == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // >> (shift)
    // ---

    void test_r_shift_1()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x >> 3;
        Integer<int> answer = 99;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_r_shift_2()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x >> 0;
        Integer<int> answer = 99999;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_r_shift_3()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x >> -19;
        CPPUNIT_ASSERT(false);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(!strcmp(e.what(), "Integer::operator >> (Integer, int)"));}
    }

    void test_r_shift_4()
    {
        try {
        Integer<int> x = 99999;
        Integer<int> z = x >> 1000;
        Integer<int> answer = 0;
        CPPUNIT_ASSERT(z == answer);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // ---
    // abs
    // ---

    void test_abs_1 () 
    {
        try {
            Integer<int>  x = -98765;
            Integer<int>& y = x.abs();
            CPPUNIT_ASSERT( x == 98765);
            CPPUNIT_ASSERT(&x == &y);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_abs_2 () 
    {
        try {
            const Integer<int> x = -98765;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == -98765);
            CPPUNIT_ASSERT(y ==  98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_abs_3 () 
    {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y == 0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    void test_abs_4 () 
    {
        try {
            const Integer<int> x = 0;
            const Integer<int> y = abs(x);
            CPPUNIT_ASSERT(x == 0);
            CPPUNIT_ASSERT(y ==  0);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
    }

    // --------
    // equal_to
    // --------

    void test_equal_to () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = 98765;
            CPPUNIT_ASSERT(      x == y);
            CPPUNIT_ASSERT(      x == 98765);
            CPPUNIT_ASSERT(  98765 == x);
            CPPUNIT_ASSERT(    !(x != y));
            CPPUNIT_ASSERT(    !(x != 98765));
            CPPUNIT_ASSERT(!(98765 != y));}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // --------
    // negation
    // --------

    void test_negation_1 () {
        try {
            const Integer<int> x = 98765;
            const Integer<int> y = -x;
            CPPUNIT_ASSERT(y == -98765);}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

        void test_negation_2 () {
    try {
        const Integer<int> x = 0;
        const Integer<int> y = -x;
        CPPUNIT_ASSERT(y == 0);}
    catch (std::invalid_argument& e) {
        CPPUNIT_ASSERT(false);}}

    // ------
    // output
    // ------

    void test_output () {
        try {
            const Integer<int> x = 98765;
            std::ostringstream out;
            out << x;
            CPPUNIT_ASSERT(out.str() == "98765");}
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}}

    // ---
    // pow
    // ---

    void test_pow_1 () {
        try {
            Integer<int> x = 2;
            int e = 16;
            Integer<int> answer = 65536;
            Integer<int> y = x.pow(e);
            CPPUNIT_ASSERT(x == answer);
            CPPUNIT_ASSERT(y == answer);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
        }

    void test_pow_2 () {
        try {
            Integer<int> x = 2;
            int e = 16;
            Integer<int> answer = 65536;
            Integer<int> y = pow(x, e);
            CPPUNIT_ASSERT(x != answer);
            CPPUNIT_ASSERT(y == answer);
        }
        catch (std::invalid_argument& e) {
            CPPUNIT_ASSERT(false);}
        }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestInteger);
    CPPUNIT_TEST(test_shift_left_digits_1);
    CPPUNIT_TEST(test_shift_left_digits_2);
    CPPUNIT_TEST(test_shift_left_digits_3);
    CPPUNIT_TEST(test_shift_left_digits_4);
    CPPUNIT_TEST(test_shift_right_digits_1);
    CPPUNIT_TEST(test_shift_right_digits_2);
    CPPUNIT_TEST(test_shift_right_digits_3);
    CPPUNIT_TEST(test_plus_digits_1);
    CPPUNIT_TEST(test_plus_digits_2);
    CPPUNIT_TEST(test_plus_digits_3);
    CPPUNIT_TEST(test_plus_digits_4);
    CPPUNIT_TEST(test_plus_digits_5);
    CPPUNIT_TEST(test_minus_digits_1);
    CPPUNIT_TEST(test_minus_digits_2);
    CPPUNIT_TEST(test_minus_digits_3);
    CPPUNIT_TEST(test_minus_digits_4);
    CPPUNIT_TEST(test_minus_digits_5);
    CPPUNIT_TEST(test_multiplies_digits_1);
    CPPUNIT_TEST(test_multiplies_digits_2);
    CPPUNIT_TEST(test_multiplies_digits_3);
    CPPUNIT_TEST(test_multiplies_digits_4);
    CPPUNIT_TEST(test_multiplies_digits_5);
    CPPUNIT_TEST(test_multiplies_digits_6);
    CPPUNIT_TEST(test_divides_digits_1);
    CPPUNIT_TEST(test_divides_digits_2);
    CPPUNIT_TEST(test_divides_digits_3);
    CPPUNIT_TEST(test_divides_digits_4);
    CPPUNIT_TEST(test_divides_digits_5);
    CPPUNIT_TEST(test_divides_digits_6);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    CPPUNIT_TEST(test_constructor_6);
    CPPUNIT_TEST(test_constructor_7);
    CPPUNIT_TEST(test_constructor_8);
    CPPUNIT_TEST(test_constructor_9);
    CPPUNIT_TEST(test_constructor_10);
    CPPUNIT_TEST(test_less_1);
    CPPUNIT_TEST(test_less_2);
    CPPUNIT_TEST(test_less_3);
    CPPUNIT_TEST(test_less_4);
    CPPUNIT_TEST(test_less_5);
    CPPUNIT_TEST(test_less_equal_1);
    CPPUNIT_TEST(test_less_equal_2);
    CPPUNIT_TEST(test_less_equal_3);
    CPPUNIT_TEST(test_less_equal_4);
    CPPUNIT_TEST(test_less_equal_5);
    CPPUNIT_TEST(test_greater_1);
    CPPUNIT_TEST(test_greater_2);
    CPPUNIT_TEST(test_greater_3);
    CPPUNIT_TEST(test_greater_4);
    CPPUNIT_TEST(test_greater_5);
    CPPUNIT_TEST(test_greaters_equal_1);
    CPPUNIT_TEST(test_greaters_equal_2);
    CPPUNIT_TEST(test_greaters_equal_3);
    CPPUNIT_TEST(test_greaters_equal_4);
    CPPUNIT_TEST(test_greaters_equal_5);
    CPPUNIT_TEST(test_plus_1);
    CPPUNIT_TEST(test_plus_2);
    CPPUNIT_TEST(test_plus_3);
    CPPUNIT_TEST(test_plus_4);
    CPPUNIT_TEST(test_plus_5);
    CPPUNIT_TEST(test_plus_6);
    CPPUNIT_TEST(test_plus_equal_1);
    CPPUNIT_TEST(test_plus_equal_2);
    CPPUNIT_TEST(test_plus_equal_3);
    CPPUNIT_TEST(test_plus_equal_4);
    CPPUNIT_TEST(test_plus_equal_5);
    CPPUNIT_TEST(test_plus_equal_6);
    CPPUNIT_TEST(test_minus_1);
    CPPUNIT_TEST(test_minus_2);
    CPPUNIT_TEST(test_minus_3);
    CPPUNIT_TEST(test_minus_4);
    CPPUNIT_TEST(test_minus_5);
    CPPUNIT_TEST(test_minus_6);
    CPPUNIT_TEST(test_minus_equal_1);
    CPPUNIT_TEST(test_minus_equal_2);
    CPPUNIT_TEST(test_minus_equal_3);
    CPPUNIT_TEST(test_minus_equal_4);
    CPPUNIT_TEST(test_minus_equal_5);
    CPPUNIT_TEST(test_minus_equal_6);
    CPPUNIT_TEST(test_mult_1);
    CPPUNIT_TEST(test_mult_2);
    CPPUNIT_TEST(test_mult_3);
    CPPUNIT_TEST(test_mult_4);
    CPPUNIT_TEST(test_mult_5);
    CPPUNIT_TEST(test_mult_6);
    CPPUNIT_TEST(test_mult_equal_1);
    CPPUNIT_TEST(test_mult_equal_2);
    CPPUNIT_TEST(test_mult_equal_3);
    CPPUNIT_TEST(test_mult_equal_4);
    CPPUNIT_TEST(test_mult_equal_5);
    CPPUNIT_TEST(test_mult_equal_6);
    CPPUNIT_TEST(test_divide_1);
    CPPUNIT_TEST(test_divide_2);
    CPPUNIT_TEST(test_divide_3);
    CPPUNIT_TEST(test_divide_4);
    CPPUNIT_TEST(test_divide_5);
    CPPUNIT_TEST(test_divide_6);
    CPPUNIT_TEST(test_divide_equal_1);
    CPPUNIT_TEST(test_divide_equal_2);
    CPPUNIT_TEST(test_divide_equal_3);
    CPPUNIT_TEST(test_divide_equal_4);
    CPPUNIT_TEST(test_divide_equal_5);
    CPPUNIT_TEST(test_divide_equal_6);
    CPPUNIT_TEST(test_mod_1);
    CPPUNIT_TEST(test_mod_2);
    CPPUNIT_TEST(test_mod_3);
    CPPUNIT_TEST(test_mod_4);
    CPPUNIT_TEST(test_mod_equal_1);
    CPPUNIT_TEST(test_mod_equal_2);
    CPPUNIT_TEST(test_mod_equal_3);
    CPPUNIT_TEST(test_mod_equal_4);
    CPPUNIT_TEST(test_l_shift_1);
    CPPUNIT_TEST(test_l_shift_2);
    CPPUNIT_TEST(test_l_shift_3);
    CPPUNIT_TEST(test_l_shift_equal_1);
    CPPUNIT_TEST(test_l_shift_equal_2);
    CPPUNIT_TEST(test_l_shift_equal_3);
    CPPUNIT_TEST(test_r_shift_1);
    CPPUNIT_TEST(test_r_shift_2);
    CPPUNIT_TEST(test_r_shift_3);
    CPPUNIT_TEST(test_r_shift_4);
    CPPUNIT_TEST(test_r_shift_equal_1);
    CPPUNIT_TEST(test_r_shift_equal_2);
    CPPUNIT_TEST(test_r_shift_equal_3);
    CPPUNIT_TEST(test_r_shift_equal_4);
    CPPUNIT_TEST(test_abs_1);
    CPPUNIT_TEST(test_abs_2);
    CPPUNIT_TEST(test_abs_3);
    CPPUNIT_TEST(test_abs_4);
    CPPUNIT_TEST(test_negation_1);
    CPPUNIT_TEST(test_negation_2);
    CPPUNIT_TEST(test_output);
    CPPUNIT_TEST(test_pow_1);
    CPPUNIT_TEST(test_pow_2);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    cout << "TestInteger.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestInteger::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
