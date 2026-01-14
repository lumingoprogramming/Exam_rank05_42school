#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint
{
    private:
        std::string str;
        static std::string reverseStr(const std::string& s);
        static void    normalizeStr(std::string& s);
        static std::string    addStr(const std::string& a, const std::string& b);
        static unsigned int toUnit(const std::string& s);

    public:
        bigint(unsigned int n);
        bigint(const std::string& s);
        bigint();
        bigint(const char *a);
        bigint(const bigint& obj);
        bigint&  operator =(const bigint& obj);
        const std::string  getStr() const;

        bigint  operator +(const bigint& obj) const;
        bigint&  operator +=(const bigint& obj);
        bigint&  operator ++();
        bigint  operator ++(int);

        bigint  operator<<(unsigned int n) const;
        bigint  operator>>(unsigned int n) const;
        bigint&  operator<<=(unsigned int n);
        bigint&  operator>>=(unsigned int n);
        bigint  operator<<(const bigint& obj) const;
        bigint  operator>>(const bigint& obj) const;
        bigint&  operator<<=(const bigint& obj);
        bigint&  operator>>=(const bigint& obj);
        bool  operator==(const bigint& obj) const;
        bool  operator!=(const bigint& obj) const;
        bool  operator<(const bigint& obj) const;
        bool  operator>(const bigint& obj) const;
        bool  operator<=(const bigint& obj) const;
        bool  operator>=(const bigint& obj) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

#endif