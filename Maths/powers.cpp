ull modmul(ull a, ull b, ull M) {
    int ret = a * b - mod * ull(1.L / mod * a * b);
    return ret + mod * (ret < 0) - mod * (ret >= (int)mod);
}
ull power(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}
ull power(ull b, ull e) {
    ull ans = 1;
    for (; e; b *= b, e /= 2)
        if (e & 1) ans *= b;
    return ans;
}
void euclid(ull a, ull b, ull& x, ull& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }

    Lint x1, y1;
    euclid(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;
}

ull inv(ull n) {
    Lint x, y;
    euclid(mod, n, x, y);
    return ((y % mod) + mod) % mod;
}
