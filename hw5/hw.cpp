#include "hw.hpp"

vector4::vector4(float x, float y, float z) : vector4(x, y, z, 1.0f) {}
vector4::vector4(float x, float y, float z, float w)
{
    _data = _mm_setr_ps(w, x, y, z);
}

float vector4::x() const { return _x; }
float vector4::y() const { return _y; }
float vector4::z() const { return _z; }
float vector4::w() const { return _w; }

vector4& vector4::add(const vector4 &other)
{
    _data = _mm_add_ps(_data, other._data);
    return *this;
}

vector4& vector4::add(float x, float y, float z)
{
    _data = _mm_add_ps(_data, _mm_setr_ps(0.0f, x, y, z));
    return *this;
}

vector4& vector4::sub(const vector4 &other)
{
    _data = _mm_sub_ps(_data, other._data);
    return *this;
}

vector4& vector4::sub(float x, float y, float z)
{
    _data = _mm_sub_ps(_data, _mm_setr_ps(0.0f, x, y, z));
    return *this;
}