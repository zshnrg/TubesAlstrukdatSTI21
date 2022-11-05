#ifndef BNMO_CONSOLE_H
#define BNMO_CONSOLE_H

#include <stdio.h>
#include "./src/adt/array.h"
#include "./src/adt/circular_queue.h"
#include "./src/adt/mesinkata.h"

#include "./src/start.h"

void menuList(TabKata *listGame, Queue *queueGame);
/* Memilih menu BNMO
    I.S. listGame dan queueGame terdefinisi mungkin kosong
    F.S. Menu dijalankan sesuai dengan input user
*/

#endif