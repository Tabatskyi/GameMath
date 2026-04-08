#include <immintrin.h>

struct vector4
{
public:
    vector4(float x, float y, float z);
    vector4(float x, float y, float z, float w);

    vector4& add(const vector4 &other);
    vector4& add(float x, float y, float z);
    vector4& sub(const vector4 &other);
    vector4& sub(float x, float y, float z);

    vector4& mul(float scale);
    vector4& mul(float scale, float w_scale);
    vector4& div(float scale);
    vector4& div(float scale, float w_scale);

    vector4& dot(const vector4 &other);
    vector4& dot(float x, float y, float z);

    float magnitude() const;
    float magnitude_square() const;

    vector4& normalize();
public:
    float x() const;
    float y() const;
    float z() const;
    float w() const;

private:
    union
    {
        __m128 _data;
        struct
        {
            float _w, _x, _y, _z;
        };
    };
};
