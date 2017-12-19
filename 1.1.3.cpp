/*
Даны четыре неотрицательных числа a, b, c и d.
Сложить две рациональные дроби a/b и c/d,
а их результат представить в виде несократимой дроби m/n.
Вывести числа m и n. a, b, c, d ≤ 1000.
*/

#include <bits/stdc++.h>

using namespace std;

int gcd(int m, int n){
    if (n > m)
        swap(m, n);
    if ((m == 0) || (n == 0))
        return m + n;
    return gcd(n, m % n);
}

int main(){
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    //Заметим, что a/b + c/d = (ad + bc)/ad. Найдем числшитель и знаменатель дроби.
    int m = a * d + b * c, n = b * d;

    //Найдем НОД(m, n)
    int k = gcd(m, n);

    //Приведем дробь m/n к несократимому виду
    cout << (int) m / k << " " << (int) n / k << endl;

    return 0;
}

