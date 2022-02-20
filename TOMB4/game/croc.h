#pragma once
#include "../global/vars.h"

void inject_croc(bool replace);

void InitialiseCroc(short item_number);
void CrocControl(short item_number);
long GetFreeLocust();
void TriggerLocust(ITEM_INFO* item);
void InitialiseLocustEmitter(short item_number);
void ControlLocustEmitter(short item_number);
void DrawLocusts();
void UpdateLocusts();
void TriggerCrocgodMissile(PHD_3DPOS* pos, short room_number, short num);
void TriggerCrocgodMissileFlame(short fx_number, short xv, short yv, short zv);
void InitialiseCrocgod(short item_number);
void CrocgodControl(short item_number);