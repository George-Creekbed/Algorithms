#ifndef SQUAREMATRIX_CPP_INCLUDED
#define SQUAREMATRIX_CPP_INCLUDED

#include <iostream>
#include "SquareMatrix.h"

using namespace std;

// assign to SquareMatrix only ints and SquareMatrix themselves for recursion!
// do not use it with any other type
template<class T> SquareMatrix<T> operator+(const SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) {
    SquareMatrix<T> ret(lhs);
    ret.setA( ret.getA() + rhs.getA() );
    ret.setB( ret.getB() + rhs.getB() );
    ret.setC( ret.getC() + rhs.getC() );
    ret.setD( ret.getD() + rhs.getD() );

    return ret;
};
template<class T> SquareMatrix<T> operator-(const SquareMatrix<T> lhs, const SquareMatrix<T>& rhs) {
    SquareMatrix<T> ret(lhs);
    ret.setA( lhs.getA() - rhs.getA() );
    ret.setB( lhs.getB() - rhs.getB() );
    ret.setC( lhs.getC() - rhs.getC() );
    ret.setD( lhs.getD() - rhs.getD() );

    return ret;
};

// this is the implementation of Strassen's algorithm
template<class T> SquareMatrix<T> operator*(const SquareMatrix<T>& lhs, const SquareMatrix<T>& rhs) {
    SquareMatrix<T> ret;
    T product_1 = lhs.getA() * ( rhs.getB() - rhs.getD() );
    T product_2 = ( lhs.getA() + lhs.getB() ) * rhs.getD();
    T product_3 = ( lhs.getC() + lhs.getD() ) * rhs.getA();
    T product_4 = lhs.getD() * ( rhs.getC() - rhs.getA() );
    T product_5 = ( lhs.getA() + lhs.getD() ) * ( rhs.getA() + rhs.getD() );
    T product_6 = ( lhs.getB() - lhs.getD() ) * ( rhs.getC() + rhs.getD() );
    T product_7 = ( lhs.getA() - lhs.getC() ) * ( rhs.getA() + rhs.getB() );
    ret.setA(product_5 + product_4 - product_2 + product_6);
    ret.setB(product_1 + product_2);
    ret.setC(product_3 + product_4);
    ret.setD(product_1 + product_5 - product_3 - product_7);

    return ret;
};

#endif // SQUAREMATRIX_CPP_INCLUDED
