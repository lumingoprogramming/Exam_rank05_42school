#include "bigint.hpp"
#include <iostream>
#include <string>
#include <sstream>

//helper functions
std::string bigint::reverseStr(const std::string& s)
{
    return(std::string(s.rbegin(), s.rend()));
}

void    bigint::normalizeStr(std::string& s)
{
    while(s.size() > 1 && s[0] == '0')
        s.erase(0, 1);
}

std::string    bigint::addStr(const std::string& a, const std::string& b)
{
    std::string o = reverseStr(a);
    std::string p = reverseStr(b);

    if(o.size() > p.size())
        p.append(o.size() - p.size(), '0');
    if(p.size() > o.size())
        o.append(p.size() - o.size(), '0');

    std::string result;
    int carry =0;

    for(size_t i = 0; i < o.size(); i++)
    {
        int sum = o[i] - '0' + p[i] - '0' + carry;
        carry = sum / 10;
        result.push_back(char (sum % 10 + '0'));
    }

    if(carry)
        result.push_back(char (carry + '0'));
    std::string res = reverseStr(result);
    normalizeStr(res);
    return res;
}

unsigned int bigint::toUnit(const std::string& s)
{
    unsigned int n;
    std::stringstream ss(s);
    ss >> n;
    return n;
}

//constructors+ assignment +getStr
bigint::bigint(): str("0")
{}

bigint::bigint(unsigned int n)
{
    std::stringstream ss;
    ss << n;
    str = ss.str();
}

bigint::bigint(const std::string& s): str(s)
{
    normalizeStr(str);
}

bigint::bigint(const bigint& obj) : str(obj.str)
{
}

bigint::bigint(const char* a)
{
    str = std::string(a);
    normalizeStr(str);
}


bigint& bigint::operator =(const bigint& obj)
{
    if(this != &obj)
        str = obj.str;
    normalizeStr(str);
    return *this;
}

const std::string bigint::getStr() const
{
    return str;
}

//addition

bigint bigint::operator +(const bigint& obj) const
{
    bigint temp(*this);
    temp.str = addStr(str, obj.str);
    return temp;
}

bigint& bigint::operator +=(const bigint& obj)
{
    str = addStr(str, obj.str);
    return *this;
}

bigint& bigint::operator ++()
{
    *this += bigint(1);
    return *this;
}

bigint bigint::operator ++(int)
{
    bigint temp(*this);
    *this += bigint(1);
    return temp;
}

//digitshift
bigint bigint::operator<<(unsigned int n) const
{
    bigint temp(*this);
    if(temp.str != "0")
        temp.str.append( n , '0');
    return temp;
}

bigint bigint::operator>>(unsigned int n) const
{
    bigint temp(*this);
    if(n >= temp.str.size())
        temp.str = "0";
    else
        temp.str.erase( temp.str.size() - n, n);
    return temp;
}

bigint& bigint::operator<<=(unsigned int n)
{
    if(str != "0")
        str.append( n , '0');
    return *this;
}

bigint& bigint::operator>>=(unsigned int n)
{
    if(n >= str.size())
        str = "0";
    else
        str.erase(str.size() - n, n);
    return *this;
}

bigint bigint::operator<<(const bigint& obj) const
{
    return(*this << toUnit(obj.str));
}

bigint bigint::operator>>(const bigint& obj) const
{
    return(*this >> toUnit(obj.str));
}

bigint& bigint::operator<<=(const bigint& obj)
{
    return(*this <<= toUnit(obj.str));
}

bigint& bigint::operator>>=(const bigint& obj)
{
    return(*this >>= toUnit(obj.str));
}

//comparison

bool bigint::operator==(const bigint& obj) const
{
    return(str == obj.str);
}

bool bigint::operator!=(const bigint& obj) const
{
    return!(str == obj.str);
}

bool bigint::operator<(const bigint& obj) const
{
    if(str.size() != obj.str.size())
        return(str.size() < obj.str.size());
    return (str < obj.str);
}

bool bigint::operator>(const bigint& obj) const
{
    return(obj < *this);
}

bool bigint::operator<=(const bigint& obj) const
{
    return!(obj < *this);
}

bool bigint::operator>=(const bigint& obj) const
{
    return!(obj > *this);
}


std::ostream& operator<<(std::ostream& os, const bigint& obj)
{
    os << obj.getStr();
    return os;
}