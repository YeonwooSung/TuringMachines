states 12
init
goBack
goEnd
end
init_cmp
cmp_X
cmp_X_goEnd
cmp_goBack
cmp_Y
cmp_Y_goEnd
accept +
reject -
alphabet 6 0 1 $ X Y &
init 0 goEnd X R
init 1 goEnd Y R
init X init_cmp X L
init Y init_cmp Y L
init _ accept _ R
init_cmp X cmp_X_goEnd $ R
init_cmp Y cmp_Y_goEnd $ R
init_cmp & accept & R
init_cmp $ accept $ R
cmp_goBack X cmp_goBack X L
cmp_goBack Y cmp_goBack Y L
cmp_goBack & cmp_goBack & L
cmp_goBack $ init_cmp & L
cmp_Y_goEnd X cmp_Y_goEnd X R
cmp_Y_goEnd Y cmp_Y_goEnd Y R
cmp_Y_goEnd & cmp_Y_goEnd $ R
cmp_Y_goEnd $ cmp_Y $ L
cmp_Y Y cmp_goBack $ L
cmp_X_goEnd X cmp_X_goEnd X R
cmp_X_goEnd Y cmp_X_goEnd Y R
cmp_X_goEnd & cmp_X_goEnd & R
cmp_X_goEnd $ cmp_X $ L
cmp_X X cmp_goBack $ L
goBack 0 goBack 0 L
goBack 1 goBack 1 L
goBack X init X R
goBack Y init Y R
goEnd 0 goEnd 0 R
goEnd 1 goEnd 1 R
goEnd _ end $ L
goEnd X end X L
goEnd Y end Y L
end 1 goBack Y L
end 0 goBack X L