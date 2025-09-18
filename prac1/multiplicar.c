#include <stdio.h>
#include <stdlib.h>

//juarezbarriosaxelnicolas
typedef unsigned long long int enterito;
enterito multiplicar(enterito x, enterito y);

int main(int argc, char *argv[])
{
    enterito x, y, res;
    switch (argc)
    {
        case 1:
            printf("Ingresa el primer numero:\n");
            scanf("%llu", &x);
            printf("Ingresa el segundo numero:\n");
            scanf("%llu", &y);
            res = multiplicar(x, y);
            printf("Resultado producto %llu * %llu = %llu\n", x, y, res);
            break;
        case 3:
            x = strtoull(argv[1], NULL, 10);
            y = strtoull(argv[2], NULL, 10);
            res = multiplicar(x, y);
            printf("Resultado producto %llu * %llu = %llu\n", x, y, res);
            break;
        default:
            printf("Mas de dos numeros ingresados.\n");
            break;
    }
    return 0;
}

enterito multiplicar(enterito x, enterito y)
{
    if (y == 0)
        return 0;
    enterito z = multiplicar(x, y/2);
    if (y%2 == 0)
        return 2 * z;
    else
        return x + (2 * z);
}
