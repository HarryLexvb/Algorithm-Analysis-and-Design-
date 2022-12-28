import time


def printSolution(matriz, n):
    for i in range(0, n):
        for j in range(0, n):
            if matriz[i][j] == 0:
                print('x', end=" ")
            else:
                print('Q', end=" ")
        print(' ')


def isSafe(matriz, r, i, N):
    for j in range(0, N):
        if matriz[j][i] == 1:  # Barre verticales desde la posición [j][i] -> i = estático.
            return False

    for j in range(0, N):
        if matriz[r][j] == 1:  # Barre horizontales desde la posición [r][j] -> r = estático.
            return False

    for j in range(0, N):  # Barre diagonales
        for k in range(0, N):
            if ((matriz[j][k]) == 1) and ((j + k == r + i) or (j - k == r - i)):
                return False

    return True


def solveNQUtil(matriz, r, x, y, N):
    if r == N and matriz[x][y] == 1:
        printSolution(matriz, N)  # llega a su fin, se imprime la solución
        return 0
    for i in range(0, N):
        if isSafe(matriz, r, i, N) or (x == r and y == i):

            # La segunda condición solo se cumple cuando se verifica la posición inicial dentro del bucle.
            # r avanza en cuanto a filas disponibles, i avanza en columnas.

            matriz[r][i] = 1
            l = solveNQUtil(matriz, r + 1, x, y, N)
            if l == 0:
                return False
            if x != r and y != i:
                matriz[r][i] = 0


def nqueens_6(n, x, y):
    matriz = [[0 for i in range(n)] for i in range(n)]  # Se crea la matriz
    matriz[x][y] = 1    # Se da la posición inicial
    inicio = time.time()
    solveNQUtil(matriz, 0, x, y, n)
    fin = time.time()

    return fin - inicio

print(nqueens_6(16, 5, 3))

