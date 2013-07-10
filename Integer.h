// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2013
// Glenn P. Downing
// worked by Ka Seng Chou
// --------------------------

// --------
// defines
// --------

#ifndef Integer_h
    #define Integer_h

//#ifdef NDEBUG
    //#define NDEBUG
//#endif

#define ZERO_ASCII_OFFSET 48

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>    // string, stoi, to_string
#include <vector>    // vector
#include <deque>     // deque
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
OI shift_left_digits (II b, II e, int n, OI x) 
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
OI shift_right_digits (II b, II e, int n, OI x) 
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
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) 
{
    int II1_length = distance(b1, e1);
    int II2_length = distance(b2, e2);
    vector<int> temp(1);

    if(II1_length > II2_length)
    {
        temp.reserve(II1_length + 1);
        copy_n(b1, II1_length - II2_length, back_insert_iterator<vector<int> >(temp));
        advance(b1, II1_length - II2_length);
        transform(b1, e1, b2, back_insert_iterator<vector<int> >(temp), [](int elem1, int elem2)
            {
                return elem1 + elem2;
            });
    }
    else
    {
        temp.reserve(II2_length + 1);
        copy_n(b2, II2_length - II1_length, back_insert_iterator<vector<int> >(temp));
        advance(b2, II2_length - II1_length);
        transform(b2, e2, b1, back_insert_iterator<vector<int> >(temp), [](int elem1, int elem2)
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

    copy_n(b1, II1_length - II2_length, back_insert_iterator<vector<int> >(temp));
    advance(b1, II1_length - II2_length);
    transform(b1, e1, b2, back_insert_iterator<vector<int> >(temp), [](int elem1, int elem2)
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
        return copy(next(find(temp.cbegin(), temp.cend(), 0)), temp.cend(), x);
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
        for_each(b2, e2, [&II2_length, &multiplicand, &multiplicand_end, &result_end, &result](int elem)
            {
                vector<int>::iterator multiplicand_temp_end = fill_n(multiplicand_end, --II2_length, 0);
                while(elem-- != 0)
                {
                    result_end = plus_digits(result.begin(), result_end, multiplicand.begin(), multiplicand_temp_end, result.begin());
                }
            });
    }
    else
    {
        result_end = copy(b2, e2, result.begin());
        multiplicand_end =  copy(b1, e1, multiplicand.begin());
        for_each(b1, e1, [&II1_length, &multiplicand, &multiplicand_end, &result_end, &result](int elem)
            {
                vector<int>::iterator multiplicand_temp_end = fill_n(multiplicand_end, --II1_length, 0);
                while(elem-- != 0)
                {
                    result_end = plus_digits(result.begin(), result_end, multiplicand.begin(), multiplicand_temp_end, result.begin());
                }
            });
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
    int dividend_len = distance(b1, e1);
    int divider_len = distance(b2, e2);
    vector<int> result(1);
    vector<int> dividend(b1, e1);
    vector<int> divider(divider_len + dividend_len - divider_len);
    vector<int> result_adder(1 + dividend_len - divider_len);
    vector<int>::iterator result_end = result.end();
    vector<int>::iterator dividend_end = dividend.end();
    vector<int>::iterator divider_end = divider.end();
    vector<int>::iterator result_adder_end = result_adder.end();
    result.reserve(dividend_len);

    result_adder[0] = 1;
    divider_end = copy(b2, e2, divider.begin());

    while(dividend_len - divider_len >= 2 || ((dividend_len - divider_len == 1) && (dividend.front() > divider.front())))
    {
        divider_end = next(divider.begin(), distance(b2, e2) + dividend_len - divider_len + 1);
        result_adder_end = next(result_adder.begin(), dividend_len - divider_len + 1);
        dividend_end = minus_digits(dividend.begin(), dividend_end, divider.begin(), divider_end, dividend.begin());
        result_end = plus_digits(result.begin(), result_end, result_adder.begin(), result_adder_end, result.begin());

        dividend_len = distance(dividend.begin(), dividend_end);
        divider_len = distance(divider.begin(), divider_end);
    }

    result_adder_end = next(result_adder.begin());

    while(lexicographical_compare(b2, e2, dividend.begin(), dividend_end) || ((distance(dividend.begin(), dividend_end) == distance(b2, e2)) && equal(dividend.begin(), dividend_end, b2)))
    {
        dividend_end = minus_digits(dividend.begin(), dividend_end, b2, e2, dividend.begin());
        result_end = plus_digits(result.begin(), result_end, result_adder.begin(), result_adder_end, result.begin());
    }

    return copy(result.begin(), result_end, x);
}

// -------
// Integer
// -------

template < typename T, typename C = std::vector<T> >
class Integer 
{
    // -----------
    // operator ==
    // -----------

    /**
     * @param lhs an Integer on the left side of the ==
     * @param rhs an Integer on the right side of the ==
     * @return bool to indicate whether the two Integers are equal or not
     * equal comparison operator for Integer
     */
    friend bool operator == (const Integer& lhs, const Integer& rhs) 
    {
        return (lhs.negative == rhs.negative) && (distance(lhs.begin_pos, lhs.end_pos) == distance(rhs.begin_pos, rhs.end_pos)) && equal(lhs.begin_pos, lhs.end_pos, rhs.begin_pos);
    }

    // -----------
    // operator !=
    // -----------

    /**
     * @param lhs an Integer on the left side of the !=
     * @param rhs an Integer on the right side of the !=
     * @return bool to indicate whether the two Integers are NOT equal or not
     * not equal comparison operator for Integer
     */
    friend bool operator != (const Integer& lhs, const Integer& rhs) 
    {
        return !(lhs == rhs);
    }

    // ----------
    // operator <
    // ----------

    /**
     * @param lhs an Integer on the left side of <
     * @param rhs an Integer on the right side of <
     * @return bool to indicate whether the Integer on the left side is smaller than that on the right side
     * smaller comparison operator for Integer
     */
    friend bool operator < (const Integer& lhs, const Integer& rhs) 
    {
        if(lhs.negative && !rhs.negative)
        {
            return true;
        }
        else if(!lhs.negative && rhs.negative)
        {
            return false;
        }
        else if(lhs.negative && rhs.negative)
        {
            return lexicographical_compare(rhs.begin_pos, rhs.end_pos, lhs.begin_pos, lhs.end_pos);
        }
        else
        {
            return lexicographical_compare(lhs.begin_pos, lhs.end_pos, rhs.begin_pos, rhs.end_pos);
        }
    }

    // -----------
    // operator <=
    // -----------

    /**
     * @param lhs an Integer on the left side of <=
     * @param rhs an Integer on the right side of <=
     * @return bool to indicate whether the Integer on the left side is smaller or equal to that on the right side
     * smaller or equal comparison operator for Integer
     */
    friend bool operator <= (const Integer& lhs, const Integer& rhs) 
    {
        return !(rhs < lhs);
    }

    // ----------
    // operator >
    // ----------

    /**
     * @param lhs an Integer on the left side of >
     * @param rhs an Integer on the right side of >
     * @return bool to indicate whether the Integer on the left side is greater than that on the right side
     * greater comparison operator for Integer
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) 
    {
        return (rhs < lhs);
    }

    // -----------
    // operator >=
    // -----------

    /**
     * @param lhs an Integer on the left side of >=
     * @param rhs an Integer on the right side of >=
     * @return bool to indicate whether the Integer on the left side is greater or equal to that on the right side
     * greater or equal comparison operator for Integer
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) 
    {
        return !(lhs < rhs);
    }

    // ----------
    // operator +
    // ----------

    /**
     * @param lhs an Integer as augend
     * @param rhs an Integer as addend
     * @return an Integer that is the sum of the two
     * + operator for Integer
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) 
    {
        return lhs += rhs;
    }

    // ----------
    // operator -
    // ----------

    /**
     * @param lhs an Integer as minuend
     * @param rhs an Integer as subtrahend
     * @return an Integer that is difference
     * - operator for Integer
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) 
    {
        return lhs -= rhs;
    }

    // ----------
    // operator *
    // ----------

    /**
     * @param lhs an Integer as multiplicand
     * @param rhs an Integer as multiplier
     * @return an Integer that is the product of the two
     * * operator for Integer
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) 
    {
        return lhs *= rhs;
    }

    // ----------
    // operator /
    // ----------

    /**
     * @param lhs an Integer as dividend
     * @param rhs an Integer as divider
     * @return an Integer that is the result of the division
     * @throw invalid_argument if (rhs == 0)
     * / operator for Integer
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) 
    {
        if(rhs == Integer(0))
        {
            throw invalid_argument("Integer::operator / (Integer,const Integer&)");
        }
        return lhs /= rhs;
    }

    // ----------
    // operator %
    // ----------

    /**
     * @param lhs an Integer on the left side of %
     * @param rhs an Integer on the right side of %
     * @return an Integer that is the result of the modulo operation
     * @throw invalid_argument if (rhs <= 0)
     * % operator for Integer
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) 
    {
        if(rhs <= Integer(0))
        {
            throw invalid_argument("Integer::operator % (Integer,const Integer&)");
        }
        return lhs %= rhs;
    }

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an Integer gettubg left shifted
     * @param rhs an int which is the number of digits to shift
     * @return an Integer that is the result of left shift operation
     * @throw invalid_argument if (rhs < 0)
     * << operator for Integer
     */
    friend Integer operator << (Integer lhs, int rhs) 
    {
        if(rhs < Integer(0))
        {
            throw invalid_argument("Integer::operator << (Integer, int)");
        }
        return lhs <<= rhs;
    }

    // -----------
    // operator >>
    // -----------

    /**
     * @param lhs an Integer gettubg right shifted
     * @param rhs an int which is the number of digits to shift
     * @return an Integer that is the result of right shift operation
     * @throw invalid_argument if (rhs < 0)
     * >> operator for Integer
     */
    friend Integer operator >> (Integer lhs, int rhs) 
    {
        if(rhs < Integer(0))
        {
            throw invalid_argument("Integer::operator >> (Integer, int)");
        }
        return lhs >>= rhs;
    }

    // -----------
    // operator <<
    // -----------

    /**
     * @param lhs an ostream
     * @param rhs an Integer getting streamed
     * @return an ostream with rhs streamed in
     * << stream operator for Integer
     */
    friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) 
    {

        if(rhs.negative)
        {
             lhs << '-';
        }
        copy(rhs.begin_pos, rhs.end_pos, ostream_iterator<int>(lhs));

        return lhs;
    }

    // ---
    // abs
    // ---

    /**
     * absolute value
     * does NOT modify the argument
     * @param x an Integer
     * @return an Integer that is the absolute value of x
     */
    friend Integer abs (Integer x) 
    {
        return x.abs();
    }

    // ---
    // pow
    // ---

    /**
     * power
     * does NOT modify the argument
     * @param x an Integer
     * @param e an int which the the number of power x is getting raised to
     * @return an Integer that is the result of the power operation
     * @throw invalid_argument if (x == 0) && (e == 0)
     * @throw invalid_argument if (e < 0)
     */
    friend Integer pow (Integer x, int e) 
    {
        if((x == Integer(0)) || e <= 0)
        {
            throw invalid_argument("Integer::pow(Integer, int)");
        }
        return x.pow(e);
    }

    private:
        // ----
        // data
        // ----

        C digits; 
        typename C::iterator end_pos;
        typename C::iterator begin_pos;
        bool negative;

    private:

        // -----
        // valid
        // -----

        bool valid () const 
        {
            return true;
        }

        // ---------------
        // expand_capacity
        // ---------------

        //expand the capacity of the container (digits)
        void expand_capacity(int increase_size)
        {
            expand_capacity(increase_size, digits);
        }

        //helper overloaded functions of expand_capacity for different underlied containers
        void expand_capacity(int increase_size, vector<T>)
        {
            digits.reserve((digits.size() + increase_size) * 3);
        }

        void expand_capacity(int increase_size, deque<T>)
        {
            digits.resize((digits.size() + increase_size) * 3);
        }

    public:
        // ------------
        // constructors
        // ------------

        /**
         * @param value an integer as the value of the Integer
         * constructor taking an integer
         */
        Integer (int value) 
        {
            if(value < 0)
            {
                negative = true;
                value = -value;
            }
            else
            {
                negative = false;
            }

            for(auto elem: to_string(value))
            {
                digits.push_back(int(elem) - ZERO_ASCII_OFFSET);
            }

            begin_pos = digits.begin();
            end_pos = digits.end();
            assert(valid());
        }

        /**
         * @param value a C++ string as the value of the Integer
         * @throw invalid_argument if value is not a valid representation of an Integer
         * constructor taking a string
         */
        explicit Integer (const string& value) 
        {
            try
            {
                int v = stoi(value);

                if(v < 0)
                {
                    negative = true;
                    v = -v;
                }
                else
                {
                    negative = false;
                }

                for(auto elem: to_string(v))
                {
                    digits.push_back(int(elem) - ZERO_ASCII_OFFSET);
                }

                end_pos = digits.end();
            }
            catch(invalid_argument e)
            {
                throw invalid_argument("Integer::Integer(const string&)");
            }
            catch(out_of_range e)
            {
                throw out_of_range("Integer::Integer(const string&)");
            }
            if(!valid())
            {
                throw invalid_argument("Integer::Integer(const string&)");
            }
        }

        // Default copy, destructor, and copy assignment.
        // Integer (const Integer&);
        // ~Integer ();
        // Integer& operator = (const Integer&);

        // ----------
        // operator -
        // ----------

        /**
         * @return the result of the negation
         * negation operation for Integer
         */
        Integer operator - () const 
        {
            Integer result = *this;
            result.negative = !result.negative;
            return result;
        }

        // -----------
        // operator ++
        // -----------

        /**
         * @return the result of the incrementation (pre)
         * pre incrementation operation for Integer
         */
        Integer& operator ++ ()
        {
            *this += 1;
            return *this;
        }

        /**
         * @return the result of the incrementation (pos)
         * pos incrementation operation for Integer
         */
        Integer operator ++ (int) 
        {
            Integer x = *this;
            ++(*this);
            return x;
        }

        // -----------
        // operator --
        // -----------

        /**
         * @return the result of the decrementation (pre)
         * pre decrementation operation for Integer
         */
        Integer& operator -- () 
        {
            *this -= 1;
            return *this;
        }

        /**
         * @return the result of the decrementation (pos)
         * pos decrementation operation for Integer
         */
        Integer operator -- (int) 
        {
            Integer x = *this;
            --(*this);
            return x;
        }

        // -----------
        // operator +=
        // -----------

        /**
         * @param rhs an Integer as addend
         * @return the result of the addition
         * += operation for Integer
         */
        Integer& operator += (const Integer& rhs) 
        {
            if(digits.max_size() < (max(digits.size(), rhs.digits.size()) + 1))
            {
                expand_capacity(max(digits.size(), rhs.digits.size()) + 1);
            }

            if(negative != rhs.negative)
            {
                if(*this >= rhs)
                {
                    if(-rhs > *this)
                    {
                        negative = true;
                        end_pos = minus_digits(rhs.begin_pos, rhs.end_pos, begin_pos, end_pos, begin_pos);
                    }
                    else
                    {
                        end_pos = minus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
                    }
                }
                else
                {
                    if(-(*this) <= rhs)
                    {
                        negative = false;
                        end_pos = minus_digits(rhs.begin_pos, rhs.end_pos, begin_pos, end_pos, begin_pos);
                    }
                    else
                    {
                        end_pos = minus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
                    }
                }
                
            }
            else
            {
                end_pos = plus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
            }
            return *this;
        }

        // -----------
        // operator -=
        // -----------

        /**
         * @param rhs an Integer as subtrahend
         * @return the result of the subtraction
         * -= operation for Integer
         */
        Integer& operator -= (const Integer& rhs) 
        {

            if(digits.max_size() < (max(digits.size(), rhs.digits.size()) + 1))
            {
                expand_capacity(max(digits.size(), rhs.digits.size()) + 1);
            }

            if(negative == rhs.negative)
            {
                if(negative)
                {
                    if(*this >= rhs)
                    {
                        negative = false;
                        end_pos = minus_digits(rhs.begin_pos, rhs.end_pos, begin_pos, end_pos, begin_pos);
                    }
                    else
                    {
                        end_pos = minus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
                    }
                }
                else
                {
                    if(*this >= rhs)
                    {
                        end_pos = minus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
                    }
                    else
                    {
                        negative = true;
                        end_pos = minus_digits(rhs.begin_pos, rhs.end_pos, begin_pos, end_pos, begin_pos);
                    }
                }
            }
            else
            {
                end_pos = plus_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);
            }
            return *this;
        }

        // -----------
        // operator *=
        // -----------

        /**
         * @param rhs an Integer as multiplier
         * @return the result of the multiplication
         * *= operation for Integer
         */
        Integer& operator *= (const Integer& rhs) 
        {
            if(digits.max_size() < (digits.size() + rhs.digits.size()))
            {
                expand_capacity(digits.size() + rhs.digits.size());
            }

            if(negative == rhs.negative)
            {
                negative = false;
            }
            else
            {
                negative = true;
            }

            end_pos = multiplies_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);

            return *this;
        }

        // -----------
        // operator /=
        // -----------

        /**
         * @param rhs an Integer as divider
         * @return the result of the division
         * @throw invalid_argument if (rhs == 0)
         * /= operation for Integer
         */
        Integer& operator /= (const Integer& rhs) 
        {
            if(rhs == Integer(0))
            {
                throw invalid_argument("Integer::operator /= (const Integer&)");
            }

            if(negative == rhs.negative)
            {
                negative = false;
            }
            else
            {
                negative = true;
            }

            end_pos = divides_digits(begin_pos, end_pos, rhs.begin_pos, rhs.end_pos, begin_pos);

            return *this;
        }

        // -----------
        // operator %=
        // -----------

        /**
         * @param rhs an Integer as modulor
         * @return the result of the modulo operation
         * @throw invalid_argument if (rhs <= 0)
         * %= operation for Integer
         */
        Integer& operator %= (const Integer& rhs) 
        {
            if(rhs <= Integer(0))
            {
                throw invalid_argument("Integer::operator %= (const Integer&)");
            }

            Integer division_result = (*this) / rhs;
            (*this) = (*this - (division_result * rhs));

            return *this;
        }

        // ------------
        // operator <<=
        // ------------

        /**
         * @param n an int (the number of digits to shift)
         * @return the result of the left shift operation
         * @throw invalid_argument if (n < 0)
         * <<= operation for Integer
         */
        Integer& operator <<= (int n) 
        {
            if(n < 0)
            {
                throw invalid_argument("Integer::operator <<= (int)");
            }
            end_pos = shift_left_digits(begin_pos, end_pos, n, begin_pos);
            return *this;
        }

        // ------------
        // operator >>=
        // ------------

        /**
         * @param n an int (the number of digits to shift)
         * @return the result of the right shift operation
         * @throw invalid_argument if (n < 0)
         * >>= operation for Integer
         */
        Integer& operator >>= (int n) 
        {
            if(n < 0)
            {
                throw invalid_argument("Integer::operator >>= (int)");
            }
            end_pos = right_left_digits(begin_pos, end_pos, n, begin_pos);
            return *this;
        }

        // ---
        // abs
        // ---

        /**
         * absolute value operation
         * @return the result of the absolute value
         */
        Integer& abs () 
        {
            negative = false;
            return *this;
        }

        // ---
        // pow
        // ---

        /**
         * power operation
         * @e an int as the number of power the Integer get raised to
         * @throw invalid_argument if (this == 0) && (e == 0)
         * @throw invalid_argument if (e < 0)
         */
        Integer& pow (int e) 
        {
            if((*this == Integer(0)) || e <= 0)
            {
                throw invalid_argument("Integer::pow(int)");
            }

            Integer temp = *this;

            while(e-- != 0)
            {
                *this *= temp;
            }

            return *this;
        }
};

#endif // Integer_h
