#include "../tomb4/pch.h"
#include "wraith.h"
#include "../specific/function_stubs.h"
#include "effect2.h"
#include "objects.h"
#include "sound.h"
#include "../specific/3dmath.h"
#include "control.h"
#include "items.h"
#include "traps.h"
#include "senet.h"

void InitialiseWraith(short item_number)
{
	ITEM_INFO* item;
	WRAITH_STRUCT* data;

	item = &items[item_number];
	data = (WRAITH_STRUCT*)game_malloc(8 * sizeof(WRAITH_STRUCT));
	item->data = data;
	item->item_flags[0] = 0;
	item->hit_points = 0;
	item->speed = WraithSpeed;

	for (int i = 0; i < 8; i++)
	{
		data->pos.x = item->pos.x_pos;
		data->pos.y = item->pos.y_pos;
		data->pos.z = item->pos.z_pos;
		data->zv = 0;
		data->yv = 0;
		data->xv = 0;
		data->b = 0;
		data->g = 0;
		data->r = 0;
		data++;
	}
}

void TriggerWraithFlame(long x, long y, long z, short xv, short yv, short zv, long objnum)
{
	SPARKS* sptr;
	uchar col;
	
	sptr = &spark[GetFreeSpark()];
	sptr->On = 1;

	if (objnum == WRAITH1)
	{
		sptr->sR = (GetRandomControl() & 0x1F) + 128;
		sptr->sG = (GetRandomControl() & 0x1F) + 48;
		sptr->sB = 24;
		sptr->dR = (GetRandomControl() & 0x1F) + 128;
		sptr->dG = (GetRandomControl() & 0x1F) + 64;
		sptr->dB = 24;
	}
	else if (objnum == WRAITH2)
	{
		sptr->sR = 24;
		sptr->sG = (GetRandomControl() & 0x1F) + 48;
		sptr->sB = (GetRandomControl() & 0x1F) + 128;
		sptr->dR = 24;
		sptr->dG = (GetRandomControl() & 0x1F) + 64;
		sptr->dB = (GetRandomControl() & 0x1F) + 128;
	}
	else
	{
		col = (GetRandomControl() & 0xF) + 64;
		sptr->sR = col;
		sptr->sG = col;
		sptr->sB = col;
		sptr->dR = col;
		sptr->dG = col;
		sptr->dB = sptr->sB + (GetRandomControl() & 0xF);
	}

	sptr->ColFadeSpeed = 4;
	sptr->FadeToBlack = 7;
	sptr->TransType = 2;
	sptr->Life = (GetRandomControl() & 7) + 12;
	sptr->sLife = sptr->Life;
	sptr->x = (GetRandomControl() & 0x1F) + x - 16;
	sptr->y = y;
	sptr->z = (GetRandomControl() & 0x1F) + z - 16;
	sptr->Friction = 85;
	sptr->Flags = 522;
	sptr->Xvel = xv;
	sptr->Yvel = yv;
	sptr->Zvel = zv;
	sptr->Gravity = 0;
	sptr->MaxYvel = 0;
	sptr->Scalar = 2;
	sptr->dSize = 2;
	sptr->Size = (GetRandomControl() & 0x1F) + 48;
	sptr->sSize = sptr->Size;
}

void TriggerWraithEffect(long x, long y, long z, short vel, long objnum)
{
	SPARKS* sptr;
	ulong scol, dcol;
	long rad, ang;
	uchar sr, sg, sb, dr, dg, db, col;

	if (objnum == WRAITH1)
	{
		sr = (GetRandomControl() & 0x1F) + 128;
		sg = (GetRandomControl() & 0x1F) + 48;
		sb = 24;
		dr = (GetRandomControl() & 0x1F) + 128;
		dg = (GetRandomControl() & 0x1F) + 48;
		db = 24;
	}
	else if (objnum == WRAITH2)
	{
		sr = 24;
		sg = (GetRandomControl() & 0x1F) + 48;
		sb = (GetRandomControl() & 0x1F) + 128;
		dr = 24;
		dg = (GetRandomControl() & 0x1F) + 48;
		db = (GetRandomControl() & 0x1F) + 128;
	}
	else
	{
		col = (GetRandomControl() & 0xF) + 64;
		sr = col;
		sg = col;
		sb = col;
		dr = col;
		dg = col;
		db = col;
	}

	scol = (sb << 24) | (sg << 16) | (sr << 8) | 1;			//sptr->On = 1; sptr->sR = sr; sptr->sG = sg; sptr->sB = sb;
	dcol = (0xFF << 24) | (db << 16) | (dg << 8) | dr;		//sptr->dR = dr; sptr->dG = dg; sptr->dB = sb; sptr->R = 0xFF;

	for (int i = 0; i < 15; i++)
	{
		sptr = &spark[GetFreeSpark()];
		*(ulong*)&sptr->On = scol;	//just.. why
		*(ulong*)&sptr->dR = dcol;
		sptr->ColFadeSpeed = 4;
		sptr->FadeToBlack = 7;
		sptr->TransType = 2;
		sptr->Life = (GetRandomControl() & 7) + 32;
		sptr->sLife = sptr->Life;
		sptr->x = (GetRandomControl() & 0x1F) + x - 16;
		sptr->y = (GetRandomControl() & 0x1F) + y - 16;
		sptr->z = (GetRandomControl() & 0x1F) + z - 16;
		rad = (GetRandomControl() & 0x3FF) + 1024;
		ang = vel + GetRandomControl() - 0x4000;
		sptr->Xvel = short((rad * phd_sin(ang)) >> 14);
		sptr->Yvel = (GetRandomControl() & 0x7F) - 64;
		sptr->Zvel = short((rad * phd_cos(ang)) >> 14);
		sptr->Friction = 4;
		sptr->Flags = 522;
		sptr->MaxYvel = 0;
		sptr->Scalar = 3;
		sptr->Gravity = (GetRandomControl() & 0x7F) - 64;
		sptr->Size = (GetRandomControl() & 0x1F) + 48;
		sptr->sSize = sptr->Size;
		sptr->dSize = sptr->Size >> 2;
	}
}

void WraithControl(short item_number)
{
	ITEM_INFO* item;
	ITEM_INFO* item2;
	ITEM_INFO* target;
	ROOM_INFO* r;
	FLOOR_INFO* floor;
	WRAITH_STRUCT* wraith;
	long x, y, z, dx, dy, dz, dist, oob, h, c;
	short rotY, rotX, speed, room_number;

	item = &items[item_number];
	SoundEffect(SFX_WRAITH_WHISPERS, &item->pos, SFX_DEFAULT);

	if (item->hit_points)
		target = &items[item->hit_points];
	else
		target = lara_item;

	if (target == lara_item || target->object_number == ANIMATING10)
	{
		dx = target->pos.x_pos - item->pos.x_pos;
		y = target->pos.y_pos;
		dz = target->pos.z_pos - item->pos.z_pos;
		dist = SQUARE(dx) + SQUARE(dz);
		dy = ABS((dist >> 13) - 512);
	}
	else
	{
		r = &room[lara_item->room_number];
		dx = r->x + (r->y_size << 9) - item->pos.x_pos;
		dz = r->z + (r->x_size << 9) - item->pos.z_pos;
		dist = SQUARE(dx) + SQUARE(dz);
		dy = ABS((dist >> 13) - 768);
		y = r->y + ((r->minfloor - r->maxceiling) >> 1);
	}

	y = y - item->pos.y_pos - dy - 128;
	rotY = short(phd_atan(dz, dx) - item->pos.y_rot);

	if (ABS(dx) > ABS(dz))
		rotX = short(phd_atan(ABS(dx) + (ABS(dz) >> 1), y));
	else
		rotX = short(phd_atan(ABS(dz) + (ABS(dx) >> 1), y));

	rotX -= item->pos.x_rot;
	speed = (WraithSpeed / item->speed) << 3;

	if (ABS(rotY) < item->item_flags[2] && (rotY > 0 == item->item_flags[2] > 0))
		item->pos.y_rot += rotY;
	else if (rotY >= 0)
	{
		if (item->item_flags[2] > 0)
		{
			item->item_flags[2] += speed;
			item->pos.y_rot += item->item_flags[2];
		}
		else
			item->item_flags[2] = 1;
	}
	else if (item->item_flags[2] >= 0)
		item->item_flags[2] = -1;
	else
	{
		item->item_flags[2] -= speed;
		item->pos.y_rot += item->item_flags[2];
	}

	if (ABS(rotX) < item->item_flags[3] && (rotX > 0 == item->item_flags[3] > 0))
		item->pos.x_rot += rotX;
	else if (rotX >= 0)
	{
		if (item->item_flags[3] > 0)
		{
			item->item_flags[3] += speed;
			item->pos.x_rot += item->item_flags[3];
		}
		else
			item->item_flags[3] = 1;
	}
	else if (item->item_flags[3] >= 0)
		item->item_flags[3] = -1;
	else
	{
		item->item_flags[3] -= speed;
		item->pos.x_rot += item->item_flags[3];
	}

	oob = 0;

	room_number = item->room_number;
	floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);
	h = GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
	c = GetCeiling(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	if (h < item->pos.y_pos || c > item->pos.y_pos)
		oob = 1;

	x = item->pos.x_pos;
	y = item->pos.y_pos;
	z = item->pos.z_pos;
	item->pos.x_pos += (item->speed * phd_sin(item->pos.y_rot)) >> 14;
	item->pos.y_pos += (item->speed * phd_sin(item->pos.x_rot)) >> 14;
	item->pos.z_pos += (item->speed * phd_cos(item->pos.y_rot)) >> 14;
	IsRoomOutsideNo = 255;
	IsRoomOutside(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	if (item->room_number != IsRoomOutsideNo && IsRoomOutsideNo != 255)
	{
		ItemNewRoom(item_number, IsRoomOutsideNo);

		for (int i = room[item->room_number].item_number; i != NO_ITEM; i = item2->next_item)
		{
			item2 = &items[i];

			if (item2->active)
			{
				if (item->object_number == WRAITH1 && item2->object_number == WRAITH2 ||	//wraith 1 and 2 wanna fite
					item->object_number == WRAITH2 && item2->object_number == WRAITH1 ||	//wraith 2 and 1 wanna fite
					item->object_number == WRAITH3 && item2->object_number == ANIMATING10)	//wraith 3 and its totem
				{
					item->hit_points = i;
					item2->hit_points = item_number;
					break;
				}
			}
		}
	}

	if (item->object_number != WRAITH3)
	{
		if (room[item->room_number].flags & ROOM_UNDERWATER)
		{
			TriggerExplosionSparks(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 2, -2, 1, item->room_number);
			item->item_flags[1]--;

			if (item->item_flags[1] <= -2)
			{
				if (item->item_flags[1] < 30)
				{
					if (item->object_number == WRAITH2)
					{
						if (item->trigger_flags)
						{
							if (!flip_stats[item->trigger_flags])
							{
								FlipMap(item->trigger_flags);
								flip_stats[item->trigger_flags] = 1;
							}
						}
					}

					KillItem(item_number);
				}
			}
			else
				item->item_flags[1] = -1;
		}
		else
		{
			item->item_flags[1]--;

			if (item->item_flags[1] < 0)
				item->item_flags[1] = 0;
		}
	}

	if (dist < 28900 && ABS(item->pos.y_pos - target->pos.y_pos + 384) < 256)
	{
		if (item->speed > 32)
			item->speed -= 12;

		if (target == lara_item)
		{
			target->hit_points -= short(dist >> 10);

			if (item->object_number == WRAITH1)
			{
				item->item_flags[1] += 400;

				if (item->item_flags[1] > 8000)
					LaraBurn();
			}
		}
		else if (target->object_number == ANIMATING10)
		{
			item->ai_bits++;

			if (item->ai_bits > 25)
			{
				item->pos.x_pos = target->pos.x_pos;
				item->pos.y_pos = target->pos.y_pos - 384;
				item->pos.z_pos = target->pos.z_pos;
				ShockwaveExplosion(item, 0x606060, -32);
				ShockwaveExplosion(item, 0x303030, 48);
				target->hit_points = 0;
				target->trigger_flags--;

				if (target->trigger_flags > 0)
					target->frame_number = anims[target->anim_number].frame_base;

				KillItem(item_number);
			}
		}
		else
		{
			target->ai_bits = 0;
			target->ai_bits |= 2;
			target->ai_bits |= 8;

			if (item->ai_bits)
			{
				TriggerExplosionSparks(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 2, -2, 1, item->room_number);
				target->hit_points = 0;
				KillItem(item->hit_points);
				KillItem(item_number);
			}
		}
	}
	else
	{
		if (wibble & 0x10)
		{
			if (item->speed < WraithSpeed)
				item->speed++;

			if (item->hit_points)
				target->ai_bits--;
		}
	}

	room_number = item->room_number;
	floor = GetFloor(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, &room_number);
	h = GetHeight(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);
	c = GetCeiling(floor, item->pos.x_pos, item->pos.y_pos, item->pos.z_pos);

	if (h >= item->pos.y_pos && c <= item->pos.y_pos)
	{
		if (oob)
			TriggerWraithEffect(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, item->pos.y_rot, item->object_number);
	}
	else if (!oob)
		TriggerWraithEffect(x, y, z, item->pos.y_rot + 0x8000, item->object_number);

	wraith = (WRAITH_STRUCT*)item->data;

	for (int i = 0; i < 7; i++)
	{
		wraith[i].pos.x += wraith[i].xv >> 4;
		wraith[i].pos.y += wraith[i].yv >> 4;
		wraith[i].pos.z += wraith[i].zv >> 4;
		wraith[i].xv -= wraith[i].xv >> 4;
		wraith[i].yv -= wraith[i].yv >> 4;
		wraith[i].zv -= wraith[i].zv >> 4;
		wraith[i + 1].pos.x = wraith[i].pos.x;
		wraith[i + 1].pos.y = wraith[i].pos.y;
		wraith[i + 1].pos.z = wraith[i].pos.z;
		wraith[i + 1].xv = wraith[i].xv;
		wraith[i + 1].yv = wraith[i].yv;
		wraith[i + 1].zv = wraith[i].zv;

		if (item->object_number == WRAITH1)	//the rgb stuff is wrong
		{
			wraith[i + 1].r = (GetRandomControl() & 0x3F) - 64;
			wraith[i + 1].g = uchar((i + 1 + (GetRandomControl() & 0x3F)) << 4);
			wraith[i + 1].b = GetRandomControl() & 0xF;
		}
		else if (item->object_number == WRAITH2)
		{
			wraith[i + 1].r = GetRandomControl() & 0xF;
			wraith[i + 1].g = uchar((i + 1 + (GetRandomControl() & 0x3F)) << 4);
			wraith[i + 1].b = (GetRandomControl() & 0x3F) - 64;
		}
		else
		{
			wraith[i + 1].r = uchar((i + 2 + (GetRandomControl() & 0x3F)) << 3);
			wraith[i + 1].g = wraith[i + 1].r;
			wraith[i + 1].b = wraith[i + 1].r + (GetRandomControl() & 0xF);
		}
	}

	wraith[0].pos.x = item->pos.x_pos;
	wraith[0].pos.y = item->pos.y_pos;
	wraith[0].pos.z = item->pos.z_pos;
	wraith[0].xv = short((item->pos.x_pos - x) << 2);
	wraith[0].yv = short((item->pos.y_pos - y) << 2);
	wraith[0].zv = short((item->pos.z_pos - z) << 2);
	TriggerWraithFlame(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, wraith[0].xv, wraith[0].yv, wraith[0].zv, item->object_number);
	dx = (item->pos.x_pos + x) >> 1;
	dy = (item->pos.y_pos + y) >> 1;
	dz = (item->pos.z_pos + z) >> 1;
	TriggerWraithFlame(dx, dy, dz, wraith[0].xv, wraith[0].yv, wraith[0].zv, item->object_number);

	if (item->object_number == WRAITH3)
		TriggerDynamic(wraith[0].pos.x, wraith[0].pos.y, wraith[0].pos.z, 16, wraith[5].r, wraith[5].g, wraith[5].b);
	else
		TriggerDynamic(wraith[0].pos.x, wraith[0].pos.y, wraith[0].pos.z, 16, wraith[1].r, wraith[1].g, wraith[1].b);
}

void inject_wraith(bool replace)
{
	INJECT(0x0041C2E0, InitialiseWraith, replace);
	INJECT(0x0041C360, TriggerWraithFlame, replace);
	INJECT(0x0041C4C0, TriggerWraithEffect, replace);
	INJECT(0x0041C6E0, WraithControl, 0);	//wrong light flashes
}
