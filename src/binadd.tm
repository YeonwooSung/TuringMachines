states 30
init
placeHash
first
first1
second
second0
second1
second10
third
third0
third1
third10
third11
toSecond
toSecond0
toSecond1
toSecond10
toThird
toThird0
toThird1
toThird10
toThird11
goBack
goBack#
goBack##
goBack1
goBack1#
goBack1##
end +
reject -
alphabet 3 0 1 #
init 0 placeHash 0 R
init 1 placeHash 1 R
placeHash 0 placeHash 0 R
placeHash 1 placeHash 1 R
placeHash # placeHash # R
placeHash _ goBack # L
goBack 0 goBack 0 L
goBack 1 goBack 1 L
goBack # goBack# # L
goBack _ goBack _ L
goBack# 0 goBack# 0 L
goBack# 1 goBack# 1 L
goBack# # goBack## # L
goBack# _ goBack# _ L
goBack## 0 goBack## 0 L
goBack## 1 goBack## 1 L
goBack## _ first _ R
goBack1 0 goBack1 0 L
goBack1 1 goBack1 1 L
goBack1 # goBack1# # L
goBack1 _ goBack1 _ L
goBack1# 0 goBack1# 0 L
goBack1# 1 goBack1# 1 L
goBack1# # goBack1## # L
goBack1# _ goBack1# _ L
goBack1## 0 goBack1## 0 L
goBack1## 1 goBack1## 1 L
goBack1## _ first1 _ R
first _ toSecond _ R
first 0 toSecond0 _ R
first 1 toSecond1 _ R
first # second # R
first1 _ toSecond _ R
first1 0 toSecond1 _ R
first1 1 toSecond10 _ R
first1 # second1 # R
toSecond 0 toSecond 0 R
toSecond 1 toSecond 1 R
toSecond # second # R
second # third # R
second _ second _ R
second 0 toThird0 _ R
second 1 toThird1 _ R
toSecond0 0 toSecond0 0 R
toSecond0 1 toSecond0 1 R
toSecond0 # second0 # R
second0 # third0 # R
second0 _ second0 _ R
second0 0 toThird0 _ R
second0 1 toThird1 _ R
toSecond1 0 toSecond1 0 R
toSecond1 1 toSecond1 1 R
toSecond1 # second1 # R
second1 # third1 # R
second1 _ second1 _ R
second1 0 toThird1 _ R
second1 1 toThird10 _ R
toSecond10 0 toSecond10 0 R
toSecond10 1 toSecond10 1 R
toSecond10 # second10 # R
second10 # third10 # R
second10 _ second10 _ R
second10 0 toThird10 _ R
second10 1 toThird11 _ R
toThird 0 toThird 0 R
toThird 1 toThird 1 R
toThird _ toThird _ R
toThird # third # R
third _ third _ R
third # end # R
toThird0 0 toThird0 0 R
toThird0 1 toThird0 1 R
toThird0 _ toThird0 _ R
toThird0 # third0 # R
third0 _ third0 _ R
third0 0 goBack _ L
toThird1 0 toThird1 0 R
toThird1 1 toThird1 1 R
toThird1 _ toThird1 _ R
toThird1 # third1 # R
third1 _ third1 _ R
third1 1 goBack _ L
toThird10 0 toThird10 0 R
toThird10 1 toThird10 1 R
toThird10 _ toThird10 _ R
toThird10 # third10 # R
third10 _ third10 _ R
third10 0 goBack1 _ L
toThird11 0 toThird11 0 R
toThird11 1 toThird11 1 R
toThird11 _ toThird11 _ R
toThird11 # third11 # R
third11 _ third11 _ R
third11 1 goBack1 _ L
