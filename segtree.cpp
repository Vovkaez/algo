#include <bits/stdc++.h>

#define ll long long
#define ld long double

using namespace std;
const long long LINF = LLONG_MAX;
const int INF = INT_MAX;
const int MOD = 1000000007;

const ld PI = 3.14159265358979323;

const int N = 1e6 + 111;
int n;

template<typename T>
struct segtree{
    int sz, w = -1;
    vector<T> a;
    segtree(const vector<T>& vec){
        sz = vec.size();
        w = (__builtin_popcount(sz) == 1 ? sz : 1 << (32 - __builtin_clz(sz)));
        a.resize((w << 1));
        for (int i = w; i < w + sz; i++)
            a[i] = vec[i - w];
        for (int i = w - 1; i > 0; i--)
            a[i] = a[i << 1] + a[(i << 1) + 1];
    }
    T sum(int l, int r, int i = 1, int lx = 0, int rx = -1){
        if (rx == -1)
            rx = w-1;
        if (l <= lx && rx <= r){
            return a[i];
        }
        if (r < lx || l > rx){
            return 0;
        }
        int m = (lx + rx) >> 1;
        return sum(l, r, i << 1, lx, m) + sum(l, r, (i << 1) + 1, m + 1, rx);
    }
    void set(int i, ll x, int j = 1, int lx = 0, int rx = -1){
        if (rx == -1)
            rx = w-1;
        if (i < lx || rx < i){
            return;
        }
        if (lx == rx){
            a[j] = x;
            return;
        }
        a[j] += x - a[w + i];
        int m = (lx + rx) >> 1;
        set(i, x, j << 1, lx, m);
        set(i, x, (j << 1) + 1, m + 1, rx);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a)
        cin >> x;
}