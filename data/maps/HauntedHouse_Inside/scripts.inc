HauntedHouse_Inside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedHouse_Inside_OnTransition
	.byte 0

@ VAR_HAUNTED_HOUSE_STATE
@ 0 - Havent seen Ghost Lady
@ 1 - Seen Ghost Lady / Reset TV scene
@ 2 - Initiated TV scene
@ 3 - Rotom is ready
@ 4 - Rotom has been caught
@ 5 - Rotom was defeated. Set to 3 when leaving house

HauntedHouse_Inside_OnTransition::
    call_if_set FLAG_CAUGHT_ROTOM, HauntedHouse_Inside_EventScript_TurnOffTV
    end

HauntedHouse_Inside_EventScript_TurnOffTV::
    setmetatile 24, 6, METATILE_Building_TV_Off, TRUE
    return

HauntedHouse_Inside_EventScript_Trigger_1::
    lockall
    setvar VAR_HAUNTED_HOUSE_STATE, 2
    setobjectxy LOCALID_GHOST_INSIDE, 24, 7
    clearflag FLAG_HIDE_HOUSE_GHOST
    releaseall
    end

HauntedHouse_Inside_EventScript_Trigger_2::
    lockall
    applymovement LOCALID_GHOST_INSIDE, Common_Movement_FaceLeft
    waitmovement 0
    applymovement LOCALID_GHOST_INSIDE, HauntedHouse_Inside_Movement_GhostAway
    waitmovement 0
    removeobject LOCALID_GHOST_INSIDE
    setvar VAR_HAUNTED_HOUSE_STATE, 3
    releaseall
    end

HauntedHouse_Inside_EventScript_Trigger_3_4::
    lockall
    setvar VAR_HAUNTED_HOUSE_STATE, 1
    removeobject LOCALID_GHOST_INSIDE
    releaseall
    end

HauntedHouse_Inside_EventScript_Trigger_5::
    call HauntedHouse_Inside_EventScript_TurnOffTV
    end
    
HauntedHouse_Inside_EventScript_Trigger_6::
    lockall
    waitstate
    applymovement LOCALID_GHOST_INSIDE, HauntedHouse_Inside_Movement_GhostUp
    waitmovement 0
    removeobject LOCALID_GHOST_INSIDE
    setvar VAR_HAUNTED_HOUSE_STATE, 1
    releaseall
    end

HauntedHouse_Inside_EventScript_DoorWontOpen::
    msgbox HauntedHouse_Inside_Text_DoorWontOpen, MSGBOX_SIGN
    end

HauntedHouse_Inside_EventScript_CantGoOutThisWay::
    msgbox HauntedHouse_Inside_Text_CantGoOutThisWay, MSGBOX_SIGN
    end

HauntedHouse_Inside_EventScript_TV::
    lockall
    goto_if_eq VAR_HAUNTED_HOUSE_STATE, 3, HauntedHouse_Inside_EventScript_BumpTV
    msgbox HauntedHouse_Inside_Text_TVIsOff
    releaseall
    end
    
HauntedHouse_Inside_EventScript_BumpTV::
    msgbox HauntedHouse_Inside_Text_TVIsOn, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, YES, HauntedHouse_Inside_EventScript_EncounterRotom
    releaseall
    end

HauntedHouse_Inside_EventScript_EncounterRotom::
    waitse
    playmoncry SPECIES_ROTOM, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    msgbox HauntedHouse_Inside_Text_EncounterRotom, MSGBOX_DEFAULT
    setwildbattle SPECIES_ROTOM, 15
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HauntedHouse_Inside_EventScript_DefeatedRotom
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HauntedHouse_Inside_EventScript_RanFromRotom
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HauntedHouse_Inside_EventScript_RanFromRotom
    call HauntedHouse_Inside_EventScript_TurnOffTV
    setvar VAR_HAUNTED_HOUSE_STATE, 4
    releaseall
    end
    
HauntedHouse_Inside_EventScript_DefeatedRotom::
    call HauntedHouse_Inside_EventScript_TurnOffTV
    setvar VAR_HAUNTED_HOUSE_STATE, 5
    msgbox HauntedHouse_Inside_Text_TryAgainLater, MSGBOX_DEFAULT
    releaseall
    end
    
HauntedHouse_Inside_EventScript_RanFromRotom::
    releaseall
    end

HauntedHouse_Inside_Text_TVIsOff::
    .string "The TV doesn't look like it works.$"
    
HauntedHouse_Inside_Text_TVIsOn::
    .string "Static fills the screen.\n"
    .string "Bump the side of the TV?$"

HauntedHouse_Inside_Text_EncounterRotom::
    .string "...\p"
    .string "ROTOM attacked!$"

HauntedHouse_Inside_Text_TryAgainLater::
    .string "ROTOM disappeared and the TV\n"
    .string "stopped working.\p"
    .string "Try coming back later.$"

HauntedHouse_Inside_Movement_GhostUp::
    slide_up
    slide_up
    step_end
    
HauntedHouse_Inside_Movement_GhostAway::
    slide_down
    slide_down
    slide_down
    slide_down
    step_end

HauntedHouse_Inside_Text_DoorWontOpen::
    .string "It looks like this door\n"
    .string "won't open.$"

HauntedHouse_Inside_Text_CantGoOutThisWay::
    .string "You can't go out this way.$"
