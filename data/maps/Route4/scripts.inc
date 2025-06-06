Route4_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route4_OnResume
	.byte 0

Route4_OnTransition::
    call_if_eq VAR_FACING, DIR_SOUTH, Route4_EventScript_SetWeather
    call_if_eq VAR_FACING, DIR_WEST, Route4_EventScript_SetWeather
    end

Route4_EventScript_SetWeather::
    setweather WEATHER_SNOW_CYCLE
    doweather
    return

Route4_OnResume::
  	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route4_EventScript_TryRemoveSnover
	end

Route4_EventScript_TryRemoveSnover::
    specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

Route4_EventScript_Snover_1::
    lockall
    applymovement LOCALID_SNOVER_1, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SNOVER_1, Common_Movement_ExclamationMark
	waitmovement 0
    waitse
    playmoncry SPECIES_SNOVER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    goto_if_set FLAG_BADGE01_GET, Route4_EventScript_BattleSnover_1
    msgbox Route4_Text_SnoverWontMove, MSGBOX_DEFAULT
    releaseall
    end
    
Route4_EventScript_Snover_2::
    lockall
    applymovement LOCALID_SNOVER_2, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SNOVER_2, Common_Movement_ExclamationMark
	waitmovement 0
    waitse
    playmoncry SPECIES_SNOVER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    goto_if_set FLAG_BADGE01_GET, Route4_EventScript_BattleSnover_2
    msgbox Route4_Text_SnoverWontMove, MSGBOX_DEFAULT
    releaseall
    end

Route4_EventScript_BattleSnover_Common::
    setwildbattle SPECIES_SNOVER, 10
	setflag FLAG_SYS_CTRL_OBJ_DELETE
    setflag FLAG_FORCE_HIDDEN_ABILITY
    dowildbattle
    waitstate
    clearflag FLAG_FORCE_HIDDEN_ABILITY
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
    return

Route4_EventScript_BattleSnover_1::
    call Route4_EventScript_BattleSnover_Common
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route4_EventScript_DefeatedSnover_1
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route4_EventScript_RanFromSnover
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route4_EventScript_RanFromSnover
	goto Route4_EventScript_SnoverFlee_1
    
Route4_EventScript_DefeatedSnover_1::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK    
Route4_EventScript_SnoverFlee_1::
    setflag FLAG_DEALT_WITH_SNOVERS
    applymovement LOCALID_SNOVER_2, Common_Movement_FaceLeft
	waitmovement 0
	applymovement LOCALID_SNOVER_2, Common_Movement_ExclamationMark
	waitmovement 0
    playmoncry SPECIES_SNOVER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    applymovement LOCALID_SNOVER_2, Route4_Movement_SnoverFleeMovement_1
    waitmovement 0
    removeobject LOCALID_SNOVER_2
    releaseall
    end

Route4_EventScript_BattleSnover_2::
    call Route4_EventScript_BattleSnover_Common
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route4_EventScript_DefeatedSnover_2
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route4_EventScript_RanFromSnover
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route4_EventScript_RanFromSnover
	goto Route4_EventScript_SnoverFlee_2
    
Route4_EventScript_DefeatedSnover_2::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK    
Route4_EventScript_SnoverFlee_2::
    setflag FLAG_DEALT_WITH_SNOVERS
    applymovement LOCALID_SNOVER_1, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_SNOVER_1, Common_Movement_ExclamationMark
	waitmovement 0
    playmoncry SPECIES_SNOVER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
    applymovement LOCALID_SNOVER_1, Route4_Movement_SnoverFleeMovement_2
    waitmovement 0
    removeobject LOCALID_SNOVER_1
    releaseall
    end

Route4_EventScript_RanFromSnover::
	applymovement LOCALID_SNOVER_1, Common_Movement_ExclamationMark
	applymovement LOCALID_SNOVER_2, Common_Movement_ExclamationMark
	waitmovement 0
    applymovement LOCALID_SNOVER_1, Route4_Movement_SnoverFleeMovement_2
    applymovement LOCALID_SNOVER_2, Route4_Movement_SnoverFleeMovement_1
    waitmovement 0
    removeobject LOCALID_SNOVER_1
    removeobject LOCALID_SNOVER_2
    releaseall
    end

Route4_Movement_SnoverFleeMovement_2::
    walk_faster_right
Route4_Movement_SnoverFleeMovement_1::
    walk_faster_right
    walk_faster_right
    walk_faster_right
    walk_faster_right
    walk_faster_right
    walk_faster_right
    walk_faster_right
    step_end

Route4_Text_SnoverWontMove::
    .string "It looks like these\n"
    .string "SNOVER won't move.\p"
    .string "Try coming back later.$"
