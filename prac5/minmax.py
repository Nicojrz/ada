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

lista1 = [4, 5, 10, -2, 3.1415, -7.115]
print("Lista original:", lista1)
print(f"Maxima diferencia: {minmax(lista1):.3f}")
lista2 = [43, 12, 0, -234, 23, 58, 39]
print("Lista original:", lista2)
print(f"Maxima diferencia: {minmax(lista2):.3f}")
lista3 = [-443.33, 302.32, 958.3685, 3.33, -34.35, -1192.2]
print("Lista original:", lista3)
print(f"Maxima diferencia: {minmax(lista3):.3f}")
