Std_RegisteredInMatchCall::
	buffertrainerclassname STR_VAR_1, VAR_0x8000
	buffertrainername STR_VAR_2, VAR_0x8000
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox gText_RegisteredTrainerinPokeNav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

EventScript_TryGetTrainerScript::
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, TRUE, EventScript_GotoTrainerScript
	releaseall
	end

EventScript_GotoTrainerScript::
	gotobeatenscript
	releaseall
	end

EventScript_ObjectApproachPlayer::
	lock
	special DoTrainerApproach
	waitstate
	gotonative LoadTrainerObjectScript

EventScript_TrainerRematchGiveItem::
    randompercentage VAR_0x8009
    goto_if_eq VAR_RESULT, FALSE, EventScript_TrainerRematchDontGiveItem
    msgbox EventScript_Text_TrainerRematchGiveItem, MSGBOX_DEFAULT
    giveitem VAR_0x8008, VAR_0x800A
EventScript_TrainerRematchDontGiveItem::
    return
