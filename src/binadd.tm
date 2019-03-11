states 23
init
f0
fc0
r0
rc0
checkAll
goBack
s_is_r
s_is_r_0
s_is_r_1
s_is_rc_0
goBack_s_is_r
s_is_rc_1
f1
fc1
r1
rc1
r0_up
empty
rc0_up
subtract1
success +
reject -
alphabet 5 0 1 # $ *
init 0 f0 $ R
init 1 f1 $ R
init # s_is_r # R
fc1 * fc1 * R
fc1 0 r1 * R
fc1 1 r0_up * R
fc1 # rc1 # R
r0_up 0 r0_up 0 R
r0_up 1 r0_up 1 R
r0_up # rc0_up # R
rc0_up * rc0_up * R
rc0_up 0 subtract1 * R
subtract1 1 goBack 0 L
subtract1 0 subtract1 1 R
rc1 * rc1 * R
rc1 1 goBack * L
r1 0 r1 0 R
r1 1 r1 1 R
r1 # rc1 # R
r1 * r1 * R
f1 0 f1 0 R
f1 1 f1 1 R
f1 # fc1 # R
s_is_r 0 s_is_r_0 $ R
s_is_r 1 s_is_r_1 $ R
s_is_r # empty # R
s_is_r * s_is_r * R
empty 0 empty * R
empty * empty * R
empty _ success * R
s_is_r_0 0 s_is_r_0 0 R
s_is_r_0 1 s_is_r_0 1 R
s_is_r_0 # s_is_rc_0 # R
s_is_rc_0 * s_is_rc_0 * R
s_is_rc_0 0 goBack_s_is_r * L
s_is_rc_0 _ goBack_s_is_r * L
goBack_s_is_r # goBack_s_is_r # L
goBack_s_is_r 0 goBack_s_is_r 0 L
goBack_s_is_r 1 goBack_s_is_r 1 L
goBack_s_is_r * goBack_s_is_r * L
goBack_s_is_r $ s_is_r $ R
s_is_r_1 0 s_is_r_1 0 R
s_is_r_1 1 s_is_r_1 1 R
s_is_r_1 # s_is_rc_1 # R
s_is_rc_1 * s_is_rc_1 * R
s_is_rc_1 1 goBack_s_is_r * L
goBack 0 goBack 0 L
goBack 1 goBack 1 L
goBack # goBack # L
goBack * goBack * L
goBack $ init $ R
checkAll # checkAll # L
checkAll * checkAll * L
checkAll 0 checkAll 0 L
checkAll $ success $ R
rc0 * rc0 * R
rc0 0 goBack * L
rc0 _ checkAll * L
r0 0 r0 0 R
r0 1 r0 1 R
r0 # rc0 # R
r0 * r0 * R
fc0 0 r0 * R
fc0 1 r1 * R
fc0 * fc0 * R
fc0 # rc0 # R
f0 0 f0 0 R
f0 1 f0 1 R
f0 # fc0 # R