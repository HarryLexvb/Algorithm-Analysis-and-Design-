import time

move_x = [1, 1, 2, 2, -1, -1, -2, -2]
move_y = [2, -2, 1, -1, 2, -2, 1, -1]


def printSolution(n, arr):
    for i in range(n):
        for j in range(n):
            print(arr[i][j], end=' ')
        print()


def isSafe(x, y, arr, n):
    # Verífica que no se sobrepase los limites de la matriz y que la posición a verificar no se haya tomado previamente.
    if x < 0 or x > n - 1 or y < 0 or y > n - 1 or arr[x][y] > 0:
        return False
    return True


def getDegree(arr, n, x, y):
    # Verifica los caminos posibles, en caso de no tener caminos posibles se retorna -1
    res = -1
    for i in range(8):
        if isSafe(x + move_x[i], y + move_y[i], arr, n):
            res = res + 1
    return res


def solve(n, arr, curr_x, curr_y, pos):
    id1 = -1
    min_degree1 = n + 1
    arr[curr_x][curr_y] = pos
    if pos == n ** 2:
        printSolution(n, arr)   # Encuentra la solución, imprime el array
        return True

    for i in range(8):
        new_x = curr_x + move_x[i]
        new_y = curr_y + move_y[i]
        if isSafe(new_x, new_y, arr, n):
            degree = getDegree(arr, n, new_x, new_y)
            if degree <= min_degree1:
                min_degree1 = degree
                id1 = i
    if id1 == -1:
        print('No hay solución')
        return False
    nx = curr_x + move_x[id1]
    ny = curr_y + move_y[id1]
    solve(n, arr, nx, ny, pos + 1)


def horse_6(n, x, y):
    pos_x = x
    pos_y = y
    arr = [[-1 for i in range(n)] for i in range(n)]
    pos = 1     # Contador de las posiciones tomadas, se va reemplazando en la matriz.

    inicio = time.time()
    solve(n, arr, pos_x, pos_y, pos)
    fin = time.time()
    return fin - inicio


print(horse_6(16, 6, 1))