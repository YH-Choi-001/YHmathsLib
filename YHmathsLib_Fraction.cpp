#ifndef YHMATHSLIB_FRACTION_CPP
#define YHMATHSLIB_FRACTION_CPP

#include "YHmathsLib_Fraction.h"

#ifndef YHMATHSLIB_CPP
#include "YHmathsLib.cpp"
#endif // #ifndef YHMATHSLIB_CPP

void YH::Lib::Fraction::myself_to_inf () {
    special_states = INFINITY_FLOATING;
    upper_val = 1;
    lower_val = 0;
}

void YH::Lib::Fraction::myself_to_nan () {
    special_states = NOT_A_NUM_FLOATING;
    upper_val = 0;
    lower_val = 0;
}

YH::Lib::Fraction YH::Lib::Fraction::create_nan_obj () const {
    return YH::Lib::Func::maths::nan_obj();
}

YH::Lib::Fraction YH::Lib::Fraction::create_inf_obj () const {
    return YH::Lib::Func::maths::inf_obj();
}

#if defined(FRACTION_CONSTRUCTOR)
    YH::Lib::Fraction::Fraction () :
    upper_val(0),
    lower_val(0),
    special_states(NORMAL_FLOATING)
    { }

    YH::Lib::Fraction::Fraction (const Func::maths::largest_float val) :
    upper_val(0),
    lower_val(0),
    special_states(NORMAL_FLOATING)
    {
        assign (val);
    }

    YH::Lib::Fraction::Fraction (const Func::maths::largest_int init_upper_val, const Func::maths::largest_int init_lower_val) :
    upper_val(init_upper_val),
    lower_val(init_lower_val),
    special_states(NORMAL_FLOATING)
    {
        if (lower_val == 0 && upper_val != 0) {
            myself_to_inf();
        } else {
            if (lower_val < 0) {
                upper_val = -upper_val;
                lower_val = -lower_val;
            }
            upper_val = YH::Lib::Func::maths::fract_simp_int(upper_val, lower_val)[0];
            lower_val = YH::Lib::Func::maths::get_result(1);
        }
    }

    YH::Lib::Fraction::Fraction (const Fraction &another_floating_pt) :
    upper_val(another_floating_pt.numerator()),
    lower_val(another_floating_pt.denominator()),
    special_states(another_floating_pt.state())
    {
        upper_val = YH::Lib::Func::maths::fract_simp_int(upper_val, lower_val)[0];
        lower_val = YH::Lib::Func::maths::get_result(1);
    }

    YH::Lib::Fraction::~Fraction () { }
#endif // #if defined(FRACTION_CONSTRUCTOR)

#if defined(FRACTION_BASIC_METHOD)
    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::numerator () const {
        return upper_val;
    }

    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::denominator () const {
        return lower_val;
    }

    YH::Lib::Fraction_states YH::Lib::Fraction::state () const {
        return special_states;
    }

    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::rnddn () const {
        // return static_cast<long long>(upper_val / lower_val);
        if (this->special_states == INFINITY_FLOATING)
            return static_cast<Func::maths::largest_int>(0x7FFEE245EAC0LL);
        else if (this->special_states == NOT_A_NUM_FLOATING)
            return 0;
        return upper_val / lower_val;
    }

    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::rndup () const {
        // (   (x > 0) ? ( RND_DOWN(x) + (x - RND_DOWN(x) > VALUABLE_DIFF) ) : ( RND_DOWN(x) - (RND_DOWN(x) - x > VALUABLE_DIFF) )   )
        //
        // if upper_val % lower_val > 0
            // if upper_val > 0
                // return upper_val / lower_val + 1
            // else
                // return upper_val / lower_val - 1
        // else
            // return upper_val / lower_val
        // (upper_val % lower_val) ? (upper_val > 0 ? 1 : -1) : (upper_val / lower_val)
        // (upper_val / lower_val) + (upper_val % lower_val) * (upper_val > 0 ? 1 : -1)
        if (this->special_states == INFINITY_FLOATING)
            return static_cast<Func::maths::largest_int>(0x7FFEE245EAC0);
        else if (this->special_states == NOT_A_NUM_FLOATING)
            return 0;
        return (upper_val / lower_val) + (upper_val % lower_val) * (upper_val > 0 ? 1 : -1);
    }

    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::floor () const {
        // (   RND_DOWN(x) - (x < 0.0L && x < RND_DOWN(x))   )
        // if upper_val >= 0
            // return rnd_dn() or you may say upper_val / lower_val
        // else // upper_val < 0
            // if upper_val % lower_val
                // return rnd_dn() - 1
            // else
                // return rnd_dn()
        if (this->special_states == INFINITY_FLOATING)
            return static_cast<Func::maths::largest_int>(0x7FFEE245EAC0);
        else if (this->special_states == NOT_A_NUM_FLOATING)
            return 0;
        return (upper_val / lower_val) - ( (upper_val < 0) && (upper_val % lower_val) );
    }

    YH::Lib::Func::maths::largest_int YH::Lib::Fraction::ceil () const {
        // (   RND_DOWN(x) + (x > 0.0L && x > RND_DOWN(x))   )
        if (this->special_states == INFINITY_FLOATING)
            return static_cast<Func::maths::largest_int>(0x7FFEE245EAC0);
        else if (this->special_states == NOT_A_NUM_FLOATING)
            return 0;
        return (upper_val / lower_val) + ( (upper_val > 0) && (upper_val % lower_val) );
    }

    YH::Lib::Func::maths::largest_float YH::Lib::Fraction::floated_num () const {
        if (this->special_states == INFINITY_FLOATING)
            return INFINITY;
        else if (this->special_states == NOT_A_NUM_FLOATING)
            return NAN;
        return static_cast<Func::maths::largest_float>(upper_val) / static_cast<Func::maths::largest_float>(lower_val);
    }
#endif // #if defined(FRACTION_BASIC_METHOD)

#if defined(FRACTION_ASSIGN_METHOD)
    YH::Lib::Fraction &YH::Lib::Fraction::assign (const Func::maths::largest_float rhs) {
        if (rhs == INFINITY) {
            myself_to_inf();
        } else if (rhs == NAN) {
            myself_to_nan();
        }
        else {
            upper_val = YH::Lib::Func::maths::fract_simp(rhs, 1.0)[0];
            lower_val = YH::Lib::Func::maths::get_result(1);
            special_states = NORMAL_FLOATING;
        }
        return *this;
    }

    YH::Lib::Fraction &YH::Lib::Fraction::assign (const Func::maths::largest_int assign_upper_val, const Func::maths::largest_int assign_lower_val) {
        if (assign_lower_val == 0 && assign_upper_val != 0) {
            myself_to_inf();
        } else {
            special_states = NORMAL_FLOATING;
            if (assign_lower_val < 0) {
                upper_val = - assign_upper_val;
                lower_val = - assign_lower_val;
            } else {
                upper_val = assign_upper_val;
                lower_val = assign_lower_val;
            }
            upper_val = YH::Lib::Func::maths::fract_simp_int(upper_val, lower_val)[0];
            lower_val = YH::Lib::Func::maths::get_result(1);
        }
        return *this;
    }

    YH::Lib::Fraction &YH::Lib::Fraction::assign (const YH::Lib::Fraction &rhs) {
        special_states = rhs.state();
        if (special_states == NORMAL_FLOATING) {
            upper_val = YH::Lib::Func::maths::fract_simp_int(rhs.numerator(), rhs.denominator())[0];
            lower_val = YH::Lib::Func::maths::get_result(1);
        } else {
            upper_val = rhs.numerator();
            lower_val = rhs.denominator();
        }
        return *this;
    }
#endif // #if defined(FRACTION_ASSIGN_METHOD)

// x_myself
// or arithmetics that involves assignment
#if defined(FRACTION_ARITHMETIC_AND_ASSIGN_METHOD)

// for member-only x_myself functions only
#define FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(x_myself_funcname) \
    YH::Lib::Fraction &YH::Lib::Fraction::x_myself_funcname (const Func::maths::largest_float rhs) { \
        return this->x_myself_funcname(YH::Lib::Func::maths::to_floating_pt(rhs)); \
    } \
    YH::Lib::Fraction &YH::Lib::Fraction::x_myself_funcname (const Func::maths::largest_int rhs_numerator, const Func::maths::largest_int rhs_denominator) { \
        YH::Lib::Fraction rhs (rhs_numerator, rhs_denominator); \
        return this->x_myself_funcname(rhs); \
    }

    // add myself
    YH::Lib::Fraction &YH::Lib::Fraction::add_myself (const YH::Lib::Fraction &rhs) {
        if (this->special_states == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
            myself_to_nan();
        } else if (this->special_states == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
            myself_to_inf();
        } else {
            const Func::maths::largest_int rhs_low = rhs.denominator();
            const Func::maths::largest_int base = YH::Lib::Func::maths::lcm(this->lower_val, rhs_low);
            this->assign(this->upper_val * (base / this->lower_val) + rhs.numerator() * (base / rhs_low), base);
        }
        return *this;
    }
    FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(add_myself);

    // sub myself
    YH::Lib::Fraction &YH::Lib::Fraction::sub_myself (const YH::Lib::Fraction &rhs) {
        if (this->special_states == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
            myself_to_nan();
        } else if (this->special_states == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
            myself_to_inf();
        } else {
            const Func::maths::largest_int rhs_low = rhs.denominator();
            const Func::maths::largest_int base = YH::Lib::Func::maths::lcm(this->lower_val, rhs_low);
            this->assign(this->upper_val * (base / this->lower_val) - rhs.numerator() * (base / rhs_low), base);
        }
        return *this;
    }
    FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(sub_myself);

    // mul myself
    YH::Lib::Fraction &YH::Lib::Fraction::mul_myself (const YH::Lib::Fraction &rhs) {
        if (this->special_states == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
            myself_to_nan();
        } else if (this->special_states == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
            myself_to_inf();
        } else {
            this->assign(this->upper_val * rhs.numerator(), this->lower_val * rhs.denominator());
        }
        return *this;
    }
    FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(mul_myself);

    // div myself
    YH::Lib::Fraction &YH::Lib::Fraction::div_myself (const YH::Lib::Fraction &rhs) {
        if (this->special_states == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
            myself_to_nan();
        } else if (this->special_states == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
            myself_to_inf();
        } else {
            this->assign(this->upper_val * rhs.denominator(), this->lower_val * rhs.numerator());
        }
        return *this;
    }
    FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(div_myself);

    // mod myself
    YH::Lib::Fraction &YH::Lib::Fraction::mod_myself (const YH::Lib::Fraction &rhs) {
        if (this->special_states == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
            myself_to_nan();
        } else if (this->special_states == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
            myself_to_inf();
        } else {
            const Func::maths::largest_int rhs_up  = rhs.numerator(); // 3
            const Func::maths::largest_int rhs_low = rhs.denominator(); // 1
            // const Func::maths::largest_int base = YH::Lib::Func::maths::lcm(lhs_low, rhs_low);
            YH::Lib::Func::maths::fract_simp_int(this->upper_val * rhs_low, this->lower_val * rhs_up);
            YH::Lib::Fraction b_times_rnddned_a_over_b ( rhs_up * ( static_cast<Func::maths::largest_int>(Func::maths::get_result(0)) / static_cast<Func::maths::largest_int>(Func::maths::get_result(1)) ), rhs_low );
            // sub(*this, b_times_rnddned_a_over_b);
            sub_myself(b_times_rnddned_a_over_b);
        }
        return *this;
    }
    FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION(mod_myself);

    // increment myself
    YH::Lib::Fraction &YH::Lib::Fraction::increment_myself () {
        YH::Lib::Func::maths::fract_simp_int(this->upper_val + this->lower_val, this->lower_val);
        this->upper_val = static_cast<Func::maths::largest_int>(YH::Lib::Func::maths::get_result(0));
        this->lower_val = static_cast<Func::maths::largest_int>(YH::Lib::Func::maths::get_result(1));
        return *this;
    }

    // decrement myself
    YH::Lib::Fraction &YH::Lib::Fraction::decrement_myself () {
        YH::Lib::Func::maths::fract_simp_int(this->upper_val - this->lower_val, this->lower_val);
        this->upper_val = static_cast<Func::maths::largest_int>(YH::Lib::Func::maths::get_result(0));
        this->lower_val = static_cast<Func::maths::largest_int>(YH::Lib::Func::maths::get_result(1));
        return *this;
    }

    #undef FRACTION_ARITHMETIC_AND_ASSIGN_METHOD_EXTENSION

#endif // #if defined(FRACTION_ARITHMETIC_AND_ASSIGN_METHOD)

// operators involving assignment, including =, +=, -=, *=, /=, %=, ++, --
#if defined(FRACTION_METHOD_OPERATORS)
    // for assignment involved methods only
    #define FRACTION_METHOD_OPERATORS_EXTENSION(operator,function_name) \
        YH::Lib::Fraction &YH::Lib::Fraction::operator    (const Fraction &rhs) { \
            return this->function_name(rhs); \
        } \
        YH::Lib::Fraction &YH::Lib::Fraction::operator    (const Func::maths::largest_float rhs) { \
            return this->function_name(rhs); \
        }

    FRACTION_METHOD_OPERATORS_EXTENSION(operator  =,assign)
    FRACTION_METHOD_OPERATORS_EXTENSION(operator +=,add_myself)
    FRACTION_METHOD_OPERATORS_EXTENSION(operator -=,sub_myself)
    FRACTION_METHOD_OPERATORS_EXTENSION(operator *=,mul_myself)
    FRACTION_METHOD_OPERATORS_EXTENSION(operator /=,div_myself)
    FRACTION_METHOD_OPERATORS_EXTENSION(operator %=,mod_myself)

    YH::Lib::Fraction &YH::Lib::Fraction::operator ++ () {
        return this->increment_myself();
    }

    YH::Lib::Fraction &YH::Lib::Fraction::operator -- () {
        return this->decrement_myself();
    }

    #undef FRACTION_METHOD_OPERATORS_EXTENSION

#endif // #if defined(FRACTION_METHOD_OPERATORS)

// reversed values such as !(), -()
// operators const
#if defined(FRACTION_METHOD_OPERATORS_CONST)
    // auto convert to bool value
    YH::Lib::Fraction::operator bool () const {
        return ( (this->special_states == NOT_A_NUM_FLOATING) || (this->special_states == INFINITY_FLOATING) || (this->upper_val) );
    }

    // boolean reverse
    bool YH::Lib::Fraction::operator ! () const {
        // if (this->special_states == NOT_A_NUM_FLOATING)
        //     return false;
        // if (this->special_states == INFINITY_FLOATING)
        //     return false;
        // return !!this->upper_val;
        // != NAN && != INF && (!!upper_val)
        // return (this->special_states != NOT_A_NUM_FLOATING) && (this->special_states != INFINITY_FLOATING) && (!!upper_val);
        return !( (this->special_states == NOT_A_NUM_FLOATING) || (this->special_states == INFINITY_FLOATING) || (this->upper_val) );
    }

    // convert the fraction to a negative number
    YH::Lib::Fraction YH::Lib::Fraction::operator - () const {
        YH::Lib::Fraction to_return (-(this->upper_val), this->lower_val);
        return to_return;
    }
#endif // #if defined(FRACTION_OPERATORS_CONST)

#if defined(FRACTION_BASIC_FUNC)
    YH::Lib::Fraction YH::Lib::Func::maths::nan_obj () {
        YH::Lib::Fraction to_return (static_cast<largest_float>(NAN));
        return to_return;
    }

    YH::Lib::Fraction YH::Lib::Func::maths::inf_obj () {
        YH::Lib::Fraction to_return (1, 0);
        return to_return;
    }

    YH::Lib::Fraction YH::Lib::Func::maths::to_floating_pt (const largest_float val) {
        if (val == INFINITY) {
            return inf_obj();
        } else if (val == NAN) {
            return nan_obj();
        }
        else {
            YH::Lib::Func::maths::fract_simp(val, 1.0);
            YH::Lib::Fraction to_return (static_cast<largest_int>(get_result(0)), static_cast<largest_int>(get_result(1)));
            return to_return;
        }
    }
#endif // #if defined(FRACTION_BASIC_FUNC)

#define FRACTION_FUNC_EXTENSION(function_name,return_type) \
        return_type YH::Lib::Func::maths::function_name (const YH::Lib::Fraction &lhs, const largest_float rhs) { \
            return YH::Lib::Func::maths::function_name(lhs, YH::Lib::Func::maths::to_floating_pt(rhs)); \
        } \
        return_type YH::Lib::Func::maths::function_name (const largest_float lhs, const YH::Lib::Fraction &rhs) { \
            return YH::Lib::Func::maths::function_name(YH::Lib::Func::maths::to_floating_pt(lhs), rhs); \
        } \
        return_type YH::Lib::Func::maths::function_name (const YH::Lib::Fraction &lhs, const largest_int rhs_numerator, const largest_int rhs_denominator) { \
            YH::Lib::Fraction rhs (rhs_numerator, rhs_denominator); \
            return YH::Lib::Func::maths::function_name(lhs, rhs); \
        } \
        return_type YH::Lib::Func::maths::function_name (const largest_int lhs_numerator, const largest_int lhs_denominator, const YH::Lib::Fraction &rhs) { \
            YH::Lib::Fraction lhs (lhs_numerator, lhs_denominator); \
            return YH::Lib::Func::maths::function_name(lhs, rhs); \
        }

// calculation of +, -, *, /, %
#if defined(FRACTION_ARITHMETIC_FUNC)

    // for non-member add, sub, mul, div, mod functions only
    #define FRACTION_ARITHMETIC_EXTENSION(function_name) \
        FRACTION_FUNC_EXTENSION(function_name,YH::Lib::Fraction)
        // YH::Lib::Fraction YH::Lib::Func::maths::func_name (const YH::Lib::Fraction &lhs, const long double rhs) {
        //     return YH::Lib::Func::maths::func_name(lhs, YH::Lib::Func::maths::to_floating_pt(rhs));
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::func_name (const long double lhs, const YH::Lib::Fraction &rhs) {
        //     return YH::Lib::Func::maths::func_name(YH::Lib::Func::maths::to_floating_pt(lhs), rhs);
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::func_name (const YH::Lib::Fraction &lhs, const long long rhs_numerator, const long long rhs_denominator) {
        //     YH::Lib::Fraction rhs (rhs_numerator, rhs_denominator);
        //     return YH::Lib::Func::maths::func_name(lhs, rhs);
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::func_name (const long long lhs_numerator, const long long lhs_denominator, const YH::Lib::Fraction &rhs) {
        //     YH::Lib::Fraction lhs (lhs_numerator, lhs_denominator);
        //     return YH::Lib::Func::maths::func_name(lhs, rhs);
        // }

    #if defined(FRACTION_ADD)
        YH::Lib::Fraction YH::Lib::Func::maths::add (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
                return nan_obj();
            } else if (lhs.state() == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
                return inf_obj();
            } else {
                const largest_int lhs_low = lhs.denominator();
                const largest_int rhs_low = rhs.denominator();
                const largest_int base = YH::Lib::Func::maths::lcm(lhs_low, rhs_low);
                YH::Lib::Fraction to_return (lhs.numerator() * (base / lhs_low) + rhs.numerator() * (base / rhs_low), base);
                return to_return;
            }
        }
        // YH::Lib::Fraction YH::Lib::Func::maths::add (const YH::Lib::Fraction &lhs, const long double rhs) {
        //     return YH::Lib::Func::maths::add(lhs, YH::Lib::Func::maths::to_floating_pt(rhs));
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::add (const long double lhs, const YH::Lib::Fraction &rhs) {
        //     return YH::Lib::Func::maths::add(YH::Lib::Func::maths::to_floating_pt(lhs), rhs);
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::add (const YH::Lib::Fraction &lhs, const long long rhs_numerator, const long long rhs_denominator) {
        //     YH::Lib::Fraction rhs (rhs_numerator, rhs_denominator);
        //     return YH::Lib::Func::maths::add(lhs, rhs);
        // }
        // YH::Lib::Fraction YH::Lib::Func::maths::add (const long long lhs_numerator, const long long lhs_denominator, const YH::Lib::Fraction &rhs) {
        //     YH::Lib::Fraction lhs (lhs_numerator, lhs_denominator);
        //     return YH::Lib::Func::maths::add(lhs, rhs);
        // }
        FRACTION_ARITHMETIC_EXTENSION(add)
    #endif // #if defined(FRACTION_ADD)

    #if defined(FRACTION_SUB)
        YH::Lib::Fraction YH::Lib::Func::maths::sub (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
                return nan_obj();
            } else if (lhs.state() == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
                return inf_obj();
            } else {
                const largest_int lhs_low = lhs.denominator();
                const largest_int rhs_low = rhs.denominator();
                const largest_int base = YH::Lib::Func::maths::lcm(lhs_low, rhs_low);
                YH::Lib::Fraction to_return (lhs.numerator() * (base / lhs_low) - rhs.numerator() * (base / rhs_low), base);
                return to_return;
            }
        }
        FRACTION_ARITHMETIC_EXTENSION(sub)
    #endif // #if defined(FRACTION_SUB)

    #if defined(FRACTION_MUL)
        YH::Lib::Fraction YH::Lib::Func::maths::mul (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
                return nan_obj();
            } else if (lhs.state() == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
                return inf_obj();
            } else {
                YH::Lib::Fraction to_return (lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
                return to_return;
            }
        }
        FRACTION_ARITHMETIC_EXTENSION(mul)
    #endif // #if defined(FRACTION_MUL)

    #if defined(FRACTION_DIV)
        YH::Lib::Fraction YH::Lib::Func::maths::div (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
                return nan_obj();
            } else if (lhs.state() == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
                return inf_obj();
            } else {
                YH::Lib::Fraction to_return (lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
                return to_return;
            }
        }
        FRACTION_ARITHMETIC_EXTENSION(div)
    #endif // #if defined(FRACTION_DIV)

    #if defined(FRACTION_MOD)
        // definition of mod:
        // a % b == c
        //     a == b * n + c
        //     c == a - b * n
        // where n == rnddn(a/b)
        //     c == a - ( b * rnddn(a / b) )
        //
        // a / b
        // rnddn(a / b)
        // b * rnddn(a / b)
        // a - ( b * rnddn(a / b) )
        YH::Lib::Fraction YH::Lib::Func::maths::mod (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) {
                return nan_obj();
            } else if (lhs.state() == INFINITY_FLOATING || rhs.state() == INFINITY_FLOATING) {
                return inf_obj();
            } else {
                const largest_int lhs_up  = lhs.numerator(); // 5
                const largest_int rhs_up  = rhs.numerator(); // 3
                const largest_int lhs_low = lhs.denominator(); // 1
                const largest_int rhs_low = rhs.denominator(); // 1
                // const largest_int base = YH::Lib::Func::maths::lcm(lhs_low, rhs_low);
                YH::Lib::Func::maths::fract_simp_int(lhs_up * rhs_low, lhs_low * rhs_up);
                YH::Lib::Fraction b_times_rnddned_a_over_b ( rhs_up * static_cast<largest_int>(get_result(0)) / static_cast<largest_int>(get_result(1)), rhs_low );
                return sub(lhs, b_times_rnddned_a_over_b);
                // (lhs.num % rhs.num) / base
                // 1/3 % 1/4 ...
                // 1/3 / 1/4 == 1/3 * 4/1 == 4/3
                // attention:
                    // only when a < 0, modded result < 0
                // if a % b == c,
                    // b * r + c == a
                    // c == a - b * r
                // 5 % 3 (== 2) == 5 - 3 * rnddn(5 ÷ 3), statement is true
                // a % b == a - b * rnddn(a/b)
                // if a >= 0:
                    // r == rnddn(a/b)
                // 5 % -3 (== 2) == 5 - -3 * rnddn(5÷ -3), statement is true
                // -5 % 3 == -2 == -5 - 3 * rnddn(-5÷3), statement is true
                // -5 % -3 == -2 == -5 - -3 * rnddn(-5÷-3), statement is true
                // 7/8 % 3/8 == 7/8 - rnddn(7/8 ÷ 3/8) * 3/8
                //           == 7/8 - rnddn(7/3) * 3/8
                //           == 7/8 - 2 * 3/8
                //           == 7/8 - 6/8
                //           == 1/8
                // 14/16 % 9/24 == 14/16 - rnddn(14/16 ÷ 9/24) * 9/24
                //              == 14/16 - rnddn(14/16 * 24/9) * 9/24
                //              == 14/16 - rnddn(336/144) * 9/24
                //              == 14/16 - 2 * 9/24
                //              == 14/16 - 18/24
                //              == find base
                //              == 42/48 - 36/48
                //              == 6/48
                //              == 1/8
                // 7/8 % -3/8 == 7/8 - rnddn(7/8 ÷ -3/8) * 3/8
                //            == 7/8 - rnddn(-7/3) * 3/8
                //            == 7/8 - -2 * 3/8
                //            == 7/8 - -6/8
                //            == 13/8
                //
                // 7/8 % 3/8 == 7/8 % 6/16 == 14/16 % 9/24
                // 7/8 / 3/8 == 7/8 * 8/3 == 7/3 == 2...1
                // 7/8 / 6/16 == 7/8 * 16/6 == 7 * 2/6 == 7 * 1/3 == 7/3 == 2...1
                // 14/16 / 9/24 == 14/16 * 24/9 == 
            }
        }
        FRACTION_ARITHMETIC_EXTENSION(mod)
    #endif // #if defined(FRACTION_MOD)

    #undef FRACTION_ARITHMETIC_EXTENSION

#endif // #if defined(FRACTION_ARITHMETIC_FUNC)

// comparison of ==, !=, <, >, <=, >=
#if defined(FRACTION_CMP_FUNC)

    // for non-member equal_to, not_equal_to, less_than, greater_than, less_than_or_equal_to, greater_than_or_equal_to functions only
    #define FRACTION_CMP_EXTENSION(function_name) \
        FRACTION_FUNC_EXTENSION(function_name,bool)
        // bool YH::Lib::Func::maths::func_name (const YH::Lib::Fraction &lhs, const long double rhs) {
        //     return YH::Lib::Func::maths::func_name(lhs, YH::Lib::Func::maths::to_floating_pt(rhs));
        // }
        // bool YH::Lib::Func::maths::func_name (const long double lhs, const YH::Lib::Fraction &rhs) {
        //     return YH::Lib::Func::maths::func_name(YH::Lib::Func::maths::to_floating_pt(lhs), rhs);
        // }
        // bool YH::Lib::Func::maths::func_name (const YH::Lib::Fraction &lhs, const long long rhs_numerator, const long long rhs_denominator) {
        //     YH::Lib::Fraction rhs (rhs_numerator, rhs_denominator);
        //     return YH::Lib::Func::maths::func_name(lhs, rhs);
        // }
        // bool YH::Lib::Func::maths::func_name (const long long lhs_numerator, const long long lhs_denominator, const YH::Lib::Fraction &rhs) {
        //     YH::Lib::Fraction lhs (lhs_numerator, lhs_denominator);
        //     return YH::Lib::Func::maths::func_name(lhs, rhs);
        // }

    // ==
    #if defined(FRACTION_EQUAL_TO)
        bool YH::Lib::Func::maths::equal_to (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return false;
            return (lhs.numerator() == rhs.numerator()) && (lhs.denominator() == rhs.denominator());
        }
        FRACTION_CMP_EXTENSION(equal_to)
    #endif // #if defined(FRACTION_EQUAL_TO)

    // !=
    #if defined(FRACTION_NOT_EQUAL_TO)
        bool YH::Lib::Func::maths::not_equal_to (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return true;
            return (lhs.numerator() != rhs.numerator()) || (lhs.denominator() != rhs.denominator());
        }
        FRACTION_CMP_EXTENSION(not_equal_to)
    #endif // #if defined(FRACTION_NOT_EQUAL_TO)

    // <
    #if defined(FRACTION_LESS_THAN)
        bool YH::Lib::Func::maths::less_than (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return false;
            const largest_int base = lcm(lhs.denominator(), rhs.denominator());
            return ( lhs.numerator() * (base / lhs.denominator()) ) < ( rhs.numerator() * (base / rhs.denominator()) );
        }
        FRACTION_CMP_EXTENSION(less_than)
    #endif // #if defined(FRACTION_LESS_THAN)

    // >
    #if defined(FRACTION_GREATER_THAN)
        bool YH::Lib::Func::maths::greater_than (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return false;
            const largest_int base = lcm(lhs.denominator(), rhs.denominator());
            return ( lhs.numerator() * (base / lhs.denominator()) ) > ( rhs.numerator() * (base / rhs.denominator()) );
        }
        FRACTION_CMP_EXTENSION(greater_than)
    #endif // #if defined(FRACTION_GREATER_THAN)

    // <=
    #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)
        bool YH::Lib::Func::maths::less_than_or_equal_to (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return false;
            const largest_int base = lcm(lhs.denominator(), rhs.denominator());
            return ( lhs.numerator() * (base / lhs.denominator()) ) <= ( rhs.numerator() * (base / rhs.denominator()) );
        }
        FRACTION_CMP_EXTENSION(less_than_or_equal_to)
    #endif // #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)

    // >=
    #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
        bool YH::Lib::Func::maths::greater_than_or_equal_to (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) {
            if (lhs.state() == NOT_A_NUM_FLOATING || rhs.state() == NOT_A_NUM_FLOATING) return false;
            const largest_int base = lcm(lhs.denominator(), rhs.denominator());
            return ( lhs.numerator() * (base / lhs.denominator()) ) >= ( rhs.numerator() * (base / rhs.denominator()) );
        }
        FRACTION_CMP_EXTENSION(greater_than_or_equal_to)
    #endif // #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)

    #undef FRACTION_CMP_EXTENSION

#endif // #if defined(FRACTION_CMP_FUNC)

#if defined(FRACTION_NONMEM_OPERATORS)

    // for non-member operators only
    #define FRACTION_NONMEN_OPERATORS_EXTENSION(operator,function_name,return_type) \
        return_type YH::Lib::Func::maths::operator (const YH::Lib::Fraction &lhs, const YH::Lib::Fraction &rhs) { \
            return function_name(lhs,rhs); \
        } \
        return_type YH::Lib::Func::maths::operator (const YH::Lib::Fraction &lhs, const largest_float rhs) { \
            return function_name(lhs,rhs); \
        } \
        return_type YH::Lib::Func::maths::operator (const largest_float lhs, const YH::Lib::Fraction &rhs) { \
            return function_name(lhs,rhs); \
        }

    #if defined(FRACTION_ARITHMETIC_FUNC)
        // +
        #if defined(FRACTION_ADD)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator +, add, YH::Lib::Fraction)
        #endif // #if defined(FRACTION_ADD)

        // -
        #if defined(FRACTION_SUB)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator -, sub, YH::Lib::Fraction)
        #endif // #if defined(FRACTION_SUB)

        // *
        #if defined(FRACTION_MUL)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator *, mul, YH::Lib::Fraction)
        #endif // #if defined(FRACTION_MUL)

        // /
        #if defined(FRACTION_DIV)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator /, div, YH::Lib::Fraction)
        #endif // #if defined(FRACTION_DIV)

        // %
        #if defined(FRACTION_MOD)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator %, mod, YH::Lib::Fraction)
        #endif // #if defined(FRACTION_MOD)
    #endif // #if defined(FRACTION_ARITHMETIC_FUNC)

    #if defined(FRACTION_CMP_FUNC)
        // ==
        #if defined(FRACTION_EQUAL_TO)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator ==, equal_to, bool)
        #endif // #if defined(FRACTION_EQUAL_TO)

        // !=
        #if defined(FRACTION_NOT_EQUAL_TO)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator !=, not_equal_to, bool)
        #endif // #if defined(FRACTION_NOT_EQUAL_TO)

        // <
        #if defined(FRACTION_LESS_THAN)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator < , less_than, bool)
        #endif // #if defined(FRACTION_LESS_THAN)

        // >
        #if defined(FRACTION_GREATER_THAN)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator > , greater_than, bool)
        #endif // #if defined(FRACTION_GREATER_THAN)

        // <=
        #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator <=, less_than_or_equal_to, bool)
        #endif // #if defined(FRACTION_LESS_THAN_OR_EQUAL_TO)

        // >=
        #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
            FRACTION_NONMEN_OPERATORS_EXTENSION(operator >=, greater_than_or_equal_to, bool)
        #endif // #if defined(FRACTION_GREATER_THAN_OR_EQUAL_TO)
    #endif // #if defined(FRACTION_CMP_FUNC)

    #undef FRACTION_NONMEM_OPERATORS_EXTENSION

#endif // #if defined(FRACTION_NONMEM_OPERATORS)

#undef FRACTION_FUNC_EXTENSION

#endif // #ifndef YHMATHSLIB_FRACTION_CPP