// check move
int checkMove(int** arr, int column){
  if(column >7 && column<0){
    return 0;}
  if (arr[0][column]==0){
    return 1;
 }
return 0; 
}



// undoMove
void undoMove(int** arr, int row , int col){
    arr[row][col]=0;
}