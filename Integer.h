// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// worked by Ka Seng Chou
// --------------------------

#ifndef Integer_h
    #define Integer_h
#endif

#ifdef NDEBUG
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string
#include <vector>    // vector
#include <algorithm> //different algorithms for iterators
#include <iterator>  //predefined iterator, iterator categories, iterator functions

using namespace std;

// -----------------
// shift_left_digits
// -----------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * coutput the shift left of the input sequence into the output sequence
 * ([b, e) << n) => x
 */
template <typename II, typename OI>
typename OI shift_left_digits (II b, II e, int n, OI x) 
{
    x = copy(b, e, x);
    return fill_n(x, n, 0);
}

// ------------------
// shift_right_digits
// ------------------

/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive) or return x (with nothing new filled with) if all digits are shifted away
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * ([b, e) >> n) => x
 */
template <typename II, typename OI>
typename OI shift_right_digits (II b, II e, int n, OI x) 
{
     return copy_n(b, distance(b, e) - n, x);
}

// -----------
// plus_digits
// -----------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive) 
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * ([b1, e1) + [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
typename OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
    int II1_length = distance(b1, e1);
    int II2_length = distance(b2, e2);
    vector<int> temp(1);

    if(II1_length > II2_length)
    {
        temp.reserve(II1_length + 1);
        copy_n(b1, II1_length - II2_length, back_insert_iterator(temp));
        advance(b1, II1_length - II2_length);
        transform(b1, e1, b2, back_insert_iterator(temp), [](int elem1, int elem2)
            {
                return elem1 + elem2;
            });
    }
    else
    {
        temp.reserve(II2_length + 1);
        copy_n(b2, II2_length - II1_length, back_insert_iterator(temp));
        advance(b2, II2_length - II1_length);
        transform(b2, e2, b1, back_insert_iterator(temp), [](int elem1, int elem2)
            {
                return elem1 + elem2;
            });
    }
    vector<int>::reverse_iterator rit = next(temp.rbegin());
    for_each(temp.rbegin(), temp.rend(), [&rit](int& elem)
        {
            if(elem >= 10)
            {
                elem -= 10;
                ++(*rit);
            }
            ++rit;
        });
    if(temp[0] == 1)
    {
        return copy(temp.cbegin(), temp.cend(), x);
    }
    else
    {
        return copy(next(temp.cbegin()), temp.cend(), x);
    }

}

// ------------
// minus_digits
// ------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive) or return x (with nothing new filled with) if the result is 0
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * ([b1, e1) - [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
    int II1_length = distance(b1, e1);
    int II2_length = distance(b2, e2);
    vector<int> temp;
    temp.reserve(II1_length);

    copy_n(b1, II1_length - II2_length, back_insert_iterator(temp));
    advance(b1, II1_length - II2_length);
    transform(b1, e1, b2, back_insert_iterator(temp), [](int elem1, int elem2)
        {
            return elem1 - elem2;
        });
    vector<int>::reverse_iterator rit = next(temp.rbegin());
    for_each(temp.rbegin(), temp.rend(), [&rit](int& elem)
        {
            if(elem < 0)
            {
                elem += 10;
                --(*rit);
            }
            ++rit;
        });
    if(find(temp.cbegin(), temp.cend(), 0) == prev(temp.end()))
    {
        return x;
    }
    else
    {
        return copy(next(find(temp.cbegin(), temp.cend()), 0) , temp.cend(), x);
    }
}

// -----------------
// multiplies_digits
// -----------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive) 
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * ([b1, e1) * [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
    int II1_length = distance(b1, e1);
    int II2_length = distance(b2, e2);
    vector<int> result(1);
    vector<int> multiplicand;
    vector<int>::iterator result_end = result.end();
    vector<int>::iterator multiplicand_end;
    result.reserve(II1_length + II2_length);
    multiplicand.reserve(II1_length + II2_length - 1);

    if(II1_length > II2_length)
    {
        result_end = copy(b1, e1, result.begin());
        multiplicand_end =  copy(b1, e1, multiplicand.begin());
        for_each(b2, e2, [&II2_length, &multiplicand, &multiplicand_end](int elem)
            {
                vector<int>::iterator multiplicand_temp_end = fill_n(multiplicand_end, --II2_length, 0);
                while(elem-- != 0)
                {
                    result_end = plus_digits(result.begin(), result_end, multiplicand.begin(), multiplicand_temp_end, result.begin());
                }
            }
    }
    else
    {
        result_end = copy(b2, e2, result.begin());
        multiplicand_end =  copy(b1, e1, multiplicand.begin());
        for_each(b1, e1, [&II1_length, &multiplicand, &multiplicand_end](int elem)
            {
                vector<int>::iterator multiplicand_temp_end = fill_n(multiplicand_end, --II1_length, 0);
                while(elem-- != 0)
                {
                    result_end = plus_digits(result.begin(), result_end, multiplicand.begin(), multiplicand_temp_end, result.begin());
                }
            }
    }
    return copy(result.begin(), result_end, x);    
}

// --------------
// divides_digits
// --------------

/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * ([b1, e1) / [b2, e2)) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
    int II1_length = distance(b1, e1);
    int II2_length = distance(b2, e2);
    vector<int> result(1);
    vector<int> dividend(b1, e1);
    vector<int> result_add_one(1, 1);
    vector<int>::iterator result_end = result.end();
    vector<int>::iterator dividend_end = dividend.end();
    result.reserve(II1_length);

    if(II1_length - II2_length >= 2 || ((II1_length - II2_length == 1) && (*b1 > *b2)))
    {
        vector<int> divider(b2, e2);
        vector<int> result_adder(1, 1);
        divider.reserve(II2_length + II1_length);
        result_adder.reserve(1 + II1_length - II2_length);

        dividend_end = minus_digits(dividend.begin(), dividend_end, divider.begin(), fill_n(divider.end(), II1_length - II2_length, 0), dividend.begin());
        result_end = plus_digits(result.begin(), result_end, result_adder.begin(), fill_n(result_adder.end(), II1_length - II2_length, 0), result.begin());

    }


    while(lexicographical_compare(b2, e2, dividend.begin(), dividend_end) || ((distance(dividend.begin(), dividend_end) == distance(b2, e2)) && equal(dividend.begin(), dividend_end, b2)))
    {
        dividend_end = minus_digits(dividend.begin(), dividend_end, b2, e2, dividend.begin());
        result_end = plus_digits(result.begin(), result_end, result_add_one.begin(), result_add_one.end(), result.begin());
    }

    return copy(result.begin(), result_end, x);
}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer {
    // -----------
    // operator ==
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator !=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) 
    {
        return !(lhs == rhs);
    }

    // ----------
    // operator <
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) {
        // <your code>
        return false;}

    // -----------
    // operator <=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) {
        return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * <your documentation>
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    // -----------

    /**
     * <your documentation>
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    // ----------

    /**
     * <your documentation>
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    // ----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

    // -----------
    // operator >>
    // -----------

    /**
     * <your documentation>
     * @throws invalid_argument if (rhs < 0)
     */
    friend Integer operator >> (Integer lhs, int rhs) {
        return lhs >>= rhs;}

    // -----------
    // operator <<
    // -----------

    /**
     * <your documentation>
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
        // <your code>
        return lhs << "0";}

    // ---
    // abs
    // ---

    /**
     * absolute value
     * does NOT modify the argument
     * <your documentation>
     */
    friend Integer abs (Integer x) {
        return x.abs();}

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * <your documentation>
     * @throws invalid_argument if (x == 0) && (e == 0)
     * @throws invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) {
        return x.pow(e);}

    private:
        // ----
        // data
        // ----

        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Integer (int value) {
            // <your code>
            assert(valid());}

        /**
         * <your documentation>
         * @throws invalid_argument if value is not a valid representation of an Integer
         */
        explicit Integer (const std::string& value) {
            // <your code>
            if (!valid())
                throw std::invalid_argument("Integer::Integer()");}

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * <your documentation>
         */
        Integer operator - () const {
            // <your code>
            return Integer(0);}

        // -----------
        // operator ++
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator ++ () {
            *this += 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator ++ (int) {
            Integer x = *this;
            ++(*this);
            return x;}

        // -----------
        // operator --
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -- () {
            *this -= 1;
            return *this;}

        /**
         * <your documentation>
         */
        Integer operator -- (int) {
            Integer x = *this;
            --(*this);
            return x;}

        // -----------
        // operator +=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator += (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator -=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator -= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator *=
        // -----------

        /**
         * <your documentation>
         */
        Integer& operator *= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator /=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs == 0)
         */
        Integer& operator /= (const Integer& rhs) {
            // <your code>
            return *this;}

        // -----------
        // operator %=
        // -----------

        /**
         * <your documentation>
         * @throws invalid_argument if (rhs <= 0)
         */
        Integer& operator %= (const Integer& rhs) {
            // <your code>
            return *this;}

        // ------------
        // operator <<=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator <<= (int n) {
            // <your code>
            return *this;}

        // ------------
        // operator >>=
        // ------------

        /**
         * <your documentation>
         */
        Integer& operator >>= (int n) {
            // <your code>
            return *this;}

        // ---
        // abs
        // ---

        /**
         * absolute value
         * <your documentation>
         */
        Integer& abs () {
            // <your code>
            return *this;}

        // ---
        // pow
        // ---

        /**
         * power
         * <your documentation>
         * @throws invalid_argument if (this == 0) && (e == 0)
         * @throws invalid_argument if (e < 0)
         */
        Integer& pow (int e) {
            // <your code>
            return *this;}};

#endif // Integer_h
