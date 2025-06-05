#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
    .affineAnims = gDummySpriteAffineAnimTable,                                                                                         \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
            .affineAnims = gDummySpriteAffineAnimTable,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_EggShiny,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */

    [SPECIES_CASTFORM_SANDY] =
    {
        .baseHP        = 70,
        .baseAttack    = 70,
        .baseDefense   = 70,
        .baseSpeed     = 70,
        .baseSpAttack  = 70,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 147 : 145,
        .evYield_HP = 1,
        .itemCommon = ITEM_MYSTIC_WATER,
        .itemRare = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_FORECAST, ABILITY_FORECAST, ABILITY_FORECAST },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Castform"),
        .cryId = CRY_CASTFORM,
        .natDexNum = NATIONAL_DEX_CASTFORM,
        .categoryName = _("Weather"),
        .height = 3,
        .weight = 8,
        .description = COMPOUND_STRING(
            "It takes this form during a sandstorm.\n"
            "In an experiment where it was placed in\n"
            "a sandbox, it didn't change to this\n"
            "form. Its body is hard and jagged."),
        .pokemonScale = 435,
        .pokemonOffset = -5,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CastformSandy,
        .frontPicSize = MON_COORDS_SIZE(24, 32), //
        .frontPicYOffset = 17, //
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 12),
            ANIMCMD_FRAME(1, 24),
            ANIMCMD_FRAME(0, 24),
            ANIMCMD_FRAME(1, 24),
            ANIMCMD_FRAME(0, 24),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE, //
        .enemyMonElevation = 16, //
        .backPic = gMonBackPic_CastformSandy,
        .backPicSize = MON_COORDS_SIZE(32, 64),
        .backPicYOffset = 0, //
        .backAnimId = BACK_ANIM_SHAKE_GLOW_RED, //
        .palette = gMonPalette_CastformSandy,
        .shinyPalette = gMonShinyPalette_CastformSandy,
        .iconSprite = gMonIcon_CastformSandy,
        .iconPalIndex = 0,
        SHADOW(1, 10, SHADOW_SIZE_S)
        FOOTPRINT(Castform)
        OVERWORLD(
            sPicTable_CastformNormal, //
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_CastformNormal, //
            gShinyOverworldPalette_CastformNormal //
        )
        .levelUpLearnset = sCastformLevelUpLearnset,
        .teachableLearnset = sCastformTeachableLearnset,
        .eggMoveLearnset = sCastformEggMoveLearnset,
        .formSpeciesIdTable = sCastformFormSpeciesIdTable,
        .formChangeTable = sCastformFormChangeTable,
    },

    [SPECIES_ANCHORAGE] =
    {
        .baseHP        = 80,
        .baseAttack    = 125,
        .baseDefense   = 75,
        .baseSpeed     = 35,
        .baseSpAttack  = 50,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER, TYPE_STEEL),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(25), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_SWIFT_SWIM, ABILITY_STRONG_JAW, ABILITY_SNIPER },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Anchorage"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_ANCHORAGE,
        .categoryName = _("Anchor"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Anchorage,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, // 
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Anchorage,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Anchorage,
        .shinyPalette = gMonShinyPalette_Anchorage,
        .iconSprite = gMonIcon_Anchorage,
        .iconPalIndex = 0,
        FOOTPRINT(Anchorage)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_ANIMON] =
    {
        .baseHP        = 48,
        .baseAttack    = 48,
        .baseDefense   = 60,
        .baseSpeed     = 48,
        .baseSpAttack  = 48,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_STEEL),
        .catchRate = 35,
        .expYield = 133,
        .evYield_HP = 2,
        .itemCommon = ITEM_QUICK_POWDER,
        .itemRare = ITEM_METAL_POWDER,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_MAGNET_PULL, ABILITY_MAGNET_PULL, ABILITY_STURDY },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Animon"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_ANIMON,
        .categoryName = _("Animated"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Animon,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Animon,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Animon,
        .shinyPalette = gMonShinyPalette_Animon,
        .iconSprite = gMonIcon_Animon,
        .iconPalIndex = 0, //
        FOOTPRINT(Animon)
        .tmIlliterate = TRUE, //
        .levelUpLearnset = sDittoLevelUpLearnset, //
        .teachableLearnset = sDittoTeachableLearnset, //
    },
    
    [SPECIES_AQUARIA] =
    {
        .baseHP        = 85,
        .baseAttack    = 75,
        .baseDefense   = 110,
        .baseSpeed     = 75,
        .baseSpAttack  = 110,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 2,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_TORRENT, ABILITY_TORRENT, ABILITY_MAGIC_BOUNCE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Aquaria"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_AQUARIA,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Aquaria,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Aquaria,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Aquaria,
        .shinyPalette = gMonShinyPalette_Aquaria,
        .iconSprite = gMonIcon_Aquaria,
        .iconPalIndex = 4,
        FOOTPRINT(Aquaria)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_AQUIS] =
    {
        .baseHP        = 70,
        .baseAttack    = 50,
        .baseDefense   = 90,
        .baseSpeed     = 60,
        .baseSpAttack  = 50,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_TORRENT, ABILITY_TORRENT, ABILITY_MAGIC_BOUNCE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Aquis"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_AQUIS,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Aquis,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Aquis,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Aquis,
        .shinyPalette = gMonShinyPalette_Aquis,
        .iconSprite = gMonIcon_Aquis,
        .iconPalIndex = 2,
        FOOTPRINT(Aquis)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 34, SPECIES_AQUARIA}),
    },
    
    [SPECIES_BELLOYANT] =
    {
        .baseHP        = 115,
        .baseAttack    = 55,
        .baseDefense   = 70,
        .baseSpeed     = 50,
        .baseSpAttack  = 80,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_DARK, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_HP = 2,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_LIMBER, ABILITY_CACOPHONY, ABILITY_MAGICIAN },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Belloyant"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_BELLOYANT,
        .categoryName = _("Bell Cat"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Belloyant,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Belloyant,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Belloyant,
        .shinyPalette = gMonShinyPalette_Belloyant,
        .iconSprite = gMonIcon_Belloyant,
        .iconPalIndex = 0,
        FOOTPRINT(Belloyant)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_BELMITT] =
    {
        .baseHP        = 65,
        .baseAttack    = 105,
        .baseDefense   = 70,
        .baseSpeed     = 100,
        .baseSpAttack  = 70,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 253,
        .evYield_Attack = 2,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_CHLOROPHYLL, ABILITY_IRON_FIST },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Belmitt"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_BELMITT,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Belmitt,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Belmitt,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Belmitt,
        .shinyPalette = gMonShinyPalette_Belmitt,
        .iconSprite = gMonIcon_Belmitt,
        .iconPalIndex = 5,
        FOOTPRINT(Belmitt)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_BLOSSOMOLE] =
    {
        .baseHP        = 35,
        .baseAttack    = 50,
        .baseDefense   = 45,
        .baseSpeed     = 60,
        .baseSpAttack  = 115,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_HEALER, ABILITY_REGENERATOR, ABILITY_TRIAGE },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Blossomole"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_BLOSSOMOLE,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Blossomole,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Blossomole,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Blossomole,
        .shinyPalette = gMonShinyPalette_Blossomole,
        .iconSprite = gMonIcon_Blossomole,
        .iconPalIndex = 1,
        FOOTPRINT(Blossomole)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_BOMSOAKER] =
    {
        .baseHP        = 60,
        .baseAttack    = 80,
        .baseDefense   = 65,
        .baseSpeed     = 40,
        .baseSpAttack  = 120,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_TORRENT, ABILITY_BOMSOAKER },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Bomsoaker"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_BOMSOAKER,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Bomsoaker,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Bomsoaker,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Bomsoaker,
        .shinyPalette = gMonShinyPalette_Bomsoaker,
        .iconSprite = gMonIcon_Bomsoaker,
        .iconPalIndex = 0,
        FOOTPRINT(Bomsoaker)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_CHIKS] =
    {
        .baseHP        = 25,
        .baseAttack    = 50,
        .baseDefense   = 30,
        .baseSpeed     = 45,
        .baseSpAttack  = 20,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 33,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_EARLY_BIRD, ABILITY_RATTLED },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Chiks"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_CHIKS,
        .categoryName = _("Chick"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Chiks,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Chiks,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Chiks,
        .shinyPalette = gMonShinyPalette_Chiks,
        .iconSprite = gMonIcon_Chiks,
        .iconPalIndex = 0, //
        FOOTPRINT(Chiks)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .eggMoveLearnset = sDoduoEggMoveLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_DODUO, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_COTTONEKO] =
    {
        .baseHP        = 95,
        .baseAttack    = 70,
        .baseDefense   = 80,
        .baseSpeed     = 120,
        .baseSpAttack  = 80,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS), //
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Cottoneko"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_COTTONEKO,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Cottoneko,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Cottoneko,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Cottoneko,
        .shinyPalette = gMonShinyPalette_Cottoneko,
        .iconSprite = gMonIcon_Cottoneko,
        .iconPalIndex = 1,
        FOOTPRINT(Cottoneko)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_CRUZ] =
    {
        .baseHP        = 50,
        .baseAttack    = 35,
        .baseDefense   = 70,
        .baseSpeed     = 50,
        .baseSpAttack  = 35,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1), //
        .abilities = { ABILITY_TORRENT, ABILITY_TORRENT, ABILITY_MAGIC_BOUNCE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Cruz"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_CRUZ,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Cruz,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Cruz,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Cruz,
        .shinyPalette = gMonShinyPalette_Cruz,
        .iconSprite = gMonIcon_Cruz,
        .iconPalIndex = 0,
        FOOTPRINT(Cruz)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 17, SPECIES_AQUIS}),
    },
    
    [SPECIES_DANDENEKO] =
    {
        .baseHP        = 80,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpeed     = 95,
        .baseSpAttack  = 60,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS), //
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Dandeneko"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_DANDENEKO, //
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Dandeneko,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Dandeneko,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Dandeneko,
        .shinyPalette = gMonShinyPalette_Dandeneko,
        .iconSprite = gMonIcon_Dandeneko,
        .iconPalIndex = 0, //
        FOOTPRINT(Dandeneko)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 34, SPECIES_COTTONEKO}),
    },
    
    [SPECIES_DYNABEAR] =
    {
        .baseHP        = 75,
        .baseAttack    = 110,
        .baseDefense   = 75,
        .baseSpeed     = 85,
        .baseSpAttack  = 110,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Dynabear"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_DYNABEAR,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Dynabear,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Dynabear,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Dynabear,
        .shinyPalette = gMonShinyPalette_Dynabear,
        .iconSprite = gMonIcon_Dynabear,
        .iconPalIndex = 0,
        FOOTPRINT(Dynabear)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_FLAMBEAR] =
    {
        .baseHP        = 35,
        .baseAttack    = 70,
        .baseDefense   = 40,
        .baseSpeed     = 55,
        .baseSpAttack  = 70,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Flambear"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_FLAMBEAR, //
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Flambear,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Flambear,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Flambear,
        .shinyPalette = gMonShinyPalette_Flambear,
        .iconSprite = gMonIcon_Flambear,
        .iconPalIndex = 0,
        FOOTPRINT(Flambear)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 17, SPECIES_VOLBEAR}),
    },
    
    [SPECIES_GOHNG] =
    {
        .baseHP        = 100,
        .baseAttack    = 150,
        .baseDefense   = 80,
        .baseSpeed     = 170,
        .baseSpAttack  = 80,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .evYield_Speed = 2,
        .genderRatio = MON_MALE,
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_MOLD_BREAKER, ABILITY_PROTEAN },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Gohng"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_GOHNG,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Gohng,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Gohng,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Gohng,
        .shinyPalette = gMonShinyPalette_Gohng,
        .iconSprite = gMonIcon_Gohng,
        .iconPalIndex = 0, //
        FOOTPRINT(Gohng)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .isLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
    },
    
    [SPECIES_GOLPY] =
    {
        .baseHP        = 20,
        .baseAttack    = 35,
        .baseDefense   = 30,
        .baseSpeed     = 30,
        .baseSpAttack  = 15,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255,
        .expYield = 26,
        .evYield_Attack = 1,
        .itemRare = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_SWIFT_SWIM, ABILITY_WATER_VEIL, ABILITY_HYDRATION },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Golpy"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_GOLPY,
        .categoryName = _("Guppy"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Golpy,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Golpy,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Golpy,
        .shinyPalette = gMonShinyPalette_Golpy,
        .iconSprite = gMonIcon_Golpy,
        .iconPalIndex = 0, //
        FOOTPRINT(Golpy)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GOLDEEN, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_GRIMEY] =
    {
        .baseHP        = 55,
        .baseAttack    = 55,
        .baseDefense   = 35,
        .baseSpeed     = 15,
        .baseSpAttack  = 20,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 255,
        .expYield = 41,
        .evYield_HP = 1,
        .itemRare = ITEM_BLACK_SLUDGE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_STENCH, ABILITY_STICKY_HOLD, ABILITY_AFTERMATH },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Grimey"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_GRIMEY,
        .categoryName = _("Grime"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Grimey,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Grimey,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Grimey,
        .shinyPalette = gMonShinyPalette_Grimey,
        .iconSprite = gMonIcon_Grimey,
        .iconPalIndex = 0, //
        FOOTPRINT(Grimey)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GRIMER, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD},{IF_NOT_TIME, TIME_NIGHT})},
                                {EVO_LEVEL, 0, SPECIES_GRIMER_ALOLA, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD},{IF_TIME, TIME_NIGHT})}),
    },
    
    [SPECIES_GROTESS] =
    {
        .baseHP        = 60,
        .baseAttack    = 75,
        .baseDefense   = 125,
        .baseSpeed     = 55,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_WATER, TYPE_DARK),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Grotess"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_GROTESS,
        .categoryName = _("Grotesque"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Grotess,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Grotess,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Grotess,
        .shinyPalette = gMonShinyPalette_Grotess,
        .iconSprite = gMonIcon_Grotess,
        .iconPalIndex = 0,
        FOOTPRINT(Grotess)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_KOTORA] =
    {
        .baseHP        = 40,
        .baseAttack    = 20,
        .baseDefense   = 40,
        .baseSpeed     = 80,
        .baseSpAttack  = 50,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STATIC, ABILITY_STATIC, ABILITY_OVERCHARGE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Kotora"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_KOTORA,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Kotora,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .backPic = gMonBackPic_Kotora,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Kotora,
        .shinyPalette = gMonShinyPalette_Kotora,
        .iconSprite = gMonIcon_Kotora,
        .iconPalIndex = 0,
        .frontAnimFrames = ANIM_FRAMES( //
            ANIMCMD_FRAME(0, 30),
            ANIMCMD_FRAME(1, 30),
            ANIMCMD_FRAME(0, 1),
        ),
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS, //
        FOOTPRINT(Kotora)
        OVERWORLD(
            sPicTable_Kotora,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Kotora,
            gShinyOverworldPalette_Kotora
        )
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_RAITORA}),
    },
    
    [SPECIES_KURSTRAW] =
    {
        .baseHP        = 50,
        .baseAttack    = 50,
        .baseDefense   = 125,
        .baseSpeed     = 100,
        .baseSpAttack  = 50,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_CURSED_BODY, ABILITY_CURSED_BODY, ABILITY_KURSTRAW },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Kurstraw"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_KURSTRAW,
        .categoryName = _("Curse"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Kurstraw,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Kurstraw,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Kurstraw,
        .shinyPalette = gMonShinyPalette_Kurstraw,
        .iconSprite = gMonIcon_Kurstraw,
        .iconPalIndex = 1,
        FOOTPRINT(Kurstraw)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_SPECIFIC_LEVEL, 0, SPECIES_PANGSHI}),
    },
    
    [SPECIES_LEFNEKO] =
    {
        .baseHP        = 60,
        .baseAttack    = 35,
        .baseDefense   = 45,
        .baseSpeed     = 75,
        .baseSpAttack  = 45,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS), //
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Lefneko"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_LEFNEKO,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Lefneko,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Lefneko,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Lefneko,
        .shinyPalette = gMonShinyPalette_Lefneko,
        .iconSprite = gMonIcon_Lefneko,
        .iconPalIndex = 0, //
        FOOTPRINT(Lefneko)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 17, SPECIES_DANDENEKO}),
    },
    
    [SPECIES_MADAME] =
    {
        .baseHP        = 70,
        .baseAttack    = 95,
        .baseDefense   = 80,
        .baseSpeed     = 135,
        .baseSpAttack  = 60,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 45,
        .expYield = 168,
        .evYield_Attack = 1,
        .evYield_Speed = 1,
        .itemRare = ITEM_LEEK,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_FIELD),
        .abilities = { ABILITY_BIG_PECKS, ABILITY_INFILTRATOR, ABILITY_SCRAPPY },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Madame"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_MADAME,
        .categoryName = _("Fancy"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Madame,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Madame,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Madame,
        .shinyPalette = gMonShinyPalette_Madame,
        .iconSprite = gMonIcon_Madame,
        .iconPalIndex = 1,
        FOOTPRINT(Madame)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_MEOWSY] =
    {
        .baseHP        = 25,
        .baseAttack    = 25,
        .baseDefense   = 20,
        .baseSpeed     = 65,
        .baseSpAttack  = 20,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 31,
        .evYield_Speed = 1,
        .itemRare = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PICKUP, ABILITY_RATTLED, ABILITY_TRUANT },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Meowsy"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_MEOWSY,
        .categoryName = _("Loafing Cat"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Meowsy,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Meowsy,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Meowsy,
        .shinyPalette = gMonShinyPalette_Meowsy,
        .iconSprite = gMonIcon_Meowsy,
        .iconPalIndex = 1,
        FOOTPRINT(Meowsy)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_MEOWTH, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD}, {IF_NOT_TIME, TIME_NIGHT})},
                                {EVO_LEVEL, 0, SPECIES_MEOWTH_ALOLA, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD}, {IF_TIME, TIME_NIGHT})},
                                {EVO_TRADE, 0, SPECIES_MEOWTH_GALAR, CONDITIONS({IF_HOLD_ITEM, ITEM_METAL_COAT})}),
    },
    
    [SPECIES_MINICORN] =
    {
        .baseHP        = 30,
        .baseAttack    = 60,
        .baseDefense   = 30,
        .baseSpeed     = 65,
        .baseSpAttack  = 35,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255,
        .expYield = 52,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_FLASH_FIRE, ABILITY_HUSTLE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Minicorn"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_MINICORN,
        .categoryName = _("Unicorn"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Minicorn,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Minicorn,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Minicorn,
        .shinyPalette = gMonShinyPalette_Minicorn,
        .iconSprite = gMonIcon_Minicorn,
        .iconPalIndex = 0, //
        FOOTPRINT(Minicorn)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_FIRE_STONE, SPECIES_PONYTA},
                                {EVO_ITEM, ITEM_SHINY_STONE, SPECIES_PONYTA_GALAR}),
    },
    
    [SPECIES_NUMPUFF] =
    {
        .baseHP        = 95,
        .baseAttack    = 100,
        .baseDefense   = 115,
        .baseSpeed     = 60,
        .baseSpAttack  = 60,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_WATER, TYPE_POISON),
        .catchRate = 30,
        .expYield = 131,
        .evYield_Defense = 2,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_POISON_POINT, ABILITY_SWIFT_SWIM, ABILITY_OBLIVIOUS },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Numpuff"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_NUMPUFF,
        .categoryName = _("Pufferfish"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Numpuff,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Numpuff,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Numpuff,
        .shinyPalette = gMonShinyPalette_Numpuff,
        .iconSprite = gMonIcon_Numpuff,
        .iconPalIndex = 0,
        FOOTPRINT(Numpuff)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_OWLDURN] =
    {
        .baseHP        = 70,
        .baseAttack    = 86,
        .baseDefense   = 96,
        .baseSpeed     = 100,
        .baseSpAttack  = 50,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 90,
        .expYield = 138,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_SNIPER, ABILITY_BIG_PECKS, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Owldurn"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_OWLDURN,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Owldurn,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Owldurn,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Owldurn,
        .shinyPalette = gMonShinyPalette_Owldurn,
        .iconSprite = gMonIcon_Owldurn,
        .iconPalIndex = 2,
        FOOTPRINT(Owldurn)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_PANGSHI] =
    {
        .baseHP        = 50,
        .baseAttack    = 125,
        .baseDefense   = 50,
        .baseSpeed     = 100,
        .baseSpAttack  = 125,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .evYield_SpAttack = 1,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_CURSED_BODY, ABILITY_CURSED_BODY, ABILITY_KURSTRAW },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Pangshi"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_PANGSHI,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Pangshi,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Pangshi,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Pangshi,
        .shinyPalette = gMonShinyPalette_Pangshi,
        .iconSprite = gMonIcon_Pangshi,
        .iconPalIndex = 2,
        FOOTPRINT(Pangshi)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_SPECIFIC_LEVEL, 0, SPECIES_KURSTRAW}),
    },
    
    [SPECIES_PARA] =
    {
        .baseHP        = 20,
        .baseAttack    = 45,
        .baseDefense   = 30,
        .baseSpeed     = 15,
        .baseSpAttack  = 20,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 255,
        .expYield = 29,
        .evYield_Attack = 1,
        .itemCommon = ITEM_TINY_MUSHROOM,
        .itemRare = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_EFFECT_SPORE, ABILITY_ANTICIPATION, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Para"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_PARA,
        .categoryName = _("Cap"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Para,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Para,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Para,
        .shinyPalette = gMonShinyPalette_Para,
        .iconSprite = gMonIcon_Para,
        .iconPalIndex = 0, //
        FOOTPRINT(Para)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_PARAS, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_PLUX] =
    {
        .baseHP        = 50,
        .baseAttack    = 75,
        .baseDefense   = 60,
        .baseSpeed     = 140,
        .baseSpAttack  = 75,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Plux"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_PLUX,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Plux,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Plux,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Plux,
        .shinyPalette = gMonShinyPalette_Plux,
        .iconSprite = gMonIcon_Plux,
        .iconPalIndex = 2,
        FOOTPRINT(Plux)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_PORYGON_C] =
    {
        .baseHP        = 85,
        .baseAttack    = 135,
        .baseDefense   = 75,
        .baseSpeed     = 90,
        .baseSpAttack  = 80,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_STEEL, TYPE_STEEL),
        .catchRate = 45,
        .expYield = 241,
        .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_ADAPTABILITY, ABILITY_DOWNLOAD, ABILITY_ANALYTIC },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Porygon-C"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_PORYGON_C,
        .categoryName = _("Virtual"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Porygon_C,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Porygon_C,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Porygon_C,
        .shinyPalette = gMonShinyPalette_Porygon_C,
        .iconSprite = gMonIcon_Porygon_C,
        .iconPalIndex = 0, //
        FOOTPRINT(Porygon_C)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_PUDDI] =
    {
        .baseHP        = 35,
        .baseAttack    = 50,
        .baseDefense   = 20,
        .baseSpeed     = 40,
        .baseSpAttack  = 50,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255,
        .expYield = 44,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_FLASH_FIRE, ABILITY_RATTLED },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Puddi"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_PUDDI,
        .categoryName = _("Puppy"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Puddi,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Puddi,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Puddi,
        .shinyPalette = gMonShinyPalette_Puddi,
        .iconSprite = gMonIcon_Puddi,
        .iconPalIndex = 0,
        FOOTPRINT(Puddi)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GROWLITHE, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_RAITORA] =
    {
        .baseHP        = 60,
        .baseAttack    = 50,
        .baseDefense   = 65,
        .baseSpeed     = 120,
        .baseSpAttack  = 80,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STATIC, ABILITY_MOTOR_DRIVE, ABILITY_OVERCHARGE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Raitora"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_RAITORA,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Raitora,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Raitora,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Raitora,
        .shinyPalette = gMonShinyPalette_Raitora,
        .iconSprite = gMonIcon_Raitora,
        .iconPalIndex = 0,
        FOOTPRINT(Raitora)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_RAYLEEP] =
    {
        .baseHP        = 55,
        .baseAttack    = 35,
        .baseDefense   = 40,
        .baseSpeed     = 80,
        .baseSpAttack  = 60,
        .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_WATER, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Rayleep"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_RAYLEEP,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."), //
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Rayleep,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Rayleep,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Rayleep,
        .shinyPalette = gMonShinyPalette_Rayleep,
        .iconSprite = gMonIcon_Rayleep,
        .iconPalIndex = 0,
        FOOTPRINT(Rayleep)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_RINRING] =
    {
        .baseHP        = 80,
        .baseAttack    = 40,
        .baseDefense   = 50,
        .baseSpeed     = 40,
        .baseSpAttack  = 50,
        .baseSpDefense = 0,
        .types = MON_TYPES(TYPE_DARK, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_LIMBER, ABILITY_CACOPHONY, ABILITY_MAGICIAN },
        .bodyColor = BODY_COLOR_BLACK, //
        .speciesName = _("Rinring"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_RINRING,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Rinring,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Rinring,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Rinring,
        .shinyPalette = gMonShinyPalette_Rinring,
        .iconSprite = gMonIcon_Rinring,
        .iconPalIndex = 0,
        FOOTPRINT(Rinring)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_BELLOYANT}),
    },
    
    [SPECIES_SUNMOLA] =
    {
        .baseHP        = 50,
        .baseAttack    = 60,
        .baseDefense   = 60,
        .baseSpeed     = 25,
        .baseSpAttack  = 40,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_SWIFT_SWIM, ABILITY_SWIFT_SWIM, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Sunmola"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_SUNMOLA,
        .categoryName = _("Sunfish"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Sunmola,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Sunmola,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Sunmola,
        .shinyPalette = gMonShinyPalette_Sunmola,
        .iconSprite = gMonIcon_Sunmola,
        .iconPalIndex = 2,
        FOOTPRINT(Sunmola)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 42, SPECIES_ANCHORAGE, CONDITIONS({IF_TYPE_IN_PARTY, TYPE_STEEL})},
                                {EVO_LEVEL, 42, SPECIES_GROTESS, CONDITIONS({IF_TYPE_IN_PARTY, TYPE_DARK})}),
    },
    
    [SPECIES_SWIEVEL] =
    {
        .baseHP        = 120,
        .baseAttack    = 85,
        .baseDefense   = 65,
        .baseSpeed     = 80,
        .baseSpAttack  = 50,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_ICE),
        .catchRate = 45,
        .expYield = 179,
        .evYield_HP = 2,
        .itemRare = ITEM_QUICK_CLAW,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SNIPER, ABILITY_SUPER_LUCK, ABILITY_SHARPNESS },
        .bodyColor = BODY_COLOR_BLUE, //
        .speciesName = _("Swievel"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_SWIEVEL,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Swievel,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Swievel,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_Swievel,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64), //
        .backPicFemale = gMonBackPic_Swievel,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64), //
        .paletteFemale = gMonPalette_Swievel,
        .shinyPaletteFemale = gMonShinyPalette_Swievel,
        .iconSpriteFemale = gMonIcon_Swievel,
        .iconPalIndexFemale = 1, //
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Swievel,
        .shinyPalette = gMonShinyPalette_Swievel,
        .iconSprite = gMonIcon_Swievel,
        .iconPalIndex = 0, //
        FOOTPRINT(Swievel)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_TANGEL] =
    {
        .baseHP        = 40,
        .baseAttack    = 30,
        .baseDefense   = 65,
        .baseSpeed     = 35,
        .baseSpAttack  = 60,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 255,
        .expYield = 51,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_LEAF_GUARD, ABILITY_REGENERATOR },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Tangel"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_TANGEL,
        .categoryName = _("Tangle"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Tangel,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Tangel,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Tangel,
        .shinyPalette = gMonShinyPalette_Tangel,
        .iconSprite = gMonIcon_Tangel,
        .iconPalIndex = 1,
        FOOTPRINT(Tangel)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_TANGELA, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_TANGRATH] =
    {
        .baseHP        = 125,
        .baseAttack    = 100,
        .baseDefense   = 50,
        .baseSpeed     = 110,
        .baseSpAttack  = 100,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = 30,
        .expYield = 167,
        .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_LEAF_GUARD, ABILITY_SOLAR_POWER },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Tangrath"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_TANGRATH,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Tangrath,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Tangrath,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Tangrath,
        .shinyPalette = gMonShinyPalette_Tangrath,
        .iconSprite = gMonIcon_Tangrath,
        .iconPalIndex = 0,
        FOOTPRINT(Tangrath)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_TRIFOX] =
    {
        .baseHP        = 23,
        .baseAttack    = 28,
        .baseDefense   = 25,
        .baseSpeed     = 40,
        .baseSpAttack  = 30,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255,
        .expYield = 37,
        .evYield_Speed = 1,
        .itemRare = ITEM_CHARCOAL,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_PICKUP, ABILITY_RATTLED },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Trifox"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_TRIFOX,
        .categoryName = _("Kit"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Trifox,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Trifox,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Trifox,
        .shinyPalette = gMonShinyPalette_Trifox,
        .iconSprite = gMonIcon_Trifox,
        .iconPalIndex = 0, //
        FOOTPRINT(Trifox)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_VULPIX_ALOLA, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD},{IF_WEATHER, WEATHER_SNOW})},
                                {EVO_LEVEL, 0, SPECIES_VULPIX, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_TURBANN] =
    {
        .baseHP        = 50,
        .baseAttack    = 20,
        .baseDefense   = 130,
        .baseSpeed     = 40,
        .baseSpAttack  = 50,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_SOLID_ROCK, ABILITY_ROCK_HEAD, ABILITY_STURDY },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Turbann"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_TURBANN,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Turbann,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Turbann,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Turbann,
        .shinyPalette = gMonShinyPalette_Turbann,
        .iconSprite = gMonIcon_Turbann,
        .iconPalIndex = 0, //
        FOOTPRINT(Turbann)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_TWINZ] =
    {
        .baseHP        = 20,
        .baseAttack    = 150,
        .baseDefense   = 40,
        .baseSpeed     = 100,
        .baseSpAttack  = 150,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_GHOST, TYPE_NORMAL),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_CONTRARY, ABILITY_NO_GUARD, ABILITY_PARENTAL_BOND },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Twinz"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_TWINZ,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Twinz,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Twinz,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Twinz,
        .shinyPalette = gMonShinyPalette_Twinz,
        .iconSprite = gMonIcon_Twinz,
        .iconPalIndex = 2,
        FOOTPRINT(Twinz)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_VOLBEAR] =
    {
        .baseHP        = 50,
        .baseAttack    = 90,
        .baseDefense   = 55,
        .baseSpeed     = 70,
        .baseSpAttack  = 90,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MONSTER),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP }, //
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Volbear"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_VOLBEAR,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Volbear,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Volbear,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Volbear,
        .shinyPalette = gMonShinyPalette_Volbear,
        .iconSprite = gMonIcon_Volbear,
        .iconPalIndex = 0,
        FOOTPRINT(Volbear)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 34, SPECIES_DYNABEAR}),
    },
    
    [SPECIES_WARWOLF] =
    {
        .baseHP        = 50,
        .baseAttack    = 145,
        .baseDefense   = 80,
        .baseSpeed     = 35,
        .baseSpAttack  = 85,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ICE, TYPE_NORMAL),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SNOW_CLOAK, ABILITY_SLUSH_RUSH },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Warwolf"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_WARWOLF,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Warwolf,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Warwolf,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Warwolf,
        .shinyPalette = gMonShinyPalette_Warwolf,
        .iconSprite = gMonIcon_Warwolf,
        .iconPalIndex = 0,
        FOOTPRINT(Warwolf)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_WHIMSEY] =
    {
        .baseHP        = 55,
        .baseAttack    = 255,
        .baseDefense   = 10,
        .baseSpeed     = 75,
        .baseSpAttack  = 135,
        .baseSpDefense = 10,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY),
        .catchRate = 30,
        .expYield = 498,
        .evYield_Attack = 3,
        .itemCommon = ITEM_LUCKY_EGG,
        .genderRatio = MON_FEMALE,
        .eggCycles = 40,
        .friendship = 140,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_NATURAL_CURE, ABILITY_SERENE_GRACE, ABILITY_IRON_FIST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Whimsey"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_WHIMSEY,
        .categoryName = _("Whimsy"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Whimsey,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Whimsey,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Whimsey,
        .shinyPalette = gMonShinyPalette_Whimsey,
        .iconSprite = gMonIcon_Whimsey,
        .iconPalIndex = 0, //
        FOOTPRINT(Whimsey)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_WOLFMAN] =
    {
        .baseHP        = 30,
        .baseAttack    = 80,
        .baseDefense   = 40,
        .baseSpeed     = 20,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ICE, TYPE_NORMAL),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SNOW_CLOAK, ABILITY_SLUSH_RUSH },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Wolfman"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_WOLFMAN,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_Wolfman,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_Wolfman,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_Wolfman,
        .shinyPalette = gMonShinyPalette_Wolfman,
        .iconSprite = gMonIcon_Wolfman,
        .iconPalIndex = 0,
        FOOTPRINT(Wolfman)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_ICE_STONE, SPECIES_WARWOLF}),
    },
    
    [SPECIES_x_AZUMARILL_x] =
    {
        .baseHP        = 50,
        .baseAttack    = 60,
        .baseDefense   = 80,
        .baseSpeed     = 100,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_WATER, TYPE_FIGHTING),
        .catchRate = 75,
        .expYield = 185,
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_THICK_FAT, ABILITY_HUGE_POWER, ABILITY_SAP_SIPPER },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Kiromarill"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_x_AZUMARILL_x,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Azumarill_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Azumarill_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Azumarill_x,
        .shinyPalette = gMonShinyPalette_x_Azumarill_x,
        .iconSprite = gMonIcon_x_Azumarill_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Azumarill_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset,//
    },
    
    [SPECIES_x_CELEBI_x] =
    {
        .baseHP        = 100,
        .baseAttack    = 100,
        .baseDefense   = 100,
        .baseSpeed     = 100,
        .baseSpAttack  = 100,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FAIRY),
        .catchRate = 255, //
        .expYield = 67, //
        .evYield_HP = 1, //
        .genderRatio = PERCENT_FEMALE(50), //
        .eggCycles = 20, //
        .friendship = STANDARD_FRIENDSHIP, //
        .growthRate = GROWTH_MEDIUM_FAST, //
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_IRON_BARBS, ABILITY_IRON_BARBS, ABILITY_SERENE_GRACE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("CelebiX"), // x_MODIFY_x
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_x_CELEBI_x,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Celebi_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Celebi_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Celebi_x,
        .shinyPalette = gMonShinyPalette_x_Celebi_x,
        .iconSprite = gMonIcon_x_Celebi_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Celebi_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .isMythical = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
    },
    
    [SPECIES_x_DUNSPARCE_x] =
    {
        .baseHP        = 60,
        .baseAttack    = 30,
        .baseDefense   = 30,
        .baseSpeed     = 15,
        .baseSpAttack  = 25,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 49,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_SERENE_GRACE, ABILITY_RUN_AWAY, ABILITY_RATTLED },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Dunslet"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_x_DUNSPARCE_x,
        .categoryName = _("Unknown"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Dunsparce_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Dunsparce_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Dunsparce_x,
        .shinyPalette = gMonShinyPalette_x_Dunsparce_x,
        .iconSprite = gMonIcon_x_Dunsparce_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Dunsparce_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_DUNSPARCE, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },
    
    [SPECIES_x_GLIGAR_x] =
    {
        .baseHP        = 95,
        .baseAttack    = 45,
        .baseDefense   = 75,
        .baseSpeed     = 125,
        .baseSpAttack  = 95,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_DARK, TYPE_FLYING),
        .catchRate = 30,
        .expYield = 192,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SUPER_LUCK, ABILITY_SHARPNESS, ABILITY_PRANKSTER },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Stingbat"),
        .cryId = CRY_NONE, //
        .natDexNum = NATIONAL_DEX_x_GLIGAR_x,
        .categoryName = _("Stinger Bat"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Gligar_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Gligar_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Gligar_x,
        .shinyPalette = gMonShinyPalette_x_Gligar_x,
        .iconSprite = gMonIcon_x_Gligar_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Gligar_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_x_WOOPER_x] =
    {
        .baseHP        = 55,
        .baseAttack    = 45,
        .baseDefense   = 45,
        .baseSpeed     = 15,
        .baseSpAttack  = 25,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_WATER, TYPE_GROUND),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 42 : 52,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_OBLIVIOUS, ABILITY_UNAWARE, ABILITY_GLUTTONY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Woober"),
        .cryId = CRY_WOOPER,
        .natDexNum = NATIONAL_DEX_x_WOOPER_x,
        .categoryName = _("Goober"),
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING(
            "Woober Woober, Woober.\n"
            "Woober! Woober Woober Woober.\n"
            "Woober Woober. Woober, Woober?\n"
            "Woober."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Wooper_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Wooper_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Wooper_x,
        .shinyPalette = gMonShinyPalette_x_Wooper_x,
        .iconSprite = gMonIcon_x_Wooper_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Wooper_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .perfectIVCount = 2,
        .isMythical = TRUE,
    },

    [SPECIES_x_GIBLE_x] =
    {
        .baseHP        = 40,
        .baseAttack    = 45,
        .baseDefense   = 45,
        .baseSpeed     = 58,
        .baseSpAttack  = 42,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_BUG),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 60 : 67,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SAND_VEIL, ABILITY_SAND_VEIL, ABILITY_ROUGH_SKIN }, //
        .bodyColor = BODY_COLOR_BLUE, //
        .speciesName = _("Gible"), //
        .cryId = CRY_GIBLE, //
        .natDexNum = NATIONAL_DEX_x_GIBLE_x,
        .categoryName = _("Land Shark"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Gible_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Gible_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 0, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Gible_x,
        .shinyPalette = gMonShinyPalette_x_Gible_x,
        .iconSprite = gMonIcon_x_Gible_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Gible_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_x_GABITE_x}),
    },

    [SPECIES_x_GABITE_x] =
    {
        .baseHP        = 50,
        .baseAttack    = 65,
        .baseDefense   = 55,
        .baseSpeed     = 68,
        .baseSpAttack  = 82,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_BUG),
        .catchRate = 45,
        .expYield = 144,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SAND_VEIL, ABILITY_SAND_VEIL, ABILITY_ROUGH_SKIN }, //
        .bodyColor = BODY_COLOR_BLUE, //
        .speciesName = _("Gabite"), //
        .cryId = CRY_GABITE, //
        .natDexNum = NATIONAL_DEX_x_GABITE_x,
        .categoryName = _("Cave"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_x_Gabite_x,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Gabite_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 0, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Gabite_x,
        .shinyPalette = gMonShinyPalette_x_Gabite_x,
        .iconSprite = gMonIcon_x_Gabite_x,
        .iconPalIndex = 0, //
        FOOTPRINT(x_Gabite_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
        .evolutions = EVOLUTION({EVO_LEVEL, 48, SPECIES_x_GARCHOMP_x}),
    },

    [SPECIES_x_GARCHOMP_x] =
    {
        .baseHP        = 80,
        .baseAttack    = 95,
        .baseDefense   = 85,
        .baseSpeed     = 108,
        .baseSpAttack  = 102,
        .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_BUG),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 300,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 270,
    #else
        .expYield = 218,
    #endif
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_SAND_VEIL, ABILITY_SAND_VEIL, ABILITY_ROUGH_SKIN }, //
        .bodyColor = BODY_COLOR_BLUE, //
        .speciesName = _("Garchomp"), //
        .cryId = CRY_GARCHOMP, //
        .natDexNum = NATIONAL_DEX_x_GARCHOMP_x,
        .categoryName = _("Mach"), //
        .height = 0, //
        .weight = 0, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder, //
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE, //
        .backPic = gMonBackPic_x_Garchomp_x,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 0, //
        .backAnimId = BACK_ANIM_NONE, //
        .palette = gMonPalette_x_Garchomp_x,
        .shinyPalette = gMonShinyPalette_x_Garchomp_x,
        .iconSprite = gMonIcon_x_Garchomp_x,
        .iconPalIndex = 0,
        FOOTPRINT(x_Garchomp_x)
        .levelUpLearnset = sNoneLevelUpLearnset, //
        .teachableLearnset = sNoneTeachableLearnset, //
    },
    
    [SPECIES_HOOTHOOT_SKANE] =
    {
        .baseHP        = 50,
        .baseAttack    = 36,
        .baseDefense   = 56,
        .baseSpeed     = 60,
        .baseSpAttack  = 30,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 52 : 58,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_SNIPER, ABILITY_BIG_PECKS, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Hoothoot"),
        .cryId = CRY_HOOTHOOT,
        .natDexNum = NATIONAL_DEX_HOOTHOOT,
        .categoryName = _("Owl"),
        .height = 7, //
        .weight = 212, //
        .description = COMPOUND_STRING( //
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256, //
        .pokemonOffset = 0, //
        .trainerScale = 256, //
        .trainerOffset = 0, //
        .frontPic = gMonFrontPic_HoothootSkane,
        .frontPicSize = MON_COORDS_SIZE(64, 64), //
        .frontPicYOffset = 0, //
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_HoothootSkane,
        .backPicSize = MON_COORDS_SIZE(64, 64), //
        .backPicYOffset = 7, //
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_HoothootSkane,
        .shinyPalette = gMonShinyPalette_HoothootSkane,
        .iconSprite = gMonIcon_HoothootSkane,
        .iconPalIndex = 2,
        FOOTPRINT(HoothootSkane)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .formSpeciesIdTable = sHoothootFormSpeciesIdTable,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_OWLDURN}),
    },
};
