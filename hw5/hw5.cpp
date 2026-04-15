#include "hw5.hpp"

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
    __m128 other_data = _mm_setr_ps(0.0f, x, y, z);
    _data = _mm_add_ps(_data, other_data);
    return *this;
}

vector4& vector4::sub(const vector4 &other)
{
    _data = _mm_sub_ps(_data, other._data);
    return *this;
}

vector4& vector4::sub(float x, float y, float z)
{
    __m128 other_data = _mm_setr_ps(0.0f, x, y, z);
    _data = _mm_sub_ps(_data, other_data);
    return *this;
}

vector4& vector4::mul(float scale)
{
    __m128 scale_vec = _mm_setr_ps(scale, scale, scale, scale);
    _data = _mm_mul_ps(_data, scale_vec);
    return *this;
}

vector4& vector4::mul(float scale, float w_scale)
{
    __m128 scale_vec = _mm_setr_ps(w_scale, scale, scale, scale);
    _data = _mm_mul_ps(_data, scale_vec);
    return *this;
}

vector4& vector4::div(float scale)
{
    __m128 scale_vec = _mm_setr_ps(scale, scale, scale, scale);
    _data = _mm_div_ps(_data, scale_vec);
    return *this;
}

vector4& vector4::div(float scale, float w_scale)
{
    __m128 scale_vec = _mm_setr_ps(w_scale, scale, scale, scale);
    _data = _mm_div_ps(_data, scale_vec);
    return *this;
}

vector4& vector4::dot(const vector4 &other)
{
    _data = _mm_dp_ps(_data, other._data, no_w_mask);
    return *this;
}

vector4& vector4::dot(float x, float y, float z)
{
    __m128 other_data = _mm_setr_ps(0.0f, x, y, z);
    _data = _mm_dp_ps(_data, other_data, no_w_mask);
    return *this;
}

float vector4::magnitude() const
{
    __m128 dp = _mm_dp_ps(_data, _data, no_w_mask);
    __m128 sqrt_dp = _mm_sqrt_ps(dp);
    return _mm_cvtss_f32(sqrt_dp);
}

float vector4::magnitude_square() const
{
    __m128 dp = _mm_dp_ps(_data, _data, no_w_mask);
    return _mm_cvtss_f32(dp);
}

vector4& vector4::normalize()
{
    float mag = magnitude();
    if (mag > 0.0f)
    {
        __m128 inv_mag = _mm_setr_ps(mag, mag, mag, mag);
        _data = _mm_div_ps(_data, inv_mag);
    }
    return *this;
}
