#ifndef SQUAREMATRIX_H_INCLUDED
#define SQUAREMATRIX_H_INCLUDED

#include <iostream>

// assign to SquareMatrix only ints and SquareMatrices for recursion!
// do not use it with any other type
template<class T> class SquareMatrix {
public:
    typedef T value_type;

    SquareMatrix(){}

// useless constructor
//    SquareMatrix(const T* input_array) {
//        a = *input_array;
//        b = *input_array[1];
//        c = *input_array[2];
//        d = *input_array[3];
//    }
    
    SquareMatrix(const T& first, const T& second, const T& third, const T& fourth) {
        a = first;
        b = second;
        c = third;
        d = fourth;
    }
    
    SquareMatrix<T>(const SquareMatrix<T>& rhs) { // copy constructor
        a = rhs.getA();
        b = rhs.getB();
        c = rhs.getC();
        d = rhs.getD();
    }
    
    SquareMatrix& operator=(const SquareMatrix rhs) {  // assignment operator
        if (&rhs != this) {
            a = rhs.getA();
            b = rhs.getB();
            c = rhs.getC();
            d = rhs.getD();
        }

        return *this;
    }
    
    ~SquareMatrix() {}  // destructor
    
    // getters and setters
    T getA() const {return a;}
    T getB() const {return b;}
    T getC() const {return c;}
    T getD() const {return d;}
    void setA(const T& input) {a = input;}
    void setB(const T& input) {b = input;}
    void setC(const T& input) {c = input;}
    void setD(const T& input) {d = input;}

private:
    // 4 quadrants
    // [a, b;
    //  c, d]
    T a, b, c, d;
};

// arithmetic operators implemented in SquareMatrix.cpp
template<class T> SquareMatrix<T> operator+(const SquareMatrix<T>, const SquareMatrix<T>&);
template<class T> SquareMatrix<T> operator-(const SquareMatrix<T>, const SquareMatrix<T>&);
template<class T> SquareMatrix<T> operator*(const SquareMatrix<T>&, const SquareMatrix<T>&);    // Strassen algorithm

#include "SquareMatrix.cpp"
#endif // SQUAREMATRIX_H_INCLUDED
