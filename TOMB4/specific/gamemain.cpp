#include "../tomb4/pch.h"
#include "gamemain.h"
#include "audio.h"
#include "file.h"
#include "function_stubs.h"
#include "function_table.h"
#include "3dmath.h"
#include "../game/text.h"
#include "time.h"
#include "winmain.h"
#include "../game/sound.h"
#include "../game/gameflow.h"
#ifdef DISCORD_RPC
#include "../tomb4/tomb4.h"
#endif

static uchar water_abs[4] = { 4, 8, 12, 16 };
static short water_shimmer[4] = { 31, 63, 95, 127 };
static short water_choppy[4] = { 16, 53, 90, 127 };

void GameClose()
{
	Log(2, "GameClose");
	ACMClose();
	FreeLevel();

	if (DestVB)
	{
		Log(4, "Released %s @ %x - RefCnt = %d", "Dest VB", DestVB, DestVB->Release());
		DestVB = 0;
	}
	else
		Log(1, "%s Attempt To Release NULL Ptr", "Dest VB");

	FREE(clipflags);

	if (wav_file_buffer)
		FREE(wav_file_buffer);

	if (ADPCMBuffer)
		FREE(ADPCMBuffer);

	FREE(malloc_buffer);
	FREE(gfScriptFile);
	FREE(gfLanguageFile);
}

unsigned int __stdcall GameMain(void* ptr)
{
	long fpcw;

	Log(2, "GameMain");

	if (GameInitialise())
	{
		InitialiseFunctionTable();
		HWInitialise();
		InitWindow(0, 0, App.dx.dwRenderWidth, App.dx.dwRenderHeight, 20, 20480, 80, App.dx.dwRenderWidth, App.dx.dwRenderHeight);
		InitFont();
		TIME_Init();
		App.SetupComplete = 1;
		fpcw = MungeFPCW(&FPCW);
		S_CDStop();
		ClearSurfaces();

		if (!App.SoundDisabled)
			SOUND_Init();

#ifdef DISCORD_RPC
		RPC_Init();
#endif

		DoGameflow();
		GameClose();
		S_CDStop();

#ifdef DISCORD_RPC
		RPC_close();
#endif

		if (fpcw)
			RestoreFPCW(FPCW);

		PostMessage(App.hWnd, WM_CLOSE, 0, 0);
		MainThread.active = 0;
		_endthreadex(1);
	}

	return 1;
}

ushort GetRandom(WATERTAB* wt, long lp)
{
	long loop;
	ushort ret;

	do
	{
		ret = rand() & 0xFC;

		for (loop = 0; loop < lp; loop++)
			if (wt[loop].random == ret)
				break;

	} while (loop != lp);

	return ret;
}

void init_water_table()
{
	long lSin;
	short sin, angle;

	srand(121197);

	for (int i = 0; i < 64; i++)
	{
		sin = rcossin_tbl[i << 7];
		WaterTable[0][i].shimmer = (63 * sin) >> 15;
		WaterTable[0][i].choppy = (16 * sin) >> 12;
		WaterTable[0][i].random = (uchar)GetRandom(&WaterTable[0][0], i);
		WaterTable[0][i].abs = 0;

		WaterTable[1][i].shimmer = (32 * sin) >> 15;
		WaterTable[1][i].choppy = 0;
		WaterTable[1][i].random = (uchar)GetRandom(&WaterTable[1][0], i);
		WaterTable[1][i].abs = -3;

		WaterTable[2][i].shimmer = (64 * sin) >> 15;
		WaterTable[2][i].choppy = 0;
		WaterTable[2][i].random = (uchar)GetRandom(&WaterTable[2][0], i);
		WaterTable[2][i].abs = 0;

		WaterTable[3][i].shimmer = (96 * sin) >> 15;
		WaterTable[3][i].choppy = 0;
		WaterTable[3][i].random = (uchar)GetRandom(&WaterTable[3][0], i);
		WaterTable[3][i].abs = 4;

		WaterTable[4][i].shimmer = (127 * sin) >> 15;
		WaterTable[4][i].choppy = 0;
		WaterTable[4][i].random = (uchar)GetRandom(&WaterTable[4][0], i);
		WaterTable[4][i].abs = 8;

		for (int j = 0, k = 5; j < 4; j++, k += 4)
		{
			for (int m = 0; m < 4; m++)
			{
				WaterTable[k + m][i].shimmer = -((sin * water_shimmer[m]) >> 15);
				WaterTable[k + m][i].choppy = sin * water_choppy[j] >> 12;
				WaterTable[k + m][i].random = (uchar)GetRandom(&WaterTable[k + m][0], i);
				WaterTable[k + m][i].abs = water_abs[m];
			}
		}
	}

	for (int i = 0; i < 32; i++)
	{
		angle = 0x10000 * i / 32;
		lSin = phd_sin(angle);
		vert_wibble_table[i] = float(sin >> (W2V_SHIFT - 1));
	}

	for (int i = 0; i < 256; i++)
	{
		angle = 0x10000 * i / 256;
		lSin = phd_sin(angle);
		unused_vert_wibble_table[i] = float(sin >> (W2V_SHIFT - 5));
	}
}

void inject_gamemain(bool replace)
{
	INJECT(0x004770C0, GameClose, replace);
	INJECT(0x00476EC0, GameMain, replace);
	INJECT(0x004773F0, GetRandom, replace);
	INJECT(0x00477180, init_water_table, replace);
}
