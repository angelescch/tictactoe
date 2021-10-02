#include "types.h"
#include "user.h"
#include "bitmaps.h"

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

#define false 0
#define true 1

// Rules
char *intro = 
" \
--------------------- TIC TAC TOE ---------------------\n\
This is a 2-players game and it is played on a 3x3 grid.\n\
The first to get 3 marks in a row is the winner.\n\
The cells are mapped to the keyboard in the following way\n\
                        |7|8|9|\n\
                        |4|5|6|\n\
                        |1|2|3|\n\
For example: if you hit the key '5' you will place your \n\
mark in the middle of the board. As well, if you hit \n\
'7' you will play on the top-left cell; and so on...\n\
Thus, the only valid plays are the numbers from 1 to 9.\n\
\n\
There are two characters; the turtle and the hare,\n\
the first turn is decided randomly, and it will be shown on\n\
the left, at the bottom of the tittle. Each player \n\
gets to play only one mark per-turn. And it is not\n\
valid to chose an occupied cell.\n\
(If you want to quit the game before it finishes you can press 'q')\n\
\n\
Are you ready to be amazed by this game? [y/n]\n\
";

static void
plot_board(int color)
{
  plotrectangle(116,  6, 118, 194, color);
  plotrectangle(178,  8, 180, 192, color);
  plotrectangle(240,  8, 242, 192, color);
  plotrectangle(302,  6, 304, 194, color);
  plotrectangle(118,  6, 302,   8, color);
  plotrectangle(118, 68, 302,  70, color);
  plotrectangle(118,130, 302, 132, color);
  plotrectangle(118,192, 302, 194, color);
}

static void
init_background(void)
{
  // Background
  plotrectangle(0, 0, 100, 200, BGND);
  plotrectangle(100, 0, 320, 200, ORNG);

  // Tic-tac-toe board
  plot_board(WHTE);

  // Title: TIC TAC TOE
  printchar('T', 10, 12, 0x0, 3);
  printchar('i', 38, 12, 0x0, 3);
  printchar('c', 66, 12, 0x0, 3);

  printchar('t', 10, 52, 0x0, 3);
  printchar('A', 38, 52, 0x0, 3);
  printchar('c', 66, 52, 0x0, 3);

  printchar('T', 10, 92, 0x0, 3);
  printchar('o', 38, 92, 0x0, 3);
  printchar('E', 66, 92, 0x0, 3);

  // Hare & Turtle playing Ilustration
  printimage(30, 18, 39, 161, draw1, 2);
  printimage(18, 12, 5, 171, draw2, 2);
}

/* update_cell dibuja la ficha correspondiente al
 * turno que se le pasa.
 * X = liebre; O = tortuga
*/
void
update_cell(int row, int column, char turn)
{
  if (turn == 'X')
    printimage(13, 18, 135+62*column, 144-62*row, hare, 2);
  if (turn == 'O')
    printimage(18, 12, 130+62*column, 150-62*row, turtle, 2);
}

/* Muestra (en un lugar a determinar, puede ser abajo
 * de "TICTACTOE") el personaje del turno correspondiente
*/
void
show_turn(char turn)
{
  plotrectangle(36, 134, 62, 160, ORNG);
  if (turn == 'X')
    printimage(13, 18, 42, 138, hare, 1);
  if (turn == 'O')
    printimage(18, 12, 40, 141, turtle, 1);
}

/* Hace una pequeña animación, en la celda que se le pasa
 * indicando que no se puede poner una ficha ahí
 * (le dibuja un marco rojo por un instante)
*/
void
occupied_cell(int row, int column)
{
  plotrectangle(116+62*column, 130-62*row, 180+62*column, 132-62*row, 0x04);
  plotrectangle(116+62*column, 132-62*row, 118+62*column, 192-62*row, 0x04);
  plotrectangle(178+62*column, 132-62*row, 180+62*column, 192-62*row, 0x04);
  plotrectangle(116+62*column, 192-62*row, 180+62*column, 194-62*row, 0x04);
  sleep(100);
  plotrectangle(116+62*column, 130-62*row, 180+62*column, 132-62*row, 0x3F);
  plotrectangle(116+62*column, 132-62*row, 118+62*column, 192-62*row, 0x3F);
  plotrectangle(178+62*column, 132-62*row, 180+62*column, 192-62*row, 0x3F);
  plotrectangle(116+62*column, 192-62*row, 180+62*column, 194-62*row, 0x3F);
}

/* Indica que la celda ingresada no se corresponde
 * con ninguna del tablero.
*/
void
invalid_cell(void)
{
  plot_board(0x04);
  sleep(100);
  plot_board(WHTE);
}

/* Muestra el ganador o en caso de empate
 * algo que lo indique
*/
void
show_result(char winner)
{
  plotrectangle(0,0,320, 200, ORNG);
  switch (winner)
  {
  case 'X':
    printimage(13, 18, 95, 10, hare, 10);
    char *msg1 = " Hare wins! "; 
    for(int i=0; i<12; i++){
      printchar(msg1[i], 0 + i*8, 100, 0x0, 1);
    }
    break;
  case 'O':
    printimage(18, 12, 70, 40, turtle, 10);
    char *msg2 = "Turtle wins!";
    for(int i=0; i<12; i++){
      printchar(msg2[i], 100 + i*8, 175, 0x0, 1);
    }
    break;
  default:
    printimage(13, 18, 188, 20, hare, 8);
    printimage(18, 12, 28, 60, turtle, 8);
    char *msg3 = "It's a tie!!";
    for(int i=0; i<12; i++){
      printchar(msg3[i], 100 + i*8, 175, 0x0, 1);
    }
    break;
  }
  sleep(500);
}

/* Dada la situación de la partida devuelve el
 * ganador ('X' ó 'O') o en caso de que no haya
 * terminado el juego o fue empate '-'
*/
char
get_winner(char board[BOARD_SIZE][BOARD_SIZE], int row, int column)
{
  char winner = '-';
  int winner_diag1_O = true, winner_diag2_O = true;
  int winner_diag1_X = true, winner_diag2_X = true;
  int winner_row_O = true, winner_col_O = true;
  int winner_row_X = true, winner_col_X = true;

  for (int k = 0; k < BOARD_SIZE; k++){
    winner_col_O = winner_col_O && board[row][k] == 'O';
    winner_row_O = winner_row_O && board[k][column] == 'O';
    winner_col_X = winner_col_X && board[row][k] == 'X';
    winner_row_X = winner_row_X && board[k][column] == 'X';
  }

  for (int k = 0; k < BOARD_SIZE; k++){
    winner_diag1_O = winner_diag1_O && board[k][k] == 'O';
    winner_diag2_O = winner_diag2_O && board[k][BOARD_SIZE - k - 1] == 'O';
    winner_diag1_X = winner_diag1_X && board[k][k] == 'X';
    winner_diag2_X = winner_diag2_X && board[k][BOARD_SIZE - k - 1] == 'X';
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
  // Init in text mode
  printf(1, intro);
  char *ans = "\0";
  ans = gets(ans, 2);
  if (strcmp("y", ans)!=0)
    exit();

  char board[BOARD_SIZE][BOARD_SIZE] = {
    { '-', '-', '-' },
    { '-', '-', '-' },
    { '-', '-', '-' }
  };
  char turn = uptime() % 2 ? 'X' : 'O';   // pseudo-random first turn
  char winner = '-';
  int cell, free_cells = 9;
  modeswitch(1);
  init_background();

  while (winner == '-' && free_cells != 0){
    show_turn(turn);
    cell = getc();
    if (cell=='q'){
      modeswitch(0);
      exit();
    }
    cell = cell - '0';
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
  modeswitch(0);
  exit();
}
