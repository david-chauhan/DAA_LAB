#include <stdio.h>
#include <math.h>

int main() {
    FILE *fp = fopen("growth.csv", "w");

    fprintf(fp,
    "n,1/n,log2n,12sqrtn,50sqrtn,n0.51,2^32*n,nlogn,100n2+6n,n2-324,2n3,nlog2n,3n\n");

    for (double n = 2; n <= 1024; n *= 2) {

        fprintf(fp,
        "%.0f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",

        n,

        log2(1.0/n),
        log2(log2(n)),
        log2(12*sqrt(n)),
        log2(50*sqrt(n)),
        log2(pow(n,0.51)),
        log2(pow(2.0,32)*n),
        log2(n*log2(n)),
        log2(100*n*n+6*n),
        log2(n*n-324),
        log2(2*n*n*n),
        log2(pow(n,log2(n))),
        log2(pow(3.0,n))
        );
    }

    fclose(fp);

    printf("growth.csv created successfully!\n");

    return 0;
}
