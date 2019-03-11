states 6
check_at_least_1
first_odd
even
odd
accept +
reject -
alphabet 3 1 # $
check_at_least_1 1 first_odd _ R
first_odd # first_odd # R
first_odd 1 even # R
first_odd _ accept _ R
even 1 odd # R
even # even # R
even _ accept _ L
odd 1 even 1 R
odd # odd # R