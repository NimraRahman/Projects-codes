#include<iostream>
using namespace std;
class bin
{
    int n,k;
public:
    void read()
    {
        cout<< "Enter n and k\n";
        cin>>n;cin>>k;
    }
    int compute();
    void display()
    {
        cout<< "The binomial coefficient is:";
        cout<<compute();
    }
    int mim(int a, int b)
    {
        if(a>b)return b;
        else return a;
    }
};
int bin::compute()
{
    int i,j;
    int a[20][20];
    for(i=0;i<=n;i++)
      {
          for(j=0;j<=mim(i,k);j++)
        {
            /*if j==0 or j==i , coefficient =1 as nC0=1 and nCn=1 where C= combination*/
            if(j==0||j==i)
            {
                a[i][j]=1;
            }
            else
                a[i][j]=a[i-1][j-1]+a[i-1][j];  // nCk=(n-1)C(k-1) + (n-1)C(k)
        }
}
    return a[n][k];// return value of nCk
}
int main()
{
    bin B;
    B.read(); // read n and k values
    B.compute(); // calculate the coefficient
    B.display(); //display the result
    return 0;
}