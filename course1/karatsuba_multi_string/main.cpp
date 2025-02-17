/**
 *
 * Modern C++ implementation of Karatsuba algorithm to perform multiplication of two large integers represented as strings
 *
 * (c) Copyright 2019 Clayton J. Wong ( http://www.claytonjwong.com )
 *
 **/

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

class Number
{
public:

    using Iter = string::const_reverse_iterator;

    Number() = default;
    ~Number() = default;
    explicit Number( const string& value ) : value_{ value } {}
    Number( const Number& ) = default;
    Number( Number&& ) = default;
    Number& operator=( const Number& ) = default;
    Number& operator=( Number&& ) = default;

    string value() const { return value_; }
    size_t size() const { return value_.size(); }
    bool empty() const { return value_.empty(); }
    char back() const { return value_.back(); }
    Iter crbegin() const { return value_.crbegin(); }
    Iter crend() const { return value_.crend(); }

    void push_back( const char c ){ value_.push_back( c ); }
    void pop_back(){ value_.pop_back(); }
    Number substr( size_t begin, size_t end ){ return Number({ value_.substr( begin, end ) }); }
    Number substr( size_t begin ){ return Number({ value_.substr( begin ) }); }
    void pow10( size_t N ){ value_.append( N, '0' ); }
    void pad( const size_t N ){ stringstream ss; ss << setw( N ) << setfill( '0' ) << value_; value_ = ss.str(); }

private:

    string value_;

};

Number operator*( const Number& lhs, const Number& rhs )
{
    stringstream parser{ lhs.value() + " " + rhs.value() };
    size_t x{ 0 }, y{ 0 };
    parser >> x >> y;
    return Number{ to_string( x * y ) };
}

Number operator+( Number lhs, Number rhs )
{
    Number result;
    auto carry{ false };
    auto N = max( lhs.size(), rhs.size() );
    lhs.pad( N ), rhs.pad( N );
    for( auto L{ lhs.crbegin() }, R{ rhs.crbegin() }; L != lhs.crend() && R != rhs.crend(); ++L, ++R )
    {
        auto sum = ( *L - '0' )+( *R - '0' )+( carry? 1 : 0 );
        if( sum >= 10 )
            sum %= 10,
            carry = true;
        else
            carry = false;
        result.push_back( sum + '0' ); // sums are appended to result in reverse order, so return result in reverse...
    }
    if( carry )
        result.push_back( '1' );
    return Number({ result.crbegin(), result.crend() }); // ( result in reverse )
}

Number operator-( Number lhs, Number rhs )
{
    Number result;
    auto borrow{ false };
    auto N = max( lhs.size(), rhs.size() );
    lhs.pad( N ), rhs.pad( N );
    for( auto L{ lhs.crbegin() }, R{ rhs.crbegin() }; L != lhs.crend() && R != rhs.crend(); ++L, ++R )
    {
        auto top{ *L - '0' }, bottom{ *R - '0' };
        if( borrow )
        {
            if( top == 0 )
                top = 9,
                borrow = true;
            else
                --top,
                borrow = false;
        }
        if( top < bottom )
            top += 10,
            borrow = true;
        auto diff{ top - bottom };
        result.push_back( diff + '0' ); // diffs are appended to result in reverse order, so return result in reverse...
    }
    return Number({ result.crbegin(), result.crend() }); // ( result in reverse )
}

ostream& operator<<( ostream& stream, const Number& rhs )
{
    stream << rhs.value();
    return stream;
}

class Solution
{
    Number go( Number x, Number y )
    {
        if( x.size() < 2 || y.size() < 2 )
            return x * y;
        auto
            M = min( x.size(), y.size() )+( min( x.size(), y.size() ) & 1 ), // add one for odd min size
            N = max( x.size(), y.size() ),
            pivot = N - M/2;
        x.pad( N ), y.pad( N );
        Number a = x.substr( 0, pivot ), b = x.substr( pivot ),
               c = y.substr( 0, pivot ), d = y.substr( pivot ),
               u = go( a, c ), v = go( a+b, c+d ), w = go( b, d );
        v = v - u - w;
        u.pow10( M );     // "multiply" u by 10^M
        v.pow10( M / 2 ); // "multiply" v by 10^M/2
        return( u + v + w );
    }

    Number multiply( const Number x, const Number y )
    {
        return go( x, y );
    }

public:

    string multiply( string num1, string num2 ){
        Number x{ num1 },
               y{ num2 };
        auto ans = multiply( x, y ).value();
        auto pos = ans.find_first_not_of( '0' );
        return( pos != string::npos )? ans.substr( pos ) : ans;
    }
};

int main()
{
    Solution s;
    string x{ "3141592653589793238462643383279502884197169399375105820974944592" },
           y{ "2718281828459045235360287471352662497757247093699959574966967627" };
    auto ans = s.multiply( x, y );
    cout << "answer: " << ans << endl;
    return 0;
}
