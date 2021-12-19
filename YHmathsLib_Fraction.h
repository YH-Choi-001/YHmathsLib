#ifndef YHMATHSLIB_FRACTION_H
#define YHMATHSLIB_FRACTION_H

#ifndef YHMATHSLIB_H
#include "YHmathsLib.h"
#endif // #ifndef YHMATHSLIB_H

namespace YH {
    namespace Lib {
        enum Fraction_states {
            NORMAL_FLOATING = 0,
            INFINITY_FLOATING,
            NOT_A_NUM_FLOATING
        };
        // The ultimate goal of using this class
        // is to prevent the losing of precision
        // from storing values in floating-point architectures.
        class Fraction {
            private:
                Func::maths::largest_int upper_val;
                Func::maths::largest_int lower_val;
                Fraction_states special_states;
                // enum { normal = 0, nan, inf, irrational }
                const Fraction &myself () const { return *this; }
                      Fraction &myself ()       { return *this; }
                void myself_to_inf ();
                void myself_to_nan ();
                Fraction create_inf_obj () const;
                Fraction create_nan_obj () const;
            public:
                #define FRACTION_CONSTRUCTOR 1
                #define FRACTION_BASIC_METHOD 1
                #define FRACTION_ASSIGN_METHOD 1
                #define FRACTION_ARITHMETIC_AND_ASSIGN_METHOD 1
                #define FRACTION_METHOD_OPERATORS 1
                #define FRACTION_METHOD_OPERATORS_CONST 1
                #if defined(FRACTION_CONSTRUCTOR)
                    Fraction ();
                    Fraction (const Func::maths::largest_float val);
                    Fraction (const Func::maths::largest_int init_upper_val, const Func::maths::largest_int init_lower_val);
                    Fraction (const Fraction &another_floating_pt);
                    ~Fraction ();
                # endif // #if defined(FRACTION_CONSTURUCTOR)
                #if defined(FRACTION_BASIC_METHOD)
                    // get the numerator in the fraction
                    Func::maths::largest_int numerator () const;
                    // get the denominator in the fraction
                    Func::maths::largest_int denominator () const;
                    // get the state of the current fraction
                    Fraction_states state () const;
                    // rounding to nearest integer: pulls the +ive or -ive value towards 0
                    Func::maths::largest_int rnddn () const;
                    // rounding to nearest integer: pulls the +ive or -ive value away from 0
                    Func::maths::largest_int rndup () const;
                    // the value decreases itself to the nearest integer, unless itself is already an integer
                    Func::maths::largest_int floor () const;
                    // the value increases itself to the nearest integer, unless itself is already an integer
                    Func::maths::largest_int ceil () const;
                    // get the floating-point number from the fraction
                    Func::maths::largest_float floated_num () const;
                # endif // #if defined(FRACTION_BASIC_METHOD)
                // assignment
                #if defined(FRACTION_ASSIGN_METHOD)
                    Fraction &assign (const Func::maths::largest_float val);
                    Fraction &assign (const Func::maths::largest_int upper_val, const Func::maths::largest_int lower_val);
                    Fraction &assign (const Fraction &rhs);
                #endif // #if defined(FRACTION_ASSIGN_METHOD)
                #if defined(FRACTION_ARITHMETIC_AND_ASSIGN_METHOD)
                    Fraction &add_myself (const Fraction &rhs);
                    Fraction &add_myself (const Func::maths::largest_float rhs);
                    Fraction &add_myself (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator);
                    Fraction &sub_myself (const Fraction &rhs);
                    Fraction &sub_myself (const Func::maths::largest_float rhs);
                    Fraction &sub_myself (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator);
                    Fraction &mul_myself (const Fraction &rhs);
                    Fraction &mul_myself (const Func::maths::largest_float rhs);
                    Fraction &mul_myself (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator);
                    Fraction &div_myself (const Fraction &rhs);
                    Fraction &div_myself (const Func::maths::largest_float rhs);
                    Fraction &div_myself (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator);
                    Fraction &mod_myself (const Fraction &rhs);
                    Fraction &mod_myself (const Func::maths::largest_float rhs);
                    Fraction &mod_myself (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator);
                    Fraction &increment_myself ();
                    Fraction &decrement_myself ();
                #endif // #if defined(FRACTION_ARITH_AND_ASSIGN_METHOD)
                // operators invloving assignment, including =, +=, -=, *=, /=, %=, ++, --
                #if defined(FRACTION_METHOD_OPERATORS)
                    Fraction &operator  = (const Fraction &rhs);
                    Fraction &operator  = (const Func::maths::largest_float rhs);
                    Fraction &operator += (const Fraction &rhs);
                    Fraction &operator += (const Func::maths::largest_float rhs);
                    Fraction &operator -= (const Fraction &rhs);
                    Fraction &operator -= (const Func::maths::largest_float rhs);
                    Fraction &operator *= (const Fraction &rhs);
                    Fraction &operator *= (const Func::maths::largest_float rhs);
                    Fraction &operator /= (const Fraction &rhs);
                    Fraction &operator /= (const Func::maths::largest_float rhs);
                    Fraction &operator %= (const Fraction &rhs);
                    Fraction &operator %= (const Func::maths::largest_float rhs);
                    Fraction &operator ++ ();
                    Fraction &operator -- ();
                #endif // #if defined(FRACTION_OPERATORS)
                // operators const
                #if defined(FRACTION_METHOD_OPERATORS_CONST)
                    // auto convert to bool value
                    operator bool () const;
                    // boolean reverse
                    bool operator ! () const;
                    // convert the fraction to a negative number
                    Fraction operator - () const;
                #endif // #if defined(FRACTION_OPERATORS_CONST)
        };
        namespace Func {
            namespace maths {
                #define FRACTION_BASIC_FUNC 1

                #define FRACTION_ARITHMETIC_FUNC 1
                    #define FRACTION_ADD 1
                    #define FRACTION_SUB 1
                    #define FRACTION_MUL 1
                    #define FRACTION_DIV 1
                    #define FRACTION_MOD 1

                #define FRACTION_CMP_FUNC 1
                    #define FRACTION_EQUAL_TO 1
                    #define FRACTION_NOT_EQUAL_TO 1
                    #define FRACTION_LESS_THAN 1
                    #define FRACTION_GREATER_THAN 1
                    #define FRACTION_LESS_THAN_OR_EQUAL_TO 1
                    #define FRACTION_GREATER_THAN_OR_EQUAL_TO 1
                // #undef FRACTION_CMP_FUNC // implementation not completed

                #define FRACTION_NONMEM_OPERATORS 1

                #if defined(FRACTION_BASIC_FUNC)
                    // returns an error object in YH::Lib::Fraction
                    ::YH::Lib::Fraction nan_obj ();
                    // returns an infinitive object in YH::Lib::Fraction
                    ::YH::Lib::Fraction inf_obj ();
                    // converts inputed floating-point value to a Fraction
                    ::YH::Lib::Fraction to_floating_pt (const largest_float val);
                #endif // #if defined(FRACTION_BASIC_FUNC)

                #if defined(FRACTION_ARITHMETIC_FUNC)
                    // addition
                    #if defined(FRACTION_ADD)
                        Fraction add (const Fraction &lhs, const Fraction &rhs);                                               // Fraction + Fraction
                        Fraction add (const Fraction &lhs, const largest_float rhs);                                              // Fraction + 0.0
                        Fraction add (const largest_float lhs, const Fraction &rhs);                                              // 0.0 + Fraction
                        Fraction add (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);   // Fraction + 0 / 1
                        Fraction add (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);   // 0 / 1 + Fraction
                    #endif // #if defined(FRACTION_ADD)
                    // subtraction
                    #if defined(FRACTION_SUB)
                        Fraction sub (const Fraction &lhs, const Fraction &rhs);                                               // Fraction - Fraction
                        Fraction sub (const Fraction &lhs, const largest_float rhs);                                              // Fraction - 0.0
                        Fraction sub (const largest_float lhs, const Fraction &rhs);                                              // 0.0 - Fraction
                        Fraction sub (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);   // Fraction - 0 / 1
                        Fraction sub (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);   // 0 / 1 - Fraction
                    #endif // #if defined(FRACTION_SUB)
                    // multiplication
                    #if defined(FRACTION_MUL)
                        Fraction mul (const Fraction &lhs, const Fraction &rhs);
                        Fraction mul (const Fraction &lhs, const largest_float rhs);
                        Fraction mul (const largest_float lhs, const Fraction &rhs);
                        Fraction mul (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        Fraction mul (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_MUL)
                    // division
                    #if defined(FRACTION_DIV)
                        Fraction div (const Fraction &lhs, const Fraction &rhs);
                        Fraction div (const Fraction &lhs, const largest_float rhs);
                        Fraction div (const largest_float lhs, const Fraction &rhs);
                        Fraction div (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        Fraction div (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_DIV)
                    // modula
                    #if defined(FRACTION_MOD)
                        Fraction mod (const Fraction &lhs, const Fraction &rhs);
                        Fraction mod (const Fraction &lhs, const largest_float rhs);
                        Fraction mod (const largest_float lhs, const Fraction &rhs);
                        Fraction mod (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        Fraction mod (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_MOD)
                #endif // #if defined(FRACTION_ARITHMETIC_FUNC)

                #if defined(FRACTION_CMP_FUNC)
                // comparison of ==, !=, <, >, <=, >=
                // INFINITY == INFINITY returns 1
                // INFINITY != INFINITY returns 0
                // INFINITY <  INFINITY returns 0
                // INFINITY >  INFINITY returns 0
                // INFINITY <= INFINITY returns 1
                // INFINITY >= INFINITY returns 1
                //      NAN == NAN      returns 0
                //      NAN != NAN      returns 1
                //      NAN <  NAN      returns 0
                //      NAN >  NAN      returns 0
                //      NAN <= NAN      returns 0
                //      NAN >= NAN      returns 0
                // combinations are:
                    // INF , INF 0
                    // NAN , NAN 1
                    // 123 , 123 ?
                    // INF , NAN 1
                    // NAN , INF 1
                    // INF , 123 1
                    // 123 , INF 1
                    // NAN , 123 1
                    // 123 , NAN 1

                    // ==
                    #if defined(FRACTION_EQUAL_TO)
                        bool equal_to (const Fraction &lhs, const Fraction &rhs);
                        bool equal_to (const Fraction &lhs, const largest_float rhs);
                        bool equal_to (const largest_float lhs, const Fraction &rhs);
                        bool equal_to (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool equal_to (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_EQUAL_TO)

                    // !=
                    #if defined(FRACTION_NOT_EQUAL_TO)
                        bool not_equal_to (const Fraction &lhs, const Fraction &rhs);
                        bool not_equal_to (const Fraction &lhs, const largest_float rhs);
                        bool not_equal_to (const largest_float lhs, const Fraction &rhs);
                        bool not_equal_to (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool not_equal_to (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_NOT_EQUAL_TO)

                    // <
                    #if defined(FRACTION_LESS_THAN)
                        bool less_than (const Fraction &lhs, const Fraction &rhs);
                        bool less_than (const Fraction &lhs, const largest_float rhs);
                        bool less_than (const largest_float lhs, const Fraction &rhs);
                        bool less_than (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool less_than (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_LESS_THAN)

                    // >
                    #if defined(FRACTION_GREATER_THAN)
                        bool greater_than (const Fraction &lhs, const Fraction &rhs);
                        bool greater_than (const Fraction &lhs, const largest_float rhs);
                        bool greater_than (const largest_float lhs, const Fraction &rhs);
                        bool greater_than (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool greater_than (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_GREATER_THAN)

                    // <=
                    #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)
                        bool less_than_or_equal_to (const Fraction &lhs, const Fraction &rhs);
                        bool less_than_or_equal_to (const Fraction &lhs, const largest_float rhs);
                        bool less_than_or_equal_to (const largest_float lhs, const Fraction &rhs);
                        bool less_than_or_equal_to (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool less_than_or_equal_to (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)

                    // >=
                    #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
                        bool greater_than_or_equal_to (const Fraction &lhs, const Fraction &rhs);
                        bool greater_than_or_equal_to (const Fraction &lhs, const largest_float rhs);
                        bool greater_than_or_equal_to (const largest_float lhs, const Fraction &rhs);
                        bool greater_than_or_equal_to (const Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator);
                        bool greater_than_or_equal_to (const largest_int lhs_numerator, const largest_int lhs_denominator, const Fraction &rhs);
                    #endif // #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
                #endif // #if defined(FRACTION_CMP_FUNC)

                #if defined(FRACTION_NONMEM_OPERATORS)
                    #if defined(FRACTION_ARITHMETIC_FUNC)
                        // +
                        #if defined(FRACTION_ADD)
                            Fraction operator + (const Fraction &lhs, const Fraction &rhs);
                            Fraction operator + (const Fraction &lhs, const largest_float rhs);
                            Fraction operator + (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_ADD)

                        // -
                        #if defined(FRACTION_SUB)
                            Fraction operator - (const Fraction &lhs, const Fraction &rhs);
                            Fraction operator - (const Fraction &lhs, const largest_float rhs);
                            Fraction operator - (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_SUB)

                        // *
                        #if defined(FRACTION_MUL)
                            Fraction operator * (const Fraction &lhs, const Fraction &rhs);
                            Fraction operator * (const Fraction &lhs, const largest_float rhs);
                            Fraction operator * (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_MUL)

                        // /
                        #if defined(FRACTION_DIV)
                            Fraction operator / (const Fraction &lhs, const Fraction &rhs);
                            Fraction operator / (const Fraction &lhs, const largest_float rhs);
                            Fraction operator / (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_DIV)

                        // %
                        #if defined(FRACTION_MOD)
                            Fraction operator % (const Fraction &lhs, const Fraction &rhs);
                            Fraction operator % (const Fraction &lhs, const largest_float rhs);
                            Fraction operator % (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_MOD)
                    #endif // #if defined(FRACTION_ARITHMETIC_FUNC)

                    #if defined(FRACTION_CMP_FUNC)
                        // ==
                        #if defined(FRACTION_EQUAL_TO)
                            bool operator == (const Fraction &lhs, const Fraction &rhs);
                            bool operator == (const Fraction &lhs, const largest_float rhs);
                            bool operator == (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_EQUAL_TO)

                        // !=
                        #if defined(FRACTION_NOT_EQUAL_TO)
                            bool operator != (const Fraction &lhs, const Fraction &rhs);
                            bool operator != (const Fraction &lhs, const largest_float rhs);
                            bool operator != (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_NOT_EQUAL_TO)

                        // <
                        #if defined(FRACTION_LESS_THAN)
                            bool operator < (const Fraction &lhs, const Fraction &rhs);
                            bool operator < (const Fraction &lhs, const largest_float rhs);
                            bool operator < (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_LESS_THAN)

                        // >
                        #if defined(FRACTION_GREATER_THAN)
                            bool operator > (const Fraction &lhs, const Fraction &rhs);
                            bool operator > (const Fraction &lhs, const largest_float rhs);
                            bool operator > (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_GREATER_THAN)

                        // <=
                        #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)
                            bool operator <= (const Fraction &lhs, const Fraction &rhs);
                            bool operator <= (const Fraction &lhs, const largest_float rhs);
                            bool operator <= (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)

                        // >=
                        #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
                            bool operator >= (const Fraction &lhs, const Fraction &rhs);
                            bool operator >= (const Fraction &lhs, const largest_float rhs);
                            bool operator >= (const largest_float lhs, const Fraction &rhs);
                        #endif // #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
                    #endif // #if defined(FRACTION_CMP_FUNC)
                #endif // #if defined(FRACTION_NONMEM_OPERATORS)
            }
        }
    }
}

using YH::Lib::Func::maths::operator  + ;
using YH::Lib::Func::maths::operator  - ;
using YH::Lib::Func::maths::operator  * ;
using YH::Lib::Func::maths::operator  / ;
using YH::Lib::Func::maths::operator  % ;
using YH::Lib::Func::maths::operator == ;
using YH::Lib::Func::maths::operator != ;
using YH::Lib::Func::maths::operator <  ;
using YH::Lib::Func::maths::operator >  ;
using YH::Lib::Func::maths::operator <= ;
using YH::Lib::Func::maths::operator >= ;

#endif // #ifndef YHMATHSLIB_FRACTION_H