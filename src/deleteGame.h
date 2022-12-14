#ifndef DELETE_GAME_H
#define DELETE_GAME_H

#include "./adt/array.h"
#include "./adt/queue.h"
#include "./adt/stack.h"
#include "./adt/scoreboardtype.h"

void deleteGame(TabKata *listGame, Queue queueGame, Stack *historyGame, Scoreboard *SB);
/* Menghapus game yang ada pada listGame
   I.S. listGame terdefinisi tidak kosong
   F.S. Game yang dipilih dihapus dari listGame,
   game yang dihapus merupaakn game buatan user */

#endif