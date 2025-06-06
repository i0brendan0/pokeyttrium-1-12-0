Route3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route3_OnTransition
	.byte 0

Route3_OnTransition::
    call_if_unset FLAG_HIDE_ROUTE3_GHOST, Route3_EventScript_SetGhostVar
    call_if_set FLAG_BADGE01_GET, Route3_EventScript_HideGhost
    end

Route3_EventScript_SetGhostVar::
    setvar VAR_TEMP_0, 2
    return

Route3_EventScript_HideGhost::
    setflag FLAG_HIDE_ROUTE3_GHOST
    return

Route3_EventScript_Ghost::
    lockall
    msgbox Route3_Text_Ghost, MSGBOX_DEFAULT
    releaseall
    end

Route3_EventScript_MoveGhostLeft::
    lockall
    applymovement LOCALID_GHOST_OUTSIDE, Route3_Movement_GhostLeft
    waitmovement 0
    setvar VAR_TEMP_0, 2
    releaseall
    end

Route3_Movement_GhostLeft::
    lock_facing_direction
    slide_left
    unlock_facing_direction
    step_end

Route3_EventScript_MoveGhostRight::
    lockall
    applymovement LOCALID_GHOST_OUTSIDE, Route3_Movement_GhostRight
    waitmovement 0
    setvar VAR_TEMP_0, 1
    releaseall
    end
    
Route3_Movement_GhostRight::
    lock_facing_direction
    slide_right
    unlock_facing_direction
    step_end

Route3_Text_Ghost::
    .string "...$"
