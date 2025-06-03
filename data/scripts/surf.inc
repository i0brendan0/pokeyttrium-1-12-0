EventScript_UseSurf::
	goto_if_unset I_HM_SURFBOARD_FLAG, EventScript_EndUseSurf
	checkitem ITEM_SURFBOARD, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndUseSurf
	lockall
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end
