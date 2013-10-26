#include "Point3D.hpp"

Point3D::Point3D() :
    x(0), y(0), z(0) {
}

Point3D::Point3D(float x, float y, float z) :
    x(x), y(y), z(z) {
}

Point3D::Point3D(const Point3D& other) :
    x(other.x), y(other.y), z(other.z) {
}

Point3D& Point3D::operator=(const Point3D& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Point3D& Point3D::operator*=(const float alpha) {
    x *= alpha;
    y *= alpha;
    z *= alpha;
    return *this;
}

Point3D& Point3D::operator+=(const Point3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Point3D Point3D::operator+(const Point3D& other) const {
    return Point3D(x + other.x, y + other.y, z + other.z);
}

Point3D Point3D::operator-(const Point3D& other) const {
    return Point3D(x - other.x, y - other.y, z - other.z);
}

Point3D Point3D::operator*(const float alpha) const {
    return Point3D(x * alpha, y * alpha, z * alpha);
}

bool Point3D::operator==(const Point3D& other) const {
    return x == other.x && y == other.y && z == other.z;
}
bool Point3D::operator!=(const Point3D& other) const {
    return !(*this == other);
}
