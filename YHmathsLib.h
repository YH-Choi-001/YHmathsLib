#ifndef YHMATHSLIB_H
#define YHMATHSLIB_H __DATE__ ", " __TIME__

// for debugging only
// #include <iostream>
// #include <string>
// #include <sstream>

#include <stdlib.h>
// for the usage of math functions such as pow(), sin(), arctan(), ...
#include <math.h>
// for the usage of signed int8_t, int16_t, int32_t, int64_t and unsigned uint8_t, uint16_t, uint32_t, uint64_t
#if defined(ARDUINO)
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif
// for the usage of maxed types
#include "../YHtypeLib/YHtypeLib.h"

namespace YH {
    namespace Lib {
        namespace Func {
            namespace maths {
                typedef types::largest_float largest_float;
                typedef types::largest_int largest_int;
                typedef types::largest_uint largest_uint;
                typedef types::smallest_float smallest_float;
                typedef types::smallest_int smallest_int;
                typedef types::smallest_uint smallest_uint;
            }
        }
    }
}

// inits the arguments into a TYPE array
#define TO_NARG(TYPE,...) (TYPE[]){__VA_ARGS__}
// inits the arguments into a long long array
// #define TO_LL_NARG(...) (long long[]){__VA_ARGS__}
#define TO_LL_NARG(...) TO_NARG(largest_int, __VA_ARGS__)
// inits the arguments into a largest_float array
// #define TO_LD_NARG(...) (largest_float[]){__VA_ARGS__}
#define TO_LD_NARG(...) TO_NARG(largest_float, __VA_ARGS__)
// get the length of the numerical array
#define PP_NARG(...) sizeof(TO_LD_NARG(__VA_ARGS__))/sizeof(largest_float)

#ifdef NUM_RESULT_SIZE
#warning "NUM_RESULT_SIZE is not prefered to change"
#else
// #define NUM_RESULT_SIZE 20
#endif // #ifdef NUM_RESULT_SIZE
#ifdef CHAR_RESULT_SIZE
#warning "CHAR_RESULT_SIZE is not prefered to change"
#else
// #define CHAR_RESULT_SIZE 256
#endif // #ifdef CHAR_RESULT_SIZE

namespace YH {
    namespace Lib {
        /*
        class Floating {
            private:
                long long intval;
                long flval;
            public:
                Floating ();
                Floating (const long double init_val);
                Floating (const Floating &init_val);
                ~Floating ();
                //
                Floating &assign (const long double rhs);
                Floating &assign (const Floating &rhs);
                //
        };
        */
        // included in YHmathsLib_Floating_pt.h
        // class Floating_pt {
        //     private:
        //         long long upper_val;
        //         long long lower_val;
        //         uint16_t special_states;
        //         // enum { normal = 0, nan, inf, irrational }
        //         Floating_pt &myself () { return *this; }
        //     public:
        //         #define FLOATING_PT_CONSTRUCTOR 1
        //         #define FLOATING_PT_BASIC_METHOD 1
        //         #define FLOATING_PT_ASSIGN_METHOD 1
        //         #define FLOATING_PT_ADD_METHOD 1
        //         #define FLOATING_PT_SUB_METHOD 1
        //         #define FLOATING_PT_MUL_METHOD 1
        //         #define FLOATING_PT_DIV_METHOD 1
        //         #define FLOATING_PT_MOD_METHOD 1
        //         #define FLOATING_PT_METHOD_OPERATORS 1
        //         #define FLOATING_PT_METHOD_OPERATORS_CONST 1
        //         #if defined(FLOATING_PT_CONSTRUCTOR)
        //             Floating_pt ();
        //             Floating_pt (const long double val);
        //             Floating_pt (const long long init_upper_val, const long long init_lower_val);
        //             Floating_pt (const Floating_pt &another_floating_pt);
        //             ~Floating_pt ();
        //         # endif // #if defined(FLOATING_PT_CONSTURUCTOR)
        //         #if defined(FLOATING_PT_BASIC_METHOD)
        //             long long upper_val () const;
        //             long long lower_val () const;
        //             long long floor () const;
        //             long long ceil () const;
        //             long double floated_num () const;
        //         # endif // #if defined(FLOATING_PT_BASIC_METHOD)
        //         // assignment
        //         #if defined(FLOATING_PT_ASSIGN_METHOD)
        //             Floating_pt &assign (const long double val);
        //             Floating_pt &assign (const long long upper_val, const long long lower_val);
        //             Floating_pt &assign (const Floating_pt &another_floating_pt);
        //         #endif // #if defined(FLOATING_PT_ASSIGN_METHOD)
        //         // addition
        //         #if defined(FLOATING_PT_ADD_METHOD)
        //             Floating_pt add (const long double val) const;
        //             Floating_pt add (const long long upper_val, const long long lower_val) const;
        //             Floating_pt add (const Floating_pt &another_floating_pt) const;
        //         #endif // #if defined(FLOATING_PT_ADD_METHOD)
        //         // subtraction
        //         #if defined(FLOATING_PT_SUB_METHOD)
        //             Floating_pt sub (const long double val) const;
        //             Floating_pt sub (const long long upper_val, const long long lower_val) const;
        //             Floating_pt sub (const Floating_pt &another_floating_pt) const;
        //         #endif // #if defined(FLOATING_PT_SUB_METHOD)
        //         // multiplication
        //         #if defined(FLOATING_PT_MUL_METHOD)
        //             Floating_pt mul (const long double val) const;
        //             Floating_pt mul (const long long upper_val, const long long lower_val) const;
        //             Floating_pt mul (const Floating_pt &another_floating_pt) const;
        //         #endif // #if defined(FLOATING_PT_MUL_METHOD)
        //         // division
        //         #if defined(FLOATING_PT_DIV_METHOD)
        //             Floating_pt div (const long double val) const;
        //             Floating_pt div (const long long upper_val, const long long lower_val) const;
        //             Floating_pt div (const Floating_pt &another_floating_pt) const;
        //         #endif // #if defined(FLOATING_PT_DIV_METHOD)
        //         // modula
        //         #if defined(FLOATING_PT_MOD_METHOD)
        //             Floating_pt mod (const long double val) const;
        //             Floating_pt mod (const long long upper_val, const long long lower_val) const;
        //             Floating_pt mod (const Floating_pt &another_floating_pt) const;
        //         #endif // #if defined(FLOATING_PT_MOD_METHOD)
        //         // operators
        //         #if defined(FLOATING_PT_METHOD_OPERATORS)
        //             Floating_pt operator = (const long double val);
        //             Floating_pt operator = (const Floating_pt &another_floating_pt);
        //             Floating_pt operator += (const long double val);
        //             Floating_pt operator += (const Floating_pt &another_floating_pt);
        //             Floating_pt operator -= (const long double val);
        //             Floating_pt operator -= (const Floating_pt &another_floating_pt);
        //             Floating_pt operator *= (const long double val);
        //             Floating_pt operator *= (const Floating_pt &another_floating_pt);
        //             Floating_pt operator /= (const long double val);
        //             Floating_pt operator /= (const Floating_pt &another_floating_pt);
        //             Floating_pt operator %= (const long double val);
        //             Floating_pt operator %= (const Floating_pt &another_floating_pt);
        //             Floating_pt operator ++ ();
        //             Floating_pt operator ++ ();
        //             Floating_pt operator -- ();
        //             Floating_pt operator -- ();
        //                 // operators const
        //                 #if defined(FLOATING_PT_METHOD_OPERATORS_CONST)
        //                     // boolean reverse
        //                     bool operator ! () const;
        //                     // addition
        //                     Floating_pt operator + (const long double val) const;
        //                     Floating_pt operator + (const Floating_pt &another_floating_pt) const;
        //                     // subtraction
        //                     Floating_pt operator - (const long double val) const;
        //                     Floating_pt operator - (const Floating_pt &another_floating_pt) const;
        //                     // multiplication
        //                     Floating_pt operator * (const long double val) const;
        //                     Floating_pt operator * (const Floating_pt &another_floating_pt) const;
        //                     // division
        //                     Floating_pt operator / (const long double val) const;
        //                     Floating_pt operator / (const Floating_pt &another_floating_pt) const;
        //                     // modula
        //                     Floating_pt operator % (const long double val) const;
        //                     Floating_pt operator % (const Floating_pt &another_floating_pt) const;
        //                 #endif // #if defined(FLOATING_PT_OPERATORS_CONST)
        //         #endif // #if defined(FLOATING_PT_OPERATORS)
        // };
        namespace Func {
            namespace maths {
                extern const char YHmathsLib_vers [];
                extern const largest_float pi;
                // private functions
                // namespace pvt {
                    // for array result returning use only
                //     template <class Store_unit>
                //     class Array_list {
                //         private:
                //             Store_unit *ptr;
                //             largest_uint len;
                //             Array_list &myself () const { return *this; }
                //         public:
                //             // default constructor
                //             Array_list ();
                //             // constructor that auto calls this->resize(request_len)
                //             Array_list (const largest_uint request_len);
                //             // get the pointer of the dynamic array of Store_unit
                //             const Store_unit *raw_ptr () const;
                //             // get the allocated length for the dynamic array
                //             largest_uint alloced_len () const;
                //             // resize the Store_unit dynamic array
                //             int16_t resize (const largest_uint request_len);
                //             // resize before calling this method
                //             int16_t movmem (const Store_unit *arr, const largest_uint arrlen = 0UL);
                //             // get the object of the inputed index
                //                   Store_unit &idx (const largest_uint index);
                //             const Store_unit &idx (const largest_uint index) const;
                //             // clear up and free occupied memory
                //             ~Array_list ();
                //     };
                //     void assignToArray (const largest_float *x, const largest_uint length);
                //     void assignToArray (const char *x, const largest_uint length);
                //     void swap_result (const largest_uint idx_1, const largest_uint idx_2);
                //     extern Array_list<largest_float> result; // acts as the buffer for complex results
                //     extern Array_list<char> char_result; // acts as the buffer for char results
                // }
                // using pvt::result;
                // using pvt::char_result;
                // public functions

                // puts the array in ascending order
                #define asc_order(...) asc_order_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                const largest_float *asc_order_ (const largest_uint count, const largest_float arr[]);
                // puts the array in descending order
                #define desc_order(...) desc_order_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                const largest_float *desc_order_ (const largest_uint count, const largest_float arr[]);

                // sum of all arguments
                #define sum(...) sum_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type sum_ (const largest_uint count, const Return_type arr[]);
                // difference of all arguments
                #define diff(...) diff_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type diff_ (const largest_uint count, const Return_type arr[]);
                // product of all arguments
                #define prod(...) prod_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type prod_ (const largest_uint count, const Return_type arr[]);
                // quotient of all arguments
                #define quot(...) quot_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type quot_ (const largest_uint count, const Return_type arr[]);
                // remainder of all arguments
                #define remn(...) remn_(PP_NARG(__VA_ARGS__),TO_LL_NARG(__VA_ARGS__))
                largest_int remn_ (const largest_uint count, const largest_int arr[]);

                // definition of template functions

                template <class Return_type>
                Return_type sum_ (const largest_uint count, const Return_type arr[]) {
                    Return_type result = arr[0]; for (largest_uint i = 1; i < count; result += arr[i++]) {}; return result; }
                template <class Return_type>
                Return_type diff_ (const largest_uint count, const Return_type arr[]) {
                    Return_type result = arr[0]; for (largest_uint i = 1; i < count; result -= arr[i++]) {}; return result; }
                template <class Return_type>
                Return_type prod_ (const largest_uint count, const Return_type arr[]) {
                    Return_type result = arr[0]; for (largest_uint i = 1; i < count; result *= arr[i++]) {}; return result; }
                template <class Return_type>
                Return_type quot_ (const largest_uint count, const Return_type arr[]) {
                    Return_type result = arr[0]; for (largest_uint i = 1; i < count; result /= arr[i++]) {}; return result; }
                // largest_int remn_ (const largest_uint count, const largest_int arr[]) {
                //     largest_int result = arr[0]; for (largest_uint i = 1; i < count; result %= arr[i++]); return result; }

                // mod the value to a certain range
                // lower_limit <= val < range
                largest_float in_range (largest_int lower_limit, largest_int upper_limit, largest_float val);

                // extreme sides
                // index of the largest value in array
                #define highest_idx(...) highest_idx_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                largest_uint highest_idx_ (const largest_uint count, const Return_type arr[]);
                // index of the smallest value in array
                #define lowest_idx(...) lowest_idx_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                largest_uint lowest_idx_ (const largest_uint count, const Return_type arr[]);
                // the largest value in array
                #define highest(...) highest_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type highest_ (const largest_uint count, const Return_type arr[]);
                // the smallest value in array
                #define lowest(...) lowest_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                template <class Return_type>
                Return_type lowest_ (const largest_uint count, const Return_type arr[]);

                // definition of template functions

                template <class Return_type>
                largest_uint highest_idx_ (const largest_uint count, const Return_type arr[]) {
                    largest_uint h = 0;
                    for (largest_uint i = 1; i < count; i++) {
                        if (arr[i] > arr[h]) h = i;
                    }
                    return h;
                }

                template <class Return_type>
                largest_uint lowest_idx_ (const largest_uint count, const Return_type arr[]) {
                    largest_uint l = 0;
                    for (largest_uint i = 1; i < count; i++) {
                        if (arr[i] < arr[l]) l = i;
                    }
                    return l;
                }

                template <class Return_type>
                Return_type highest_ (const largest_uint count, const Return_type arr[]) {
                    Return_type toReturn = arr[0];
                    for (largest_uint i = 1; i < count; i++) {
                        if (arr[i] > toReturn) toReturn = arr[i];
                    }
                    return toReturn;
                }

                template <class Return_type>
                Return_type lowest_ (const largest_uint count, const Return_type arr[]) {
                    Return_type toReturn = arr[0];
                    for (largest_uint i = 1; i < count; i++) {
                        if (arr[i] < toReturn) toReturn = arr[i];
                    }
                    return toReturn;
                }

                // average
                // mean
                #define mean(...) mean_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                largest_float mean_ (const largest_uint count, const largest_float arr[]);
                // median
                #define median(...) median_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                largest_float median_ (const largest_uint count, const largest_float arr[]);
                // mode, which is impossible to be understood, not recommended
                #define mode(...) mode_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
                const largest_float *mode_ (const largest_uint count, const largest_float arr[]);

                // power a value with int indice
                largest_float power_int_idx (const largest_float toPow, const largest_int index = 2);
                // root a value with int base
                largest_float root_int_base (const largest_float toRoot, const largest_int base = 2);
                // power a value with an index that supports floating-point numbers
                largest_float power (const largest_float toPow, const largest_float index = 2.0);
                // root a value with base
                largest_float root (const largest_float toRoot, const largest_float base = 2.0);
                #ifdef _LIBCPP_STRING
                // root a value with a base to a std::string
                std::string root_to_str (const largest_float toRoot, const largest_int base = 2, const uint8_t max_return_length = 10);
                #endif // #ifdef _LIBCPP_STRING
                // factorial
                // long double is returned rather than long long because it has a larger storage
                largest_float factorial (int16_t val);
                // rnddn(input) pulls + / - num to 0
                largest_int rnddn (const largest_float input);
                // rndup(input) pulls + / - num away 0
                largest_int rndup (const largest_float input);
                // (input < 0.5) ? return input : return input + 1;
                largest_int rndoff (const largest_float input);
                // mode 0 = rnd off, mode 1 = rnd down, mode 2 = rnd up
                largest_int rnd (const largest_float input, const int16_t mode = 0);
                // increases the value not more than 1 to an integer
                largest_int ceil (const largest_float input);
                // decreases the value not more than 1 to an integer
                largest_int floor (const largest_float input);

                // check if 2 values are roughly equal
                bool rough_equal (const largest_float lhs, const largest_float rhs, const uint8_t cmp_len = 12);

                // trigonometry

                // trigonometry in radian mode

                // result == y / r == sin θ in radian mode
                largest_float sinR (const largest_float radian);
                // result == θ == arcsin (y / r) in radian mode
                largest_float asinR (const largest_float opposite_side_to_hypotenuse);
                // result == x / r == cos θ in radian mode
                largest_float cosR (const largest_float radian);
                // result == θ == arccos (x / r) in radian mode
                largest_float acosR (const largest_float adjacent_side_to_hypotenuse);
                // result == y / x == tan θ in radian mode
                largest_float tanR (const largest_float radian);
                // result == θ == arctan (y / x) in radian mode
                largest_float atanR (const largest_float opposite_side_to_adjacent_side);
                // result == r / y == csc θ in radian mode
                largest_float cscR (const largest_float radian);
                // result == θ == arccsc (r / y) in radian mode
                largest_float acscR (const largest_float hypotenuse_to_opposite_side);
                // result == r / x == sec θ in radian mode
                largest_float secR (const largest_float radian);
                // result == θ == arcsec (r / x) in radian mode
                largest_float asecR (const largest_float hypotenuse_to_adjacent_side);
                // result == x / y == cot θ in radian mode
                largest_float cotR (const largest_float radian);
                // result == θ == arccot (x / y) in radian mode
                largest_float acotR (const largest_float adjacent_side_to_opposite_side);

                // rad. == angle° * π ÷ 180
                largest_float angle2radian (const largest_float angle);
                // angle° == rad. ÷ π * 180
                largest_float radian2angle (const largest_float radian);

                // trigonometry in angle mode

                // result == y / r == sin θ in angle mode
                largest_float sinA (const largest_float angle);
                // result == θ == arcsin (y / r) in angle mode
                largest_float asinA (const largest_float opposite_side_to_hypotenuse);
                // result == x / r == cos θ in angle mode
                largest_float cosA (const largest_float angle);
                // result == θ == arccos (x / r) in angle mode
                largest_float acosA (const largest_float adjacent_side_to_hypotenuse);
                // result == y / x == tan θ in angle mode
                largest_float tanA (const largest_float angle);
                // result == θ == arctan (y / x) in angle mode
                largest_float atanA (const largest_float opposite_side_to_adjacent_side);
                // result == r / y == csc θ in angle mode
                largest_float cscA (const largest_float angle);
                // result == θ == arccsc (r / y) in angle mode
                largest_float acscA (const largest_float hypotenuse_to_opposite_side);
                // result == r / x == sec θ in angle mode
                largest_float secA (const largest_float angle);
                // result == θ == arcsec (r / x) in angle mode
                largest_float asecA (const largest_float hypotenuse_to_adjacent_side);
                // result == x / y == cot θ in angle mode
                largest_float cotA (const largest_float angle);
                // result == θ == arccot (x / y) in angle mode
                largest_float acotA (const largest_float adjacent_side_to_opposite_side);

                template <class Return_type>
                // return the absolute value
                // output == |input|
                Return_type absolute (const Return_type input);
                template <class Return_type>
                // return input value in a positive num
                // output == |input|
                Return_type toPositive (const Return_type input);
                template <class Return_type>
                // return input value in a negative num
                // output == - |input|
                Return_type toNegative (const Return_type input);

                // definition of template functions

                template <class Return_type>
                Return_type absolute (const Return_type input) { return input < 0 ? -input : input; }
                template <class Return_type>
                Return_type toPositive (const Return_type input) { return input < 0 ? -input : input; }
                template <class Return_type>
                Return_type toNegative (const Return_type input) { return input > 0 ? -input : input; }

                template <class Return_type>
                // limits the value between lower_limit and upper_limit
                // equivalent to constrain() in Arduino libraries
                Return_type limiting (const Return_type value, const Return_type lower_limit, const Return_type upper_limit);
                template <class Return_type>
                // On a 1-dimension number line,
                // there is a point P on a straight line AB.
                // This function gets the ratio of AP : PB
                // and fits the ratio into another straight line CD
                // to find the value of the new point.
                // equivalent to map() in Arduino libraries
                Return_type mapping (const Return_type value, const Return_type orig_low, const Return_type orig_high, const Return_type new_low, const Return_type new_high);

                // definition of template functions

                template <class Return_type>
                Return_type limiting (const Return_type value, const Return_type lower_limit, const Return_type upper_limit) {
                    // if (value < lower_limit) return lower_limit;
                    // else if (value > upper_limit) return upper_limit;
                    // else return value;
                    return ( value < lower_limit ? lower_limit : (value > upper_limit ? upper_limit : value) );
                }
                template <class Return_type>
                Return_type mapping (const Return_type value, const Return_type orig_low, const Return_type orig_high, const Return_type new_low, const Return_type new_high) {
                    // AP == value - orig_low
                    // PB == orig_high - value
                    // AP + PB == value - orig_low + orig_high - value
                    //         == orig_high - orig_low
                    // (AP * B + PB * A) ÷ (AP + PB)
                    return ( (value-orig_low) * new_high + (orig_high-value) * new_low ) / (orig_high-orig_low);
                }

                // triangular number
                largest_int tri_num (const largest_int index);
                // Fibonacci number
                largest_int fib_num (const largest_int index);
                // prime number
                bool pri_num (const largest_int input);
                // nCr == n! ÷ [ (n-r)!r! ]
                largest_uint nCr (const largest_uint n, const largest_uint r);
                // nPr == n! ÷ (n-r)!
                largest_uint nPr (const largest_uint n, const largest_uint r);

                // Highest common factor of 2 integers
                largest_uint hcf (const largest_int a, const largest_int b);
                // Least common multiple of 2 integers
                largest_uint lcm (const largest_int a, const largest_int b);

                // simplify the numerator and denominator in a fraction
                // return pointer of an [2] array in a faster process since both are integral types
                const largest_float *fract_simp_int (const largest_int up, const largest_int low);
                // return pointer of an [2] array
                const largest_float *fract_simp (const largest_float up, const largest_float low);

                // // CASIO fx-3650P compatible series

                // // edited from CASIO fx-3650P
                // // return long double [7] array {x, y, p, q, r, s, A}
                // // p * r == a, p * s + q * r == b, q * s == c
                // const largest_float *quad_equ_x_intercept (const largest_float input_A, const largest_float input_B, const largest_float input_C);
                // // return long double [2] array {x_coordinate_of_vertex, y_coordinate_of_vertex}
                // const largest_float *quad_equ_vertex (const largest_float input_A, const largest_float input_B, const largest_float input_C);
                // // input alpha and beta to get the constants in integer in general form of quad equation
                // const largest_float *ab2quad_equ (const largest_float alpha, const largest_float beta);
                // // y = mx + c
                // // returns A, B, C in Ax + By + C = 0
                // const largest_float *linear_equ (const largest_float m, const largest_float c);
                // // point-slope form
                // // y - y1 = m(x - x1)
                // // returns A, B, C in Ax + By + C = 0
                // const largest_float *linear_equ (const largest_float x, const largest_float y, const largest_float m);
                // // two-point form
                // // y - y1 = [ (y1 - y2) ÷ (x1 - x2) ] (x - x1)
                // // returns A, B, C in Ax + By + C = 0
                // const largest_float *linear_equ (const largest_float x1, const largest_float y1, const largest_float x2, const largest_float y2);

                // // get distance between 2 points
                // // [0] is the result, [1] is in surd form
                // const largest_float *pt_dist (const largest_float x1, const largest_float y1, const largest_float x2, const largest_float y2);
                // // get distance between 2 points
                // largest_float pt_dist (const largest_float x1, const largest_float y1, const largest_float z1, const largest_float x2, const largest_float y2, const largest_float z2);
                // //
                // #define points_dist(...) points_dist_ (PP_NARG(__VA_ARGS__), TO_LD_NARG(__VA_ARGS__))
                // largest_float points_dist_ (const int16_t count, const largest_float *arr);
                // // get slope between 2 points
                // // [0] is the result, [1] is the numerator, [2] is the denominator
                // const largest_float *pt_slope (const largest_float x1, const largest_float y1, const largest_float x2, const largest_float y2);
                // // [0] is the x-coordinate, [1] is the y-coordinate
                // const largest_float *get_pt_by_ratio (const largest_float Ax, const largest_float Ay, const largest_float Bx, const largest_float By, const largest_float AP, const largest_float PB);
                // // [0] is the x-coordinate, [1] is the y-coordinate
                // const largest_float *get_midp_cord (const largest_float Ax, const largest_float Ay, const largest_float Bx, const largest_float By);

                // #define b2d(val) binary_to_decimal(#val)
                // largest_uint binary_to_decimal (const char *str);

                // fundamentals of base switching functions
                // convert input char to value
                // returns -1 when input does not match 0-9, a-z, A-Z
                int16_t charToVal (const char input);
                // convert input value to capital letter
                // returns '\\0' when input is out of range 0-35
                // returns '-' for -1
                // returns '.' for -2
                // returns '\0' for -255
                char valToCapLetter (const int16_t input);
                // complicated functions converting bases of strings containing values
                // converts inputed string to a base-10 value (supports strings with floating-points)
                largest_float base_n_to_base_10 (const char *str, const uint16_t base_from, char* *remaining_unrecognised_str = NULL);
                // converts inputed floating-point value to a string in another base
                // also act as val to str converting function when base_to == 10
                // note: str_max_len includes the '\\0' char
                const char *base_10_to_base_n (const largest_float val, const uint16_t base_to, const largest_uint str_max_len = 24U, const bool round_off_last_digit = 1);
                // converts C-string of an argumented base to another C-string of another argumented base
                const char *change_base_of_str (const char *inputed_str, const uint16_t base_from, const uint16_t base_to, const largest_uint str_max_len = 24U);

                // finds the intercept of 2 straight lines
                // with the form y = mx + c
                // returned array: [0] == x-coordinate, [1] == y-coordinate
                // warning: The function will fail when y is not a co-domain of the straight line equation, 
                // where m and c are INFINITY or NAN or undefined.
                // note: When treating with vertical lines,
                // use the overload function that accepts a, b, c as constants for the linear equation.
                const largest_float *intercept_of_2_st_lines (const largest_float m1, const largest_float c1, const largest_float m2, const largest_float c2);
                // finds the intercept of 2 straight lines
                // with the general form ax + by + c = 0
                // returned array: [0] == x-coordinate, [1] == y-coordinate
                // warning: the function will fail when any arguments are INFINITY or NAN
                // note: the function is able to handle vertical lines
                const largest_float *intercept_of_2_st_lines (const largest_float a1, const largest_float b1, const largest_float c1, const largest_float a2, const largest_float b2, const largest_float c2);

                // read the result in the long double result array
                const largest_float &get_result (const largest_uint idx);
                // activate the library
                // actually is useless (library is originally designed for external business use)
                // using_mode only allows 0555 mode
                int activate (int using_mode, const char *password);
            }
        }
/*
class Maths {
    private:
        short integer_in_private;
        void assignToArray (const long double *x, const long int length);
        void assignToArray (const char *x, const long int length);
        void swap_result (const int idx_1, const int idx_2);
    public:
        long double ppi;
        long double result [1000];
        char char_result [1024];

        // puts the array in ascending order
        #define asc_order(...) asc_order_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        const long double *asc_order_ (long count, const long double arr[]);
        // puts the array in descending order
        #define desc_order(...) desc_order_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        const long double *desc_order_ (long count, const long double arr[]);

        // sum of all arguments
        #define sum(...) sum_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double sum_ (const long count, const long double arr[]);
        // difference of all arguments
        #define diff(...) diff_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double diff_ (const long count, const long double arr[]);
        // product of all arguments
        #define prod(...) prod_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double prod_ (const long count, const long double arr[]);
        // quotient of all arguments
        #define quot(...) quot_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double quot_ (const long count, const long double arr[]);

        // extreme sides
        // highest
        #define highest_idx(...) highest_idx_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        unsigned long highest_idx_ (const long count, const long double arr[]);
        // lowest
        #define lowest_idx(...) lowest_idx_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        unsigned long lowest_idx_ (const long count, const long double arr[]);
        // highest
        #define highest(...) highest_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double highest_ (const long count, const long double arr[]);
        // lowest
        #define lowest(...) lowest_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double lowest_ (const long count, const long double arr[]);

        // average
        // mean
        #define mean(...) mean_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double mean_ (const long count, const long double arr[]);
        // median
        #define median(...) median_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        long double median_ (const long count, const long double arr[]);
        // mode
        #define mode(...) mode_(PP_NARG(__VA_ARGS__),TO_LD_NARG(__VA_ARGS__))
        const long double *mode_ (const long count, const long double arr[]);

        long double power (long double toPow, int index = 2);
        //max_return_length is the looping amount
        std::string root (const long double toRoot, const int base = 2, const int max_return_length = 20);
        //rnddn(input) pulls + / - num to 0
        long long rnddn (const long double input);
        //rndup(input) pulls + / - num away 0
        long long rndup (const long double input);
        //(input < 0.5) ? return input : return input + 1;
        long long rndoff (const long double input);
        // mode 0 = rnd off, mode 1 = rnd down, mode 2 = rnd up
        long long rnd (const long double input, const short mode = 0);
        // sin angle, default pi = 3.141592653589793238462643383279502884197
        long double sinA (const long double angle);
        // asin angle, default pi = 3.141592653589793238462643383279502884197
        long double asinA (const long double opposite_side_to_hypotenuse);
        // cos angle, default pi = 3.141592653589793238462643383279502884197
        long double cosA (const long double angle);
        // acos angle, default pi = 3.141592653589793238462643383279502884197
        long double acosA (const long double adjacent_side_to_hypotenuse);
        // tan angle, default pi = 3.141592653589793238462643383279502884197
        long double tanA (const long double angle);
        // atan angle, default pi = 3.141592653589793238462643383279502884197
        long double atanA (const long double opposite_side_to_adjacent_side);

        // return input value in a positive num
        long double toPositive (const long double input);
        // return input value in a negative num
        long double toNegative (const long double input);

        // triangular number
        long long tri_num (const long long index);
        // Fibonacci number
        long long fib_num (const long long index);
        // prime number
        bool pri_num (long long input);

        // return pointer of an [2] array
        const long double *fractSimp (long double up, long double low);
        // edited from CASIO fx-3650p
        // return pointer of an [4] array {p, q, r, s}
        // p * r == a, p * s + q * r == b, q * s == c
        const long double *quadratic_equation (const float input_A, const float input_B, const float input_C);

        // convert input char to value
        short charToVal (char input);
        // convert input value to capital letter
        char valToCapLetter (short input);
        // convert input value in any base to base 10
        long long to10base (std::string input, short base);
        // convert 10-based input value to any base
        const char *DenaryToAnyBase (long long input, short base);
        // change the base of value
        const char *base_converter(std::string input, short input_base, short output_base);

        const long double &get_result(const long idx);
};
/*/
    }
}
//typedef YH::Lib::Maths YHmathsLib;

// #include "YHmathsLib_Floating_pt.h" project renamed as YHmathsLib_Fraction
// #include "YHmathsLib_expand_type.h" project abandoned 🙃
#include "YHmathsLib_Fraction.h"

#endif