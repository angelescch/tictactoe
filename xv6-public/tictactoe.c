#include "types.h"
#include "user.h"

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

#define false 0
#define true 1

//colors
#define  ORNG   0x2E   //orange
#define  WHTE   0x3F   //white
#define  GRAY   0x07   //gray
#define  LGRN   0x30   //light green
#define  DGRN   0x22   //dark green

// bitmaps
  char hare[]={
  ORNG, ORNG, ORNG, ORNG, 0x00, 0x00, ORNG, 0x00, 0x00, ORNG, ORNG, ORNG, ORNG,
  ORNG, ORNG, ORNG, 0x00, WHTE, 0x00, ORNG, 0x00, WHTE, 0x00, ORNG, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, 0x00, WHTE, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, GRAY, 0x00, ORNG, 0x00, GRAY, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, 0x00, WHTE, GRAY, 0x00, ORNG, 0x00, GRAY, WHTE, 0x00, ORNG, ORNG,
  ORNG, ORNG, ORNG, 0x00, GRAY, GRAY, 0x00, GRAY, GRAY, 0x00, ORNG, ORNG, ORNG,
  ORNG, ORNG, 0x00, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, 0x00, ORNG, ORNG,
  ORNG, 0x00, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, 0x00, ORNG,
  ORNG, 0x00, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, GRAY, 0x00, ORNG,
  0x00, GRAY, GRAY, 0x00, GRAY, GRAY, GRAY, GRAY, GRAY, 0x00, GRAY, GRAY, 0x00,
  0x00, GRAY, GRAY, 0x00, WHTE, WHTE, 0x00, WHTE, WHTE, 0x00, GRAY, GRAY, 0x00,
  0x00, GRAY, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, GRAY, 0x00,
  ORNG, 0x00, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, 0x00, ORNG,
  ORNG, ORNG, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, ORNG, ORNG,
  };
  char turtle[]={
  ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, DGRN, DGRN, DGRN, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG,
  ORNG, ORNG, ORNG, ORNG, ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG, ORNG,
  ORNG, ORNG, ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, ORNG, LGRN, LGRN, LGRN, LGRN, ORNG,
  ORNG, ORNG, ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, ORNG, LGRN, LGRN, 0x00, LGRN, LGRN,
  ORNG, ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, 0x00, LGRN, LGRN,
  ORNG, ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, LGRN, LGRN,
  ORNG, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, LGRN,
  LGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, ORNG, ORNG,
  LGRN, LGRN, LGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, ORNG, ORNG, ORNG,
  ORNG, ORNG, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, ORNG, ORNG, ORNG, ORNG, ORNG,
  ORNG, ORNG, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, ORNG, ORNG, ORNG, ORNG, ORNG,
  ORNG, ORNG, LGRN, LGRN, LGRN, ORNG, ORNG, ORNG, ORNG, ORNG, LGRN, LGRN, LGRN, ORNG, ORNG, ORNG, ORNG, ORNG,
  };
  char draw2[]={
  WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, DGRN, DGRN, DGRN, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, 
  WHTE, WHTE, WHTE, WHTE, WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, WHTE, 
  WHTE, WHTE, WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, WHTE, LGRN, LGRN, LGRN, LGRN, WHTE, 
  WHTE, WHTE, WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, WHTE, LGRN, LGRN, 0x00, LGRN, LGRN, 
  WHTE, WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, 0x00, LGRN, LGRN, 
  WHTE, WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, LGRN, LGRN, 
  WHTE, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, LGRN, 
  LGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, WHTE, WHTE, 
  LGRN, LGRN, LGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, DGRN, LGRN, LGRN, LGRN, WHTE, WHTE, WHTE, 
  WHTE, WHTE, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, WHTE, WHTE, WHTE, WHTE, WHTE, 
  WHTE, WHTE, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, LGRN, WHTE, WHTE, WHTE, WHTE, WHTE, 
  WHTE, WHTE, LGRN, LGRN, LGRN, WHTE, WHTE, WHTE, WHTE, WHTE, LGRN, LGRN, LGRN, WHTE, WHTE, WHTE, WHTE, 0x00
  };
  char draw1[]={
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,GRAY,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,GRAY,0x00,GRAY,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,GRAY,0x00,GRAY,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,0x00,0x00,GRAY,GRAY,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,GRAY,GRAY,GRAY,GRAY,GRAY,0x00,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,GRAY,0x00,WHTE,WHTE,GRAY,GRAY,GRAY,0x00,WHTE,WHTE,0x00,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,WHTE,WHTE,WHTE,GRAY,GRAY,WHTE,0x00,0x00,WHTE,WHTE,0x00,0x00,WHTE,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,GRAY,WHTE,WHTE,WHTE,WHTE,GRAY,GRAY,0x00,0x00,WHTE,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,GRAY,GRAY,GRAY,GRAY,0x00,0x00,WHTE,WHTE,
  WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,0x00,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,GRAY,GRAY,WHTE,GRAY,GRAY,GRAY,0x00,WHTE,WHTE,
  WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,0x00,WHTE,WHTE,GRAY,GRAY,0x00,0x00,WHTE,
  WHTE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,GRAY,GRAY,GRAY,0x00,WHTE,0x00,
  WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,WHTE,WHTE,WHTE,0x00,0x00,0x00,0x00,WHTE,WHTE,GRAY,WHTE,WHTE,WHTE,WHTE,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,WHTE,0x00,WHTE,WHTE,WHTE,0x00,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,GRAY,GRAY,0x00,0x00,0x00,WHTE,
  WHTE,0x00,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,WHTE,0x00,WHTE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,WHTE,WHTE,WHTE
  };

static void
print_letter(char letter, int x, int y)
{
  plotrectangle(x, y, x+24, y+8, 0x00);         // upper line (T, I, C, A, O and E)
  if(letter == 't' || letter == 'i')
    plotrectangle(x+8, y+8, x+16, y+32, 0x00);  // vertical line in the middle  (T, I)
  else
    plotrectangle(x, y+8, x+8, y+32, 0x00);     // left line (C, A, 0, E)
  if(letter == 'c' || letter == 'e' || letter == 'i' || letter == 'o')
    plotrectangle(x, y+24, x+24, y+32, 0x00);   //bottom line (I, E, C, O)
  if(letter == 'a' || letter == 'o')
    plotrectangle(x+16, y, x+24, y+32, 0x00);   //right line (A, O)
  if(letter == 'a' || letter == 'e')
    plotrectangle(x+8, y+12, x+16, y+20, 0x00); //horizonatal line in the middle (E, A)
}

static void
init_board(void)
{
  // Backgroung
  plotrectangle(0, 0, 100, 200, 0x3F);
  plotrectangle(100, 0, 320, 200, ORNG);

  // Tic-tac-toe board
  plotrectangle(116, 6, 118, 194, 0x3F);
  plotrectangle(178, 8, 180, 192, 0x3F);
  plotrectangle(240, 8, 242, 192, 0x3F);
  plotrectangle(302, 6, 304, 194, 0x3F);
  plotrectangle(118, 6, 302, 8, 0x3F);
  plotrectangle(118, 68, 302, 70, 0x3F);
  plotrectangle(118, 130, 302, 132, 0x3F);
  plotrectangle(118, 192, 302, 194, 0x3F);

  // Title: TIC TAC TOE
  print_letter('t', 10, 12);
  print_letter('i', 38, 12);
  print_letter('c', 66, 12);

  print_letter('t', 10, 52);
  print_letter('a', 38, 52);
  print_letter('c', 66, 52);

  print_letter('t', 10, 92);
  print_letter('o', 38, 92);
  print_letter('e', 66, 92);

  // Hare & Turtle playing Ilustration
  printimage(30,18,39,160, draw1, 2);
  printimage(18, 12, 5,171,draw2,2);
}

/* update_cell dibuja la ficha correspondiente al
 * turno que se le pasa.
 * X = liebre; O = tortuga
*/
void
update_cell(int row, int column, char turn)
{
  if (turn == 'X')
    printimage(30, 18, 118+62*column, 20+62*row, draw1, 2);
  if (turn == 'O')
    printimage(18, 12, 130+62*column, 26+62*row, draw2, 2);
}

/* Muestra (en un lugar a determinar, puede ser abajo
 * de "TICTACTOE") el personaje del turno correspondiente
*/
void
show_turn(char turn)
{
  if (turn == 'X')
    printimage(30, 18, 32, 134, draw1, 1);
  if (turn == 'O')
    printimage(18, 12, 38, 137, draw2, 1);
}

/* Hace una pequeña animación, en la celda que se le pasa
 * indicando que no se puede poner una ficha ahí
 * (le dibuja un marco rojo por un instante)
*/
void
occupied_cell(int row, int column)
{
  plotrectangle(116+62*column, 6+62*row, 180+62*column, 8+62*row, 4);
  plotrectangle(116+62*column, 68+62*row, 180+62*column, 70+62*row, 4);
  plotrectangle(116+62*column, 6+62*row, 118+62*column, 70+62*row, 4);
  plotrectangle(178+62*column, 6+62*row, 180+62*column, 70+62*row, 4);
  sleep(100);
  plotrectangle(116+62*column, 6+62*row, 180+62*column, 8+62*row, 0x3F);
  plotrectangle(116+62*column, 68+62*row, 180+62*column, 70+62*row, 0x3F);
  plotrectangle(116+62*column, 6+62*row, 118+62*column, 70+62*row, 0x3F);
  plotrectangle(178+62*column, 6+62*row, 180+62*column, 70+62*row, 0x3F);
}

/* Indica que la celda ingresada no se corresponde
 * con ninguna del tablero. (Puede ser un signo de
 * exclamación rojo)
*/
void
invalid_cell(void)
{}

/* Muestra el ganador o en caso de empate
 * algo que lo indique
*/
void
show_result(char winner)
{}

/* Toma un único char a través de un
* imput por teclado
*/
static int
get_cell(void)
{
  char *tmp = "\0";
  tmp = gets(tmp, 2);
  return atoi(tmp);
}

/* Dada la situación de la partida devuelve el
 * ganador ('X' ó 'O') o en caso de que no haya
 * terminado el juego o fue empate '-'
*/
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
