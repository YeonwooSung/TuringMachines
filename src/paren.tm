states 7
look_for_closing_paran

look_for_open_round
look_for_open_curly

go_to_start
check_complete
accept +

alphabet 5 { ( ) } X

look_for_closing_paran ( look_for_closing_paran ( R
look_for_closing_paran { look_for_closing_paran { R
look_for_closing_paran X look_for_closing_paran X R
look_for_closing_paran _ check_complete _ L

look_for_closing_paran ) look_for_open_round X L
look_for_closing_paran } look_for_open_curly X L

look_for_open_round ( go_to_start X L
look_for_open_round X look_for_open_round X L

look_for_open_curly { go_to_start X L
look_for_open_curly X look_for_open_curly X L


go_to_start ( go_to_start ( L
go_to_start ) go_to_start ) L
go_to_start { go_to_start { L
go_to_start } go_to_start } L
go_to_start X go_to_start X L
go_to_start _ look_for_closing_paran _ R

check_complete X check_complete X L
check_complete _ accept _ S