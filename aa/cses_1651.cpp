// https://cses.fi/problemset/task/1651

#include <iostream>
#include <vector>

using lld = long long int;

using namespace std;


class BIT {
public:
    int _n;
    vector<lld> _bit;

    BIT(int n) {
        _n = n;
        _bit.assign(n + 5, 0);
    }

    void update(int a, int b, int u) {
        while (a <= _n) {
            _bit[a] += u;
            a += a & (-a);
        }

        b++;
        while (b <= _n) {
            _bit[b] -= u;
            b += b & (-b);
        }
    }

    lld query(int pos) {
        lld res = 0;
        while (pos > 0) {
            res += _bit[pos];
            pos -= pos & (-pos);
        }
        return res;
    }
};


class BIT2 {
public:
    int _n;
    vector<lld> _bit;

    BIT2(int n) {
        _n = n;
        _bit.assign(n + 5, 0);
    }

    void update(int a, int b, int u) {
        while (b > 0) {
            _bit[b] += u;
            b -= b & (-b);
        }

        a--;
        while (a > 0) {
            _bit[a] -= u;
            a -= a & (-a);
        }
    }

    lld query(int pos) {
        lld res = 0;
        while (pos <= _n) {
            res += _bit[pos];
            pos += pos & (-pos);
        }
        return res;
    }
};


int main() {
    int type, a, b, u, pos, n, q, x;
    cin >> n;
    cin >> q;
    BIT2 bit = BIT2(n);
    for(int i = 1; i <= n; ++i) {
        cin >> x;
        bit.update(i, i, x);
    }

    for(int i = 0; i < q; ++i) {
        cin >> type;
        if(type == 1) {
            cin >> a;
            cin >> b;
            cin >> u;
            bit.update(a, b, u);
        } else {
            cin >> pos;
            cout << bit.query(pos) << endl;
        }
    }

    return 0;
}