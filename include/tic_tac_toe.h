#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#define SIZE 3 // Define the size of the board

// Function prototypes
void initialize_board();
void display_board();
void display_score();
void clear_screen();
int is_winner(char symbol);
int is_draw();
void player_move();
void computer_move(int difficulty);
int minimax(char board[SIZE][SIZE], int depth, int isMaximizing);
int check_available_moves();
void play_game(int difficulty);
int prompt_difficulty();

#endif // TIC_TAC_TOE_H
