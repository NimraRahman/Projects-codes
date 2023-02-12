#include <iostream>
using namespace std;

// self-made function of factorial
int factorial(int);
int nCr(int, int);
int main()
{
    int n, i, j;

    cout << "Enter the number of rows: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (j = 0; j <= n - i; j++) // first inner loop to print spaces
            cout << " ";
        // second inner loop to print combination for each i and j
        for (j = 0; j <= i; j++)
            cout << nCr(i, j) << " ";
        cout << endl;
    }
    return 0;
}
int nCr(int n, int r) // to find combination or nCr which gives binomial theorem by combination of pascals triangle
{
    return (factorial(n) / (factorial(n - r) * factorial(r)));
}

// to find/call factorial
int factorial(int n)
{
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}
/*
Algorithm: Pascal’s triangle

1. declares an initialize a variable ‘n’ for the number of rows.
2. start an outer loop for ‘i’ to ‘n’.
3. make an inner loop for ‘j’ to “n-1″, print a single space (” “) and close the loop.
4. make another inner loop for ‘j’ to ‘i’
5. print nCr or C(n, r) for each ‘i’ and ‘j’ and close the loop. (means iCj or C(i, j))
6. change the line after each second inner loop (for every ‘i’ after the inner loop)
7. Exit
*/