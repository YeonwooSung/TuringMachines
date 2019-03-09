state ?

init
goBack
goEnd_X
goEnd_Y
end_X
end_Y
init_cmp
cmp_X
cmp_X_goEnd
cmp_goBack
cmp_Y
cmp_Y_goEnd
accept +
reject -

alphabet 3 0 1 $

init 0 goEnd_X X R
init 1 goEnd_Y Y R
init X init_cmp X L
init Y init_cmp Y L

init_cmp X cmp_X_goEnd $ R
init_cmp Y cmp_Y_goEnd $ R
init_cmp $ accept $ R

cmp_goBack X cmp_goBack X L
cmp_goBack Y cmp_goBack Y L
cmp_goBack $ init_cmp $ L

cmp_Y_goEnd X cmp_Y_goEnd X R
cmp_Y_goEnd Y cmp_Y_goEnd Y R
cmp_Y_goEnd $ cmp_Y $ L

cmp_Y Y cmp_goBack $ L

cmp_X_goEnd X cmp_X_goEnd X R
cmp_X_goEnd Y cmp_X_goEnd Y R
cmp_X_goEnd $ cmp_X $ L

cmp_X X cmp_goBack $ L

goBack 0 goBack 0 L
goBack 1 goBack 1 L
goBack X init X R
goBack Y init Y R
goEnd_Y 0 goEnd_Y 0 R
goEnd_Y 1 goEnd_Y 1 R
goEnd_Y _ end_Y $ L
goEnd_Y X end_Y X L
goEnd_Y Y end_Y Y L
end_Y 1 goBack Y L
goEnd_X 0 goEnd_X 0 R
goEnd_X 1 goEnd_X 1 R
goEnd_X _ end_X $ L
goEnd_X X end_X X L
goEnd_X Y end_X Y L
end_X 0 goBack X L