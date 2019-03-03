states 7
init
lookForClosingParen
lookForOpenParen
goToStart
checkComplete
accept +
reject -
alphabet 3 ( ) $
init ( lookForClosingParen ( R
init _ checkComplete $ R
lookForClosingParen ( lookForClosingParen ( R
lookForClosingParen $ lookForClosingParen $ R
lookForClosingParen _ checkComplete _ L
lookForClosingParen ) lookForOpenParen $ L
lookForOpenParen ( goToStart $ L
lookForOpenParen $ lookForOpenParen $ L
goToStart ( goToStart ( L
goToStart ) goToStart ) L
goToStart $ goToStart $ L
goToStart _ lookForClosingParen _ R
checkComplete $ checkComplete $ L
checkComplete _ accept _ R
