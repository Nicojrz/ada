import math

def maxdif(A, ini, fin):
    #caso base: 1 elemento.
    if ini == fin:
        return [A[ini], A[ini]]
    
    mid = math.floor((ini + fin) / 2)

    izq = maxdif(A, ini, mid)
    der = maxdif(A, mid+1, fin)

    mintotal = min(izq[0], der[0])
    maxtotal = max(izq[1], der[1])

    return [mintotal, maxtotal]

def minmax(A):
    M = maxdif(A, 0, len(A)-1)
    return abs(M[1] - M[0])

lista = [4, 5, 10, -2, 3.1415, -7.115]
print("Lista original:", lista)
print(f"Maxima diferencia: {minmax(lista):.3f}")
