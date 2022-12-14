#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "towerOfHanoi.h"

int power(int x, int y) {
    int result = 1;
    for (int i = 0; i < y; i++) {
        result = result * x;
    }
    return result;
}

int playTowerOfHanoi() {
    int nDisk = 5;
    int score = 10, turn = 0;
    float minus = 1;


    clear();
    do {    
        currentWord = toKata("START");
        do {
            printf("Jumlah piringan: %d\n", nDisk);
            printf("\nSelamat datang di Tower of Hanoi! Gunakan perintah di bawah ini.\n");
            printf("| CHANGE DISK\t Mengganti jumlah piringan\n");
            printf("| START\t\t Memulai permainan\n\n");
            if (!(IsWordEq(currentWord, toKata("CHANGE DISK")) || IsWordEq(currentWord, toKata("START")))) printf("Perintah tidak valid!\n");
            printf("> ");
            GetCommand();
            clear();
        } while (!(IsWordEq(currentWord, toKata("CHANGE DISK")) || IsWordEq(currentWord, toKata("START"))));

        if (IsWordEq(currentWord, toKata("CHANGE DISK"))) {
            int n = 1;
            do {
                clear();
                printf("Jumlah piringan: %d\n\n", nDisk);
                if (n < 1) printf("Jumlah piringan tidak valid!\n");
                printf("Masukkan jumlah piringan baru: ");
                GetCommand();
                n = 0;
                for (int i = 0; i < currentWord.Length; i ++) {
                    n *= 10;
                    n += currentWord.TabWord[i] - '0';
                }
            } while (n < 1);
            nDisk = n;
            score = nDisk * 2;
        }
        clear();
    } while (!IsWordEq(currentWord, toKata("START")));
    clear();

    printGuideToH();

    int idealMove = power(2, nDisk) - 1;

    Stack T1, T2, T3;
    CreateEmptyStack(&T1);
    CreateEmptyStack(&T2);
    CreateEmptyStack(&T3);

    // Initialization
    for (int i = nDisk - 1; i >= 0; i--) {
        Word disk; disk.Length = 0;
        for (int j = 0; j < (i * 2) + 1; j  ++) {
            disk.TabWord[disk.Length] = '#';
            disk.Length++;
        }
        Push(&T1, disk);
    }

    
    Word Tin, Tout;
    boolean takeTurn;
    boolean isQuit = false;
    while (!(NbElmtStack(T3) == nDisk) && !isQuit) {
        takeTurn = false;
        printTower(T1, T2, T3, nDisk);
        printf("\nTIANG ASAL   : ");
        GetCommand();
        
        if ((currentWord.Length == 1) && (currentWord.TabWord[0] - 'A' >= 0) && (currentWord.TabWord[0] - 'A' < 3)) {
            Tout = currentWord;
            printf("TIANG TUJUAN : ");
            GetCommand();
            if ((currentWord.Length == 1) && (currentWord.TabWord[0] - 'A' >= 0) && (currentWord.TabWord[0] - 'A' < 3)) {
                Tin = currentWord;
                if (IsWordEq(Tin, Tout)) {
                    printf("\nTiang yang dipilih tidak boleh sama.");
                } else {
                    if (Tout.TabWord[0] == 'A') {
                        if (Tin.TabWord[0] == 'B') {
                            takeTurn = moveDisk(&T1, &T2);
                        } else {
                            takeTurn = moveDisk(&T1, &T3);
                        }
                    } else if (Tout.TabWord[0] == 'B') {
                        if (Tin.TabWord[0] == 'A') {
                            takeTurn = moveDisk(&T2, &T1);
                        } else {
                            takeTurn = moveDisk(&T2, &T3);
                        }
                    } else {
                        if (Tin.TabWord[0] == 'A') {
                            takeTurn = moveDisk(&T3, &T1);
                        } else {
                            takeTurn = moveDisk(&T3, &T2);
                        }
                    }
                    if (turn > idealMove && minus < score - 1 && takeTurn) {
                        minus = minus * (float) (1 + (0.48 / nDisk));
                    }
                    if (takeTurn) {
                        printf("\nMemindahkan piringan ke %c...", Tin.TabWord[0]);
                        turn++;
                    }
                }
            } else if (IsWordEq(currentWord, toKata("Q"))) {
                printf("\nBerhasil keluar permainan.");
                isQuit = true;
            } else {
                printf("\nMasukan tiang tidak valid.");
            }
        } else if (IsWordEq(currentWord, toKata("Q"))) {
            printf("\nBerhasil keluar permainan.");
            isQuit = true;
        } else {
            printf("\nMasukan tiang tidak valid.");
        }
        fflush(stdout); sleep(2);
        clear();
    }
    if (turn > idealMove) {
        score = score - (int) minus;
    }
    if (isQuit) score = 0;
    printTower(T1, T2, T3, nDisk);
    if (!isQuit) printf("\nKamu berhasil!\n\nSkor didapatkan: %d\n\n", score);
    else printf("\nBoo! Kamu gagal menyelesaikan permanan >:(.\nSkor akhir: %d\n\n", score);
    return score;
}

boolean moveDisk(Stack* Tout, Stack* Tin) {
    if (IsEmptyStack(*Tout)) {
        printf("\nTiang asal kosong!\n");
        return false;
    }
    infotype moved, top;
    Pop(Tout, &moved);
    if (!IsEmptyStack(*Tin)) {
        if (InfoTop(*Tin).Length < moved.Length) {
            printf("\nPiringan tidak dapat menimpa piringan yang lebih kecil.\n");
            Push(Tout, moved);
            return false;
        }
    }
    Push(Tin, moved);
    return true;
}

void printTower(Stack T1, Stack T2, Stack T3, int nDisk) {
    int towerHeight = 3, towerWide = 5, baseWide = 5, diskRadius = 2;
    if (nDisk > 3) {
        towerHeight = nDisk;
        baseWide = nDisk * 2 - 3;
        towerWide = baseWide + 2;
        diskRadius = nDisk - 1;
    }

    infotype disk;
    for (int i = 0; i < towerHeight; i++) {
        if (towerHeight - i == NbElmtStack(T1)) {
            Pop(&T1, &disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
            TulisWord(disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
        } else {
            for (int j = 0; j < towerWide; j++) {
                if (j == towerWide / 2) printf("|");
                else printf(" ");
            }
        }
        if (towerHeight - i == NbElmtStack(T2)) {
            Pop(&T2, &disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
            TulisWord(disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
        } else {
            for (int j = 0; j < towerWide; j++) {
                if (j == towerWide / 2) printf("|");
                else printf(" ");
            }
        }
        if (towerHeight - i == NbElmtStack(T3)) {
            Pop(&T3, &disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
            TulisWord(disk);
            for (int j = disk.Length / 2; j < diskRadius; j++) {
                printf(" ");
            }
        } else {
            for (int j = 0; j < towerWide; j++) {
                if (j == towerWide / 2) printf("|");
                else printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < towerWide; j ++) {
            if ((towerWide - baseWide) / 2 < j && towerWide - ((towerWide - baseWide) / 2) - 1 > j) printf("=");
            else if (j == (towerWide - baseWide) / 2) printf("[");
            else if (towerWide - ((towerWide - baseWide) / 2) - 1 == j) printf("]");
            else printf(" ");
        }
    }
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < towerWide / 2; j++) printf(" ");
        printf("%c", 'A' + i);
        for (int j = 0; j < towerWide / 2; j++) printf(" ");
    }
    printf("\n");
}

void printGuideToH() {
    for (int i = 8; i > 0; i--) {
        printf(" _______                                        ___      _______                     __ \n|_     _|.-----.--.--.--.-----.----.    .-----.'  _|    |   |   |.---.-.-----.-----.|__|\n  |   |  |  _  |  |  |  |  -__|   _|    |  _  |   _|    |       ||  _  |     |  _  ||  |\n  |___|  |_____|________|_____|__|      |_____|__|      |___|___||___._|__|__|_____||__|\n\n================================== Petunjuk Permainan ==================================\n\n1. Permainan berakhir jika semua piringan berhasil dipindah ke tiang C.\n2. Hanya satu piringan yang dapat dipindahkan dalam satu putaran.\n3. Setiap putaran terdiri dari mengambil piringan bagian atas dari salah satu tumpukan\n   dan meletakkannya di atas tumpukan lainnya. Dengan kata lain, sebuah piringan hanya\n   dapat dipindahkan jika itu adalah piringan paling atas di tumpukan.\n4. Piringan yang lebih besar tidak boleh ditempatkan di atas piringan yang lebih kecil.\n\n========================================================================================\n\nPermainan akan dimulai dalam %d ...", i);
        fflush(stdout); sleep(1);
        clear();
    }
}