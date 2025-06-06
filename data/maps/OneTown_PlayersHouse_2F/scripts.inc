OneTown_PlayersHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PlayersHouse_2F_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, PlayersHouse_2F_OnTransition
	.byte 0

PlayersHouse_2F_OnFrame:
    map_script_2 VAR_ONE_TOWN_TOWN_STATE, 1, PlayersHouse_2F_ForceWalkDown_1
	.2byte 0

PlayersHouse_2F_OnTransition:
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	end

PlayersHouse_2F_ForceWalkDown_1::
    setvar VAR_ONE_TOWN_TOWN_STATE, 2
    end

PlayersHouse_2F_ForceWalkDown_2::
    lockall
    msgbox PlayersHouse_2F_Text_CantLeaveYet, MSGBOX_DEFAULT
    applymovement LOCALID_PLAYER, Common_Movement_WalkDown
    waitmovement
    releaseall
    end

PlayersHouse_2F_WallClock_NEW::
	goto_if_set FLAG_SET_WALL_CLOCK, PlayersHouse_2F_CheckWallClock_NEW
	msgbox PlayersHouse_2F_Text_ClockIsStopped, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special StartWallClock
	waitstate
	delay 30
	setvar VAR_ONE_TOWN_TOWN_STATE, 3
	setflag FLAG_SET_WALL_CLOCK
	playse SE_EXIT
	releaseall
	end

PlayersHouse_2F_CheckWallClock_NEW:
	incrementgamestat GAME_STAT_CHECKED_CLOCK
	fadescreen FADE_TO_BLACK
	special Special_ViewWallClock
	waitstate
	releaseall
	end

PlayersHouse_2F_GameCube_NEW::
	msgbox PlayersHouse_2F_Text_ItsAGameCube_NEW, MSGBOX_SIGN
	end

PlayersHouse_2F_Notebook_NEW::
	msgbox PlayersHouse_2F_Text_Notebook_NEW, MSGBOX_SIGN
	end

PlayersHouse_2F_PC_NEW::
	lockall
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

PlayersHouse_2F_Text_CantLeaveYet:
    .string "You can't leave yet.\n"
    .string "Check the clock.$"

PlayersHouse_2F_Text_ClockIsStopped_NEW:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

PlayersHouse_2F_Text_ItsAGameCube_NEW:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"

PlayersHouse_2F_Text_Notebook_NEW:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE RULE NO. 1\n"
	.string "Open the MENU with START.\p"
	.string "ADVENTURE RULE NO. 2\n"
	.string "Record your progress with SAVE.\p"
	.string "The remaining pages are blank…$"
