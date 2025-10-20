import math

def nextpowtwo(n):
    return int(math.pow(2, math.ceil(math.log2(n))))

def resizemat(mat, rows, cols):
    resized = [[0 for _ in range(cols)] for _ in range(rows)]
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            resized[i][j] = mat[i][j]
    return resized

def add(a, b, size, sign = 1):
    res = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(size):
            res[i][j] = a[i][j] + sign * b[i][j]
    return res

def strassen(mat1, mat2):
    n = len(mat1)
    # caso base
    res = [[0 for _ in range(n)] for _ in range(n)]
    if n == 1:
        res[0][0] = mat1[0][0] * mat2[0][0]
        return res
    # submatrices
    half = n // 2
    # matriz a
    a11 = [[0 for _ in range(half)] for _ in range(half)]
    a12 = [[0 for _ in range(half)] for _ in range(half)]
    a21 = [[0 for _ in range(half)] for _ in range(half)]
    a22 = [[0 for _ in range(half)] for _ in range(half)]
    # matriz b
    b11 = [[0 for _ in range(half)] for _ in range(half)]
    b12 = [[0 for _ in range(half)] for _ in range(half)]
    b21 = [[0 for _ in range(half)] for _ in range(half)]
    b22 = [[0 for _ in range(half)] for _ in range(half)]
    # Fill the submatrices
    for i in range(half):
        for j in range(half):
            a11[i][j] = mat1[i]       [j]
            a12[i][j] = mat1[i]       [j + half]
            a21[i][j] = mat1[i + half][j]
            a22[i][j] = mat1[i + half][j + half]
            b11[i][j] = mat2[i]       [j]
            b12[i][j] = mat2[i]       [j + half]
            b21[i][j] = mat2[i + half][j]
            b22[i][j] = mat2[i + half][j + half]
    # Compute the 7 products using Strassen’s formulas
    m1 = strassen(add(a11, a22, half)    , add(b11, b22, half)    )
    m2 = strassen(add(a21, a22, half)    , b11                    )
    m3 = strassen(a11                    , add(b12, b22, half, -1))
    m4 = strassen(a22                    , add(b21, b11, half, -1))
    m5 = strassen(add(a11, a12, half)    , b22                    )
    m6 = strassen(add(a21, a11, half, -1), add(b11, b12, half)    )
    m7 = strassen(add(a12, a22, half, -1), add(b21, b22, half)    )
    # Calculate result quadrants from m1...m7
    c11 = add(add(m1, m4, half), add(m7, m5, half, -1), half)
    c12 = add(m3, m5, half)
    c21 = add(m2, m4, half)
    c22 = add(add(m1, m3, half), add(m6, m2, half, -1), half)
    # Combine result quadrants into final matrix
    for i in range(half):
        for j in range(half):
            res[i][j]               = c11[i][j]
            res[i][j + half]        = c12[i][j]
            res[i + half][j]        = c21[i][j]
            res[i + half][j + half] = c22[i][j]
    return res

# multiplicacion de A (n x m) y B (m x q) 
def multiply(A, B):
    # calcular nuevo tamaño en potencia de 2
    n = len(A)
    m = len(A[0])
    q = len(B[0])
    size = nextpowtwo(max(n, max(m, q)))
    # redimensionar a y b al nuevo tamaño
    Ares = resizemat(A, size, size)
    Bres = resizemat(B, size, size)
    # calcular con strassen
    Cres = strassen(Ares, Bres)
    # extraer matriz C (n x q)
    C = [[0 for _ in range(q)] for _ in range(n)]
    for i in range(n):
        for j in range(q):
            C[i][j] = Cres[i][j]
    return C

def printmat(M):
    for row in M:
        for val in row:
            print(val, end = "\t")
        print()

if __name__ == "__main__":
    print("Matriz A1")
    A1 = [[1, 2, 3], [4, 5, 6]]
    printmat(A1)
    print("Matriz B1")
    B1 = [[7, 8], [9, 10], [11, 12]]
    printmat(B1)
    print("Matriz R1 (=A1*B1)")
    R1 = multiply(A1, B1)
    printmat(R1)

    print("Matriz A2")
    A2 = [[3, 4, 8, 2], [1, 0, 9, 2], [3, 2, 2, 1], [2, 9, 8, 5]]
    printmat(A2)
    print("Matriz B2")
    B2 = [[4, 9, 19, 2], [9, 10, 3, 5], [5, 4, 2, 5], [3, 4, 5, 2]]
    printmat(B2)
    print("Matriz R2 (=A2*B2)")
    R2 = multiply(A2, B2)
    printmat(R2)

    print("Matriz A3")
    A3 = [[1, 1], [0, 1]]
    printmat(A3)
    print("Matriz B3")
    B3 = [[1, 1], [0, 1]]
    printmat(B3)
    print("Matriz R3 (=A3*B3)")
    R3 = multiply(A3, B3)
    printmat(R3)