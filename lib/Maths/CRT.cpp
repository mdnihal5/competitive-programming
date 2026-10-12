tuple<int, int, int> extGcd(int a, int b) {
    if (!b) return {a, 1, 0};
    auto [g, x, y] = extGcd(b, a % b);
    return {g, y, x - a / b * y};
}

pair<int, int> crt(int a, int m, int b, int n) {
    auto [g, p, q] = extGcd(m, n);
    assert((a - b) % g == 0);
    int l = n / g;
    a = (a % m + m) % m;
    int k = ((b - a) / g % l + l) % l * ((p % l + l) % l) % l;
    return {a + m * k, m / g * n};
}
