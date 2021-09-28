#include "types.h"
#include "user.h"

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

#define false 0
#define true 1
#define BG 0x2E

/*                                  WONEJO
BG, BG, BG, BG, 0x00, 0x00, BG, 0x00, 0x00, BG, BG, BG, BG
BG, BG, BG, 0x00, 0xFF, 0x00, BG, 0x00, 0xFF, 0x00, BG, BG, BG
BG, BG, 0x00, 0xFF, 0xFF, 0x00, BG, 0x00, 0xFF, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0xFF, 0x00, BG, 0x00, 0xFF, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0xFF, 0x00, BG, 0x00, 0xFF, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0xFF, 0x00, BG, 0x00, 0xFF, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0xFF, 0x00, BG, 0x00, 0xFF, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0x08, 0x00, BG, 0x00, 0x08, 0xFF, 0x00, BG, BG
BG, BG, 0x00, 0xFF, 0x08, 0x00, BG, 0x00, 0x08, 0xFF, 0x00, BG, BG
BG, BG, BG, 0x00, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00, BG, BG, BG
BG, BG, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, BG, BG
BG, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, BG
BG, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, BG
0x00, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x00
0x00, 0x08, 0x08, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x08, 0x08, 0x00
0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00
BG, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, BG
BG, BG, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, BG, BG
*/

static void
print_letter(char letter, int x, int y)
{
  //arriba
  plotrectangle(x, y, x+24, y+8, 0x00);
  if(letter == 't' || letter == 'i')
    //medio vertical
    plotrectangle(x+8, y+8, x+16, y+32, 0x00);
  else
    // izquierda
    plotrectangle(x, y+8, x+8, y+32, 0x00);
  if(letter == 'c' || letter == 'e' || letter == 'i' || letter == 'o')
    //abajo
    plotrectangle(x, y+24, x+24, y+32, 0x00);
  if(letter == 'a' || letter == 'o')
    //derecha
    plotrectangle(x+16, y, x+24, y+32, 0x00);
  if(letter == 'a' || letter == 'e')
    //medio horizontal
    plotrectangle(x+8, y+12, x+16, y+20, 0x00);
}

static void
init_board(void)
{
  //fondo
  plotrectangle(0, 0, 100, 200, 0x3F);
  plotrectangle(100, 0, 320, 200, BG);
  //tablero
  plotrectangle(178, 8, 180, 192, 0x3F);
  plotrectangle(240, 8, 242, 192, 0x3F);
  plotrectangle(118, 68, 302, 70, 0x3F);
  plotrectangle(118, 130, 302, 132, 0x3F);

  // title: TIC TAC TOE
  print_letter('t', 10, 12);
  print_letter('i', 38, 12);
  print_letter('c', 66, 12);

  print_letter('t', 10, 52);
  print_letter('a', 38, 52);
  print_letter('c', 66, 52);

  print_letter('t', 10, 92);
  print_letter('o', 38, 92);
  print_letter('e', 66, 92);
}

void
update_cell(int row, int column, char turn)
{}

void
show_turn(char turn)
{}

void
occupied_cell(int row, int column)
{}

void
invalid_cell(void)
{}

void
show_result(char winner)
{}

static int
get_cell(void)
{
  char *tmp = "\0";
  tmp = gets(tmp, 2);
  return atoi(tmp);
}

char
get_winner(char board[BOARD_SIZE][BOARD_SIZE], int row, int column)
{
  char winner = '-';
  int winner_diag1_O = true, winner_diag2_O = true, winner_diag1_X = true, winner_diag2_X = true;
  int winner_row_O = true, winner_col_O = true, winner_row_X = true, winner_col_X = true;

  for (int k = 0; k < BOARD_SIZE; k++){
    winner_col_O = winner_col_O && board[row][k] == 'O';
    winner_row_O = winner_row_O && board[k][column] == 'O';
    winner_col_X = winner_col_X && board[row][k] == 'X';
    winner_row_X = winner_row_X && board[k][column] == 'X';
  }

  for (int k = 0; k < BOARD_SIZE; k++){
    winner_diag1_O = winner_diag1_O && board[k][k] == 'O';
    winner_diag2_O = winner_diag2_O && board[BOARD_SIZE][BOARD_SIZE - k] == 'O';
    winner_diag1_X = winner_diag1_X && board[k][k] == 'X';
    winner_diag2_X = winner_diag2_X && board[BOARD_SIZE][BOARD_SIZE - k] == 'X';
  }

  if (winner_diag1_O || winner_diag2_O || winner_row_O || winner_col_O) 
    winner = 'O';
  if (winner_diag1_X || winner_diag2_X || winner_row_X || winner_col_X) 
    winner = 'X';

  return winner;
}

int
main(void)
{
  char board[BOARD_SIZE][BOARD_SIZE] = {
    { '-', '-', '-' },
    { '-', '-', '-' },
    { '-', '-', '-' }
  };
  char turn = uptime() % 2 ? 'X' : 'O';   // pseudo-random first turn
  char winner = '-';
  int cell, free_cells = 9;

  modeswitch(1);
  init_board();

  while (winner == '-' && free_cells != 0){
    show_turn(turn);
    cell = get_cell();
    cell--;     // transform cell index to be 0-based
    if (cell >= 0 && cell <= CELL_MAX){
      int row = cell / BOARD_SIZE;
      int column = cell % BOARD_SIZE;
      if (board[row][column] == '-'){
        free_cells--;
        board[row][column] = turn;
        update_cell(row, column, turn);
        turn = turn == 'X' ? 'O' : 'X';
        winner = get_winner(board, row, column);
      } else
        occupied_cell(row, column);
    } else
      invalid_cell();
  }
  show_result(winner);

  exit();
}
