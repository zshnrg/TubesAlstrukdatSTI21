#ifndef QUIT_H
#define QUIT_H

#include "./save.h"
#include "./start.h"
#include "./adt/array.h"
#include "./adt/scoreboardtype.h"

/* MODUL Save */

void quit(TabKata listGame, Stack historyGame, Scoreboard *SB);
/*  Keluar program BNMO.
    I.S. stateBNMO true.
    F.S. stateBNMO false.
*/

#endif