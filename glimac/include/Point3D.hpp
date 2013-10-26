#pragma once

struct Point3D {
    float x, y, z;

    Point3D();
    Point3D(float x, float y, float z);

    Point3D(const Point3D& other);
    Point3D& operator=(const Point3D& other);

    Point3D& operator*=(const float alpha);
    Point3D& operator+=(const Point3D& other);

    Point3D operator+(const Point3D& other) const;
    Point3D operator-(const Point3D& other) const;
    Point3D operator*(const float alpha) const;

    bool operator==(const Point3D& other) const;
    bool operator!=(const Point3D& other) const;
};

