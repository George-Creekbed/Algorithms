/* Integer multiplication algorithms:
   1) multiplication as taught in grade school
   2) Karatsuba multiplication (recursive)    */
   

#include <cstdint>  // allows the uintmax_t, an int type allowing larger values
#include <iostream>
#include <cmath>   // std::pow
#include <numeric> // std::accumulate
#include <limits>  // std::numeric_limits

using namespace std;

uintmax_t imin = numeric_limits<uintmax_t>::min(); // uintmax_t minimum value
uintmax_t imax = numeric_limits<uintmax_t>::max(); 
// maximum integer available on implementation, UINTMAX_MAX = 2^63 - 1 

uintmax_t inDigits(const uintmax_t in, uintmax_t* in_as_array = nullptr, uintmax_t index = 0)
{
    uintmax_t aux = in;
    if (in > 9)
        aux = in / 10;

    if (in_as_array)
    {
        if (in > 9)
            in_as_array[index++] = in - (aux * 10);
        else if (in > 0)
            in_as_array[index++] = in;
    }
    if (in > 9)
        aux = inDigits(aux, in_as_array, index);

    return aux;
}


void doSizeOfInteger(uintmax_t in, uintmax_t& counter)
{
    uintmax_t aux = in;
    if (in > 9)
    {
        aux = in / 10;
        ++counter;
        doSizeOfInteger(aux, counter);
    }

    return;
}


uintmax_t sizeOfInteger(uintmax_t in)
{
    uintmax_t counter = 1;
    doSizeOfInteger(in, counter);

    return counter;
}


void makeArray(uintmax_t a, uintmax_t* array_a, uintmax_t size_a)
{
    for (uintmax_t i = 0; i != size_a; ++i)
    {
        inDigits(a, array_a);
        //cout << "array_a at " << i << " " << array_a[i] << endl;
    }

    return;
}


uintmax_t schoolMultiplication(uintmax_t a, uintmax_t b)
{
    uintmax_t size_a = sizeOfInteger(a);
    uintmax_t size_b = sizeOfInteger(b);
    uintmax_t array_a[size_a];
    uintmax_t array_b[size_b];
    makeArray(a, array_a, size_a);
    makeArray(b, array_b, size_b);

    // digit by digit multiplication
    uintmax_t partial_sums[size_b];
    for (uintmax_t j = 0; j != size_b; ++j)
    {
        partial_sums[j] = 0;
        for (uintmax_t i = 0; i != size_a; ++i)
            partial_sums[j] += (uintmax_t) round(pow(10, i)) * array_b[j] * array_a[i];//round necessary. pow() works with doubles

        partial_sums[j] = (uintmax_t) round(pow(10, j)) * partial_sums[j];
    }
    uintmax_t result = accumulate(partial_sums, partial_sums + size_b, (uintmax_t) 0);

    return result;
}


uintmax_t karatsubaMultiplication(uintmax_t factor_1, uintmax_t factor_2)
{
    int size_1 = sizeOfInteger(factor_1);
    int size_2 = sizeOfInteger(factor_2);
    uintmax_t array_1[size_1];
    uintmax_t array_2[size_2];
    makeArray(factor_1, array_1, size_1);
    makeArray(factor_2, array_2, size_2);
    
    // divide factors in 2 parts
    uintmax_t a, b, c, d;
    b = *array_1; // * round(pow(10, size_1 / 2));
    for (int i = 1; i != size_1/2; ++i)
        b = b + array_1[i] * (uintmax_t) round(pow(10, i));

    a = *(array_1 + size_1 / 2);
    for (int i = size_1/2 + 1; i != size_1; ++i)
        a = a + array_1[i] * (uintmax_t) round(pow(10, i - size_1 / 2));

    d = *array_2; // * round(pow(10, size_1 / 2));
    for (int i = 1; i != size_2/2; ++i)
        d = d + array_2[i] * (uintmax_t) round(pow(10, i));

    c = *(array_2 + size_2/2);
    for (int i = size_2/2 + 1; i != size_2; ++i)
        c = c + array_2[i] * (uintmax_t) round(pow(10, i - size_2 / 2));

    cout << "Karatsuba internal recursions: a: " << a << " b: " << b << " c: " << c << " d: " << d << endl;

    // step 1: a*c
    uintmax_t ac, bd;
    if (((size_1/2) > 2) || ((size_2/2 + 1) > 2))
        ac = karatsubaMultiplication(a, c);
    else
        ac = a * c;

    // step 2: b*d
    if (((size_1/2 + 1) > 2) || ((size_2/2) > 2))
        bd = karatsubaMultiplication(b, d);
    else
        bd = b * d;

    // step 3: (a+b)*(c+d)
    uintmax_t step_3 = (a + b) * (c + d);
    //cout << "step3: " << step_3 << endl;
    
    // step 4:
    uintmax_t step_4 = step_3 - (ac + bd);
    //cout << "step4: " << step_4 * (uintmax_t) round(pow(10, size_2/2))<< " ac increased: "
    //     << ac * (uintmax_t) round(pow(10, size_2)) << " size_2 " << size_2 << endl;
    
    // step 5:
    if (size_2 % 2 == 1) {size_2 = size_2 - 1;}
    uintmax_t result = ac * (uintmax_t) round(pow(10, size_2)) + bd +
                          step_4 * (uintmax_t) round(pow(10, size_2/2));
    //cout << "result: " << result << endl;

    return result;
}


int main()
{
// uncomment and pick a and b of your choice if 
// you don't want to input them from command prompt
//    cout << "567890 * 123450 = " << endl;
//    uintmax_t a = 5678906567512125;
//    uintmax_t b = 1234505458909842;

// comment block if you don't want to input them from command prompt
    uintmax_t a, b;
    cout << "Input 2 integer factors of equal size (at least 2 digits per number): \n";
    cout << "Try to avoid inner 0s: \n";
    cin >> a >> b;
    
    if ((a < 0) || (b < 0))
        cout << "Only positive values" << endl;
    else if ((a == 0) || (b == 0))
        cout << a << " * " << b << " = 0" << endl;
    else
    {
        cout << "School algorithm:    " << a << " * " << b << " = " << schoolMultiplication(a, b) << endl;
        cout << "Karatsuba algorithm: " << a << " * " << b << " = " << karatsubaMultiplication(a, b) << endl;
    }

    // maximum available on implementation, UINTMAX_MAX = 2^63 - 1
    //cout << "imax = " << imax << " UINTMAX_MAX = " << UINTMAX_MAX << endl;
    
    return 0;
}
