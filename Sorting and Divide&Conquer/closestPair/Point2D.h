#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED

#include <cmath>    // std::pow, std::sqrt

class Point2D {
public:
    // constructors
    Point2D(): _ordinal(0){}
    Point2D(const double x, const double y, const int ordinal):
        _x(x), _y(y), _ordinal(ordinal) {}

    // relational operators
    friend bool operator==(const Point2D lhs, const Point2D rhs) {
        if (lhs._x == rhs._x && lhs._y == rhs._y && lhs._ordinal == rhs._ordinal) return true;

        return false;
    }

    // getters and setters
    double getX() const {return _x;}
    double getY() const {return _y;}
    double getOrdinal() const {return _ordinal;}
    void setX(const double input) {_x = input;}
    void setY(const double input) {_y = input;}
    void setOrdinal(const int input) {_ordinal = input;}

private:
    // data
    double _x, _y;
    int _ordinal;   // label provided in case point is part of a set of points that needs sorting
};

// computes Euclidean distance between two Point2Ds
double distance(const Point2D& p1, const Point2D& p2) {
    return std::sqrt( std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2) );
}

// helps sorting Point2Ds by x or y or ordinal
bool compareX(const Point2D& p1, const Point2D& p2) {
	return p1.getX() <= p2.getX();
}
bool compareY(const Point2D& p1, const Point2D& p2) {
	return p1.getY() <= p2.getY();
}
bool compareOrdinal(const Point2D& p1, const Point2D& p2) {
	return p1.getOrdinal() <= p2.getOrdinal();
}

#endif // POINT2D_H_INCLUDED
