// String hashing

const long long MOD1 = 1000015553, MOD2 = 1000028537;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count()); // random number generator

int uniform(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

template <int MOD> 
struct str_hash {
    static int P;
    vector<ll> h, p;
    str_hash () {}
    str_hash(string s) : h(s.size()), p(s.size()) {
        p[0] = 1, h[0] = s[0];
        for (int i = 1; i < s.size(); i++)
            p[i] = p[i - 1]*P%MOD, h[i] = (h[i - 1]*P + s[i])%MOD;
    }
    ll operator()(int l, int r) { // retorna hash s[l...r]
        ll hash = h[r] - (l ? h[l - 1]*p[r - l + 1]%MOD : 0);
        return hash < 0 ? hash + MOD : hash;
    }
};

template<int MOD> int str_hash<MOD>::P = uniform(256, MOD - 1); // l > |sigma|

struct Hash {
    // Uses 2 primes to better avoid colisions
    str_hash<MOD1> H1;
    str_hash<MOD2> H2;
 
    Hash (string s) : H1(str_hash<MOD1>(s)), H2(str_hash<MOD2>(s)) {}
 
    ll operator()(int l, int r) {
        ll ret1 = H1(l, r), ret2 = H2(l, r);
        return (ret1 << 30) ^ (ret2);
    }
};
