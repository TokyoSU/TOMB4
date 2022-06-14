#include "../tomb4/pch.h"
#include "audio.h"
#include "file.h"
#include "function_stubs.h"
#include "dxshell.h"

const char* TrackFileNames[112] =
{
	"044_attack_part_i.wav",
	"008_voncroy9a.wav",
	"100_attack_part_ii.wav",
	"010_voncroy10.wav",
	"015_voncroy14.wav",
	"073_secret.wav",
	"109_lyre_01.wav",
	"042_action_part_iv.wav",
	"043_action_part_v.wav",
	"030_voncroy30.wav",
	"012_voncroy11b.wav",
	"011_voncroy11a.wav",
	"063_misc_inc_01.wav",
	"014_voncroy13b.wav",
	"111_charmer.wav",
	"025_voncroy24b.wav",
	"023_voncroy23.wav",
	"006_voncroy7.wav",
	"024_voncroy24a.wav",
	"110_lyre_02.wav",
	"020_voncroy19.wav",
	"034_voncroy34.wav",
	"054_general_part_ii.wav",
	"036_voncroy36.wav",
	"004_voncroy5.wav",
	"035_voncroy35.wav",
	"027_voncroy27.wav",
	"053_general_part_i.wav",
	"022_voncroy22b.wav",
	"028_voncroy28_l11.wav",
	"003_voncroy4.wav",
	"001_voncroy2.wav",
	"041_action_part_iii.wav",
	"057_general_part_v.wav",
	"018_voncroy17.wav",
	"064_misc_inc_02.wav",
	"033_voncroy33.wav",
	"031_voncroy31_l12.wav",
	"032_voncroy32_l13.wav",
	"016_voncroy15.wav",
	"065_misc_inc_03.wav",
	"040_action_part_ii.wav",
	"112_gods_part_iv.wav",
	"029_voncroy29.wav",
	"007_voncroy8.wav",
	"013_voncroy12_13a_lara4.wav",
	"009_voncroy9b_lara3.wav",
	"081_dig.wav",
	"085_intro.wav",
	"071_ominous_part_i.wav",
	"095_phildoor.wav",
	"061_in_the_pyramid_part_i",
	"050_underwater_find_part_i.wav",
	"058_gods_part_i.wav",
	"005_voncroy6_lara2.wav",
	"045_authentic_tr.wav",
	"060_gods_part_iii.wav",
	"055_general_part_iii.wav",
	"059_gods_part_ii.wav",
	"068_mystery_part_ii.wav",
	"076_captain2.wav",
	"019_lara6_voncroy18.wav",
	"002_voncroy3.wav",
	"066_misc_inc_04.wav",
	"067_mystery_part_i.wav",
	"038_a_short_01.wav",
	"088_key.wav",
	"017_voncroy16_lara5.wav",
	"026_vc25_l9_vc26_l10.wav",
	"056_general_part_iv.wav",
	"021_vc20_l7_vc21_l8_vc22a.wav",
	"096_sarcoph.wav",
	"087_jeepb.wav",
	"091_minilib1.wav",
	"086_jeepa.wav",
	"051_egyptian_mood_part_i.wav",
	"078_croywon.wav",
	"092_minilib2.wav",
	"083_horus.wav",
	"049_close_to_the_end_part_ii.wav",
	"037_vc37_l15_vc38.wav",
	"097_scorpion.wav",
	"089_larawon.wav",
	"094_minilib4.wav",
	"098_throne.wav",
	"048_close_to_the_end.wav",
	"070_mystery_part_iv.wav",
	"093_minilib3.wav",
	"072_puzzle_part_i.wav",
	"074_backpack.wav",
	"069_mystery_part_iii.wav",
	"052_egyptian_mood_part_ii.wav",
	"084_inscrip.wav",
	"099_whouse.wav",
	"047_boss_02.wav",
	"080_crypt2.wav",
	"090_libend.wav",
	"046_boss_01.wav",
	"062_jeep_thrills_max.wav",
	"079_crypt1.wav",
	"082_finale.wav",
	"075_captain1.wav",
	"105_a5_battle.wav",
	"077_crocgod.wav",
	"039_tr4_title_q10.wav",
	"108_a8_coastal.wav",
	"107_a7_train+.wav",
	"101_a1_in_dark.wav",
	"102_a2_in_drips.wav",
	"104_a4_weird1.wav",
	"106_a6_out_day.wav",
	"103_a3_out_night.wav"
};

void OpenStreamFile(char* name)
{
	__try
	{
		EnterCriticalSection(&audio_cs);
	}
	__finally
	{
		LeaveCriticalSection(&audio_cs);
	}

	audio_stream_fp = FileOpen(name);

	if (!audio_stream_fp)
	{
		Log(1, "%s - Not Found", name);
		return;
	}

	SEEK(audio_stream_fp, 90, SEEK_SET);
	audio_fp_write_ptr = wav_file_buffer;
	memset(wav_file_buffer, 0, 0x37000);

	if (READ(wav_file_buffer, 1, 0x37000, audio_stream_fp) < 0x37000 && auido_play_mode == 1)
	{
		SEEK(audio_stream_fp, 90, SEEK_SET);
		Log(0, "FileReset In OpenStreamFile");
	}
}

void GetADPCMData()
{
	if (!audio_stream_fp)
		return;

	memset(audio_fp_write_ptr, 0, 0x5800);

	if (READ(audio_fp_write_ptr, 1, 0x5800, audio_stream_fp) < 0x5800 && auido_play_mode == 1)
	{
		Log(0, "FileReset In GetADPCMData");
		SEEK(audio_stream_fp, 90, 0);
	}

	audio_fp_write_ptr += 0x5800;

	if ((long)audio_fp_write_ptr >= long(wav_file_buffer + 0x37000))
		audio_fp_write_ptr = wav_file_buffer;
}

void ACMSetVolume()
{
	long volume;

	if (!MusicVolume)
		volume = -10000;
	else
		volume = -4000 * (100 - MusicVolume) / 100;

	if (G_DSBuffer)
		G_DSBuffer->SetVolume(volume);
}

void ACMEmulateCDPlay(long track, long mode)
{
	char name[256];

	__try
	{
		EnterCriticalSection(&audio_cs);
	}
	__finally
	{
		LeaveCriticalSection(&audio_cs);
	}

	wsprintf(name, "audio\\%s", TrackFileNames[track]);

	if (mode)
		Log(8, "Playing %s %s %d", name, "Looped", track);
	else
		Log(8, "Playing %s %s %d", name, "", track);

	XATrack = track;
	XAReqTrack = track;
	XAFlag = 6;
	auido_play_mode = mode;
	OpenStreamFile(name);

	if (!audio_stream_fp)
		return;

	memcpy(ADPCMBuffer, audio_fp_write_ptr, 0x5800);
	GetADPCMData();
	DXAttempt(G_DSBuffer->Lock(0, audio_buffer_size, (LPVOID*)&pAudioWrite, &AudioBytes, 0, 0, 0));
	acmStreamConvert(hACMStream, &StreamHeaders[0], ACM_STREAMCONVERTF_BLOCKALIGN | ACM_STREAMCONVERTF_START);
	memcpy(ADPCMBuffer, audio_fp_write_ptr, 0x5800);
	GetADPCMData();
	acmStreamConvert(hACMStream, &StreamHeaders[1], ACM_STREAMCONVERTF_BLOCKALIGN);
	DXAttempt(G_DSBuffer->Unlock(pAudioWrite, audio_buffer_size, 0, 0));
	CurrentNotify = 2;
	NextWriteOffset = 2 * NotifySize;
	ACMSetVolume();
	G_DSBuffer->Play(0, 0, DSBPLAY_LOOPING);
}

void inject_audio(bool replace)
{
	INJECT(0x0046DE50, OpenStreamFile, replace);
	INJECT(0x0046E0F0, GetADPCMData, replace);
	INJECT(0x0046D7B0, ACMSetVolume, replace);
	INJECT(0x0046E180, ACMEmulateCDPlay, replace);
}
