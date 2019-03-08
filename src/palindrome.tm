states 10
start
going_to_end_a
going_to_end_b
going_to_end_c
end_a
end_b
end_c
going_to_start
accept +
reject -
alphabet 4 a b c $
start a going_to_end_a $ R
start b going_to_end_b $ R
start c going_to_end_c $ R
start $ start $ R
start _ accept _ R
going_to_end_a a going_to_end_a a R
going_to_end_a b going_to_end_a b R
going_to_end_a c going_to_end_a c R
going_to_end_a _ end_a $ L
going_to_end_a $ end_a $ L
going_to_end_b a going_to_end_b a R
going_to_end_b b going_to_end_b b R
going_to_end_b c going_to_end_b c R
going_to_end_b _ end_b $ L
going_to_end_b $ end_b $ L
going_to_end_c a going_to_end_c a R
going_to_end_c b going_to_end_c b R
going_to_end_c c going_to_end_c c R
going_to_end_c _ end_c $ L
going_to_end_c $ end_c $ L
end_a a going_to_start $ L
end_b b going_to_start $ L
end_c c going_to_start $ L
end_a $ accept $ R
end_b $ accept $ R
end_c $ accept $ R
going_to_start a going_to_start a L
going_to_start b going_to_start b L
going_to_start c going_to_start c L
going_to_start $ start $ L