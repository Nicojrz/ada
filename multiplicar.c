#include <stdio.h>
#include <stdlib.h>

//juarezbarriosaxelnicolas

int multiplicar(int x, int y);

int main(int argc, char * argv[])
{
    int x,y,res;

    switch (argc)
    {
    case 1:
        printf("Ingresa el primer numero:\n");
        scanf("%d",&x);
        printf("Ingresa el segundo numero:\n");
        scanf("%d",&y);
        res = multiplicar(x,y);
        printf("Resultado producto %d * %d = %d\n", x, y, res);
        break;
    case 3:
        x = atoi(argv[1]);
        y = atoi(argv[2]);
        res = multiplicar(x,y);
        printf("Resultado producto %d * %d = %d\n", x, y, res);
        break;
    default:
        printf("Mas de dos numeros ingresados.\n");
        break;
    }

    return 0;
}

int multiplicar(int x, int y)
{
    if(y == 0)
        return 0;
    int z = multiplicar(x, y/2);
    if(y%2 == 0)
        return 2*z;
    else
        return x+(2*z);
}