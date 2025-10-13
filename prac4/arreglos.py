def merge(A, B):
    i, j = 0, 0
    C = []
    while i < len(A) and j < len(B):
        if A[i] <= B[j]:
            C.append(A[i])
            i += 1
        else:
            C.append(B[j])
            j += 1
    # Agregar elementos restantes
    while i < len(A):
        C.append(A[i])
        i += 1
    while j < len(B):
        C.append(B[j])
        j += 1
    return C

def combine(arrays):
    if not arrays:
        return []
    if len(arrays) == 1:
        return arrays[0]

    mitad = len(arrays) // 2
    izq = combine(arrays[:mitad])
    der = combine(arrays[mitad:])

    return merge(izq, der)

# Ejemplo de prueba
A1 = [1, 4, 7]
A2 = [2, 5, 8]
A3 = [0, 3, 6]
A4 = [9, 10, 11]

lista = [A1, A2, A3, A4]
print("Combinar k arreglos:", combine(lista))
