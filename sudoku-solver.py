import time

def draw_baord(array) -> None:
    cutoff = [2, 5]
    board = ''
    board += '-'*63 + "\n"
    for row in range(0, 9):
        for col in range(0, 9):
            board += slot(array[row][col])
            if col == 8:
                board += '\n'
        if row in cutoff:
            board += '-'*63 + "\n"
    board += '-'*63 + "\n"
    return board

def slot(num) -> str:
    return f"|  {num}  |"

def check_valid(array, row, col, num):
    starting_row = row - row % 3
    starting_col = col - col % 3

    for i in range(0, 9):
        if array[row][i] == num:
            return False

    for i in range(0, 9):
        if array[i][col] == num:
            return False

    for i in range(0, 3):
        for j in range(0, 3):
            if array[i + starting_row][i + starting_col] == num:
                return False
    
    return True

def find_empty(array) -> tuple:
    for row in range(0, 9):
        for col in range(0, 9):
            if array[row][col] == 0:
                return row, col
    return None

def solver(array) -> bool:
    cord = find_empty(array)
    if cord == None:
        return True

    for i in range(1, 10):
        if check_valid(array, cord[0], cord[1], i):
            array[cord[0]][cord[1]] = i
            if solver(array):
                return True
            array[cord[0]][cord[1]] = 0
    return False

if __name__ == '__main__':
    start_time = time.time()
    array = [
         [ 5,3,0, 0,7,0, 0,0,0 ]
        ,[ 6,0,0, 1,9,5, 0,0,0 ]
        ,[ 0,9,8, 0,0,0, 0,6,0 ]
        ,[ 8,0,0, 0,6,0, 0,0,3 ]
        ,[ 4,0,0, 8,0,3, 0,0,1 ]
        ,[ 7,0,0, 0,2,0, 0,0,6 ]
        ,[ 0,6,0, 0,0,0, 2,8,0 ]
        ,[ 0,0,0, 4,1,9, 0,0,5 ]
        ,[ 0,0,0, 0,8,0, 0,7,9 ]
    ]
    
    print(draw_baord(array))
    solver(array)
    print(draw_baord(array))
    print(f'Solve Time -> {time.time() - start_time}')