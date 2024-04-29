/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RGB.hpp
*/

#ifndef RGB_HPP
#define RGB_HPP

#include <sys/types.h>

class RGB {
public:
    unsigned int R = 0;
    unsigned int G = 0;
    unsigned int B = 0;

    RGB() = default;
    RGB(unsigned int R, unsigned int G, unsigned int B) : R(R), G(G), B(B) {}
    RGB(const RGB& other) = default;
    RGB(RGB&& other) = default;
    ~RGB() = default;

    RGB& operator=(const RGB& other) = default;
    RGB& operator=(RGB&& other) = default;

    bool operator==(const RGB& other) const
    {
        return R == other.R && G == other.G && B == other.B;
    }
    bool operator!=(const RGB& other) const
    {
        return R != other.R || G != other.G || B != other.B;
    }

    RGB operator+(const RGB& other) const
    {
        return RGB{static_cast<unsigned int>(R + other.R),
            static_cast<unsigned int>(G + other.G),
            static_cast<unsigned int>(B + other.B)};
    }
    RGB operator+=(const RGB& other)
    {
        R += other.R;
        G += other.G;
        B += other.B;
        return *this;
    }
    RGB operator+(double val) const
    {
        return RGB{static_cast<unsigned int>(R + val),
            static_cast<unsigned int>(G + val),
            static_cast<unsigned int>(B + val)};
    }
    RGB operator+=(double val)
    {
        R += val;
        G += val;
        B += val;
        return *this;
    }
    RGB operator-(double val) const
    {
        return RGB{static_cast<unsigned int>(R - val),
            static_cast<unsigned int>(G - val),
            static_cast<unsigned int>(B - val)};
    }
    RGB operator-=(double val)
    {
        R -= val;
        G -= val;
        B -= val;
        return *this;
    }
    RGB operator-(const RGB& other) const
    {
        return RGB{static_cast<unsigned int>(R - other.R),
            static_cast<unsigned int>(G - other.G),
            static_cast<unsigned int>(B - other.B)};
    }
    RGB operator-=(const RGB& other)
    {
        R -= other.R;
        G -= other.G;
        B -= other.B;
        return *this;
    }
    RGB operator*(const RGB& other) const
    {
        return RGB{(R * other.R),
            (G * other.G),
            (B * other.B)};
    }
    RGB operator*=(const RGB& other)
    {
        R *= other.R;
        G *= other.G;
        B *= other.B;
        return *this;
    }
    RGB operator*(double val) const
    {
        return RGB{static_cast<unsigned int>(R * val),
            static_cast<unsigned int>(G * val),
            static_cast<unsigned int>(B * val)};
    }
    RGB operator*=(double val)
    {
        R *= val;
        G *= val;
        B *= val;
        return *this;
    }
    RGB operator/(const RGB& other) const
    {
        return RGB{static_cast<unsigned int>(R / other.R),
            static_cast<unsigned int>(G / other.G),
            static_cast<unsigned int>(B / other.B)};
    }
    RGB& operator/=(const RGB& other)
    {
        R /= other.R;
        G /= other.G;
        B /= other.B;
        return *this;
    }
    RGB operator/(double val) const
    {
        return RGB{static_cast<unsigned int>(R / val),
            static_cast<unsigned int>(G / val),
            static_cast<unsigned int>(B / val)};
    }
    RGB& operator/=(double val)
    {
        R /= val;
        G /= val;
        B /= val;
        return *this;
    }
};

#endif
