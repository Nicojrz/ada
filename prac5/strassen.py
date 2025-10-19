import math

# Return the next power of two greater than or equal to n
def nextPowerOfTwo(n):
    return int(math.pow(2, math.ceil(math.log2(n))))

# Resize a matrix to newR x newC and 
# fill extra space with zeros
def resizeMatrix(mat, newR, newC):
    resized = [[0 for _ in range(newC)] for _ in range(newR)]
    for i in range(len(mat)):
        for j in range(len(mat[0])):
            resized[i][j] = mat[i][j]
    return resized

# Perform matrix addition or subtraction 
# of size×size matrices
# sign = 1 for addition, -1 for subtraction
def add(a, b, size, sign=1):
    res = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(size):
            res[i][j] = a[i][j] + sign * b[i][j]
    return res

# Recursive implementation of Strassen's 
# matrix multiplication
# Assumes both matrices are size×size 
# and size is a power of 2
def strassen(mat1, mat2):
    n = len(mat1)

    # Base case: 1×1 matrix multiplication
    res = [[0 for _ in range(n)] for _ in range(n)]
    if n == 1:
        res[0][0] = mat1[0][0] * mat2[0][0]
        return res

    # Split matrices into 4 submatrices
    newSize = n // 2
    a11 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    a12 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    a21 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    a22 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    b11 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    b12 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    b21 = [[0 for _ in range(newSize)] for _ in range(newSize)]
    b22 = [[0 for _ in range(newSize)] for _ in range(newSize)]

    # Fill the submatrices
    for i in range(newSize):
        for j in range(newSize):
            a11[i][j] = mat1[i][j]
            a12[i][j] = mat1[i][j + newSize]
            a21[i][j] = mat1[i + newSize][j]
            a22[i][j] = mat1[i + newSize][j + newSize]
            b11[i][j] = mat2[i][j]
            b12[i][j] = mat2[i][j + newSize]
            b21[i][j] = mat2[i + newSize][j]
            b22[i][j] = mat2[i + newSize][j + newSize]

    # Compute the 7 products using Strassen’s formulas
    m1 = strassen(add(a11, a22, newSize), add(b11, b22, newSize))
    m2 = strassen(add(a21, a22, newSize), b11)
    m3 = strassen(a11, add(b12, b22, newSize, -1))
    m4 = strassen(a22, add(b21, b11, newSize, -1))
    m5 = strassen(add(a11, a12, newSize), b22)
    m6 = strassen(add(a21, a11, newSize, -1), add(b11, b12, newSize))
    m7 = strassen(add(a12, a22, newSize, -1), add(b21, b22, newSize))

    # Calculate result quadrants from m1...m7
    c11 = add(add(m1, m4, newSize), add(m7, m5, newSize, -1), newSize)
    c12 = add(m3, m5, newSize)
    c21 = add(m2, m4, newSize)
    c22 = add(add(m1, m3, newSize), add(m6, m2, newSize, -1), newSize)

    # Combine result quadrants into final matrix
    for i in range(newSize):
        for j in range(newSize):
            res[i][j] = c11[i][j]
            res[i][j + newSize] = c12[i][j]
            res[i + newSize][j] = c21[i][j]
            res[i + newSize][j + newSize] = c22[i][j]

    return res

# Multiply mat1 (n×m) and mat2 (m×q) 
# using Strassen’s method
def multiply(mat1, mat2):
    # Compute size of the smallest power of 2 ≥ max(n, m, q)
    n = len(mat1)
    m = len(mat1[0])
    q = len(mat2[0])
    size = nextPowerOfTwo(max(n, max(m, q)))

    # Pad both matrices to size×size with zeros
    aPad = resizeMatrix(mat1, size, size)
    bPad = resizeMatrix(mat2, size, size)

    # Perform Strassen multiplication on padded matrices
    cPad = strassen(aPad, bPad)

    # Extract the valid n×q result from the padded result
    C = [[0 for _ in range(q)] for _ in range(n)]
    for i in range(n):
        for j in range(q):
            C[i][j] = cPad[i][j]

    return C

if __name__ == "__main__":
    mat1 = [[1, 2, 3], [4, 5, 6]]
    mat2 = [[7, 8], [9, 10], [11, 12]]

    res = multiply(mat1, mat2)

    for row in res:
        for val in row:
            print(val, end=" ")
        print()
