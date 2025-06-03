EventScript_HiddenTree::
    goto_if_unset FLAG_HIDDEN_TREE_EXPLANATION, EventScript_HiddenTree_NotEnabled
    lockall
    msgbox Text_HiddenTreeAskShake, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_HiddenTree_End
    special FindHiddenTreeResult
    goto_if_eq VAR_RESULT, FALSE, EventScript_HiddenTree_Empty
    goto_if_ne VAR_0x8001, 0, EventScript_HiddenTree_GotItem @@ will be able to hold multiple quantities
    special FindHiddenTreePokemon
    setwildbattle VAR_0x8000, 1 @@ VAR_0x8001
    waitstate
    setflag FLAG_FORCE_HIDDEN_ABILITY @@ x_MODIFY_x will overwrite if the flag was set beforehand
    dowildbattle
    clearflag FLAG_FORCE_HIDDEN_ABILITY
EventScript_HiddenTree_Empty:
    msgbox Text_HiddenTreeEmpty, MSGBOX_DEFAULT
EventScript_HiddenTree_End:
    releaseall
EventScript_HiddenTree_NotEnabled:
    end
    
EventScript_HiddenTree_GotItem:
    callstd STD_FIND_ITEM
    releaseall
    end

Text_HiddenTreeAskShake:
    .string "This tree looks lively.\n"
    .string "Do you want to shake it?$"

Text_HiddenTreeEmpty:
    .string "There's nothing here.$"
