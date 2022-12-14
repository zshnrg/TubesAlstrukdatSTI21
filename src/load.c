#include <stdio.h>
#include <unistd.h>
#include "load.h"

void load(TabKata *listGame, Stack* historyGame, Word fileName, Scoreboard *SB) {
    TabKata addedGame;
    MakeEmpty(&addedGame);

    char file[50] = ".txt";
    for (int i = 0; i < fileName.Length; i++) {
        file[i] = fileName.TabWord[i];
    }
    file[fileName.Length] = '\0';

    readTxt(file, &addedGame, historyGame, SB);

    for (int i = 0; i < addedGame.Neff; i++) {
        if (!IsMember(*listGame, addedGame.TK[i])) {
            SetEl(listGame, (*listGame).Neff, addedGame.TK[i]);
        }
    }
    if(!IsEmpty(addedGame)) {
        printf("Save file berhasil dibaca. BNMO berhasil dijalankan.\n\n");
        stateBNMO = true;
    } else {
        printf("Save file gagal dibaca.\n\n");
    }
    fflush(stdout);
}