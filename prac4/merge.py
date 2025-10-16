#merge de dos arreglos dados
def merge(A, B):
    i, j = 0, 0
    C = []
    #recorrer arreglo, comparar y ordenar
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
# Ejemplo de uso
A = [1, 3, 5, 7]
B = [2, 4, 6, 8]
print("A:", A)
print("B:", B)
print("Merge:", merge(A, B))
