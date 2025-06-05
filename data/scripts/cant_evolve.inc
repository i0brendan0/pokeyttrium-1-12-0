EventScript_ChosenMonCantEvolve::
    special ChoosePartyMon
    waitstate
    goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, EventScript_ChosenMonCantEvolve_Toggle
    msgbox EventScript_ChosenMonCantEvolve_Text_DidntPick, MSGBOX_DEFAULT
    release
    end

EventScript_ChosenMonCantEvolve_Toggle::
    specialvar VAR_RESULT, ScriptGetPartyMonSpecies
    goto_if_eq VAR_RESULT, SPECIES_EGG, EventScript_ChosenMonCantEvolve_CantPickEgg
	special BufferMonNickname
    specialvar VAR_RESULT, SetChosenMonCantEvolve
    goto_if_eq VAR_RESULT, TRUE, EventScript_ChosenMonCantEvolve_MonCantEvolveNow
EventScript_ChosenMonCantEvolve_MonCanEvolveNow::
    msgbox EventScript_ChosenMonCantEvolve_Text_CanEvolveNow, MSGBOX_DEFAULT
    release
    end
    
EventScript_ChosenMonCantEvolve_MonCantEvolveNow::
    msgbox EventScript_ChosenMonCantEvolve_Text_CantEvolveNow, MSGBOX_DEFAULT
    release
    end

EventScript_ChosenMonCantEvolve_CantPickEgg::
    msgbox EventScript_ChosenMonCantEvolve_Text_CantPickEgg, MSGBOX_DEFAULT
    release
    end
    
EventScript_ChosenMonCantEvolve_Text_DidntPick::
    .string "Come back if you change\n"
    .string "your mind.$"

EventScript_ChosenMonCantEvolve_Text_CanEvolveNow::
    .string "Your {STR_VAR_1} can\n"
    .string "evolve normally now.$"

EventScript_ChosenMonCantEvolve_Text_CantEvolveNow::
    .string "Your {STR_VAR_1} can't\n"
    .string "evolve now.$"

EventScript_ChosenMonCantEvolve_Text_CantPickEgg::
    .string "I can't do that to an EGG.$"
