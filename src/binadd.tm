states 13
subtract_from_first
subtract_from_second
go_to_beginning
go_left_3
go_left_4
go_to_last_0
go_to_last_1
go_to_last_2
subtract_from_last_0
subtract_from_last_1
check_result_zero
success +
reject -
alphabet 3 0 1 #
subtract_from_first 1 go_to_last_0 0 R
subtract_from_first 0 subtract_from_first 1 R
subtract_from_first # subtract_from_second # R
subtract_from_second 1 go_to_last_2 0 R
subtract_from_second 0 subtract_from_second 1 R
subtract_from_second # check_result_zero # R
go_to_last_0 0 go_to_last_0 0 R
go_to_last_0 1 go_to_last_0 1 R
go_to_last_0 # go_to_last_1 # R
go_to_last_1 0 go_to_last_1 0 R
go_to_last_1 1 go_to_last_1 1 R
go_to_last_1 # subtract_from_last_0 # R
go_to_last_2 0 go_to_last_2 0 R
go_to_last_2 1 go_to_last_2 1 R
go_to_last_2 # subtract_from_last_1 # R
subtract_from_last_0 1 go_to_beginning 0 L
subtract_from_last_0 0 subtract_from_last_0 1 R
subtract_from_last_1 1 go_left_3 0 L
subtract_from_last_1 0 subtract_from_last_1 1 R
go_to_beginning 0 go_to_beginning 0 L
go_to_beginning 1 go_to_beginning 1 L
go_to_beginning # go_to_beginning # L
go_to_beginning _ subtract_from_first _ R
go_left_3 0 go_left_3 0 L
go_left_3 1 go_left_3 1 L
go_left_3 # go_left_4 # L
go_left_4 0 go_left_4 0 L
go_left_4 1 go_left_4 1 L
go_left_4 # subtract_from_second # R
check_result_zero 0 check_result_zero 0 R
check_result_zero _ success _ R