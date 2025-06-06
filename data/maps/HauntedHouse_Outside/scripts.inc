HauntedHouse_Outside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HauntedHouse_Outside_OnTransition
	.byte 0

HauntedHouse_Outside_OnTransition::
    call_if_eq VAR_HAUNTED_HOUSE_STATE, 5, HauntedHouse_Outside_EventScript_ResetGhostState
    end
    
HauntedHouse_Outside_EventScript_ResetGhostState::
    setvar VAR_HAUNTED_HOUSE_STATE, 3
    return
