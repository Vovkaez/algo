#include <vector>

template<typename T, typename F>
struct sparse_table{
    std::vector<std::vector<T>> t;
    std::vector<int> lg;
    F f; // f is not necessary idempotent
    sparse_table(std::vector<T> a, F _f) : f(_f){
        int n = a.size();
        lg.assign(n + 1, 0);
        lg[1] = 0;
        for (int l = 2; l <= n; ++l)
            lg[l] = lg[l-1] + (__builtin_popcount(l) == 1);
        t.assign(n, std::vector<T>(lg[n] + 1, 0));
        for (int i = 0; i < n; ++i)
            t[i][0] = a[i];
        for (int k = 1; (1 << k) <= n; ++k){
            int l = 1 << k;
            for (int i = 0; i + l - 1 < n; ++i)
                t[i][k] = f(t[i][k-1], t[i+l/2][k-1]);
        }
    }
    T ask(int l, int r){
        int k = lg[r - l + 1];
        if (l + (1 << k) > r) return t[l][k];
        return f(t[l][k], ask(l + (1 << k), r));
    }
};
