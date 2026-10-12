vector<int> sos(vector<int> f) {
    for (int b = 1; b < (int)f.size(); b <<= 1)
        for (int mask = 0; mask < (int)f.size(); mask++)
            if (mask & b) f[mask] += f[mask ^ b];
    return f;
}
