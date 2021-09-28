#include "types.h"
#include "user.h"

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

#define false 0
#define true 1
#define BG 0x2A

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

void
init_board(void)
{
  plotrectangle(0,0,319, 199, BG);
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
