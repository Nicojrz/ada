import math

def leerden():
    den = []
    entrada = input("Ingresa las denominaciones en pesos (separadas por espacio):\n")
    temp = entrada.split()
    print("Denominaciones leídas:")
    for s in temp:
        valor = float(s)
        den.append(valor)
        print(f"{valor} ")
    print()
    return den

def quicksort(A):
    if len(A) <= 1:
        return A
    else:
        piv = A[len(A) // 2]
        izq = [x for x in A if x > piv]   # mayores
        mid = [x for x in A if x == piv]  # iguales
        der = [x for x in A if x < piv]   # menores
        return quicksort(izq) + mid + quicksort(der)  # orden descendente

def cambio(den, montoPesos):
    # Convertir todo a centavos
    den_cent = [int(x * 100) for x in den]
    montoCent = int(round(montoPesos * 100))
    
    resultado = [0] * len(den_cent)
    resto = montoCent
    
    # Calcular cantidad de monedas de cada denominación
    for i in range(len(den_cent)):
        resultado[i] = resto // den_cent[i]
        resto = resto % den_cent[i]
        if resto == 0:
            break
            
    return resultado

if __name__ == "__main__":
    denominaciones = leerden()
    denominaciones = quicksort(denominaciones)
    montoPesos = float(input("Ingresa el monto en pesos:\n"))
    resultado = cambio(denominaciones, montoPesos)
    
    print(f"\nMonedas necesarias para ${montoPesos:.2f}:\n")
    for i in range(len(denominaciones)):
        print(f"${denominaciones[i]:.2f} -> {resultado[i]} monedas")
