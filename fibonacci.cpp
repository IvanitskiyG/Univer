#include <iostream>
#include <cmath>
#include <vector>
/* f(1)=f(2)=1
f(n)=f(n-1)+f(n-2)*/
using namespace std;
long long f_rec(long long n){
    if (n <= 2){
        return 1;
    }
    return f_rec(n - 1) + f_rec(n - 2);
}
long long f_cyc(long long n){
    if (n <= 2){
        return 1;
    }
    long long a = 1;
    long long b = 1;
    long long t;
    for (long long i=3;i<=n;i++){
        t = a + b;
        a = b;
        b = t;
    }
    return b;
}
vector<long long> m_mul(vector<long long> a, vector<long long> b){
    /*0 1
      2 3*/
    vector<long long> c;
    for (int i=0;i<4;i++){
        c.push_back(0);
    }
    c[0] = a[0] * b[0] + a[1] * b[2];
    c[1] = a[0] * b[1] + a[1] * b[3];
    c[2] = a[2] * b[0] + a[3] * b[2];
    c[3] = a[2] * b[1] + a[3] * b[3];
    return c;
}
vector<long long> pov(vector<long long> a, long long p){
    if (p == 1){
        return a;
    }
    if (p % 2 == 0){
        vector<long long> x = pov(a, p/2);
        return m_mul(x, x);
    }
    return m_mul(pov(a,p-1), a);
}
long long f_mat(long long n){
    vector<long long> m;
    vector<long long> res;
    for (short i=1;i<=4;i++){
        m.push_back(1-i/4);
    }
    res = pov(m, n);
    return res[1];
}
template <long long n> struct fib_t
{
    static const long long v = fib_t<n-1>::v + fib_t<n-2>::v;
};
template <> struct fib_t <1>
{
    static const long long v = 1;
};
template <> struct fib_t <2>
{
    static const long long v = 1;
};

int main(){
    long long n;
    cin >> n;
    long long f_t = fib_t<10>::v;
    cout << "Template:  " << f_t << endl;
    long long f_r = f_rec(n);
    cout << "Recursion: " << f_r << endl;
    long long f_c = f_cyc(n);
    cout << "Cycle:     " << f_c << endl;
    long long f_m = f_mat(n);
    cout << "Matrix:    " << f_m << endl;
}
