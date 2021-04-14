#include <stdio.h>
#include <stdlib.h>

typedef struct fraction{
    long long int num;
    long long int den;
}frac;

long long int gcd(long long int n1, long long int n2){
    long long int gcd = 1;
    for (long long int i = 2; i <= n1 && i <= n2; ++i) {
        if (n1 % i == 0 && n2 % i == 0)
            gcd = i;
    }
    return gcd;
}

long long int lcm(long long int n1, long long int n2){
    return (n1*n2)/gcd(n1,n2);
}

frac subtract_fractions(frac f1, frac f2){
    frac result;
    long long int lcm_den = lcm(f1.den,f2.den);
    result.den = lcm_den;
    result.num = f1.num*(lcm_den/f1.den) - f2.num*(lcm_den/f2.den);
    return result;
}

frac simplify_frac(frac f){
    long long int gcd_f = gcd(f.num,f.den);
    f.num = f.num/gcd_f;
    f.den = f.den/gcd_f;
    return f;
}



int main(){
    frac input;
    frac consta;
    consta.num=1;
    consta.den =2;
    printf("Please provide input fraction (of the form num/den):");
    scanf("%lld/%lld", &input.num,&input.den);
    long long int i=2;
    if(input.num > input.den){
        printf("%lld",input.num/input.den);
        input.num = input.num - (input.num/input.den)*input.den;
    }
    else {
        printf("0");
    }
    while(input.num!=0){
        input = simplify_frac(input);
        frac partial;
        partial.num=1;
        partial.den=i;
        frac result = subtract_fractions(input,partial);
        if (result.num >= 0){
            printf(" + %lld/%lld",partial.num,partial.den);
            input.num = result.num;
            input.den = result.den;
        }
        i++;
    }
    return 0;
}
