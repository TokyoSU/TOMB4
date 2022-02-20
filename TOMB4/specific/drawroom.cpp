#include "../tomb4/pch.h"
#include "drawroom.h"
#include "function_stubs.h"
#include "dxshell.h"
#include "polyinsert.h"
#include "function_table.h"

void ProjectVerts(long nVerts, D3DTLVERTEX* v, short* clip)
{
	float zv;
	short clip_distance;

	for (int i = 0; i < nVerts; i++)
	{
		v->tu = v->sx;
		v->tv = v->sy;
		clip_distance = 0;

		if (v->sz < f_mznear)
			clip_distance = -128;
		else
		{
			zv = f_mpersp / v->sz;

			if (v->sz > FogEnd)
			{
				clip_distance = 16;
				v->sz = f_zfar;
			}

			v->sx = zv * v->sx + f_centerx;
			v->sy = zv * v->sy + f_centery;
			v->rhw = f_moneopersp * zv;

			if (bWaterEffect)
			{
				v->sx += vert_wibble_table[((wibble + (long)v->sy) >> 3) & 0x1F];
				v->sy += vert_wibble_table[((wibble + (long)v->sx) >> 3) & 0x1F];
			}

			if (v->sx < clip_left)
				clip_distance++;
			else if (v->sx > clip_right)
				clip_distance += 2;

			if (v->sy < clip_top)
				clip_distance += 4;
			else if (v->sy > clip_bottom)
				clip_distance += 8;
		}

		*clip++ = clip_distance;
		v++;
	}
}

void ProjectWaterVerts(long nVerts, D3DTLVERTEX* v, short* clip)
{
	ROOM_INFO* r;
	float shift, zv;
	long x, y, z, rndoff, cR, cG, cB, col;
	short clip_distance;
	uchar rnd;

	r = &room[current_room];

	for (int i = 0; i < nVerts; i++)
	{
		clip_distance = 0;
		x = (long)((r->x + r->verts[i].x) * 0.015625F);
		y = (long)((r->y + r->verts[i].y) * 0.015625F);
		z = (long)((r->z + r->verts[i].z) * 0.0078125F);
		rndoff = (x + y + z) & 0xFC;
		rnd = WaterTable[r->MeshEffect][rndoff & 0x3F].random;
		shift = WaterTable[r->MeshEffect][((wibble >> 2) + rnd) & 0x3F].choppy;
		v->sy += shift;

		v->tu = v->sx;
		v->tv = v->sy;

		if (v->sz < f_mznear)
			clip_distance = -128;
		else
		{
			zv = f_mpersp / v->sz;

			if (v->sz > FogEnd)
			{
				clip_distance = 256;
				v->sz = f_zfar;
			}

			v->sx = zv * v->sx + f_centerx;
			v->sy = zv * v->sy + f_centery;
			v->rhw = f_moneopersp * zv;

			if (v->sx < clip_left)
				clip_distance++;
			else if (v->sx > clip_right)
				clip_distance += 2;

			if (v->sy < clip_top)
				clip_distance += 4;
			else if (v->sy > clip_bottom)
				clip_distance += 8;

			rnd = WaterTable[r->MeshEffect][rndoff].random;
			col = -WaterTable[r->MeshEffect][((wibble >> 2) + rnd) & 0x3F].choppy;
			cR = CLRR(v->color) + col;
			cG = CLRG(v->color) + col;
			cB = CLRB(v->color) + col;

			if (cR > 255)
				cR = 255;

			if (cG > 255)
				cG = 255;

			if (cB > 255)
				cB = 255;

			if (cR < 0)
				cR = 0;

			if (cG < 0)
				cG = 0;

			if (cB < 0)
				cB = 0;

			v->color = RGBA(cR, cG, cB, 0xFF);
		}

		*clip++ = clip_distance;
		v++;
	}
}

void ProjectShoreVerts(long nVerts, D3DTLVERTEX* v, short* clip)
{
	ROOM_INFO* r;
	float zv;
	long x, y, z, rndoff, cR, cG, cB;
	short clip_distance, col;
	uchar rnd, abs;
	char shimmer;

	r = &room[current_room];

	for (int i = 0; i < nVerts; i++)
	{
		x = (long)((r->x + r->verts[i].x) * 0.015625F);
		y = (long)((r->y + r->verts[i].y) * 0.015625F);
		z = (long)((r->z + r->verts[i].z) * 0.0078125F);
		rndoff = (x + y + z) & 0xFC;
		v->tu = v->sx;
		v->tv = v->sy;
		clip_distance = 0;

		if (v->sz < f_mznear)
			clip_distance = -128;
		else
		{
			zv = f_mpersp / v->sz;

			if (v->sz > FogEnd)
			{
				clip_distance = 256;
				v->sz = f_zfar;
			}

			v->sx = zv * v->sx + f_centerx;
			v->sy = zv * v->sy + f_centery;
			v->rhw = f_moneopersp * zv;

			if (bWaterEffect)
			{
				v->sx += vert_wibble_table[((wibble + (long)v->sy) >> 3) & 0x1F];
				v->sy += vert_wibble_table[((wibble + (long)v->sx) >> 3) & 0x1F];
			}

			if (v->sx < clip_left)
				clip_distance++;
			else if (v->sx > clip_right)
				clip_distance += 2;

			if (v->sy < clip_top)
				clip_distance += 4;
			else if (v->sy > clip_bottom)
				clip_distance += 8;

			rnd = WaterTable[r->MeshEffect][rndoff & 0x3C].random;
			shimmer = WaterTable[r->MeshEffect][((wibble >> 2) + rnd) & 0x3F].shimmer;
			abs = WaterTable[r->MeshEffect][((wibble >> 2) + rnd) & 0x3F].abs;
			col = (shimmer + abs) << 3;
			cR = CLRR(v->color) + col;
			cG = CLRG(v->color) + col;
			cB = CLRB(v->color) + col;

			if (cR > 255)
				cR = 255;

			if (cG > 255)
				cG = 255;

			if (cB > 255)
				cB = 255;

			if (cR < 0)
				cR = 0;

			if (cG < 0)
				cG = 0;

			if (cB < 0)
				cB = 0;

			v->color = RGBA(cR, cG, cB, 0xFF);
		}

		*clip++ = clip_distance;
		v++;
	}
}

void ProcessRoomData(ROOM_INFO* r)
{
	D3DVERTEX* vptr;
	LIGHTINFO* light;
	PCLIGHT_INFO* pclight;
	FOGBULB_STRUCT* bulb;
	D3DVERTEXBUFFERDESC vb;
	short* data_ptr;
	short* faces;
	short* prelight;
	float intensity;
	long nWaterVerts, nShoreVerts, nRestOfVerts, nLights, nBulbs;
	ushort cR, cG, cB;

	data_ptr = r->data;
	r->nVerts =*data_ptr++;

	if (!r->nVerts)
	{
		r->num_lights = 0;
		r->SourceVB = 0;
		return;
	}

	data_ptr += r->nVerts * 6;
	r->FaceData = data_ptr;
	r->gt4cnt = *data_ptr++;
	data_ptr += r->gt4cnt * 5;
	r->gt3cnt = *data_ptr;
	r->verts = (D3DVECTOR*)game_malloc(sizeof(D3DVECTOR) * r->nVerts);
	faces = (short*)malloc(2 * r->nVerts);
	prelight = (short*)malloc(2 * r->nVerts);
	data_ptr = r->data + 1;	//go to vert data
	nWaterVerts = 0;

	for (int i = 0; i < r->nVerts; i++)	//get water verts
	{
		if (data_ptr[4] & 0x2000)
		{
			r->verts[nWaterVerts].x = (float)data_ptr[0];
			r->verts[nWaterVerts].y = (float)data_ptr[1];
			r->verts[nWaterVerts].z = (float)data_ptr[2];
			prelight[nWaterVerts] = data_ptr[5];
			faces[i] = (short)(nWaterVerts | 0x8000);
			nWaterVerts++;
		}

		data_ptr += 6;
	}

	data_ptr = r->data + 1;
	nShoreVerts = 0;

	for (int i = 0; i < r->nVerts; i++)	//again for shore verts
	{
		if (data_ptr[4] & 0x4000 && !(data_ptr[4] & 0x2000))
		{
			r->verts[nShoreVerts + nWaterVerts].x = (float)data_ptr[0];
			r->verts[nShoreVerts + nWaterVerts].y = (float)data_ptr[1];
			r->verts[nShoreVerts + nWaterVerts].z = (float)data_ptr[2];
			prelight[nShoreVerts + nWaterVerts] = data_ptr[5];
			faces[i] = (short)(nShoreVerts + nWaterVerts);
			nShoreVerts++;
		}

		data_ptr += 6;
	}

	data_ptr = r->data + 1;
	nRestOfVerts = 0;

	for (int i = 0; i < r->nVerts; i++)	//one more for everything else
	{
		if (!(data_ptr[4] & 0x4000) && !(data_ptr[4] & 0x2000))
		{
			r->verts[nRestOfVerts + nShoreVerts + nWaterVerts].x = (float)data_ptr[0];
			r->verts[nRestOfVerts + nShoreVerts + nWaterVerts].y = (float)data_ptr[1];
			r->verts[nRestOfVerts + nShoreVerts + nWaterVerts].z = (float)data_ptr[2];
			prelight[nRestOfVerts + nShoreVerts + nWaterVerts] = data_ptr[5];
			faces[i] = (short)(nRestOfVerts + nShoreVerts + nWaterVerts);
			nRestOfVerts++;
		}

		data_ptr += 6;
	}

	data_ptr = r->FaceData + 1;
	r->nWaterVerts = nWaterVerts;
	r->nShoreVerts = nShoreVerts;

	for (int i = 0; i < r->gt4cnt; i++)	//get quad data
	{
		if (faces[data_ptr[0]] & 0x8000 || faces[data_ptr[1]] & 0x8000 || faces[data_ptr[2]] & 0x8000 || faces[data_ptr[3]] & 0x8000)
			data_ptr[4] |= 0x4000;

		data_ptr[0] = faces[data_ptr[0]] & 0x7FFF;
		data_ptr[1] = faces[data_ptr[1]] & 0x7FFF;
		data_ptr[2] = faces[data_ptr[2]] & 0x7FFF;
		data_ptr[3] = faces[data_ptr[3]] & 0x7FFF;
		data_ptr += 5;	//onto the next quad
	}

	data_ptr++;//skip over tri count

	for (int i = 0; i < r->gt3cnt; i++)	//tris
	{
		data_ptr[0] = faces[data_ptr[0]] & 0x7FFF;
		data_ptr[1] = faces[data_ptr[1]] & 0x7FFF;
		data_ptr[2] = faces[data_ptr[2]] & 0x7FFF;
		data_ptr += 4;
	}

	free(faces);
	CreateVertexNormals(r);
	r->prelight = (long*)game_malloc(4 * r->nVerts);
	r->prelightwater = (long*)game_malloc(4 * r->nVerts);
	r->watercalc = 0;
	vb.dwNumVertices = r->nVerts;
	vb.dwSize = sizeof(D3DVERTEXBUFFERDESC);
	vb.dwCaps = 0;
	vb.dwFVF = D3DFVF_VERTEX;
	DXAttempt(App.dx.lpD3D->CreateVertexBuffer(&vb, &r->SourceVB, D3DDP_DONOTCLIP, 0));
	r->SourceVB->Lock(DDLOCK_WRITEONLY, (void**)&vptr, 0);
	r->posx = (float)r->x;
	r->posy = (float)r->y;
	r->posz = (float)r->z;
	data_ptr = r->data + 1;

	for (int i = 0; i < r->nVerts; i++)
	{
		vptr->x = r->verts[i].x + (float)r->x;
		vptr->y = r->verts[i].y + (float)r->y;
		vptr->z = r->verts[i].z + (float)r->z;
		vptr->nx = r->vnormals[i].x;
		vptr->ny = r->vnormals[i].y;
		vptr->nz = r->vnormals[i].z;
		cR = ((prelight[i] & 0x7C00) >> 10) << 3;
		cG = ((prelight[i] & 0x3E0) >> 5) << 3;
		cB = (prelight[i] & 0x1F) << 3;
		r->prelight[i] = RGBA(cR, cG, cB, 0xFF);
		cR = (ushort)((cR * water_color_R) >> 8);
		cG = (ushort)((cR * water_color_G) >> 8);
		cB = (ushort)((cR * water_color_B) >> 8);
		r->prelightwater[i] = RGBA(cR, cG, cB, 0xFF);
		vptr++;
		data_ptr += 6;
	}

	r->SourceVB->Unlock();
	free(prelight);
	r->pclight = 0;

	if (r->num_lights)
	{
		r->pclight = (PCLIGHT_INFO*)game_malloc(sizeof(PCLIGHT_INFO) * r->num_lights);
		nLights = 0;
		nBulbs = NumLevelFogBulbs;

		for (int i = 0; i < r->num_lights; i++)
		{
			light = &r->light[i];

			if (light->Type == LIGHT_FOG)
			{
				if (NumLevelFogBulbs >= 20)
				{
					Log(1, "Fog Bulb Discarded - More Than %d", 20);
					continue;
				}

				bulb = &FogBulbs[nBulbs];
				bulb->inRange = 0;
				bulb->density = light->r;
				bulb->WorldPos.x = (float)light->x;
				bulb->WorldPos.y = (float)light->y;
				bulb->WorldPos.z = (float)light->z;
				bulb->rad = light->Outer;
				bulb->sqrad = SQUARE(bulb->rad);
				bulb->inv_sqrad = 1 / bulb->sqrad;
				nBulbs++;
				NumLevelFogBulbs = nBulbs;
			}
			else
			{
				if (!light->r && !light->g && !light->b && light->Type == LIGHT_SPOT)
					continue;

				pclight = &r->pclight[nLights];
				pclight->r = light->r * 0.0039215689F;
				pclight->g = light->g * 0.0039215689F;
				pclight->b = light->b * 0.0039215689F;
				intensity = r->light[nLights].Intensity;

				if (intensity < 0)
					intensity = -intensity;

				intensity *= 0.00012208521F;
				pclight->r *= intensity;
				pclight->g *= intensity;
				pclight->b *= intensity;

				if (r->light[nLights].Type)
					pclight->shadow = (long)(intensity * 255);

				pclight->x = (float)light->x;
				pclight->y = (float)light->y;
				pclight->z = (float)light->z;
				pclight->ix = light->x;
				pclight->iy = light->y;
				pclight->iz = light->z;
				pclight->nx = -light->nx;
				pclight->ny = -light->ny;
				pclight->nz = -light->nz;
				pclight->inx = (long)(light->nx * -16384.0F);
				pclight->iny = (long)(light->ny * -16384.0F);
				pclight->inz = (long)(light->nz * -16384.0F);
				pclight->Inner = light->Inner;
				pclight->Outer = light->Outer;
				pclight->InnerAngle = 2 * acos(light->Inner);
				pclight->OuterAngle = 2 * acos(light->Outer);

				if (r->light[nLights].Type == LIGHT_SPOT && pclight->OuterAngle > 3.1415927F)
				{
					Log(1, "SpotLight Corrected");
					pclight->OuterAngle = 3.1415927F;
				}

				pclight->Cutoff = light->Cutoff;
				pclight->Type = light->Type;
				nLights++;
			}
		}
	}

	if (r->num_lights > MaxRoomLights)
		MaxRoomLights = r->num_lights;

	r->SourceVB->Optimize(App.dx._lpD3DDevice, 0);
}

void PrelightVertsNonMMX(long nVerts, D3DTLVERTEX* v, ROOM_INFO* r)
{
	long* prelight;
	long pR, pG, pB, vR, vG, vB, cR, cG, cB;

	if (bWaterEffect && !(r->flags & ROOM_UNDERWATER))
		prelight = r->prelightwater;
	else
		prelight = r->prelight;

	for (int i = 0; i < r->nWaterVerts; i++)
	{
		pR = r->prelight[i] & 0xFF0000;
		pG = r->prelight[i] & 0xFF00;
		pB = r->prelight[i] & 0xFF;
		vR = v->color & 0xFF0000;
		vG = v->color & 0xFF00;
		vB = v->color & 0xFF;
		cR = pR + vR;
		cG = pG + vG;
		cB = pB + vB;

		if (cR > 0xFF0000)
			cR = 0xFF0000;

		if (cG > 0xFF00)
			cG = 0xFF00;

		if (cB > 0xFF)
			cB = 0xFF;

		v->specular &= 0xFF000000;
		v->color = (v->color & 0xFF000000) | cR | cG | cB;
	}

	for (int i = r->nWaterVerts; i < r->nVerts; i++)
	{
		pR = prelight[i] & 0xFF0000;
		pG = prelight[i] & 0xFF00;
		pB = prelight[i] & 0xFF;
		vR = v->color & 0xFF0000;
		vG = v->color & 0xFF00;
		vB = v->color & 0xFF;
		cR = pR + vR;
		cG = pG + vG;
		cB = pB + vB;

		if (cR > 0xFF0000)
			cR = 0xFF0000;

		if (cG > 0xFF00)
			cG = 0xFF00;

		if (cB > 0xFF)
			cB = 0xFF;

		v->color = (v->color & 0xFF000000) | cR | cG | cB;
		CalcColorSplit(v->color, &v->color);
		v++;
	}
}

void InsertRoom(ROOM_INFO* r)
{
	TEXTURESTRUCT* pTex;
	D3DTLVERTEX* v;
	short* data;
	short numQuads, numTris;
	bool doublesided;

	clip_left = r->left;
	clip_right = r->right;
	clip_bottom = r->bottom;
	clip_top = r->top;

	if (r->nVerts)
	{
		DXAttempt(DestVB->ProcessVertices(D3DVOP_LIGHT | D3DVOP_TRANSFORM, 0, r->nVerts, r->SourceVB, 0, App.dx._lpD3DDevice, 0));
		DestVB->Lock(DDLOCK_READONLY, (void**)&v, 0);
		bWaterEffect = camera.underwater != 0;
		ProjectWaterVerts(r->nWaterVerts, v, clipflags);
		ProjectShoreVerts(r->nShoreVerts, &v[r->nWaterVerts], &clipflags[r->nWaterVerts]);
		ProjectVerts(r->nVerts - r->nWaterVerts - r->nShoreVerts, &v[r->nWaterVerts + r->nShoreVerts], &clipflags[r->nWaterVerts + r->nShoreVerts]);

		if (App.mmx)
			PrelightVertsMMX(r->nVerts, v, r);
		else
			PrelightVertsNonMMX(r->nVerts, v, r);

		data = r->FaceData;
		numQuads = *data++;

		for (int i = 0; i < numQuads; i++, data += 5)
		{
			pTex = &textinfo[data[4] & 0x3FFF];
			doublesided = (data[4] >> 15) & 1;

			if (!pTex->drawtype)
				AddQuadZBuffer(v, data[0], data[1], data[2], data[3], pTex, doublesided);
			else if (pTex->drawtype <= 2)
				AddQuadSorted(v, data[0], data[1], data[2], data[3], pTex, doublesided);
		}

		numTris = *data++;

		for (int i = 0; i < numTris; i++, data += 4)
		{
			pTex = &textinfo[data[3] & 0x3FFF];
			doublesided = (data[3] >> 15) & 1;

			if (!pTex->drawtype)
				AddTriZBuffer(v, data[0], data[1], data[2], pTex, doublesided);
			else if (pTex->drawtype <= 2)
				AddTriSorted(v, data[0], data[1], data[2], pTex, doublesided);
		}

		DestVB->Unlock();
	}
}

void inject_drawroom(bool replace)
{
	INJECT(0x00471E00, ProjectVerts, replace);
	INJECT(0x00471F40, ProjectWaterVerts, replace);
	INJECT(0x00472190, ProjectShoreVerts, replace);
	INJECT(0x00471420, ProcessRoomData, replace);
	INJECT(0x004724C0, PrelightVertsNonMMX, replace);
	INJECT(0x00472650, InsertRoom, replace);
}