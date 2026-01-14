/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumin <lumin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:17:04 by lumin             #+#    #+#             */
/*   Updated: 2025/12/10 13:41:32 by lumin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  VECT2_HPP
#define VEXT2_HPP
#include <iostream>
#include <string>

class vect2
{
    private:
        int x;
        int y;
  
    public:
        vect2();
        vect2(int i, int p);
        vect2(const vect2& source);
        vect2&  operator=(const vect2& src);
        ~vect2();
        int operator[](int index) const;
        int& operator[](int index);
        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);
        vect2& operator+=(const vect2& obj);
        vect2& operator-=(const vect2& obj);
        vect2& operator*=(const vect2& obj);
        
        vect2 operator+(const vect2& obj) const;
        vect2 operator-(const vect2& obj) const;
        vect2 operator*(const vect2& obj) const;
        bool operator==(const vect2& obj) const;
        bool operator!=(const vect2& obj) const;
        vect2 operator-() const;
        vect2 operator*(int num) const;
        vect2& operator*=(int num);
};

std::ostream& operator<<(std::ostream& os, const vect2& obj);
vect2 operator*(int num, const vect2& obj);

#endif