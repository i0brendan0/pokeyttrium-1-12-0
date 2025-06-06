OneTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PlayersHouse_1F_OnWarp
    map_script MAP_SCRIPT_ON_FRAME_TABLE, PlayersHouse_1F_OnFrame
	.byte 0

PlayersHouse_1F_OnWarp:
    map_script_2 VAR_ONE_TOWN_TOWN_STATE, 0, PlayersHouse_1F_FaceUp
	.2byte 0

PlayersHouse_1F_FaceUp:
    turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
    end

PlayersHouse_1F_OnFrame:
    map_script_2 VAR_ONE_TOWN_TOWN_STATE, 0, PlayersHouse_1F_TVScene
    map_script_2 VAR_ONE_TOWN_TOWN_STATE, 3, PlayersHouse_1F_ToTwoCity
	.2byte 0

PlayersHouse_1F_TVScene:
    lockall
    msgbox PlayersHouse_1F_Text_TVMessage, MSGBOX_DEFAULT
    setvar VAR_ONE_TOWN_TOWN_STATE, 1
	setrespawn HEAL_LOCATION_ONE_TOWN_PLAYERS_HOUSE_2F
    releaseall
    end

PlayersHouse_1F_CantLeaveYet::
    lockall
    msgbox PlayersHouse_1F_Text_CantLeaveYet, MSGBOX_DEFAULT
    applymovement LOCALID_PLAYER, Common_Movement_WalkUp
    waitmovement
    releaseall
    end

PlayersHouse_1F_ToTwoCity::
    lockall
    msgbox PlayersHouse_1F_Text_ToTwoCity, MSGBOX_DEFAULT
    setvar VAR_ONE_TOWN_TOWN_STATE, 4
    releaseall
    end

PlayersHouse_1F_Text_TVMessage:
    .string "This will say a TV program.\p"
    .string "It will mention the POKéMON LEAGUE.\p"
    .string "It will say to go to TWO CITY.$"

PlayersHouse_1F_Text_CantLeaveYet:
    .string "You can't leave yet. Go upstairs.$"

PlayersHouse_1F_Text_ToTwoCity:
    .string "Go to Two City.$"
