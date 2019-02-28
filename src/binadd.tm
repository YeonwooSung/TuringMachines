states 28
sPlaceHash
sFirst
sFirst1
sSecond
sSecond0
sSecond1
sSecond10
sThird
sThird0
sThird1
sThird10
sThird11
sToSecond
sToSecond0
sToSecond1
sToSecond10
sToThird
sToThird0
sToThird1
sToThird10
sToThird11
sGoBack
sGoBack#
sGoBack##
sGoBack1
sGoBack1#
sGoBack1##
sEnd +

alphabet 3 0 1 #
//place hash in the end to recognize when finished
sPlaceHash 0 sPlaceHash 0 R
sPlaceHash 1 sPlaceHash 1 R
sPlaceHash # sPlaceHash # R
sPlaceHash _ sGoBack # L

//go back with 0
sGoBack 0 sGoBack 0 L
sGoBack 1 sGoBack 1 L
sGoBack # sGoBack# # L
sGoBack _ sGoBack _ L

//go back with 0 second section
sGoBack# 0 sGoBack# 0 L
sGoBack# 1 sGoBack# 1 L
sGoBack# # sGoBack## # L
sGoBack# _ sGoBack# _ L

//go back with 0 first section
sGoBack## 0 sGoBack## 0 L
sGoBack## 1 sGoBack## 1 L
sGoBack## _ sFirst _ R

//go back with 1
sGoBack1 0 sGoBack1 0 L
sGoBack1 1 sGoBack1 1 L
sGoBack1 # sGoBack1# # L
sGoBack1 _ sGoBack1 _ L

//go back with 1 second section
sGoBack1# 0 sGoBack1# 0 L
sGoBack1# 1 sGoBack1# 1 L
sGoBack1# # sGoBack1## # L
sGoBack1# _ sGoBack1# _ L

//go back with 1 first section
sGoBack1## 0 sGoBack1## 0 L
sGoBack1## 1 sGoBack1## 1 L
sGoBack1## _ sFirst1 _ R

//start with 0
sFirst _ sToSecond _ R
sFirst 0 sToSecond0 _ R
sFirst 1 sToSecond1 _ R
sFirst # sSecond # R

//start with 1
sFirst1 _ sToSecond _ R
sFirst1 0 sToSecond1 _ R
sFirst1 1 sToSecond10 _ R
sFirst1 # sSecond1 # R

//to second when none in first
sToSecond 0 sToSecond 0 R
sToSecond 1 sToSecond 1 R
sToSecond # sSecond # R

//in second with nothing
sSecond # sThird # R
sSecond _ sSecond _ R
sSecond 0 sToThird0 _ R
sSecond 1 sToThird1 _ R

//to second with 0
sToSecond0 0 sToSecond0 0 R
sToSecond0 1 sToSecond0 1 R
sToSecond0 # sSecond0 # R

//in second with 0
sSecond0 # sThird0 # R
sSecond0 _ sSecond0 _ R
sSecond0 0 sToThird0 _ R
sSecond0 1 sToThird1 _ R

//to second with 1
sToSecond1 0 sToSecond1 0 R
sToSecond1 1 sToSecond1 1 R
sToSecond1 # sSecond1 # R

//in second with 1
sSecond1 # sThird1 # R
sSecond1 _ sSecond1 _ R
sSecond1 0 sToThird1 _ R
sSecond1 1 sToThird10 _ R

//to second with 10
sToSecond10 0 sToSecond10 0 R
sToSecond10 1 sToSecond10 1 R
sToSecond10 # sSecond10 # R

//in second with 10
sSecond10 # sThird10 # R
sSecond10 _ sSecond10 _ R
sSecond10 0 sToThird10 _ R
sSecond10 1 sToThird11 _ R

//to third with nothing
sToThird 0 sToThird 0 R
sToThird 1 sToThird 1 R
sToThird _ sToThird _ R
sToThird # sThird # R

//in third with nothing
sThird _ sThird _ R
sThird # sEnd # S

//to third with 0
sToThird0 0 sToThird0 0 R
sToThird0 1 sToThird0 1 R
sToThird0 _ sToThird0 _ R
sToThird0 # sThird0 # R

//in third with 0
sThird0 _ sThird0 _ R
sThird0 0 sGoBack _ L

//to third with 1
sToThird1 0 sToThird1 0 R
sToThird1 1 sToThird1 1 R
sToThird1 _ sToThird1 _ R
sToThird1 # sThird1 # R

//in third with 1
sThird1 _ sThird1 _ R
sThird1 1 sGoBack _ L

//to third with 10
sToThird10 0 sToThird10 0 R
sToThird10 1 sToThird10 1 R
sToThird10 _ sToThird10 _ R
sToThird10 # sThird10 # R

//in third with 10
sThird10 _ sThird10 _ R
sThird10 0 sGoBack1 _ L

//to third with 11
sToThird11 0 sToThird11 0 R
sToThird11 1 sToThird11 1 R
sToThird11 _ sToThird11 _ R
sToThird11 # sThird11 # R

//in third with 11
sThird11 _ sThird11 _ R
sThird11 1 sGoBack1 _ L