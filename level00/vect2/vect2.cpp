/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumin <lumin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:16:05 by lumin             #+#    #+#             */
/*   Updated: 2026/01/07 13:48:18 by lumin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"
#include <iostream>

//constructors

vect2::vect2(): x(0), y(0) {}

vect2::vect2(int i, int p) : x(i), y(p) {}

vect2::vect2(const vect2& source) : x(source.x), y(source.y) {}

vect2&  vect2::operator=(const vect2& src)
{
    if(this != &src)
    {
        this->x = src.x;
        this->y = src.y; 
    }
    return *this;
}

vect2::~vect2() {}


int vect2::operator[](int index) const
{
    return(index == 0 ? x : y);
}

int& vect2::operator[](int index) 
{
    return(index == 0 ? x : y);
}

//Increment/Decrement

vect2& vect2::operator++()
{
    x++;
    y++;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 temp = *this;
    x++;
    y++;
    return temp;
}

vect2& vect2::operator--()
{
    x--;
    y--;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 temp = *this;
    x--;
    y--;
    return temp;
}

vect2& vect2::operator+=(const vect2& obj)
{
    x = x + obj.x;
    y = y + obj.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& obj)
{
    x = x - obj.x;
    y = y - obj.y;
    return *this;
}
/*
vect2& vect2::operator*=(const vect2& obj)
{
    x = x * obj.x;
    y = y * obj.y;
    return *this;
}*/

vect2 vect2::operator*(int num) const
{
    return(vect2 (x * num, y * num));
}

vect2& vect2::operator*=(int num)
{
    x *= num;
    y *= num;
    return(*this);
}


vect2 vect2::operator+(const vect2& obj) const
{
    return( vect2(x + obj.x, y + obj.y));
}

vect2 vect2::operator-(const vect2& obj) const
{
    return( vect2(x - obj.x, y - obj.y));
}

vect2 vect2::operator*(const vect2& obj) const
{
    return( vect2(x * obj.x, y * obj.y));
}

bool vect2::operator==(const vect2& obj) const
{
    return (x == obj.x && y == obj.y);
}

bool vect2::operator!=(const vect2& obj) const
{
    return !(x == obj.x && y == obj.y);
}

vect2 vect2::operator-() const
{
    return(vect2(-x, -y));
}

std::ostream& operator<<(std::ostream& os, const vect2& obj)
{
    os << "{" << obj[0] << ", " << obj[1] << "}";
    return os;
}

vect2 operator*(int num, const vect2& obj)
{
    return( vect2(num * obj[0], num * obj[1]));
}

/*
vect2 vect2::operator*(const vect2& obj) const
{
    return( vect2(x * obj.x, y * obj.y));
}
*/
