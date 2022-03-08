#include "Vector3.h"

float Vector3::Magnitude()
{   
    int xx = x*x;
    if(xx < 0)
        xx * -1;

    int yy = y*y;
    if(yy < 0)
        yy * -1;

    int zz = z*z;
    if(zz < 0)
        zz * -1;
    return std::sqrtf(xx + yy + zz);
}

float Vector3::sqrMagnitude()
{
    return (x * x + y * y + z * z);
}

Vector3 Vector3::Normalize()
{

    float m = Magnitude();
    if(m!= 0)
    {
        x = x / m;
        y = y / m;
        z = z / m;
    }

    return Vector3(x,y,z);
}

Vector3 Vector3::sqrNormalize()
{
    float m = sqrMagnitude();
    x = x / m;
    y = y / m;
    z = z / m;
    return Vector3(x, y, z);
}

bool Vector3::operator==(const Vector3& otherv) const
{
    if (otherv.x != x && otherv.y != y && otherv.z != z)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Vector3::operator!=(const Vector3& otherv) const
{
    return !(*this == otherv);
}

Vector3& Vector3::operator=(const Vector3& otherv)
{
    x = otherv.x;
    y = otherv.y;
    z = otherv.z;

    return *this;
}

Vector3& Vector3::operator+(const Vector3& otherv)
{
    int nx,ny,nz;
    nx = x + otherv.x;
    ny = y += otherv.y;
    nz = z += otherv.z;
    Vector3 nv(nx,ny,nz);
    return nv;
}

Vector3& Vector3::operator-(const Vector3& otherv)
{
    int nx, ny, nz;
    nx = x - otherv.x;
    ny = y - otherv.y;
    nz = z - otherv.z;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator*(const Vector3& otherv)
{
    int nx, ny, nz;
    nx = x * otherv.x;
    ny = y * otherv.y;
    nz = z * otherv.z;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator/(const Vector3& otherv)
{
    int nx, ny, nz;
    nx = x / otherv.x;
    ny = y / otherv.y;
    nz = z / otherv.z;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator+=(const Vector3& otherv)
{
    x += otherv.x;
    y += otherv.y;
    z += otherv.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& otherv)
{
    x -= otherv.x;
    y -= otherv.y;
    z -= otherv.z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& otherv)
{
    x *= otherv.x;
    y *= otherv.y;
    z *= otherv.z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& otherv)
{
    x /= otherv.x;
    y /= otherv.y;
    z /= otherv.z;
    return *this;
}

Vector3& Vector3::operator+(float f)
{
    int nx, ny, nz;
    nx = x + f;
    ny = y + f;
    nz = z + f;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator-(float f)
{
    int nx, ny, nz;
    nx = x - f;
    ny = y - f;
    nz = z - f;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator*(float f)
{
    int nx, ny, nz;
    nx = x * f;
    ny = y * f;
    nz = z * f;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator/(float f)
{
    int nx, ny, nz;
    nx = x / f;
    ny = y / f;
    nz = z / f;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator+=(float f)
{
    x += f;
    y += f;
    z += f;
    return *this;
}

Vector3& Vector3::operator-=(float f)
{
    x -= f;
    y -= f;
    z -= f;
    return *this;
}

Vector3& Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector3& Vector3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;
    return *this;
}

Vector3& Vector3::operator+(int i)
{
    int nx, ny, nz;
    nx = x + i;
    ny = y + i;
    nz = z + i;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator-(int i)
{
    int nx, ny, nz;
    nx = x - i;
    ny = y - i;
    nz = z - i;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator*(int i)
{
    int nx, ny, nz;
    nx = x * i;
    ny = y * i;
    nz = z * i;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator/(int i)
{
    int nx, ny, nz;
    nx = x / i;
    ny = y / i;
    nz = z / i;
    Vector3 nv(nx, ny, nz);
    return nv;
}

Vector3& Vector3::operator+=(int i)
{
    x += i;
    y += i;
    z += i;
    return (*this);
}

Vector3& Vector3::operator-=(int i)
{
    x -= i;
    y -= i;
    z -= i;
    return (*this);
}

Vector3& Vector3::operator*=(int i)
{
    x *= i;
    y *= i;
    z *= i;
    return (*this);
}

Vector3& Vector3::operator/=(int i)
{
    x /= i;
    y /= i;
    z /= i;
    return (*this);
}


std::ostream& operator<<(std::ostream& ostr, const Vector3& vec)
{
    ostr << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return ostr;
}