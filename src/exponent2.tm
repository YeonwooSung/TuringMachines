states 9
q0
q1
q2
q3
q4
q5
q6
q7 +
q8 -
alphabet 7 a b c X Y Z $
q0 a q1 X R
q1 a q1 a R
q1 Y q1 Y R
q1 b q2 Y R
q2 b q2 b R
q2 Z q2 Z R
q2 c q3 Z L
q2 _ q4 $ L
q3 a q3 a L
q3 b q3 b L
q3 Y q3 Y L
q3 Z q3 Z L
q3 X q0 X R
q4 b q4 b L
q4 Y q4 Y L
q4 a q4 a L
q4 X q6 X R
q5 a q5 a R
q5 Y q5 Y R
q5 b q4 Y R
q5 _ q7 _ L
q5 $ q7 $ L
q6 a q5 X R