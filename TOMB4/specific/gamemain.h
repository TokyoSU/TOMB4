#pragma once
#include "../global/vars.h"

void inject_gamemain(bool replace);

void GameClose();
unsigned int __stdcall GameMain(void* ptr);
ushort GetRandom(WATERTAB* wt, long lp);
void init_water_table();
bool GameInitialise();
long S_SaveGame(long slot_num);
long S_LoadGame(long slot_num);

extern WATERTAB WaterTable[22][64];
extern THREAD MainThread;
extern float vert_wibble_table[32];
extern long SaveCounter;
extern short FPCW;
