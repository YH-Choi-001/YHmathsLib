#ifndef YHMATHSLIB_CPP
#define YHMATHSLIB_CPP __DATE__ ", " __TIME__

#include "YHmathsLib.h"

#define NUM_RESULT_SIZE 16
#define CHAR_RESULT_SIZE 64

// #define SIMPLE_ROUNDING
#define CUSTOM_TRIGONOMETRY    // define custom trigo functions
#undef USE_CUSTOM_TRIGONOMETRY // but do not replace them with math.h original function

namespace YH {
    namespace Lib {
        namespace Func {
            namespace maths {
                const largest_float pi = 3.141592653589793238462643383279502884197L;
                const char YHmathsLib_vers [] = YHMATHSLIB_CPP;
                namespace pvt { // private stuff restricted to this implementation file only
                    namespace { // declared static, anonymous-namespace prevents external linkage
                        // for array result returning use only
                        template <class Store_unit>
                        class Array_list {
                            private:
                                Store_unit *ptr;
                                largest_uint len;
                                Array_list &myself () const { return *this; }
                            public:
                                // default constructor
                                Array_list ();
                                // constructor that auto calls this->resize(request_len)
                                Array_list (const largest_uint request_len);
                                // get the pointer of the dynamic array of Store_unit
                                const Store_unit *raw_ptr () const;
                                // get the allocated length for the dynamic array
                                largest_uint alloced_len () const;
                                // resize the Store_unit dynamic array
                                int16_t resize (const largest_uint request_len);
                                // resize before calling this method
                                int16_t movmem (const Store_unit *arr, const largest_uint arrlen = 0UL);
                                // get the object of the inputed index
                                    Store_unit &idx (const largest_uint index);
                                const Store_unit &idx (const largest_uint index) const;
                                // clear up and free occupied memory
                                ~Array_list ();
                        };
                        void assignToArray (const largest_float *x, const largest_uint length);
                        void assignToArray (const char *x, const largest_uint length);
                        void swap_result (const largest_uint idx_1, const largest_uint idx_2);
                        // endof type declaration
                        Array_list<largest_float> result (NUM_RESULT_SIZE);
                        Array_list<char> char_result (CHAR_RESULT_SIZE);
                        //const int result_len = NUM_RESULT_SIZE;
                        //const int char_result_len = NUM_RESULT_SIZE;
                        //long double result [NUM_RESULT_SIZE];
                        //char char_result [CHAR_RESULT_SIZE];
                        // methods of Array_list
                        template <class Store_unit>
                        Array_list<Store_unit>::Array_list () : ptr(NULL), len(0UL) {}
                        template <class Store_unit>
                        Array_list<Store_unit>::Array_list (const largest_uint request_len) : ptr(NULL), len(0UL) { Array_list::resize(request_len); }
                        template <class Store_unit>
                        const Store_unit *Array_list<Store_unit>::raw_ptr () const { return ptr; }
                        template <class Store_unit>
                        largest_uint Array_list<Store_unit>::alloced_len () const { return len; }
                        template <class Store_unit>
                        int16_t Array_list<Store_unit>::resize (const largest_uint request_len) {
                            if (ptr != NULL) {
                                // cpy work is done
                                delete[] ptr;
                                ptr = NULL;
                            }
                            if (ptr == NULL/* && request_len > 0*/) {
                                ptr = new Store_unit [request_len];
                                if (ptr == NULL) {
                                    len = 0U;
                                    return -1;
                                } else {
                                    len = request_len;
                                    return 0;
                                }
                            }
                            return -1;
                        }
                        // resize before calling this method
                        template <class Store_unit>
                        int16_t Array_list<Store_unit>::movmem (const Store_unit *arr, const largest_uint arrlen /* = 0UL */ ) {
                            if (arr == NULL) {
                                return -1;
                            } else {
                                for (largest_uint i = 0U; i < len; i++) {
                                    ptr[i] = (i < arrlen) ? arr[i] : 0;
                                }
                            }
                            return 0;
                        }
                        template <class Store_unit>
                            Store_unit &Array_list<Store_unit>::idx (const largest_uint index)       {
                            return ptr[index < len ? index : len - 1];
                        }
                        template <class Store_unit>
                        const Store_unit &Array_list<Store_unit>::idx (const largest_uint index) const {
                            return ptr[index < len ? index : len - 1];
                        }
                        template <class Store_unit>
                        Array_list<Store_unit>::~Array_list () {
                            if (ptr != NULL) {
                                delete[] ptr;
                                ptr = NULL;
                                len = 0U;
                            }
                        }
                        void assignToArray (const largest_float *x, const largest_uint length) {
                            //const size_t result_len = sizeof(YH::Lib::Func::maths::pvt::result) / sizeof(YH::Lib::Func::maths::pvt::result[0]);
                            //for (size_t i = 0;
                            //    i < result_len;
                            //    i++)
                            //{
                            //    YH::Lib::Func::maths::pvt::result[i] = (i < length) ? x[i] : 0;
                            //}
                            result.resize(length);
                            result.movmem(x, length);
                        }

                        void assignToArray (const char *x, const largest_uint length) {
                            //const size_t char_result_len = sizeof(YH::Lib::Func::maths::pvt::char_result) / sizeof(YH::Lib::Func::maths::pvt::char_result[0]);
                            //for (size_t i = 0;
                            //    i < char_result_len;
                            //    i++)
                            //{
                            //    YH::Lib::Func::maths::pvt::char_result [i] = (i < length) ? x[i] : 0;
                            //}
                            char_result.resize(length);
                            char_result.movmem(x, length);
                        }

                        void swap_result (const largest_uint idx_1, const largest_uint idx_2) {
                            /*
                            const YH::Lib::Func::maths::largest_float temp = YH::Lib::Func::maths::pvt::result[idx_1];
                            YH::Lib::Func::maths::pvt::result[idx_1] = YH::Lib::Func::maths::pvt::result[idx_2];
                            YH::Lib::Func::maths::pvt::result[idx_2] = temp;
                            */
                            const largest_float temp = result.idx(idx_1);
                            result.idx(idx_1) = result.idx(idx_2);
                            result.idx(idx_2) = temp;
                        }

                    }
                }
            }
        }
    }
}

#define MATHS_ACTV (YH::Lib::Func::maths::pvt::actv_state==1)
#define MATHS_UNACTV (YH::Lib::Func::maths::pvt::actv_state!=1)


#if defined(SIMPLE_ROUNDING)

    #define VALUABLE_DIFF 0.000000000001L
    // 3.8 becomes 3, -3.8 becomes -3
    #define RND_DOWN(x) (static_cast<YH::Lib::Func::maths::largest_int>(x))
    // 3.2 becomes 4, -3.2 becomes -4
    // if x > 0
        // if x - round_down(x) > 0.00001
            // return round_down(x) + 1
        // else
            // return round_down(x)
    // else // x < 0
        // if round_down(x) - x > 0.00001
            // return round_down(x) - 1
        // else
            // return round_down(x)
    // (x > 0) ? ( (x - RND_DOWN(x) > VALUABLE_DIFF) ? (RND_DOWN(x) + 1) : RND_DOWN(x) ) : ( (RND_DOWN(x) - x > VALUABLE_DIFF) ? (RND_DOWN(x) - 1) : RND_DOWN(x) )
    // (   (x > 0) ? ( RND_DOWN(x) + (x - RND_DOWN(x) > VALUABLE_DIFF) ) : ( RND_DOWN(x) - (RND_DOWN(x) - x > VALUABLE_DIFF) )   )
    // (   RND_DOWN(x) + ( (x > 0) ? (x - RND_DOWN(x) > VALUABLE_DIFF) : -(RND_DOWN(x) - x > VALUABLE_DIFF) )   )
    #define RND_UP(x) (   RND_DOWN(x) + ( (x > 0) ? (x - RND_DOWN(x) > VALUABLE_DIFF) : -(RND_DOWN(x) - x > VALUABLE_DIFF) )   )
    #define RND_OFF(x)   (   (x > 0.0) ? ( RND_DOWN(x) + (x - RND_DOWN(x) >= 0.5) ) : ( RND_DOWN(x) - (RND_DOWN(x) - x > 0.5) )   )
    #define RND_CEIL(x)  (   RND_DOWN(x) + (x > 0.0 && x > RND_DOWN(x))   )
    #define RND_FLOOR(x) (   RND_DOWN(x) - (x < 0.0 && x < RND_DOWN(x))   )

#else // A_LITTLE_COMPLICATED_ROUNDING

    #undef RND_DOWN
    template <class T>
    YH::Lib::Func::maths::largest_float RND_DOWN (T x);
    #undef RND_UP
    template <class T>
    YH::Lib::Func::maths::largest_float RND_UP (T x);
    #undef RND_OFF
    template <class T>
    YH::Lib::Func::maths::largest_float RND_OFF (T x);
    #undef RND_CEIL
    template <class T>
    YH::Lib::Func::maths::largest_float RND_CEIL (T x);
    #undef RND_FLOOR
    template <class T>
    YH::Lib::Func::maths::largest_float RND_FLOOR (T x);

    template <class T>
    YH::Lib::Func::maths::largest_float RND_DOWN (T x) {
        YH::Lib::Func::maths::largest_float i = RND_UP(x);
        // // if (x > 0.0) {
        // //     for (; i > x; i--);
        // // } else {
        // //     for (; i < x; i++);
        // // }
        // // return i;
        // if (i > x && x > 0.0) i--;
        // else if (i < x && x < 0.0) i++;
        // return i;
        return i - (x > 0.0 && i > x) + (x < 0.0 && i < x);
    }

    template <class T>
    YH::Lib::Func::maths::largest_float RND_UP (T x) {
        YH::Lib::Func::maths::largest_float i =
            static_cast<YH::Lib::Func::maths::largest_int>(x * static_cast<YH::Lib::Func::maths::largest_float>(0.999999940395355224609375));
        if (x > 0.0) {
            for (; i < x; i++);
        } else {
            for (; i > x; i--);
        }
        return i;
    }

    template <class T>
    YH::Lib::Func::maths::largest_float RND_OFF (T x) {
        const YH::Lib::Func::maths::largest_float rnddn = RND_DOWN(x);
        // return (x > 0.0L) ? (x - rnddn < 0.5L ? rnddn : rnddn + 1.0L) : (rnddn - x <= 0.5L ? rnddn : rnddn - 1.0L);
        // return (x > 0.0L) ? (x - rnddn < 0.5L ? rnddn : rnddn + 1.0L) : (rnddn - x > 0.5L ? rnddn - 1.0L : rnddn);
        return (x > 0.0) ? ( rnddn + (x - rnddn >= 0.5) ) : ( rnddn - (rnddn - x > 0.5) );
    }

    template <class T>
    YH::Lib::Func::maths::largest_float RND_CEIL (T x) {
        const YH::Lib::Func::maths::largest_float rnddn = RND_DOWN(x);
        // if x > 0
            // if x > RND_DOWN(x)
                // return RND_DOWN(x) + 1
            // else if (x == RND_DOWN(x))
                // return RND_DOWN(x)
        // else // x <= 0
            // return RND_DOWN(x)

        // when x > 0
            // x >= rnddn >= 0
        // (x > 0.0L) ? (x > rnddn ? rnddn + 1.0L : rnddn) : rnddn;
        // return (x > 0.0L) ? (rnddn + (x > rnddn)) : rnddn;
        return rnddn + (x > 0.0 && x > rnddn);
    }

    template <class T>
    YH::Lib::Func::maths::largest_float RND_FLOOR (T x) {
        // simplest form: return RND_OFF(x - 0.5L);
        const YH::Lib::Func::maths::largest_float rnddn = RND_DOWN(x);
        // (x > 0.5L) ? (x - rnddn < 1.0L ? rnddn : rnddn + 1.0L) : (rnddn - x > 0.5L ? rnddn - 1.0L : rnddn)
        // (x > 0.5L) ? (   (always true)   rnddn               ) : (rnddn > x ? rnddn - 1.0L : rnddn)
        // (x > 0.5L) ? (   (always true)   rnddn               ) : (x < rnddn ? rnddn - 1.0L : rnddn)
        // return (x > 0.5L) ? rnddn : (x < rnddn ? rnddn - 1.0L : rnddn);
        // return (x >= 0.0L) ? rnddn : (x < rnddn ? rnddn - 1.0L : rnddn);
        // when x < 0
            // x <= rnddn <= 0
        // (x < 0.0L) ? (x < rnddn ? rnddn - 1.0L : rnddn) : rnddn;
        // return (x < 0.0L) ? (rnddn - (x < rnddn)) : rnddn;
        return rnddn - (x < 0.0 && x < rnddn);
    }

#endif


#if defined(CUSTOM_TRIGONOMETRY)
YH::Lib::Func::maths::largest_float SINE         (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float COSINE       (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float TANGENT      (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 15U);
YH::Lib::Func::maths::largest_float SECANT       (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float COSECANT     (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float COTANGENT    (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);

YH::Lib::Func::maths::largest_float ARCSINE      (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float ARCCOSINE    (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float ARCTANGENT   (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 100000U);
YH::Lib::Func::maths::largest_float ARCSECANT    (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float ARCCOSECANT  (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 10U);
YH::Lib::Func::maths::largest_float ARCCOTANGENT (const YH::Lib::Func::maths::largest_float x, const uint32_t rpt_idx = 100000U);

YH::Lib::Func::maths::largest_float SINE (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    // if (x_in_radian > YH::Lib::Func::maths::pi/4) return COSINE(YH::Lib::Func::maths::pi/2 - x_in_radian, rpt_idx);
    YH::Lib::Func::maths::largest_float result = 0.0;
    YH::Lib::Func::maths::largest_float powered = x_in_radian;
    YH::Lib::Func::maths::largest_float factorized = 1.0;
    YH::Lib::Func::maths::largest_float squared_x_in_radian = x_in_radian * x_in_radian;
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2U + 1U;
    bool i_is_even = false;
    // factorized = (factorized = factorized * (++i)) * (++i)
    for ( YH::Lib::Func::maths::largest_uint i = 1U; i < max; powered *= squared_x_in_radian, factorized *= (i + 1) * (i + 2), i += 2U ) {
        result +=
        ((i_is_even = !i_is_even) ? 1.0 : -1.0) * powered /
        factorized;
    }
    return result;
}

YH::Lib::Func::maths::largest_float COSINE (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    // if (x_in_radian > YH::Lib::Func::maths::pi/4) return SINE(YH::Lib::Func::maths::pi/2 - x_in_radian, rpt_idx);
    // cos(x) == sin(x + pi / 2.0L)
    YH::Lib::Func::maths::largest_float result = 0.0;
    YH::Lib::Func::maths::largest_float powered = 1.0;
    YH::Lib::Func::maths::largest_float factorized = 1.0;
    YH::Lib::Func::maths::largest_float squared_x_in_radian = x_in_radian * x_in_radian;
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2U;
    bool i_is_even = true;
    for ( YH::Lib::Func::maths::largest_uint i = 0U; i < max; powered *= squared_x_in_radian, factorized *= (i + 1) * (i + 2), i += 2U ) {
        result +=
        ((i_is_even = !i_is_even) ? -1.0 : 1.0) * powered /
        factorized;
    }
    return result;
}

YH::Lib::Func::maths::largest_float TANGENT (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    // return SINE(x, rpt_idx) / COSINE(x, rpt_idx);
    YH::Lib::Func::maths::largest_float sin_x = 0.0;
    YH::Lib::Func::maths::largest_float cos_x = 0.0;
    YH::Lib::Func::maths::largest_float powered = 1.0;
    YH::Lib::Func::maths::largest_float factorized = 1.0;
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2U;
    for ( YH::Lib::Func::maths::largest_uint i = 0U; i < max; powered *= x_in_radian, factorized *= (++i) ) {
        if (i % 2U) sin_x +=
        (i % 4U == 1U ? 1.0 : -1.0) * powered /
        factorized;
        else cos_x +=
        (i % 4U ? -1.0 : 1.0) * powered /
        factorized;
    }
    return sin_x / cos_x;
}

YH::Lib::Func::maths::largest_float SECANT (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    return 1.0 / COSINE(x_in_radian, rpt_idx);
}

YH::Lib::Func::maths::largest_float COSECANT (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    return 1.0 / SINE(x_in_radian, rpt_idx);
}

YH::Lib::Func::maths::largest_float COTANGENT (const YH::Lib::Func::maths::largest_float x_in_radian, const uint32_t rpt_idx) {
    // return SINE(x, rpt_idx) / COSINE(x, rpt_idx);
    YH::Lib::Func::maths::largest_float sin_x = 0.0;
    YH::Lib::Func::maths::largest_float cos_x = 0.0;
    YH::Lib::Func::maths::largest_float powered = 1.0;
    YH::Lib::Func::maths::largest_float factorized = 1.0;
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2U;
    for ( YH::Lib::Func::maths::largest_uint i = 0U; i < max; powered *= x_in_radian, factorized *= (++i) ) {
        if (i % 2U) sin_x +=
        (i % 4U == 1U ? 1.0 : -1.0) * powered /
        factorized;
        else cos_x +=
        (i % 4U ? -1.0 : 1.0) * powered /
        factorized;
    }
    return cos_x / sin_x;
}

YH::Lib::Func::maths::largest_float ARCSINE (const YH::Lib::Func::maths::largest_float sined_val, const uint32_t rpt_idx) {
    if (sined_val > 1 || sined_val < -1) return NAN; // range of domain: -1 <= sined_val <= 1, so as to ensure the domain is in range
    if (sined_val < 0) return -ARCSINE(-sined_val, rpt_idx); // -ive asin (+ive val) ensures that 0 <= sined_val for calculation with less error
    if (!sined_val) return 0;
    YH::Lib::Func::maths::largest_float result = 0.0;
    YH::Lib::Func::maths::largest_float num = 1.0;
    YH::Lib::Func::maths::largest_float denom = 1.0;
    YH::Lib::Func::maths::largest_float powered = sined_val;
    const YH::Lib::Func::maths::largest_float squared_sined_val = sined_val * sined_val;
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2;
    for (YH::Lib::Func::maths::largest_uint i = 1U; i < max; powered *= squared_sined_val, num *= i, denom *= i + 1, i+=2) {
        result +=
        num / denom * // num == 1 * 1 * 3 * 5 * 7 * 9 * 11 * 13 * 15 * 17 * ... ; denom == 1 * 2 * 4 * 6 * 8 * 10 * 12 * 14 * 16 * 18 * ... ;
        powered / i; // i == 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, ...
    }
    return result;
}

// Let cos(θ) be z.
// ∵               z = cos(θ)
// ∴         acos(z) = θ
// ∵  sin(π / 2 + θ) = cos(θ)
//    sin(π / 2 + θ) = z
// ∴         asin(z) = π / 2 + θ
//
//             π / 2 = π / 2
//   (π / 2 + θ) - θ = π / 2
// asin(z) - acos(z) = π / 2
//          -acos(z) = π / 2 - asin(z)
//           acos(z) = -(π / 2) + asin(z)
//           acos(z) = asin(z) - (π / 2)
// ∵     -π / 2 <= asin(z) <= π / 2 (range of co-domain of asin)
// ∴         -π <= asin(z) - (π / 2) <= 0
// ∴          π >= (π / 2) - asin(z) >= 0
// ∴          0 <= (π / 2) - asin(z) <= π
// However, the range of co-domain of arccos: 0 <= result <= π
YH::Lib::Func::maths::largest_float ARCCOSINE (const YH::Lib::Func::maths::largest_float cosined_val, const uint32_t rpt_idx) {
    if (cosined_val > 1 || cosined_val < -1) return NAN;
    return YH::Lib::Func::maths::pi / 2 - ARCSINE(cosined_val, rpt_idx);
}

// Let tan(θ) be z.
// ∵               z = tan(θ)
// ∵               z = sin(θ) / cos(θ)
// ∵               z = (tan(θ) / √(tan²θ + 1)) / (1 / √(tan²θ + 1))
// ∵               z = (tan(θ) / √(tan²θ + 1)) * (√(tan²θ + 1))
// ∴         atan(z) = θ
// ∵    √(tan²θ + 1) = hypoteneuse
YH::Lib::Func::maths::largest_float ARCTANGENT (const YH::Lib::Func::maths::largest_float taned_val, const uint32_t rpt_idx) {
    // if (taned_val == 1) return YH::Lib::Func::maths::pi/4;
    if (!taned_val) return 0;
    if (taned_val > 1) return YH::Lib::Func::maths::pi/2 - ARCTANGENT(1/taned_val, rpt_idx); // angle > π/4
    if (taned_val < 0) return -ARCTANGENT(-taned_val, rpt_idx); // -ive atan (+ive val) for calculation with less error
    YH::Lib::Func::maths::largest_float result = 0.0;
    YH::Lib::Func::maths::largest_float powered = taned_val;
    const YH::Lib::Func::maths::largest_float taned_val_sq = taned_val * taned_val;
    // const YH::Lib::Func::maths::largest_uint max = 4294967295U > (rpt_idx * 2) ? 4294967295U : (rpt_idx * 2);
    const YH::Lib::Func::maths::largest_uint max = rpt_idx * 2;
    bool i_is_even = true;
    for (YH::Lib::Func::maths::largest_uint i = 1U; i < max; powered *= taned_val_sq, i+=2) {
        result +=
        ((i_is_even = !i_is_even) ? -1 : 1) * powered / i;
    }
    // powered = YH::Lib::Func::maths::power(taned_val, 0x1000000ULL);
    // for (YH::Lib::Func::maths::largest_uint i = 0x1000000ULL; i < max + 0x1000000ULL; i+=2) {
    //     result +=
    //     ((i_is_even = !i_is_even) ? -1 : 1) * powered / i;
    //     powered *= taned_val * taned_val;
    // }
    return result;
    // return result =
    // taned_val - YH::Lib::Func::maths::power(taned_val, 3) / 3 + YH::Lib::Func::maths::power(taned_val, 5) / 5 - YH::Lib::Func::maths::power(taned_val, 7) / 7;
}

YH::Lib::Func::maths::largest_float ARCSECANT (const YH::Lib::Func::maths::largest_float z, const uint32_t rpt_idx) {
    return ARCCOSINE(1/z, rpt_idx);
}

YH::Lib::Func::maths::largest_float ARCCOSECANT (const YH::Lib::Func::maths::largest_float z, const uint32_t rpt_idx) {
    return ARCSINE(1/z, rpt_idx);
}

YH::Lib::Func::maths::largest_float ARCCOTANGENT (const YH::Lib::Func::maths::largest_float z, const uint32_t rpt_idx) {
    return YH::Lib::Func::maths::pi/2 - ARCTANGENT(z, rpt_idx);
}

#if defined(USE_CUSTOM_TRIGONOMETRY)
    // func
    #define sin(...) SINE(__VA_ARGS__)
    #define cos(...) COSINE(__VA_ARGS__)
    #define tan(...) TANGENT(__VA_ARGS__)
    #define sec(...) SECANT(__VA_ARGS__)
    #define csc(...) COSECANT(__VA_ARGS__)
    #define cot(...) COTANGENT(__VA_ARGS__)
    // arc func
    #define asin(...) ARCSINE(__VA_ARGS__)
    #define acos(...) ARCCOSINE(__VA_ARGS__)
    #define atan(...) ARCTANGENT(__VA_ARGS__)
    #define asec(...) ARCSECANT(__VA_ARGS__)
    #define acsc(...) ARCCOSECANT(__VA_ARGS__)
    #define acot(...) ARCCOTANGENT(__VA_ARGS__)
#endif // #if defined(USE_CUSTOM_TRIGONOMETRY)

#endif //#if defined(CUSTOM_TRIGONOMETRY)

// implementation only if strlen, strncmp, strncpy is not defined
#if !defined(_STRING_H_)
// strlen
    size_t YHc_strLib_c_strlen (const char *str) {
        size_t i = 0;
        for (;str[i] != '\0'; i++);
        return i;
    }
// strncmp
    int YHc_strLib_c_strncmp (const char *lhs, const char *rhs, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if (lhs[i] < rhs[i]) return -1;
            else if (lhs[i] > rhs[i]) return 1;
            else if (/*lhs[i] == rhs[i] && */lhs[i] == '\0') return 0;
        }
        return 0;
    }
// strncpy
    char *YHc_strLib_c_strncpy (char *dst, const char *src, const size_t len) {
        for (size_t i = 0; i < len; i++) {
            if ((dst[i] = src[i]) == '\0') return dst;
        }
        return dst;
    }

#define strlen(...) YHc_strLib_c_strlen(__VA_ARGS__)
#define strncmp(...) YHc_strLib_c_strncmp(__VA_ARGS__)
#define strncpy(...) YHc_strLib_c_strncpy(__VA_ARGS__)

#endif // #if !defined(_STRING_H_)


#define TO_POSITIVE(x) ( x < 0 ? -x : x )
#define TO_NEGATIVE(x) ( x > 0 ? -x : x )

#define TRI_NUM(x) x < 0 ? -( (-x) * ( (-x) + 1) / 2) : (x * (x + 1) / 2)


const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::asc_order_ (const largest_uint count, const largest_float arr[]) {
    largest_uint arr_len = count;
    pvt::assignToArray(arr, count);
    for (largest_uint i = 0; i < arr_len /* grounded automatically */; i++, arr_len--) {
        // pcs lowest
        largest_uint l_i = i;
        for (largest_uint j = i + 1; j < arr_len; j++) {
            //if (YH::Lib::Func::maths::pvt::result[j] < YH::Lib::Func::maths::pvt::result[l_i]) l_i = j;
            if (pvt::result.idx(j) < pvt::result.idx(l_i)) l_i = j;
        }
        if (l_i != i) pvt::swap_result(l_i, i);
        // pcs highest
        largest_uint h_i = i;
        for (largest_uint j = i + 1; j < arr_len; j++) {
            //if (YH::Lib::Func::maths::pvt::result[j] > YH::Lib::Func::maths::pvt::result[h_i]) h_i = j;
            if (pvt::result.idx(j) > pvt::result.idx(h_i)) h_i = j;
        }
        if (h_i != arr_len - 1) pvt::swap_result(h_i, arr_len - 1);
    }
    return pvt::result.raw_ptr();
    // return YH::Lib::Func::maths::pvt::result.raw_ptr();
}

const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::desc_order_ (const largest_uint count, const largest_float arr[]) {
    largest_uint arr_len = count;
    pvt::assignToArray(arr, count);
    for (largest_uint i = 0; i < arr_len /* grounded automatically */; i++, arr_len--) {
        // pcs lowest
        largest_uint l_i = i;
        for (largest_uint j = i + 1; j < arr_len; j++) {
            //if (YH::Lib::Func::maths::pvt::result[j] < YH::Lib::Func::maths::pvt::result[l_i]) l_i = j;
            if (pvt::result.idx(j) < pvt::result.idx(l_i)) l_i = j;
        }
        if (l_i != arr_len - 1) pvt::swap_result(l_i, arr_len - 1);
        // pcs highest
        largest_uint h_i = i;
        for (largest_uint j = i + 1; j < arr_len; j++) {
            //if (YH::Lib::Func::maths::pvt::result[j] > YH::Lib::Func::maths::pvt::result[h_i]) h_i = j;
            if (pvt::result.idx(j) > pvt::result.idx(h_i)) h_i = j;
        }
        if (h_i != i) pvt::swap_result(h_i, i);
    }
    return pvt::result.raw_ptr();
    // return YH::Lib::Func::maths::pvt::result.raw_ptr();
}

// the 4 functions below are defined in header file, because template functions cannot be separately compiled

// template <class Return_type>
// Return_type YH::Lib::Func::maths::sum_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; toReturn += arr[i++]);
//     return toReturn;
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::diff_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; toReturn -= arr[i++]);
//     return toReturn;
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::prod_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; toReturn *= arr[i++]);
//     return toReturn;
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::quot_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; toReturn /= arr[i++]);
//     return toReturn;
// }

YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::remn_ (const largest_uint count, const largest_int arr[]) {
    largest_int toReturn = arr[0];
    for (largest_uint i = 1; i < count; toReturn %= arr[i++]);
    return toReturn;
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::in_range (largest_int lower_limit, largest_int upper_limit, largest_float val) {
    if (upper_limit < lower_limit) {
        largest_int temp = upper_limit;
        upper_limit = lower_limit;
        lower_limit = temp;
    } else if (upper_limit == lower_limit) {
        return upper_limit;
    } else {
        const largest_int limit_diff = upper_limit - lower_limit;
        while (val >= upper_limit) {
            val -= limit_diff;
        }
        while (val < lower_limit) {
            val += limit_diff;
        }
    }
    return val;
}

// the 4 functions below are defined in header file, because template functions cannot be separately compiled

// template <class Return_type>
// YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::highest_idx_ (const largest_uint count, const Return_type arr[]) {
//     largest_uint h = 0;
//     for (largest_uint i = 1; i < count; i++) {
//         if (arr[i] > arr[h]) h = i;
//     }
//     return h;
// }

// template <class Return_type>
// YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::lowest_idx_ (const largest_uint count, const Return_type arr[]) {
//     largest_uint l = 0;
//     for (largest_uint i = 1; i < count; i++) {
//         if (arr[i] < arr[l]) l = i;
//     }
//     return l;
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::highest_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; i++) {
//         if (arr[i] > toReturn) toReturn = arr[i];
//     }
//     return toReturn;
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::lowest_ (const largest_uint count, const Return_type arr[]) {
//     Return_type toReturn = arr[0];
//     for (largest_uint i = 1; i < count; i++) {
//         if (arr[i] < toReturn) toReturn = arr[i];
//     }
//     return toReturn;
// }

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::mean_ (const largest_uint count, const largest_float arr[]) {
    return sum_(count, arr) / count;
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::median_ (const largest_uint count, const largest_float arr[]) {
    asc_order_(count, arr);
    if (count % 2) return get_result(count / 2);
    else return (get_result(count / 2) + get_result(count / 2 - 1)) / 2;
}

const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::mode_ (const largest_uint count, const largest_float arr[]) {
    largest_float reg_num [count]; // registers the numbers
    largest_float freq [count];    // stores the frequences
    largest_uint counter = 0;
    for (largest_uint i = 0; i < count; i++) {
        bool val_repeated = false;
        for (largest_uint j = 0; j < i; j++) {
            if (reg_num[j] == arr[i]) {
                val_repeated = true;
                freq[j]++;
                break;
            }
        }
        if (!val_repeated) {
            reg_num[counter] = arr[i];
            freq[counter] = 1;
            ++counter;
        }
    }
    largest_int max_freq = static_cast<largest_int>(highest_(counter, freq));
    largest_int result_counter = 0;
    pvt::assignToArray((largest_float *)0, count);
    if (max_freq > 1) {
        for (largest_uint k = 0; k < counter; k++) {
            if (freq[k] == max_freq) {
                //YH::Lib::Func::maths::pvt::result[result_counter++] = reg_num[k];
                pvt::result.idx(result_counter++) = reg_num[k];
            }
        }
    } else {
        // max_freq == 1 or == 0
        // but nothing to do with it
    }
    //return YH::Lib::Func::maths::pvt::result;
    return pvt::result.raw_ptr();
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::power_int_idx (const largest_float toPow, const largest_int index) {
    largest_float output1 = 1.0;
    if (index > 0) {
        for (largest_int i = 0; i < index; i++) {
            output1 *= toPow;
        }
    } else {
        for (largest_int i = 0; i > index; i--) {
            output1 /= toPow;
        }
    }
    return output1;
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::root_int_base (const largest_float toRoot, const largest_int base) {
    if (toRoot < 0) return NAN; // 0x 7fc0 0000 == [0111 1111] [1100 0000] [0000 0000] [0000 0000]
    else if (toRoot == 0) return 0; // √0
    largest_uint rootInInt = 0;
    for (largest_uint j = 0; j < toRoot; rootInInt = j++) {
        if (power_int_idx(j, base) > toRoot) {
            // j--;
            break;
        }
    }
    if (power_int_idx(rootInInt, base) == toRoot) return static_cast<largest_float>(rootInInt);
    largest_float toReturn = static_cast<largest_float>(rootInInt);
    int16_t base10 = 0;
    for (uint16_t i = 0; i < 30 /* long_double_precision_length */ ; i++) {
        const largest_float currBase = power_int_idx(10, --base10);
        for (uint16_t k = 1; k <= 10; k++) {
            if (power_int_idx(toReturn + k * currBase, base) > toRoot || k == 10) {
                toReturn += (k - 1) * currBase;
                break;
            }
        }
        if (power_int_idx(toReturn, base) == toRoot) return toReturn;
    }
    return toReturn;
}

// 3.5 power 2.23
// == (3.5 power 2) * (3.5 power 0.2) * (3.5 power 0.03)
// == (3.5 power 2) * (3.5 power 0.23)
// == (3.5 power 2) * (3.5 root (1÷0.23))
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::power (const largest_float toPow, const largest_float index) {
    fract_simp(index, 1);
    return power_int_idx(   root_int_base( toPow, static_cast<largest_int>(get_result(1)) ), static_cast<largest_int>(get_result(0))   );
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::root (const largest_float toPow, const largest_float index) {
    fract_simp(index, 1);
    return power_int_idx(   root_int_base( toPow, static_cast<largest_int>(get_result(0)) ), static_cast<largest_int>(get_result(1))   );
}

#ifdef _LIBCPP_STRING
std::string YH::Lib::Func::maths::root_to_str (const largest_float toRoot, const largest_int base, const uint8_t max_return_length) {
    if (toRoot < 0) return "i";
    else if (toRoot == 0) return "0";
    if (max_return_length < 1) return "";
    std::string RootedS = "";
    largest_uint rootInInt = 0;
    for (largest_uint j = 0; j < toRoot; rootInInt = j++) {
        if (power(j, base) > toRoot) {
            // j--;
            break;
        }
    }
    RootedS = std::to_string(rootInInt);
    // if the rooted number is exactly an integer
    if (power(std::stold(RootedS), base) == toRoot) return RootedS;
    RootedS.push_back('.');
    size_t RootedS_int_leng = RootedS.length();
    for (size_t i = 0; i < (size_t)(max_return_length - RootedS_int_leng); i++) {
        RootedS.push_back('0');
        for (int16_t k = 0; k < 10; k++) {
            RootedS [RootedS.length() - 1] = *(std::to_string(k)).c_str();
            if (power(std::stold(RootedS), base) > toRoot) {
                RootedS [RootedS.length() - 1] = *(std::to_string(--k)).c_str();
                break;
            }
        }
        if (power(std::stold(RootedS), base) == toRoot) return RootedS;
    }
    return RootedS [RootedS.length() - 1] == '.' ? RootedS.substr(0, RootedS.length() - 1) : RootedS;
}
#endif // #ifdef _LIBCPP_STRING

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::factorial (int16_t val) {
    largest_float ret = 1;
    /*
    switch (sizeof(ret)) {
        case 1:
            if (val > 5) return 0;
            break;
        case 2:
            if (val > 8) return 0;
            break;
        case 3:
            if (val > 10) return 0;
            break;
        case 5:
        case 6:
        case 7:
        //
        case 4:
            if (val > 12) return 0;
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 8:
            if (val > 20) return 0;
            break;
        case 16:
            if (val > 35) return 0;
            break;
        default:
            if (val > 69) return 0;
            break;
    }
    */
    // const bool neg = val < 0;
    if (val < 0) val = -val;
    for (int16_t i = 0; i < val; ret *= ++i);
    // return neg ? -ret : ret;
    return ret;
}

YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::rnddn (const largest_float input) {
    return RND_DOWN(input);
    // return static_cast<long long>(input);
}
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::rndup (const largest_float input) {
    return RND_UP(input);
    // const long long dnval = static_cast<long long>(input);
    // return (input - dnval) > 0.000000000001L ? dnval + 1 : dnval;
    //                            123456789*12
}
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::rndoff (const largest_float input) {
    return RND_OFF(input);
    // long long dnval = static_cast<long long>(input);
    // return input - dnval < 0.5L ? dnval : dnval + 1;
}
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::rnd (const largest_float input, const int16_t mode) {
    switch (mode) {
        case 0:
            return RND_OFF(input);
            break;
        case 1:
            return RND_DOWN(input);
            break;
        case 2:
            return RND_UP(input);
            break;
        default:
            return 0;
            break;
    }
}
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::ceil (const largest_float input) {
    return RND_CEIL(input);
    // return input >= 0 ?
    //     YH::Lib::Func::maths::rndup(input) :
    //     0 - YH::Lib::Func::maths::rnddn(0 - input);
}
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::floor (const largest_float input) {
    return RND_FLOOR(input);
    // return input >= 0 ?
    //     YH::Lib::Func::maths::rnddn(input) :
    //     0 - YH::Lib::Func::maths::rndup(0 - input);
}

bool YH::Lib::Func::maths::rough_equal (const largest_float lhs, const largest_float rhs, const uint8_t cmp_len) {
    // return (lhs > rhs ? lhs - rhs < 0.00000762939453125 : rhs - lhs < 0.00000762939453125);
    // printf("lhs: %1.50Lf\nrhs: %1.50Lf\n", lhs, rhs);
    // printf("primary check %d\t( lhs: %lld\trhs: %lld )\n", rnddn(lhs) == rnddn(rhs), rnddn(lhs), rnddn(rhs));
    // if (rnddn(lhs) != rnddn(rhs)) return false;
    // printf("lhs aft dp * 131072: %1.50Lf\nrhs aft dp * 131072: %1.50Lf\n", ( lhs - rnddn(lhs) ) * 131072, ( rhs - rnddn(rhs) ) * 131072);
    // fflush(stdout);
    // return rnddn((lhs - rnddn(lhs)) * 131072) == rnddn((rhs - rnddn(rhs)) * 131072);
    // return (lhs > rhs ? lhs - rhs < 0.0000152587890625 : rhs - lhs < 0.0000152587890625) && rnddn((lhs - rnddn(lhs)) * 131072) == rnddn((rhs - rnddn(rhs)) * 131072);
    // return std::to_string(lhs) == std::to_string(rhs);
    char lhs_str [cmp_len];
    strncpy(lhs_str, base_10_to_base_n(lhs, 10, cmp_len), cmp_len);
    return !strncmp(lhs_str, base_10_to_base_n(rhs, 10, cmp_len), cmp_len);
}


YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::sinR (const largest_float angle) {
    return sin(angle);
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::asinR (const largest_float opposite_side_to_hypotenuse) {
    return asin(opposite_side_to_hypotenuse);
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cosR (const largest_float angle) {
    return cos(angle);
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acosR (const largest_float adjacent_side_to_hypotenuse) {
    return acos(adjacent_side_to_hypotenuse);
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::tanR (const largest_float angle) {
    return tan(angle);
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::atanR (const largest_float opposite_side_to_adjacent_side) {
    return atan(opposite_side_to_adjacent_side);
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cscR (const largest_float angle) {
    #if defined(csc)
    return csc(angle);
    #else
    return 1.0 / sin(angle);
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acscR (const largest_float hypotenuse_to_opposite_side) {
    #if defined(acsc)
    return acsc(hypotenuse_to_opposite_side);
    #else
    return asin(1.0/hypotenuse_to_opposite_side);
    #endif
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::secR (const largest_float angle) {
    #if defined(sec)
    return sec(angle);
    #else
    return 1.0 / cos(angle);
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::asecR (const largest_float hypotenuse_to_adjacent_side) {
    #if defined(asec)
    return asec(hypotenuse_to_adjacent_side);
    #else
    return acos(1.0/hypotenuse_to_adjacent_side);
    #endif
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cotR (const largest_float angle) {
    #if defined(cot)
    return cot(angle);
    #else
    return 1.0 / tan(angle);
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acotR (const largest_float adjacent_side_to_opposite_side) {
    #if defined(acot)
    return acot(adjacent_side_to_opposite_side);
    #else
    return pi/2 - atan(adjacent_side_to_opposite_side);
    #endif
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::angle2radian (const largest_float angle) {
    return angle * YH::Lib::Func::maths::pi / 180.0L;
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::radian2angle (const largest_float radian) {
    return radian / YH::Lib::Func::maths::pi * 180.0L;
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::sinA (const largest_float angle) {
    return sin(angle2radian(angle));
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::asinA (const largest_float opposite_side_to_hypotenuse) {
    return radian2angle(asin(opposite_side_to_hypotenuse));
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cosA (const largest_float angle) {
    return cos(angle2radian(angle));
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acosA (const largest_float adjacent_side_to_hypotenuse) {
    return radian2angle(acos(adjacent_side_to_hypotenuse));
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::tanA (const largest_float angle) {
    return tan(angle2radian(angle));
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::atanA (const largest_float opposite_side_to_adjacent_side) {
    return radian2angle(atan(opposite_side_to_adjacent_side));
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cscA (const largest_float angle) {
    #if defined(csc)
    return csc(angle2radian(angle));
    #else
    return 1.0 / sin(angle2radian(angle));
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acscA (const largest_float hypotenuse_to_opposite_side) {
    #if defined(acsc)
    return radian2angle(acsc(hypotenuse_to_opposite_side));
    #else
    return radian2angle(asin(1.0/hypotenuse_to_opposite_side));
    #endif
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::secA (const largest_float angle) {
    #if defined(sec)
    return sec(angle2radian(angle));
    #else
    return 1.0 / cos(angle2radian(angle));
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::asecA (const largest_float hypotenuse_to_adjacent_side) {
    #if defined(asec)
    return radian2angle(asec(hypotenuse_to_adjacent_side));
    #else
    return radian2angle(acos(1.0/hypotenuse_to_adjacent_side));
    #endif
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::cotA (const largest_float angle) {
    #if defined(cot)
    return cot(angle2radian(angle));
    #else
    return 1.0 / tan(angle2radian(angle));
    #endif
}
YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::acotA (const largest_float adjacent_side_to_opposite_side) {
    #if defined(acot)
    return radian2angle(acot(adjacent_side_to_opposite_side));
    #else
    return radian2angle(pi/2 - atan(adjacent_side_to_opposite_side));
    #endif
}

// the 3 functions below are defined in header file, because template functions cannot be separately compiled

// template <class Return_type>
// Return_type YH::Lib::Func::maths::absolute (const Return_type input) {
//     return TO_POSITIVE(input);
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::toPositive (const Return_type input) {
//     return TO_POSITIVE(input);
// }

// template <class Return_type>
// Return_type YH::Lib::Func::maths::toNegative (const Return_type input) {
//     return TO_NEGATIVE(input);
// }

YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::tri_num (const largest_int index) {
    return TRI_NUM(index);
    // bool isPositive = index > 0;
    // long long n = isPositive ? index : 0 - index;
    // n = (n * (n + 1) / 2);
    // return isPositive ? n : 0 - n;
    /*
     * Alternate way
     * long long result = 0;
     * for (int i = 1; i < n + 1; result += i++);
     * return result;
     */
}

// 0 1 2 3 4 5 6 07 08 09 10 11  12
// 0 1 1 2 3 5 8 13 21 34 55 89 144
YH::Lib::Func::maths::largest_int YH::Lib::Func::maths::fib_num (const largest_int index) {
    largest_int a = 0, b = 1, c = 1;
    const largest_uint positive_index = TO_POSITIVE(index);
    for (largest_uint i = 0; i < positive_index; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return (index > 0) ? a : (0 - a);
}

bool YH::Lib::Func::maths::pri_num (const largest_int input) {
    if (input <= 1) return false;
    largest_int i = 2;
    do {
        if (!(input % i) && input != i) return false;
        i++;
    } while (i < input / 2);
    return true;
}

YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::nCr (const largest_uint n, const largest_uint r) {
    if (r > n) return 0;
    if (r > n / 2) return nCr(n, n-r);
    // nCr == n! ÷ [ (n-r)!r! ]
    // n! == n * (n-1) * (n-2) * ... * (n-r)!
    largest_uint numerator = 1;
    for (largest_uint i = n; i > n-r; numerator *= i--) { }
    return numerator / factorial(r);
}

YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::nPr (const largest_uint n, const largest_uint r) {
    // nPr == n! ÷ (n-r)!
    if (r > n) return 0; // result == n! ÷ (-ive)!, which (-ive)! is undefined
    largest_uint to_return = 1;
    for (largest_uint i = n; i > n-r; to_return *= i--) { }
    return to_return;
}

// 4, 5 result 1
// 24, 48 result 24
// -4, 4 result 4
// 36, -48 result 12
// -12, -8 result 4 (-3 * 4, -2 * 4)
// 4.5, 7.5 result 1.5 but floating_point_number not supported
// should convert to 45, 75 before calling function
YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::hcf (const largest_int a, const largest_int b) {
    const largest_uint a_positive = TO_POSITIVE(a);
    const largest_uint b_positive = TO_POSITIVE(b);
    // const long double ald = static_cast<long double>(YH::Lib::Func::maths::toPositive(a));
    // const long double bld = static_cast<long double>(YH::Lib::Func::maths::toPositive(b));
    // dangerous
    // long double power10 = 1;
    // for (power10 = 1; a != YH::Lib::Func::maths::rnddn(a) || b != YH::Lib::Func::maths::rnddn(b); a *= 10, b *= 10, power10 *= 10) { }
    for (largest_uint i = (a_positive > b_positive ? a_positive : b_positive); i > 0ULL; i--) {
        /*
        if (ald / i == static_cast<long double>(YH::Lib::Func::maths::rnddn(ald / i)) &&
            bld / i == static_cast<long double>(YH::Lib::Func::maths::rnddn(bld / i)))
            return i;
        */
        if ( !(a_positive % i) && !(b_positive % i) ) return i;
    }
    return 0ULL;
}

YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::lcm (const largest_int a, const largest_int b) {
    const largest_uint a_positive = TO_POSITIVE(a);
    const largest_uint b_positive = TO_POSITIVE(b);
    const largest_uint biggest_cm = a_positive * b_positive; // biggest common multiplyer
    // const long double ald = static_cast<long double>(YH::Lib::Func::maths::toPositive(a));
    // const long double bld = static_cast<long double>(YH::Lib::Func::maths::toPositive(b));
    // const long double biggest_cm = ald * bld;
    for (largest_uint i = (a_positive > b_positive ? a_positive : b_positive); i < biggest_cm; i++) {
        /*
        if (i / ald == static_cast<long double>(YH::Lib::Func::maths::rnddn(i / ald)) &&
            i / bld == static_cast<long double>(YH::Lib::Func::maths::rnddn(i / bld)))
            return i;
        */
        if ( !(i % a_positive) && !(i % b_positive) ) return i;
    }
    return biggest_cm;
}

const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::fract_simp_int (const largest_int up, const largest_int low) {
    largest_int base = static_cast<largest_int>(hcf(up, low));
    if (up < 0 && low < 0) base = (-base);
    largest_float to_return [2] = {static_cast<largest_float>(up / base), static_cast<largest_float>(low / base)};
    pvt::assignToArray (to_return, 2);
    return pvt::result.raw_ptr();
}

const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::fract_simp (const largest_float up, const largest_float low) {
    if (up == rndup(up) && low == rndup(low)) return fract_simp_int(static_cast<largest_int>(up), static_cast<largest_int>(low));
    const largest_float fractSimp_h = up / low;
    #define contain_dec(x) (!rough_equal(x, rndoff(x))) // returns 1 if the val contains value after d.p.
    // long double fractSimp_a = fractSimp_h, fractSimp_b = 1;
    // //
    // for (long double i = 1.0L;
    //         YH::Lib::Func::maths::rndup(fractSimp_a) > fractSimp_a ?
    //             (YH::Lib::Func::maths::rndup(fractSimp_a) - fractSimp_a) > 0.0000000001L :
    //             (fractSimp_a - YH::Lib::Func::maths::rndup(fractSimp_a)) > 0.0000000001L;
    //     fractSimp_b = i++) {
    //     //printf("fractSimp_a: %1.50Lf\nrndup val: %1.50Lf\n\n\n\n\n", fractSimp_a, static_cast<long double>(YH::Lib::Func::maths::rndup(fractSimp_a)));
    //     fractSimp_a = i * fractSimp_h;
    //     // fractSimp_b = i;
    // }
    // //
    // // const long long base = YH::Lib::Func::maths::hcf(up, low);
    // // long double toReturn [2] = {up / base, low / base};
    // long double toReturn [2] = {YH::Lib::Func::maths::rndoff(fractSimp_a), fractSimp_b};
    // YH::Lib::Func::maths::pvt::assignToArray (toReturn, sizeof(toReturn) / sizeof(toReturn[0]));
    // //return YH::Lib::Func::maths::pvt::result;
    // return YH::Lib::Func::maths::pvt::result.raw_ptr();
    // new way of doing it
    largest_float i = 1.0L;
    for (; contain_dec(fractSimp_h * i); i++) {
        // printf("rnddn: %lld,\trndup: %lld\n", rnddn(fractSimp_h * i), rndup(fractSimp_h * i));
    }
    largest_float to_return [2] = {static_cast<largest_float>(rndoff(fractSimp_h * i)), i};
    pvt::assignToArray (to_return, 2);
    return pvt::result.raw_ptr();
    #undef contain_dec
}


// const long double *YH::Lib::Func::maths::quad_equ_x_intercept (const long double input_A, const long double input_B, const long double input_C) {
//     /*
//     CLRmem:
//     ? -> A:
//     ? -> B:
//     ? -> C:
//     B² - 4AC -> C:
//     (√C - B) / (2A) -> X:
//     (-√C - B) / (2A) -> Y:
//     Lbl 1:
//     1 M+:
//     XM:
//     Fix 0:
//     Rnd:
//     Norm 1:
//     XM ≠ Ans => Goto 1:
//     A / M -> A:
//     M M- output
//     -X Ans output
//     Y -> X:
//     D = 0 -> D => Goto 1:
//     // (D == 0) -> D => Goto 1:
//     A
//     */
//     pvt::assignToArray((long double *)NULL, 7);         // clear output buffer
//     int result_arrcount = 0; // result[1000] is used to store the output values
//                              // while result_arrcount is used to indicate the index of result[] to be written
//     long double A, B, C, D, X, Y, M, Ans;               // declare the 7 variables
//     A = B = C = D = X = Y = M = Ans = 0.0F;             // Mem clear:
//     A = input_A, B = input_B, C = input_C;              // ? -> A: ? -> B: ? -> C:
//     C = Ans = B*B - 4*A*C;                              // B² - 4AC -> C:
//     result.idx(result_arrcount++) =
//     X = Ans = (root(C) - B) /2 /A;                      // 2^-1 A^-1 (√C - B -> X output
//     result.idx(result_arrcount++) =
//     Y = Ans = (- root(C) - B) /2 /A;                    // 2^-1 A^-1 (-√C - B -> Y output
//     Lbl_1:                                              // Lbl 1:
//     Ans = M += 1;                                       // 1 M+:
//     Ans = rndoff(X * M);                                // XM: fix 0: Rnd: Norm 1:
//     if (!rough_equal(X * M, Ans)) goto Lbl_1;           // XM ≠ Ans => Goto 1:
//     A = Ans = A / M;                                    // A / M -> A:
//     result.idx(result_arrcount++) = (Ans = M); M-= M;   // M M- output
//     result.idx(result_arrcount++) = Ans = (-X * Ans);   // -X Ans output
//     X = Y;                                              // Y -> X:
//     if ((D = (D == 0))) goto Lbl_1;                     // D = 0 -> D => Goto 1:
//     result.idx(result_arrcount++) = A;                  // A (output)
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::quad_equ_vertex (const long double input_A, const long double input_B, const long double input_C) {
//     // general form         to           h-k form
//     // Ax² + Bx + C = 0     to     A(x - h)² + k = 0
//     //
//     // finding h and k with completing square method
//     //                               Ax² + Bx + C = 0
//     //                         A(x² + (B/A)x) + C = 0
//     //                       A(x² + 2(B/2A)x) + C = 0
//     //   A(x² + 2(B/2A)x + (B/2A)² - (B/2A)²) + C = 0
//     //  A(x² + 2(B/2A)x + (B/2A)² - (B²/4A²)) + C = 0
//     // A(x² + 2(B/2A)x + (B/2A)²) - A(B²/4A²) + C = 0
//     //                 A(x + B/2A)² - (B²/4A) + C = 0
//     //            A( x - (-B/2A) )² - (B²/4A) + C = 0
//     //       A( x - (-B/2A) )² - (B²/4A) + 4AC/4A = 0
//     //          A( x - (-B/2A) )² + (4AC - B²)/4A = 0
//     //     A( x - (-B/2A) )² + ( -(B² - 4AC) )/4A = 0
//     //                A( x - (-B/2A) )² + (-∆/4A) = 0
//     // h == -B/2A, k == -∆/4A
//     pvt::assignToArray((long double []){-input_B / 2 / input_A, input_C - input_B * input_B / 4 / input_A}, 2);
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::ab2quad_equ (const long double alpha, const long double beta) {
//     /* 
//      * 
//      * Prgm to find out the quad equation with 2 roots
//      * 
//      * Mem clear:
//      * ? -> A:
//      * ? -> B:
//      * -A - B -> X:
//      * AB -> Y:
//      * Lbl 1:
//      * 1 M+:
//      * XM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * XM ≠ Ans => goto 1:
//      * Lbl 3:
//      * YM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * YM = Ans => goto 2:
//      * 1 M+:
//      * goto 3:
//      * Lbl 2:
//      * M output
//      * XM output
//      * YM (output)
//      * 
//      */
//     pvt::assignToArray((long double *)NULL, 3);    // clear output buffer
//     int result_arrcount = 0;                       // keeps track of the index of result to be inputed
//     long double A, B, C, D, X, Y, M, Ans;          // declares the 7 variables
//     A = B = C = D = X = Y = M = Ans = 0.0F;        // Mem clear:
//     A = alpha;                                     // ? -> A:
//     B = beta;                                      // ? -> B:
//     X = Ans = -A - B;                              // -A - B -> X:
//     Y = Ans = A * B;                               // AB -> Y:
//     // std::cout << "X: " << X << "\n" << "Y: " << Y << "\n";
//     Lbl_1:                                         // Lbl 1:
//     Ans = M += 1;                                  // 1 M+:
//     Ans = rndoff(X * M);                           // XM: Fix 0: Rnd: Norm 1:
//     // printf("X * M: %1.50Lf\nAns: %1.50Lf\n", X * M, Ans);
//     if (!rough_equal(X * M, Ans)) goto Lbl_1;      // XM ≠ Ans => goto 1:
//     Lbl_3:                                         // Lbl 3:
//     Ans = rndoff(Y * M);                           // YM: Fix 0: Rnd: Norm 1:
//     // printf("Y * M: %1.50Lf\nAns: %1.50Lf\n", Y * M, Ans);
//     if (rough_equal(X * M, Ans)) goto Lbl_2;       // YM = Ans => goto 2:
//     Ans = M += 1;                                  // 1 M+:
//     goto Lbl_3;                                    // goto 3:
//     Lbl_2:                                         // Lbl 2:
//     result.idx(result_arrcount++) = M;             // M output
//     result.idx(result_arrcount++) = Ans = X * M;   // XM output
//     result.idx(result_arrcount) = Ans = Y * M;     // YM (output)
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::linear_equ (const long double m, const long double c) {
//     /* 
//      * 
//      * Prgm to find out A, B, C in linear equation with y = mx + c
//      * Mem clear:
//      * ? -> M:      // replace M with A if you want to shorten the prgm
//      * ? -> C:
//      * M -> A:
//      *              // (1 * m * M)x + (-1 * M)y + (c * M)1 = 0
//      * 0 -> M:
//      * Lbl 1:
//      * 1 M+:
//      * AM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * AM ≠ Ans => goto 1:
//      * Lbl 3:
//      * CM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * CM = Ans => goto 2:
//      * 1 M+:
//      * goto 3:
//      * Lbl 2:
//      * A < 0 => -M -> M:
//      * AM output
//      * -M output
//      * CM (output)
//      * 
//      */
//     pvt::assignToArray((long double *)NULL, 3);    // clear output buffer
//     int result_arrcount = 0;                       // keeps track of the index of result to be inputed
//     long double A, B, C, D, X, Y, M, Ans;          // declares the 7 variables
//     A = B = C = D = X = Y = M = Ans = 0;
//     Ans = M = m;
//     Ans = C = c;
//     Ans = A = M;
//     Ans = M = 0;
//     Lbl_1:
//     Ans = M += 1;
//     Ans = rndoff(A * M);
//     if (!rough_equal(A * M, Ans)) goto Lbl_1;
//     Lbl_3:
//     Ans = rndoff(C * M);
//     if (rough_equal(C * M, Ans)) goto Lbl_2;
//     M += 1;
//     goto Lbl_3;
//     Lbl_2:
//     if (A < 0) M = -M;
//     result.idx(result_arrcount++) = Ans = A * M;
//     result.idx(result_arrcount++) = Ans = -M;
//     result.idx(result_arrcount) = Ans = C * M;
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::linear_equ (const long double x, const long double y, const long double m) {
//     /* 
//      * 
//      * Prgm to find out A, B, C in linear equation with y - y1 = m(x - x1)
//      * y - y1 = mx - mx1
//      *      0 = mx - y - mx1 + y1
//      * A == m, B == -1, C == y1-mx1
//      * Mem clear:
//      * ? -> X:
//      * ? -> Y:
//      * ? -> M:
//      * M -> A:
//      * y - MX -> C:
//      * 0 -> M:
//      * Lbl 1:
//      * 1 M+:
//      * AM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * AM ≠ Ans => Goto 1:
//      * Lbl 3:
//      * CM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * CM = Ans => Goto 2:
//      * 1 M+:
//      * Goto 3:
//      * Lbl 2:
//      * A < 0 => -M -> M:
//      * AM output
//      * -M output
//      * CM (output)
//      * 
//      */
//     /* 
//      * 
//      * Shortened vers:
//      * 
//      * Prgm to find out A, B, C in linear equation with y - y1 = m(x - x1)
//      * Mem clear:
//      * ? -> X:
//      * ? -> Y:
//      * ? -> A:
//      * AX - Y -> C:
//      * -A -> A:
//      * Lbl 1:
//      * 1 M+:
//      * AM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * AM ≠ Ans => Goto 1:
//      * Lbl 3:
//      * CM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * CM = Ans => Goto 2:
//      * 1 M+:
//      * Goto 3:
//      * Lbl 2:
//      * AM output
//      * -M output
//      * CM
//      * 
//      */
//     pvt::assignToArray((long double *)NULL, 3);    // clear output buffer
//     int result_arrcount = 0;                       // keeps track of the index of result to be inputed
//     long double A, B, C, D, X, Y, M, Ans;          // declares the 7 variables
//     A = B = C = D = X = Y = M = Ans = 0;
//     Ans = X = x;
//     Ans = Y = y;
//     Ans = M = m;
//     Ans = A = M;
//     Ans = C = Y - M * X;
//     Ans = M = 0;
//     Lbl_1:
//     Ans = M += 1;
//     Ans = rndoff(A * M);
//     if (!rough_equal(A * M, Ans)) goto Lbl_1;
//     Lbl_3:
//     Ans = rndoff(C * M);
//     if (rough_equal(C * M, Ans)) goto Lbl_2;
//     M += 1;
//     goto Lbl_3;
//     Lbl_2:
//     if (A < 0) M = -M;
//     result.idx(result_arrcount++) = Ans = A * M;
//     result.idx(result_arrcount++) = Ans = -M;
//     result.idx(result_arrcount) = Ans = C * M;
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::linear_equ (const long double x1, const long double y1, const long double x2, const long double y2) {
//     /* 
//      * 
//      * Prgm to find out A, B, C in linear equation with y - y1 = [ (y1 - y2) ÷ (x1 - x2) ] (x - x1)
//      *                  y - y1 = [ (y1 - y2) ÷ (x1 - x2) ] (x - x1)
//      *       (y - y1)(x1 - x2) = (y1 - y2)(x - x1)
//      * yx1 - y1x1 - yx2 + x2y1 = y1x - y2x - y1x1 + y2x1
//      * yx1        - yx2 + x2y1 = y1x - y2x        + y2x1
//      *       y(x1 - x2) + x2y1 = x(y1 - y2) + y2x1
//      *                       0 = (y1 - y2)x - (x1 - x2)y + y2x1 - x2y1
//      *                       0 = (y1 - y2)x + (x2 - x1)y + y2x1 - x2y1
//      * A == y1 - y2, B == x2 - x1, C == y2 * x1 - x2 * y1
//      * ? -> A:
//      * ? -> B:
//      * ? -> C:
//      * ? -> D:
//      * AD - BC -> Y:
//      * (B - D) / Y -> X:
//      * (C - A) / Y -> Y:
//      * Lbl 1:
//      * 1 M+:
//      * XM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * XM ≠ Ans => goto 1:
//      * Lbl 3:
//      * YM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * YM = Ans => goto 2:
//      * 1 M+:
//      * goto 3:
//      * Lbl 2:
//      * X < 0 => -M -> M:
//      * XM output
//      * YM output
//      * M (output)
//      * 
//      */
//     /* 
//      * 
//      * Shortened vers: // actually nothing is shorten
//      * 
//      * ? -> A:
//      * ? -> B:
//      * ? -> C:
//      * ? -> D:
//      * AD - BC -> Y:
//      * (B - D) / Y -> X:
//      * (C - A) / Y -> Y:
//      * Lbl 1:
//      * 1 M+:
//      * XM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * XM ≠ Ans => goto 1:
//      * Lbl 3:
//      * YM:
//      * Fix 0:
//      * Rnd:
//      * Norm 1:
//      * YM = Ans => goto 2:
//      * 1 M+:
//      * goto 3:
//      * Lbl 2:
//      * X < 0 => -M -> M:
//      * XM output
//      * YM output
//      * M (output)
//      * 
//      */
//     pvt::assignToArray((long double *)NULL, 3);    // clear output buffer
//     int result_arrcount = 0;                       // keeps track of the index of result to be inputed
//     long double A, B, C, D, X, Y, M, Ans;          // declares the 7 variables
//     A = B = C = D = X = Y = M = Ans = 0;
//     A = Ans = x1;
//     B = Ans = y1;
//     C = Ans = x2;
//     D = Ans = y2;
//     Y = Ans = A * D - B * C;
//     X = Ans = (B - D) / Y;
//     Y = Ans = (C - A) / Y;
//     Lbl_1:
//     Ans = M += 1;
//     Ans = rndoff(X * M);
//     if (!rough_equal(X * M, Ans)) goto Lbl_1;
//     Lbl_3:
//     Ans = rndoff(Y * M);
//     if (rough_equal(Y * M, Ans)) goto Lbl_2;
//     Ans = M += 1;
//     goto Lbl_3;
//     Lbl_2:
//     if (X < 0) M = Ans = -M;
//     result.idx(result_arrcount++) = Ans = X * M;
//     result.idx(result_arrcount++) = Ans = Y * M;
//     result.idx(result_arrcount) = Ans = M;
//     return result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::pt_dist (const long double x1, const long double y1, const long double x2, const long double y2) {
//     const long double to_root_len = ( YH::Lib::Func::maths::power((x1 - x2), 2) + YH::Lib::Func::maths::power((y1 - y2), 2) );
//     const long double arr[2] = {YH::Lib::Func::maths::root(to_root_len, 2), to_root_len};
//     YH::Lib::Func::maths::pvt::assignToArray(arr, sizeof(arr) / sizeof(arr[0]));
//     //return YH::Lib::Func::maths::pvt::result;
//     return YH::Lib::Func::maths::pvt::result.raw_ptr();
// }

// long double YH::Lib::Func::maths::pt_dist (const long double x1, const long double y1, const long double z1, const long double x2, const long double y2, const long double z2) {
//     return root (    power (  root ( power ((x1 - x2), 2) + power ((y1 - y2), 2) , 2)  , 2) + power ((z1 - z2), 2)    );
// }

// YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::points_dist_ (const int16_t count, const largest_float *arr) {
//     largest_float result = 0;
//     largest_float c1 = 0;
//     largest_float c2 = 0;
//     const largest_int half_count = count / 2;
//     for (int i = 0; i < half_count; i++) {
//         c1 = arr[i];
//         c2 = arr[i + half_count];
//         result = root (power (result, 2) + power ((c1 - c2), 2), 2);
//     }
//     return result;
// }

// const long double *YH::Lib::Func::maths::pt_slope (const long double x1, const long double y1, const long double x2, const long double y2) {
//     const long double y_dist = y1 - y2;
//     const long double x_dist = x1 - x2;
//     YH::Lib::Func::maths::fract_simp(y_dist, x_dist);
//     //const long double arr[3] = {y_dist / x_dist, YH::Lib::Func::maths::pvt::result[0], YH::Lib::Func::maths::pvt::result[1]};
//     const long double arr[3] = {y_dist / x_dist, YH::Lib::Func::maths::pvt::result.idx(0), YH::Lib::Func::maths::pvt::result.idx(1)};
//     YH::Lib::Func::maths::pvt::assignToArray(arr, sizeof(arr) / sizeof(arr[0]));
//     //return YH::Lib::Func::maths::pvt::result;
//     return YH::Lib::Func::maths::pvt::result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::get_pt_by_ratio (const long double Ax, const long double Ay, const long double Bx, const long double By, const long double AP, const long double PB) {
//     YH::Lib::Func::maths::fract_simp((Ax * PB + Bx * AP), (AP + PB));
//     /*
//     const long double c1 = YH::Lib::Func::maths::pvt::result[0];
//     const long double c2 = YH::Lib::Func::maths::pvt::result[1];
//     */
//     const long double c1 = YH::Lib::Func::maths::pvt::result.idx(0);
//     const long double c2 = YH::Lib::Func::maths::pvt::result.idx(1);
//     YH::Lib::Func::maths::fract_simp((Ay * PB + By * AP), (AP + PB));
//     /*
//     const long double c3 = YH::Lib::Func::maths::pvt::result[0];
//     const long double c4 = YH::Lib::Func::maths::pvt::result[1];
//     */
//     const long double c3 = YH::Lib::Func::maths::pvt::result.idx(0);
//     const long double c4 = YH::Lib::Func::maths::pvt::result.idx(1);
//     const long double coordinates [6] = {(Ax * PB + Bx * AP) / (AP + PB), (Ay * PB + By * AP) / (AP + PB), c1, c2, c3, c4};
//     YH::Lib::Func::maths::pvt::assignToArray(coordinates, sizeof(coordinates) / sizeof(coordinates[0]));
//     //return YH::Lib::Func::maths::pvt::result;
//     return YH::Lib::Func::maths::pvt::result.raw_ptr();
// }

// const long double *YH::Lib::Func::maths::get_midp_cord (const long double Ax, const long double Ay, const long double Bx, const long double By) {
//     YH::Lib::Func::maths::fract_simp((Ax + Bx), 2);
//     /*
//     const long double c1 = YH::Lib::Func::maths::pvt::result[0];
//     const long double c2 = YH::Lib::Func::maths::pvt::result[1];
//     */
//     const long double c1 = YH::Lib::Func::maths::pvt::result.idx(0);
//     const long double c2 = YH::Lib::Func::maths::pvt::result.idx(1);
//     YH::Lib::Func::maths::fract_simp((Ay + By), 2);
//     /*
//     const long double c3 = YH::Lib::Func::maths::pvt::result[0];
//     const long double c4 = YH::Lib::Func::maths::pvt::result[1];
//     */
//     const long double c3 = YH::Lib::Func::maths::pvt::result.idx(0);
//     const long double c4 = YH::Lib::Func::maths::pvt::result.idx(1);
//     const long double coordinates [6] = {(Ax + Bx) / 2, (Ay + By) / 2, c1, c2, c3, c4};
//     YH::Lib::Func::maths::pvt::assignToArray(coordinates, sizeof(coordinates) / sizeof(coordinates[0]));
//     //return YH::Lib::Func::maths::pvt::result;
//     return YH::Lib::Func::maths::pvt::result.raw_ptr();
// }

// YH::Lib::Func::maths::largest_uint YH::Lib::Func::maths::binary_to_decimal (const char *str) {
//     largest_uint to_return = 0;
//     while (*str != '\0') {
//         to_return <<= 1;
//         to_return += (*str == '0') ? 0 : 1;
//         str++;
//     }
//     return to_return;
// }

int8_t YH::Lib::Func::maths::char_to_val (const char input) {
    switch (input) {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
        //
        case 'A':
        case 'a':
            return 10;
            break;
        case 'B':
        case 'b':
            return 11;
            break;
        case 'C':
        case 'c':
            return 12;
            break;
        case 'D':
        case 'd':
            return 13;
            break;
        case 'E':
        case 'e':
            return 14;
            break;
        case 'F':
        case 'f':
            return 15;
            break;
        case 'G':
        case 'g':
            return 16;
            break;
        case 'H':
        case 'h':
            return 17;
            break;
        case 'I':
        case 'i':
            return 18;
            break;
        case 'J':
        case 'j':
            return 19;
            break;
        case 'K':
        case 'k':
            return 20;
            break;
        case 'L':
        case 'l':
            return 21;
            break;
        case 'M':
        case 'm':
            return 22;
            break;
        case 'N':
        case 'n':
            return 23;
            break;
        case 'O':
        case 'o':
            return 24;
            break;
        case 'P':
        case 'p':
            return 25;
            break;
        case 'Q':
        case 'q':
            return 26;
            break;
        case 'R':
        case 'r':
            return 27;
            break;
        case 'S':
        case 's':
            return 28;
            break;
        case 'T':
        case 't':
            return 29;
            break;
        case 'U':
        case 'u':
            return 30;
            break;
        case 'V':
        case 'v':
            return 31;
            break;
        case 'W':
        case 'w':
            return 32;
            break;
        case 'X':
        case 'x':
            return 33;
            break;
        case 'Y':
        case 'y':
            return 34;
            break;
        case 'Z':
        case 'z':
            return 35;
            break;
        default:
            return -1;
            break;
    }
}

char YH::Lib::Func::maths::val_to_cap_letter (const int16_t input) {
    switch (input) {
        case -1:
            return '-';
            break;
        case -2:
            return '.';
            break;
        case -255:
            return '\0';
            break;
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return '2';
            break;
        case 3:
            return '3';
            break;
        case 4:
            return '4';
            break;
        case 5:
            return '5';
            break;
        case 6:
            return '6';
            break;
        case 7:
            return '7';
            break;
        case 8:
            return '8';
            break;
        case 9:
            return '9';
            break;
        //
        case 10:
            return 'A';
            break;
        case 11:
            return 'B';
            break;
        case 12:
            return 'C';
            break;
        case 13:
            return 'D';
            break;
        case 14:
            return 'E';
            break;
        case 15:
            return 'F';
            break;
        case 16:
            return 'G';
            break;
        case 17:
            return 'H';
            break;
        case 18:
            return 'I';
            break;
        case 19:
            return 'J';
            break;
        case 20:
            return 'K';
            break;
        case 21:
            return 'L';
            break;
        case 22:
            return 'M';
            break;
        case 23:
            return 'N';
            break;
        case 24:
            return 'O';
            break;
        case 25:
            return 'P';
            break;
        case 26:
            return 'Q';
            break;
        case 27:
            return 'R';
            break;
        case 28:
            return 'S';
            break;
        case 29:
            return 'T';
            break;
        case 30:
            return 'U';
            break;
        case 31:
            return 'V';
            break;
        case 32:
            return 'W';
            break;
        case 33:
            return 'X';
            break;
        case 34:
            return 'Y';
            break;
        case 35:
            return 'Z';
            break;
        default:
            return '\0';
            break;
    }
}

YH::Lib::Func::maths::largest_float YH::Lib::Func::maths::base_n_to_base_10 (const char *str, const uint16_t base_from, char* *remaining_unrecognized_str) {
    largest_int int_val = 0;
    largest_uint i = 0;
    int8_t pcsing_val = 0;
    for (; str[i] != '.' && str[i] != '\0'; i++) {
        pcsing_val = char_to_val(str[i]);
        if (pcsing_val == -1 || static_cast<uint16_t>(pcsing_val) >= base_from) {
            if (remaining_unrecognized_str != NULL) *remaining_unrecognized_str = const_cast<char *>(str + i);
            return int_val;
        }
        int_val *= base_from;
        int_val += char_to_val(str[i]);
    }
    if (str[i++] == '.') {
        largest_float float_val = int_val;
        largest_float base_powering = 1;
        for (; str[i] != '\0'; i++) {
            pcsing_val = char_to_val(str[i]);
            if (pcsing_val == -1 || static_cast<uint16_t>(pcsing_val) >= base_from) {
                if (remaining_unrecognized_str != NULL) *remaining_unrecognized_str = const_cast<char *>(str + i);
                return float_val;
            }
            base_powering /= base_from;
            float_val += pcsing_val * base_powering;
        }
        return float_val;
    } else {
        return int_val;
    }
}

const char *YH::Lib::Func::maths::base_10_to_base_n (const largest_float val, const uint16_t base_to, const largest_uint str_max_len, const bool round_off_last_digit) {
    if (base_to < 2 || str_max_len < 2) return NULL; // base == 0 || base == 1 || str_max_len == 0 || str_max_len == 1
    if (!str_max_len) {
        pvt::assignToArray("", 1);
        return pvt::char_result.raw_ptr();
    }
    if (val == NAN) {
        pvt::assignToArray("nan", 4);
        return pvt::char_result.raw_ptr();
    } else if (val == INFINITY) {
        pvt::assignToArray("inf", 4);
        return pvt::char_result.raw_ptr();
    }
    char holding_str [str_max_len]; // acts as the string buffer to be copied then returned
    //
    // -1 represents val < 1, -10 indicates the location of decimal-point
    largest_int holding_str_cal_val [str_max_len]; // the buffer that holds the digits corresponding to the string buffer above
    bool is_val_neg = val < 0;
    bool int_part_equals_0 = false; // to indicate if val >= 1
    // set the whole buffer to \\0
    for (size_t i = 0; i < str_max_len; i++) {
        holding_str[i] = '\0';
        holding_str_cal_val[i] = -255;
    }
    // ... process the data
    // convert the integer part first
    largest_uint i = 0;
    largest_int pcs_int_val = rnddn(val);
    largest_uint int_val_require_len = 0;
    while (pcs_int_val) {
        pcs_int_val /= base_to;
        int_val_require_len++;
    }
    if (int_val_require_len == 0) {
        int_val_require_len++;
        int_part_equals_0 = true;
    }
    const largest_uint int_holding_str_sum_len_minus_1 = int_val_require_len + is_val_neg;
    // char int_holding_str [int_holding_str_sum_len]; // int part
    // holding_str [int_holding_str_sum_len_minus_1] = '\0';
    // holding_str_cal_val [int_holding_str_sum_len_minus_1] = -255;
    if (is_val_neg) {
        holding_str_cal_val[i] = -1;
        // holding_str[i] = '-';
        i++;
        holding_str_cal_val[i] = -255;
        // holding_str[i] = '\0';
    }
    if (int_part_equals_0) {
        holding_str_cal_val[i] = 0;
        // holding_str[i] = '0';
        i++;
        holding_str_cal_val[i] = -255;
        // holding_str[i] = '\0';
    }
    pcs_int_val = is_val_neg ? -rnddn(val) : rnddn(val);
    for (largest_int j = int_holding_str_sum_len_minus_1 - 1; pcs_int_val; pcs_int_val /= base_to, j--) {
        holding_str_cal_val[j] = pcs_int_val % base_to;
        // holding_str[j] = valToCapLetter(holding_str_cal_val[j]);
    }
    // strncpy(holding_str, int_holding_str, int_holding_str_sum_len);
    // convert the part after decimal point
    //
    largest_uint k = int_holding_str_sum_len_minus_1;
    holding_str_cal_val[k] = -2;
    // holding_str[k] = '.'; // add the decimal point into the string
    k++;
    largest_float pcs_float_val = is_val_neg ? (rnddn(val) - val) : (val - rnddn(val));
    const largest_uint k_upper_limit = str_max_len - 1;
    while (k < k_upper_limit) {
        pcs_float_val *= base_to;
        holding_str_cal_val[k] = rnddn(pcs_float_val) % base_to;
        // holding_str[k] = valToCapLetter(holding_str_cal_val[k]);
        k++;
        pcs_float_val -= rnddn(pcs_float_val);
    }
    // holding_str[k] = '\0';
    if (round_off_last_digit) {
        pcs_float_val *= base_to; // extract the digit after the max_str_len
        if ((rnddn(pcs_float_val) % base_to) >= (base_to / 2U)) {
            // correct to max_str_len sig. fig.
            // last char += 1
            if (holding_str_cal_val[--k] > -1 || holding_str_cal_val[k] == -2) { // when the value == -2, [k] is pointing to the '.' sign in the string
                if (holding_str_cal_val[k] == -2) --k;
                holding_str_cal_val[k] += 1;
                // holding_str[k] = valToCapLetter(holding_str_cal_val[k]);
                while (holding_str_cal_val[k] == base_to) {
                    holding_str_cal_val[k] = 0;
                    // holding_str[k] = valToCapLetter(holding_str_cal_val[k]);
                    if (!k) {
                        // k == 0
                        // right shift 1 char
                        for (largest_uint p = str_max_len - 1; p > 0; p--) {
                            holding_str_cal_val[p] = holding_str_cal_val[p - 1];
                        }
                        k = 1;
                    }
                    if (holding_str_cal_val[--k] > -1 || holding_str_cal_val[k] == -2) {
                        if (holding_str_cal_val[k] == -2) --k;
                        holding_str_cal_val[k] += 1;
                        // holding_str[k] = valToCapLetter(holding_str_cal_val[k]);
                    } else if (holding_str_cal_val[k] == -1) {
                        // [k] is pointing to the '-' sign in the string
                        break;
                    }
                }
            } else if (holding_str_cal_val[k] == -1) {
                // [k] is pointing to the '-' sign in the string
            }
        }
    }
    if (holding_str_cal_val[str_max_len - 2] == '.') holding_str[str_max_len - 2] = '\0';
    holding_str_cal_val[str_max_len - 1] = -255;
    for (largest_uint i = 0; i < str_max_len; i++) {
        holding_str[i] = val_to_cap_letter(holding_str_cal_val[i]);
    }
    pvt::assignToArray(holding_str, str_max_len);
    return pvt::char_result.raw_ptr();
}

const char *YH::Lib::Func::maths::change_base_of_str (const char *inputed_str, const uint16_t base_from, const uint16_t base_to, const largest_uint str_max_len) {
    return base_10_to_base_n(base_n_to_base_10(inputed_str, base_from, NULL), base_to, str_max_len);
}

// old method of changing bases of strings containing values
// disadvantage: cannot process floating-point numbers

// long long YH::Lib::Func::maths::to10base (std::string input, short base) {
//     long long result = 0;
//     for (int i = 0; i < input.length(); i++) {
//         short temp = charToVal(input[input.length() - 1 - i]);
//         if (temp != -1) result += temp * power(base, i);
//     }
//     return result;
// }

// const char *YH::Lib::Func::maths::DenaryToAnyBase (long long input, short base) {
//     int i = 1;
//     for (i = 1; input >= power(base, i); i++);
//     short d_result[i];
//     long long cal_input = input;
//     for (int j = 0; j < i; j++) {
//         d_result[i - j - 1] = cal_input % base;
//         cal_input = (cal_input - (cal_input % base)) / base;
//     }
//     char cc_result[i + 1];
//     for (int k = 0; k < i; k++) {
//         cc_result[k] = valToCapLetter(d_result[k]);
//     }
//     cc_result[i] = '\0';
//     YH::Lib::Func::maths::pvt::assignToArray(cc_result, sizeof(cc_result) / sizeof(cc_result[0]));
//     return YH::Lib::Func::maths::pvt::char_result.raw_ptr();
// }

// const char *YH::Lib::Func::maths::base_converter(std::string input, short input_base, short output_base) {
//     return YH::Lib::Func::maths::DenaryToAnyBase(YH::Lib::Func::maths::to10base(input, input_base), output_base);
// }

// { y = 3, y = 0x + 3
// { x = 4, y = INFx + NAN
// x = 4, 1x + 0y - 4 = 0
// slope = -1/0, y-itcp=4/0


const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::intercept_of_2_st_lines (const largest_float m1, const largest_float c1, const largest_float m2, const largest_float c2) {
    // y = mx + c
    // y = m1x + c1, y = m2x + c2
    // m1x + c1 == m2x + c2
    // m1x - m2x == c2 - c1
    // (m1 - m2)x == c2 - c1
    // x == (c2 - c1) ÷ (m1 - m2)
    // x solved
    // y = m1x + c1
    // y solved
    if (m1 == INFINITY || m1 == NAN || c1 == INFINITY || c1 == NAN || m2 == INFINITY || m2 == NAN || c2 == INFINITY || c2 == NAN) {
        // line 1 or line 2 is vertical line
        // no intercepts
        const largest_float temp [2] = {NAN, NAN};
        pvt::assignToArray(temp, 2);
    }
    if (m1 == m2) {
        // both straight lines have the same slope
        if (c1==c2) {
            // infinite intercepts
            const largest_float temp [2] = {INFINITY, INFINITY};
            pvt::assignToArray(temp, 2);
        } else {
            // no intercepts
            const largest_float temp [2] = {NAN, NAN};
            pvt::assignToArray(temp, 2);
        }
    } else {
        const largest_float x = (c2-c1) / (m1-m2);
        const largest_float temp [2] = {x, m1*x+c1};
        pvt::assignToArray(temp, 2);
    }
    return pvt::result.raw_ptr();
}

const YH::Lib::Func::maths::largest_float *YH::Lib::Func::maths::intercept_of_2_st_lines (const largest_float a1, const largest_float b1, const largest_float c1, const largest_float a2, const largest_float b2, const largest_float c2) {
    // Ax + By + C = 0
    // By = -C - Ax
    // y = (-C - Ax) ÷ B
    // y = -C÷B - Ax÷B
    // y = (-A÷B)x + (-C÷B)
    // y = mx + c
    const bool b1_is0 = (!b1);
    const bool b2_is0 = (!b2);
    if (b1_is0 && b2_is0) {
        // both are vertical lines
        if (c1/a1 == c2/a2) {
            // same x-intercept
            // infinite intercepts
            const largest_float temp [2] = {INFINITY, INFINITY};
            pvt::assignToArray(temp, 2);
        } else {
            // different x-intercept
            // no intercepts
            const largest_float temp [2] = {NAN, NAN};
            pvt::assignToArray(temp, 2);
        }
    } else if (b1_is0) {
        // line 1 is vertical line
        // a1x + c1 == 0
        // x == -c1/a1
        const largest_float x = -c1/a1;
        const largest_float temp [2] = {x, -a2*x/b2+c2};
        pvt::assignToArray(temp, 2); // use line 2 constants bc it is not a vertical line
    } else if (b2_is0) {
        // line 2 is vertical line
        // a2x + c2 == 0
        // x == -c2/a2
        const largest_float x = -c2/a2;
        const largest_float temp [2] = {x, -a1*x/b1+c1};
        pvt::assignToArray(temp, 2); // use line 1 constants bc it is not a vertical line
    } else {
        // neither one is vertical line
        intercept_of_2_st_lines(-a1/b1, -c1/b1, -a2/b2, -c2/b2);
    }
    return pvt::result.raw_ptr();
}

const YH::Lib::Func::maths::largest_float &YH::Lib::Func::maths::get_result (const largest_uint index) {
    return pvt::result.idx(index);
}

#undef MATHS_ACTV
#undef MATHS_UNACTV

#if defined(USE_CUSTOM_TRIGONOMETRY)
#undef sin
#undef cos
#undef tan
#undef sec
#undef csc
#undef cot
#undef asin
#undef acos
#undef atan
#undef asec
#undef acsc
#undef acot
#endif // #if defined(USE_CUSTOM_TRIGONOMETRY)

// #include "YHmathsLib_Floating_pt.cpp" project renamed as YHmathsLib_Fraction
// #include "YHmathsLib_expand_type.cpp" project abandoned 🙃
#include "YHmathsLib_Fraction.cpp"

#endif // #ifndef YHMATHSLIB_CPP