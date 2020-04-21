#include <iostream>
#include "SquareMatrix.h"

using namespace std;

// driver function for testing Strassen algorithm for matrix operator*
int main()
{
    cout << "Example: multiply 2 matrices 8x8: " << endl;
    // 16 single quadrants
    SquareMatrix<int> M_1Aa(1, 2, 3, 4);
    SquareMatrix<int> M_1Ab(5, 6, 7, 8);
    SquareMatrix<int> M_1Ac(9, 10, 11, 12);
    SquareMatrix<int> M_1Ad(13, 14, 15, 16);
    SquareMatrix<int> M_1Ba(1, 12, 3, 4);
    SquareMatrix<int> M_1Bb(5, 7, 7, 8);
    SquareMatrix<int> M_1Bc(9, 25, 11, 12);
    SquareMatrix<int> M_1Bd(13, 14, 15, 16);
    SquareMatrix<int> M_1Ca(1, 2, 3, 4);
    SquareMatrix<int> M_1Cb(5, 26, 7, 8);
    SquareMatrix<int> M_1Cc(9, 10, 11, 12);
    SquareMatrix<int> M_1Cd(13, 14, 19, 16);
    SquareMatrix<int> M_1Da(1, 2, 13, 4);
    SquareMatrix<int> M_1Db(5, 6, 7, 8);
    SquareMatrix<int> M_1Dc(9, 60, 11, 12);
    SquareMatrix<int> M_1Dd(13, 14, 10, 16);
    // 4 broader quadrants
    SquareMatrix< SquareMatrix<int> > M_1A(M_1Aa, M_1Ab, M_1Ac, M_1Ad);
    SquareMatrix< SquareMatrix<int> > M_1B(M_1Ba, M_1Bb, M_1Bc, M_1Bd);
    SquareMatrix< SquareMatrix<int> > M_1C(M_1Ca, M_1Cb, M_1Cc, M_1Cd);
    SquareMatrix< SquareMatrix<int> > M_1D(M_1Da, M_1Db, M_1Dc, M_1Dd);
    // final 8x8 matrix
    SquareMatrix< SquareMatrix< SquareMatrix<int> > > M_1(M_1A, M_1B, M_1C, M_1D);
    // the other matrix is equal to the first (their product will thus be M_1**2)
    SquareMatrix< SquareMatrix< SquareMatrix<int> > > M_2(M_1);

    SquareMatrix< SquareMatrix< SquareMatrix<int> > > M_result = M_1 * M_2;

    int M_result_row_1[8] = {M_result.getA().getA().getA(), M_result.getA().getA().getB(),
                             M_result.getA().getB().getA(), M_result.getA().getB().getB(),
                             M_result.getB().getA().getA(), M_result.getB().getA().getB(),
                             M_result.getB().getB().getA(), M_result.getB().getB().getB()};

    cout << "result: " << endl;
    for (int i = 0; i != 8; ++i )
        cout << M_result_row_1[i] << " ";
    cout << endl;

    // other test, 2x2 multiplication
    SquareMatrix<int> prova = M_1Aa * M_1Ab;
    cout << "result 2: " << endl;
    cout << prova.getA() << " " << prova.getB() << '\n';
    cout << prova.getC() << " " << prova.getD() << endl;

    // test 4x4 multiplication
    SquareMatrix< SquareMatrix<int> > prova2 = M_1A * M_1B;
    cout << "result 3: " << endl;
    cout << prova2.getA().getA() << " " << prova2.getA().getB() << " " << prova2.getB().getA() << " " << prova2.getB().getB() << '\n';
    cout << prova2.getA().getC() << " " << prova2.getA().getD() << " " << prova2.getB().getC() << " " << prova2.getB().getD() << '\n';
    cout << prova2.getC().getA() << " " << prova2.getC().getB() << " " << prova2.getD().getA() << " " << prova2.getD().getB() << '\n';
    cout << prova2.getC().getC() << " " << prova2.getC().getD() << " " << prova2.getD().getC() << " " << prova2.getD().getD() << endl;

    return 0;
}
