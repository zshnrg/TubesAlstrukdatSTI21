#ifndef BNMO_CONSOLE_H
#define BNMO_CONSOLE_H

#include <stdio.h>
#include <unistd.h>
#include "./src/adt/array.h"
#include "./src/adt/queue.h"
#include "./src/adt/mesinkata.h"
#include "./src/adt/listlinier.h"
#include "./src/adt/map.h"
#include "./src/adt/set.h"
#include "./src/adt/stack.h"

#include "./src/start.h"
#include "./src/save.h"
#include "./src/load.h"
#include "./src/createGame.h"
#include "./src/listGame.h"
#include "./src/deleteGame.h"
#include "./src/queueGame.h"
#include "./src/playGame.h"
#include "./src/skipGame.h"
#include "./src/quit.h"
#include "./src/help.h"
#include "./src/history.h"
#include "./src/resetHistory.h"
#include "./src/scoreboard.h"
#include "./src/resetScoreboard.h"
#include "./src/function.h"

void menuList(TabKata *listGame, Queue *queueGame, Stack *historyGame, Scoreboard *SB);
/* Memilih menu BNMO
    I.S. listGame dan queueGame terdefinisi mungkin kosong
    F.S. Menu dijalankan sesuai dengan input user
*/

#endif
