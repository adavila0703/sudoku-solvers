function drawBoard(array){
    cutOff = [ 2, 5 ];
    board = '';
    board += '-'.repeat(63) + '\n';
    for (let row = 0; row < 9; row++){
        for (let col = 0; col < 9; col++){
            board += slot(array[row][col])
            if (col == 8){
                board += '\n'
            }
        }
        if (cutOff.includes(row)){
            board += '-'.repeat(63) + '\n';
        }
    }
    return board
}

function slot(num){
    return '|  ' + String(num) + '  |';
}

function checkValid(array, row, col, num){
    let startingRow = row - row % 3;
    let startingCol = col - col % 3;

    for (let i = 0; i < 9; i++){
        if (array[row][i] == num){
            return false;
        }
    }
    for (let i = 0; i < 9; i++){
        if (array[i][col] == num){
            return false;
        }
    }
    for (let i = 0; i < 3; i++){
        for (let j = 0; j < 3; j++){
            if (array[i + startingRow][j + startingCol] == num){
                return false;
            }
        }
    }
    return true;
}

function findEmpty(array){
    for (let row = 0; row < 9; row++){
        for (let col = 0; col < 9; col++){
            if (array[row][col] == 0){
                return [row, col];
            }
        }
    }
    return null;
}

function solver(array){

    let replaceNum = [ 1, 2, 3, 4, 5, 6, 7, 8, 9];
    let cord = findEmpty(array);

    if (cord == null){
        return true;
    }

    for (let i = 0; i < replaceNum.length; i++){
        if (checkValid(array, cord[0], cord[1], replaceNum[i])){
            array[cord[0]][cord[1]] = replaceNum[i];
            if (solver(array)){
                return true;
            }
            array[cord[0]][cord[1]] = 0;
        }
    }
    return false;
}

let startTime = Date.now();
let array = [
     [ 5,3,0, 0,7,0, 0,0,0 ]
    ,[ 6,0,0, 1,9,5, 0,0,0 ]
    ,[ 0,9,8, 0,0,0, 0,6,0 ]
    ,[ 8,0,0, 0,6,0, 0,0,3 ]
    ,[ 4,0,0, 8,0,3, 0,0,1 ]
    ,[ 7,0,0, 0,2,0, 0,0,6 ]
    ,[ 0,6,0, 0,0,0, 2,8,0 ]
    ,[ 0,0,0, 4,1,9, 0,0,5 ]
    ,[ 0,0,0, 0,8,0, 0,7,9 ]
];

console.log(drawBoard(array));
solver(array);
console.log(drawBoard(array));
console.log('Solve Time -> ', Date.now() - startTime + 'm');