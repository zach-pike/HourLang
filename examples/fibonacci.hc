function nthFib(n) {
    a = 1;
    b = 0;
    for (i=0; i<n; i+=1;) {
        c = a + b;

        a = b;
        b = c;
    }

    return b;
}

print(nthFib(10));