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

# multiplicacion de A (n×m) y B (m×q) 
def multiply(A, B):
    # calcular nuevo tamaño en potencia de 2
    n = len(A)
    m = len(A[0])
    q = len(B[0])
    size = nextpowtwo(max(n, max(m, q)))
    # redimensionar a y b al nuevo tamaño
    ares = resizemat(mat1, size, size)
    bres = resizemat(mat2, size, size)
    # calcular con strassen
    cres = strassen(ares, bres)
    # extraer matriz
    C = [[0 for _ in range(q)] for _ in range(n)]
    for i in range(n):
        for j in range(q):
            C[i][j] = cres[i][j]
    return C

if __name__ == "__main__":
    mat1 = [[1, 2, 3], [4, 5, 6]]
    mat2 = [[7, 8], [9, 10], [11, 12]]

    res = multiply(mat1, mat2)

    for row in res:
        for val in row:
            print(val, end=" ")
        print()
