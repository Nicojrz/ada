#funcion recursiva, divide en dos el arreglo
def deldup(A):
    if len(A) <= 1:
        return A
    mitad = len(A) // 2
    izq = deldup(A[:mitad])
    der = deldup(A[mitad:])
    return fussin(izq, der)
#funcion merge sin duplicados
def fussin(izq, der):
    i, j = 0, 0
    R = []
    while i < len(izq) and j < len(der):
        #recorrrer arreglo izq
        if izq[i] < der[j]:
            if not R or R[-1] != izq[i]:
                R.append(izq[i])
            i += 1
        #recorrer arreglo der
        elif izq[i] > der[j]:
            if not R or R[-1] != der[j]:
                R.append(der[j])
            j += 1
        #son iguales, tomar izq y recorrer ambos
        else:
            if not R or R[-1] != izq[i]:
                R.append(izq[i])
            i += 1
            j += 1
    # Copiar sobrantes sin duplicados
    while i < len(izq):
        if not R or R[-1] != izq[i]:
            R.append(izq[i])
        i += 1
    while j < len(der):
        if not R or R[-1] != der[j]:
            R.append(der[j])
        j += 1
    return R
# Ejemplo de prueba
A = [5, 1, 3, 3, 2, 2, 4, 5, 1]
print("Arreglo original", A)
print("Sin duplicados:", deldup(A))
