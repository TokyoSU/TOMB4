#pragma once
#include "../global/vars.h"

void inject_sound(bool replace);

void GetPanVolume(SoundSlot* slot);
void StopSoundEffect(long sfx);
void SOUND_Init();
void SOUND_Stop();
long SoundEffect(long sfx, PHD_3DPOS* pos, long flags);
void SayNo();

enum sfx_options
{
    SFX_DEFAULT     = 0,
    SFX_WATER       = 1,
    SFX_ALWAYS      = 2,
    SFX_SETPITCH    = 4
};

enum sound_effect_names
{
    SFX_LARA_FEET,
    SFX_LARA_CLIMB2,
    SFX_LARA_NO,
    SFX_LARA_SLIPPING,
    SFX_LARA_LAND,
    SFX_LARA_CLIMB1,
    SFX_LARA_DRAW,
    SFX_LARA_HOLSTER,
    SFX_LARA_FIRE,
    SFX_LARA_RELOAD,
    SFX_LARA_RICOCHET,
    SFX_PUSH_BLOCK_END,
    SFX_METAL_SCRAPE_LOOP1,
    SFX_SMALL_SCARAB_FEET,
    SFX_BIG_SCARAB_ATTACK,
    SFX_BIG_SCARAB_DEATH,
    SFX_BIG_SCARAB_FLYING,
    SFX_LARA_WET_FEET,
    SFX_LARA_WADE,
    SFX_RUMBLE_LOOP,
    SFX_METAL_SCRAPE_LOOP,
    SFX_CRICKET_LOOP,
    SFX_WOOD_BRIDGE_FALL,
    SFX_STARGATE_SWIRL,
    SFX_LARA_KNEES_SHUFFLE,
    SFX_PUSH_SPX_SWITCH,
    SFX_LARA_CLIMB3,
    SFX_UNUSED,
    SFX_LARA_SHIMMY2,
    SFX_LARA_JUMP,
    SFX_LARA_FALL,
    SFX_LARA_INJURY,
    SFX_LARA_ROLL,
    SFX_LARA_SPLASH,
    SFX_LARA_GETOUT,
    SFX_LARA_SWIM,
    SFX_LARA_BREATH,
    SFX_LARA_BUBBLES,
    SFX_SPINNING_PUZZLE,
    SFX_LARA_KEY,
    SFX_COG_RESAW_LIBRARY,
    SFX_LARA_GENERAL_DEATH,
    SFX_LARA_KNEES_DEATH,
    SFX_LARA_UZI_FIRE,
    SFX_LARA_UZI_STOP,
    SFX_LARA_SHOTGUN,
    SFX_LARA_BLOCK_PUSH1,
    SFX_LARA_BLOCK_PUSH2,
    SFX_SARLID_PALACES,
    SFX_LARA_SHOTGUN_SHELL,
    SFX_UNDERWATER_DOOR,
    SFX_LARA_BLKPULL,
    SFX_LARA_FLOATING,
    SFX_LARA_FALLDEATH,
    SFX_LARA_GRABHAND,
    SFX_LARA_GRABBODY,
    SFX_LARA_GRABFEET,
    SFX_RATCHET_3SHOT,
    SFX_RATCHET_1SHOT,
    SFX_WATER_LOOP_NOTINUSE,
    SFX_UNDERWATER,
    SFX_UNDERWATER_SWITCH,
    SFX_LARA_PICKUP,
    SFX_PUSHABLE_SOUND,
    SFX_DOOR_GENERAL,
    SFX_HELICOPTER_LOOP,
    SFX_ROCK_FALL_CRUMBLE,
    SFX_ROCK_FALL_LAND,
    SFX_PENDULUM_BLADES,
    SFX_STALEGTITE,
    SFX_LARA_THUD,
    SFX_GENERIC_SWOOSH,
    SFX_GENERIC_HEAVY_THUD,
    SFX_CROC_FEET,
    SFX_SWINGING_FLAMES,
    SFX_STONE_SCRAPE,
    SFX_BLAST_CIRCLE,
    SFX_BAZOOKA_FIRE,
    SFX_MP5_FIRE,
    SFX_WATERFALL_LOOP,
    SFX_CROC_ATTACK,
    SFX_CROC_DEATH,
    SFX_PORTCULLIS_UP,
    SFX_PORTCULLIS_DOWN,
    SFX_DOUBLE_DOOR_BANG,
    SFX_DOUBLE_DOOR_CREAK,
    SFX_PETES_PYRA_STONE,
    SFX_PETES_PYRA_PNEU,
    SFX_AHMET_DIE,
    SFX_AHMET_ATTACK,
    SFX_AMHET_HANDS,
    SFX_AHMET_FEET,
    SFX_AHMET_SWIPE,
    SFX_AHMET_WAIT,
    SFX_GUIDE_JUMP,
    SFX_GENERAL_FOOTSTEPS1,
    SFX_GUIDE_LAND_USENOT,
    SFX_POUR,
    SFX_SCALE1,
    SFX_SCALE2,
    SFX_BEETLARA_WINDUP,
    SFX_BEETLE_CLK_WHIRR,
    SFX_BEETLE_CLK_EXP,
    SFX_MINE_EXP_OVERLAY,
    SFX_MP5_STOP,
    SFX_EXPLOSION1,
    SFX_EXPLOSION2,
    SFX_EARTHQUAKE_LOOP,
    SFX_MENU_ROTATE,
    SFX_MENU_SELECT,
    SFX_MENU_EMPTY,
    SFX_MENU_CHOOSE,
    SFX_TICK_TOCK,
    SFX_MENU_EMPTY1,
    SFX_MENU_COMBINE,
    SFX_MENU_EMPTY2,
    SFX_MENU_MEDI,
    SFX_LARA_CLIMB_WALLS_NOISE,
    SFX_WATER_LOOP,
    SFX_VONCROY_JUMP,
    SFX_LOCUSTS_LOOP,
    SFX_DESERT_EAGLE_FIRE,
    SFX_BOULDER_FALL,
    SFX_LARA_MINI_LOAD,
    SFX_LARA_MINI_LOCK,
    SFX_LARA_MINI_FIRE,
    SFX_GATE_OPENING,
    SFX_LARA_ELECTRIC_LOOP,
    SFX_LARA_ELECTRIC_CRACKLES,
    SFX_BLOOD_LOOP,
    SFX_BIKE_START,
    SFX_BIKE_IDLE,
    SFX_BIKE_ACCELERATE,
    SFX_BIKE_MOVING,
    SFX_BIKE_SIDE_IMPACT,
    SFX_BIKE_FRONT_IMPACT,
    SFX_SOFT_WIND_LOOP,
    SFX_BIKE_LAND,
    SFX_CROCGOD_ROAR,
    SFX_CROCGOD_WINGS,
    SFX_CROCGOD_LAND,
    SFX_CROCGOD_FIRE_ROAR,
    SFX_BIKE_STOP,
    SFX_GENERIC_BODY_SLAM,
    SFX_MP5_OVERLAY,
    SFX_LARA_SPIKE_DEATH,
    SFX_LARA_DEATH3,
    SFX_ROLLING_BALL,
    SFX_BLK_PLAT_RAISE_LOW,
    SFX_RUMBLE_NEXTDOOR,
    SFX_LOOP_FOR_SMALL_FIRES,
    SFX_CHAINS_LIBRARY,
    SFX_JEEP_START,
    SFX_JEEP_IDLE,
    SFX_JEEP_ACCELERATE,
    SFX_JEEP_MOVE,
    SFX_JEEP_STOP,
    SFX_BATS_1,
    SFX_ROLLING_DOOR,
    SFX_LAUNCHER_1,
    SFX_LAUNCHER_2,
    SFX_TRAPDOOR_OPEN,
    SFX_TRAPDOOR_CLOSE,
    SFX_EMPTY1,
    SFX_BABOON_STAND_WAIT,
    SFX_BABOON_ATTACK_LOW,
    SFX_BABOON_ATTACK_JUMP,
    SFX_BABOON_JUMP,
    SFX_BABOON_DEATH,
    SFX_BAT_SQUEAL_FULL,
    SFX_BAT_SQK,
    SFX_BAT_FLAP,
    SFX_SPHINX_NOSE_RASP,
    SFX_SPHINX_WALK,
    SFX_SPHINX_NOISE,
    SFX_DOG_HOWL,
    SFX_DOG_HIT_GOUND,
    SFX_FOUNTAIN_LOOP,
    SFX_DOG_FOOT_1,
    SFX_DOG_JUMP,
    SFX_DOG_BITE,
    SFX_DOG_DEATH,
    SFX_THUNDER_RUMBLE,
    SFX_THUNDER_CRACK,
    SFX_WRAITH_WHISPERS,
    SFX_EMPTY2,
    SFX_EMPTY3,
    SFX_SKEL_FOOTSTEP,
    SFX_SKEL_ATTACK,
    SFX_GENERIC_SWORD_SWOOSH,
    SFX_SKEL_SWORD_CLANG,
    SFX_SKEL_STICK_GROUND,
    SFX_GEN_PULL_SWORD,
    SFX_SKEL_LAND_HEAVY,
    SFX_GUIDE_SCARE,
    SFX_JEEP_DOOR_OPEN,
    SFX_JEEP_DOOR_CLOSE,
    SFX_ELEC_ARCING_LOOP,
    SFX_ELEC_ONE_SHOT,
    SFX_EMPTY4,
    SFX_LIBRARY_COG_LOOP,
    SFX_JEEP_SIDE_IMPACT,
    SFX_JEEP_FRONT_IMPACT,
    SFX_JEEP_LAND,
    SFX_SPINNING_GEM_SLOTS,
    SFX_RUMMBLE,
    SFX_WARTHOG_HEADBUTT,
    SFX_WARTHOG_DEATH,
    SFX_SET_SPIKE_TIMER,
    SFX_WARTHOG_SQUEAL,
    SFX_WARTHOG_FEET,
    SFX_WARTHOG_GRUNT,
    SFX_SAVE_CRYSTAL,
    SFX_HORSE_RICOCHETS,
    SFX_METAL_SHUTTERS_SMASH,
    SFX_GEM_DROP_ON_FLOOR,
    SFX_SCORPION_SCREAM,
    SFX_SCORPION_FEET,
    SFX_SCORPION_CLAWS,
    SFX_SCORPION_TAIL_WHIP,
    SFX_SCORPION_SMALL_FEET,
    SFX_METAL_GATE_OPEN,
    SFX_HORSE_TROTTING,
    SFX_KN_TEMPLAR_WALK,
    SFX_KN_TEMPLAR_GURGLES,
    SFX_KN_SWORD_SCRAPE,
    SFX_KN_TEMPLAR_ATTACK,
    SFX_KN_SWORD_CLANG,
    SFX_KN_SWORD_SWOOSH,
    SFX_MUMMY_ATTACK,
    SFX_MUMMY_WALK,
    SFX_MUMMY_GURGLES,
    SFX_MUMMY_TAKE_HIT,
    SFX_SMALL_FAN,
    SFX_LARGE_FAN,
    SFX_LARA_CROSSBOW,
    SFX_SMALL_CREATURE_FEET,
    SFX_SAS_GADGIE_DIE,
    SFX_WATER_FLUSHES,
    SFX_GUID_ZIPPO,
    SFX_LEAP_SWITCH,
    SFX_OLD_SWITCH,
    SFX_DEMIGODS_FEET,
    SFX_DEMIGODS_BULL_SNORT,
    SFX_DEMIGODS_BULL_HAMMER,
    SFX_DEMIGODS_S_WAVE_RUMB,
    SFX_DEMIGOD_WEAP_SWOOSH,
    SFX_DEMIGOD_FALCON_SQUEAL,
    SFX_DEMIGOD_FALCON_PLAS,
    SFX_DEMIGOD_RISE,
    SFX_DEMI_TUT_PLASMA_SPRAY,
    SFX_DEMI_SIREN_SWAVE,
    SFX_DEMIGODS_TUT_GROWL,
    SFX_JOBY_ELECTRIC_INSERT,
    SFX_BAD_LAND,
    SFX_DOOR_GEN_THUD,
    SFX_BAD_GRUNTS,
    SFX_BAD_DIE,
    SFX_BAD_JUMP,
    SFX_BAD_TROOP_STUN,
    SFX_BAD_SWORDAWAY,
    SFX_BAD_TROOP_UZI,
    SFX_BAD_SWORD_RICO,
    SFX_BAD_TROOP_UZI_END,
    SFX_TROOP_SCROP_CRIES,
    SFX_SAS_TROOP_FEET,
    SFX_GENERIC_NRG_CHARGE,
    SFX_SAS_MG_FIRE,
    SFX_HAMMER_HEAD_WADE,
    SFX_SMALL_SWITCH,
    SFX_EMPTY5,
    SFX_SIREN_WING_FLAP,
    SFX_SIREN_NOIZES,
    SFX_SIREN_ATTACK,
    SFX_SIREN_DEATH,
    SFX_SIREN_GEN_NOISES,
    SFX_SETT_SIREN_PLASMA,
    SFX_HAMMER_HEAD_ATK,
    SFX_SMALL_DOOR_SUBWAY,
    SFX_TRAIN_DOOR_OPEN,
    SFX_TRAIN_DOOR_CLOSE,
    SFX_VONCROY_KNIFE_SWISH,
    SFX_TRAIN_UNLINK_BREAK,
    SFX_OBJ_BOX_HIT,
    SFX_OBJ_BOX_HIT_CHANCE,
    SFX_OBJ_GEM_SMASH,
    SFX_CATBLADES_DRAW,
    SFX_SWIRLY_LONG_MOVE_SFX,
    SFX_FOOTSTEPS_MUD,
    SFX_HORSEMAN_HORSE_NEIGH,
    SFX_FOOTSTEPS_GRAVEL,
    SFX_FOOTSTEPS_SAND_GRASS,
    SFX_FOOTSTEPS_WOOD,
    SFX_FOOTSTEPS_MARBLE,
    SFX_FOOTSTEPS_METAL,
    SFX_GEN_SPHINX_DOORTHD,
    SFX_SETT_PLASMA_1,
    SFX_SETT_BOLT_1,
    SFX_SETT_FEET,
    SFX_SETT_NRG_CHARGE,
    SFX_SETT_NRG_CHARGE2,
    SFX_HORSEMAN_TAKEHIT,
    SFX_HORSEMAN_WALK,
    SFX_HORSEMAN_GRUNT,
    SFX_HORSEMAN_FALL,
    SFX_HORSEMAN_DIE,
    SFX_MAPPER_SWITCH_ON,
    SFX_MAPPER_OPEN,
    SFX_MAPPER_LAZER,
    SFX_MAPPER_MOVE,
    SFX_MAPPER_CLUNK,
    SFX_BLADES_DRAW,
    SFX_BLADES_CLASH_LOUD,
    SFX_BLADES_CLASH_QUIET,
    SFX_HAMMER_TRAP_BANG,
    SFX_DOOR_BIG_STONE,
    SFX_SETT_BIG_ROAR,
    SFX_BABOON_CHATTER,
    SFX_BABOON_ROLL,
    SFX_SWOOSH_SWIRLY_DOUBLE,
    SFX_DOOR_SETTDOOR_SQK,
    SFX_DOOR_SETTDOOR_CLANK,
    SFX_SETT_JUMP_ATTACK,
    SFX_JOBY_BLOCK,
    SFX_SETT_TAKE_HIT,
    SFX_DART_SPITT,
    SFX_LARA_CROWBAR_GEM,
    SFX_CROWBAR_DOOR_OPEN,
    SFX_LARA_LEVER_GEN_SQKS,
    SFX_HORSEMAN_GETUP,
    SFX_EXH_BASKET_OPEN,
    SFX_EXH_MUMCOFF_OPE1,
    SFX_EXH_MUMCOFF_OPE2,
    SFX_EXH_MUM_JOLT,
    SFX_EXH_MUMHEAD_SPIN,
    SFX_EXH_MUMMY_RAHHH,
    SFX_EXH_ROLLER_BLINDS,
    SFX_LARA_LEVER_PART1,
    SFX_LARA_LEVER_PART2,
    SFX_LARA_POLE_CLIMB,
    SFX_LARA_POLE_LOOP,
    SFX_TRAP_SPIKEBALL_SPK,
    SFX_LARA_PULLEY,
    SFX_TEETH_SPIKES,
    SFX_SAND_LOOP,
    SFX_LARA_USE_OBJECT,
    SFX_LIBRARY_COG_SQKS,
    SFX_HIT_ROCK,
    SFX_LARA_NO_FRENCH,
    SFX_LARA_NO_JAPAN,
    SFX_LARA_CROW_WRENCH,
    SFX_LARA_ROPE_CREAK,
    SFX_BOWLANIM,
    SFX_SPHINX_DOOR_WOODCRACK,
    SFX_BEETLE_CLK_WHIRR1,
    SFX_MAPPER_PYRAMID_OPEN,
    SFX_LIGHT_BEAM_JOBY,
    SFX_GUIDE_FIRE_LIGHT,
    SFX_AUTOGUNS,
    SFX_PULLEY_ANDY,
    SFX_STEAM,
    SFX_JOBY_GARAGE_DOOR,
    SFX_JOBY_WIND,
    SFX_SANDHAM_IN_THE_HOUSE,
    SFX_SANDHAM_CONVEYS,
    SFX_CRANKY_GRAPE_CRUSH,
    SFX_BIKE_HIT_OBJECTS,
    SFX_BIKE_HIT_ENEMIES,
    SFX_FLAME_EMITTER,
    SFX_LARA_CLICK_SWITCH,

    NumSamples
};
