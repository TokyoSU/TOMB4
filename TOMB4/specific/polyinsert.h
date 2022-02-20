#pragma once
#include "../global/vars.h"

void inject_polyinsert(bool replace);

void HWR_DrawSortList(D3DTLBUMPVERTEX* info, short num_verts, short texture, short type);
void DrawSortList();

#define CalcColorSplit	( (void(__cdecl*)(D3DCOLOR, D3DCOLOR*)) 0x00484A20 )
#define InitialiseSortList	( (void(__cdecl*)()) 0x00481860 )
#define SortPolyList	( (void(__cdecl*)(long, SORTLIST**)) 0x00481810 )
#define InitialiseFogBulbs	( (void(__cdecl*)()) 0x00481DF0 )
#define CreateFXBulbs	( (void(__cdecl*)()) 0x004819B0 )
#define ClearFXFogBulbs	( (void(__cdecl*)()) 0x004818A0 )
#define IsVolumetric	( (long(__cdecl*)()) 0x00481AD0 )
#define AddQuadClippedSorted	( (void(__cdecl*)(D3DTLVERTEX*, short, short, short, short, TEXTURESTRUCT*, long)) 0x004842A0 )