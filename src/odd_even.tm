states 5
init
even
odd
accept +
reject -
alphabet 2 1 #
init _ accept _ R
init 1 odd # R
odd 1 even # R
even 1 odd # R
even _ accept _ R