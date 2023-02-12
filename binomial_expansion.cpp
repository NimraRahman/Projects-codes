#include <iostream>
using namespace std;

// self-made function for Binomial Expansion
int coeffHelper(int n, int k)
{
    if (n > k)
        return n * coeffHelper(n - 1, k);
    else
        return 1;
}
int fact(int k)
{
    if (k > 1)
        return k * fact(k - 1);
    else
        return 1;
}

int coeff(int n, int k)
{
    if (n <= k)
        return 1;
    int x = 0;
    if (k > n - k)
    {
        x = coeffHelper(n, k) / fact(n - k);
    }
    else
    {
        x = coeffHelper(n, n - k) / fact(k);
    }
    return x;
}

int main()
{
    // enter the power of the binomial
    cout << "Enter the number of Power : ";
    int power = 1;
    cin >> power;
    if (power <= 0)
    {
        cout << "Invalid input!";
        return 0;
    }
    // To display the binomial expansion
    string x = "X", y = "Y";
    cout << "(X+Y)^" << power << " = ";
    for (int k = 0; k <= power; ++k)
    {
        if (k == 0)
            cout << x << "^" << power << " + ";
        else if (k == 1 && power - k == 1)
            cout << coeff(power, k) << " " << x << " " << y << " + ";
        else if (k == 1 && power - k != 1)
            cout << coeff(power, k) << " " << x << "^" << power - k << " " << y << " + ";
        else if (k != 1 && power - k == 1)
            cout << coeff(power, k) << " " << x << " " << y << "^" << k << " + ";
        else if (k < power)
            cout << coeff(power, k) << " " << x << "^" << power - k << " " << y << "^" << k << " + ";
        else
            cout << y << "^" << power;
    }

    return 0;
}