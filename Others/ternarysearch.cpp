// https://codeforces.com/contest/1999/submission/275347916
    while (low + 1 < high) {
        int x = low + (high - low) / 3;
        int y = low + (high - low) * 2 / 3;
        int R = solve (x, y);
 
        if (R == x * y) low = y;
        else if (R == x * (y + 1) ) {
            low = x, high = y;
 
        } else high = x;
    }
