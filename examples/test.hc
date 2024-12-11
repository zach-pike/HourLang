function myTestFunc(a, b) {
    sum=0;

    for (i=0; i<a; i+=1;) {
        for (k=0; k<b; k+=1;) {
            sum += 1;
        }
    }

    return sum;
}

print(myTestFunc(10, 5));