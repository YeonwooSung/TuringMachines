states 8
init
lookForClosingParen
lookForClosingParen_init
lookForOpenParen
goToStart
checkComplete
accept +
reject -
alphabet 3 ( ) $
init ( lookForClosingParen_init _ R
init _ checkComplete $ R
lookForClosingParen_init ( lookForClosingParen_init ( R
lookForClosingParen_init ) goToStart $ L
lookForClosingParen ( lookForClosingParen ( R
lookForClosingParen $ lookForClosingParen $ R
lookForClosingParen _ checkComplete $ L
lookForClosingParen ) lookForOpenParen $ L
lookForOpenParen ( goToStart $ L
lookForOpenParen $ lookForOpenParen $ L
goToStart ( goToStart ( L
goToStart ) goToStart ) L
goToStart $ goToStart $ L
goToStart _ lookForClosingParen _ R
checkComplete $ checkComplete $ L
checkComplete _ accept _ R