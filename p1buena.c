#include <stdio.h>
#include <math.h>
#include <sys/time.h>

int fib1 (int n);
int fib2 (int n);
int fib3 (int n);
double microsegundos();
void test();
void calc_tiempos_fib1();
void calc_tiempos_fib2();
void calc_tiempos_fib3();
void mostrartablas();

int main() {
    test();
    mostrartablas();
    return 0;
}

int fib1 (int n) {
    if (n < 2)
        return n;
    else
        return (fib1(n-1) + fib1(n-2));
}

int fib2 (int n) {
    int i = 1; int j = 0; int k;
    for (k = 1; k <= n; ++k) {
        j=i+j;
        i=j-i;
    }
    return j;
}

int fib3 (int n) {
    int i,j,k,h,t;
    i=1;j=0;k=0;h=1;t=0;
    while (n>0) {
        if (n % 2 != 0) {
            t=j*h;
            j=i*h + j*k + t;
            i=i*k + t;
        }
        t=h*h;
        h=2*k*h + t;
        k=k*k + t;
        n=n/2;
    }
    return j;
}

void test() {
printf("Tabla para comprobar que los 3 algoritmos funcionan correctamente\n");
    printf("    n       fib1(n)         fib2(n)         fib3(n)\n");
    for (int i = 1; i <= 10; ++i) {
        printf("%5d%11d%16d%17d\n", i, fib1(i), fib2(i), fib3(i));
    }
}

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void calc_tiempos_fib1() {
    double t,t1,ta,tb,x,y,z; int n, i;
    printf("\t  n\t  t(n)\t      t(n)/f(n)\t   t(n)/g(n)\tt(n)/h(n)\n");
    for (n = 2; n <= 32; n=2*n) {
        ta = microsegundos();
        fib1(n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {
            ta = microsegundos();
            for (i = 0; i < 1000; i++) {
                fib1(n);
            }
            tb = microsegundos();
            t1 = tb-ta;
            t = t1/1000;
            x = t / pow(1.1, n);  
            y = t / (pow(((1 + sqrt(5))/2), n));  
            z = t / pow(2, n);  
            printf("(*)%8d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
        else {
            x = t / pow(1.1, n);  
            y = t / (pow(((1 + sqrt(5))/2), n));  
            z = t / pow(2, n);  
            printf("%11d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
    }
}

void calc_tiempos_fib2() {
    double t,t1,ta,tb,x,y,z; int n, i;
    printf("\t  n\t  t(n)\t      t(n)/f(n)\t   t(n)/g(n)\tt(n)/h(n)\n");    
    for (n = 1000; n <= 10000000 ; n = n * 10) {
        ta = microsegundos();
        fib2(n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) {  
            ta = microsegundos();
            for (i = 0; i < 1000; ++i) { 
                fib2(n);
            }
            tb = microsegundos();
            t1 = tb - ta;
            t = t1/1000;
            x = t / pow(n,0.8);  
            y = t / n;  
            z = t / (n*log(n));  
            printf("(*)%8d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
        else {
            x = t / pow(n,0.8);  
            y = t / n;  
            z = t / (n*log(n));  
            printf("%11d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
    }
}

void calc_tiempos_fib3() {
    double t,t1,ta,tb,x,y,z; int n, i;
    printf("\t  n\t  t(n)\t      t(n)/f(n)\t   t(n)/g(n)\tt(n)/h(n)\n");    
    for (n = 1000; n <= 10000000 ; n = n * 10) {
        ta = microsegundos();
        fib3(n);
        tb = microsegundos();
        t = tb - ta;
        if (t < 500) { 
            ta = microsegundos();
            for (i = 0; i < 1000; ++i) { 
                fib3(n);
            }
            tb = microsegundos();
            t1 = tb - ta;
            t = t1/1000;
            x = t/(sqrt(log(n)));  
            y = t/log(n); 
            z = t/pow(n,0.5);  
            printf("(*)%8d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
        else {
            x = t / (sqrt(log(n))); 
            y = t / log(n);  
            z = t / pow(n, 0.5);  
            printf("%11d%12.4f%15.5f%14.5f%14.8f\n",n,t,x,y,z);
        }
    }
}

void mostrartablas() {
    printf("\n----- TIEMPOS FIB 1: -----\n\n");
    calc_tiempos_fib1();
    printf("\n----- TIEMPOS FIB 2: -----\n\n");
    calc_tiempos_fib2();
    printf("\n----- TIEMPOS FIB 3: -----\n\n");
    calc_tiempos_fib3();
}