import Math;

function collatz(n) {
    i = 0;
    while (n > 1) {
        if (mod(n, 2) == 0) {
            n /= 2;
        } else {
            n *= 3;
            n += 1;
        }

        i += 1;
    }

    return i;
}

print(collatz(10));