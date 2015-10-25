#!/bin/sh
if [ ! -d "out/" ]; then 
	mkdir out
fi
make clean
make 
echo "Running scalability tests..."

echo "First exercise"
##################################################
#######  BLACK AND WHITE  TESTS ##################
##################################################
# black and white with scale 2
echo "**********BW Scale 2***********"
echo "1 Thread"
./homework 'in/highresolution_bw.pgm' 'out/highresolution2.pgm' 2 1
echo "2 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution2.pgm' 2 2
echo "4 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution2.pgm' 2 4
echo "8 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution2.pgm' 2 8
# black and white with scale 8
echo "**********BW Scale 8***********"
echo "1 Thread"
./homework 'in/highresolution_bw.pgm' 'out/highresolution8.pgm' 8 1
echo "2 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution8.pgm' 8 2
echo "4 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution8.pgm' 8 4
echo "8 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution8.pgm' 8 8
# black and white with scale 3
echo "**********BW Scale 3***********"
echo "1 Thread"
./homework 'in/highresolution_bw.pgm' 'out/highresolution3.pgm' 3 1
echo "2 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution3.pgm' 3 2
echo "4 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution3.pgm' 3 4
echo "8 Threads"
./homework 'in/highresolution_bw.pgm' 'out/highresolution3.pgm' 3 8


##################################################
##########         COLOR TESTS  ##################
##################################################
# color with scale 2
echo "**********Color Scale 2***********"
echo "1 Thread"
./homework 'in/highresolution_color.pnm' 'out/highresolution2.pnm' 2 1
echo "2 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution2.pnm' 2 2
echo "4 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution2.pnm' 2 4
echo "8 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution2.pnm' 2 8
# color with scale 8
echo "********Color Scale 8********"
echo "1 Thread"
./homework 'in/highresolution_color.pnm' 'out/highresolution8.pnm' 8 1
echo "2 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution8.pnm' 8 2
echo "4 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution8.pnm' 8 4
echo "8 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution8.pnm' 8 8
# color with scale 3
echo "*************Color Scale 3*********"
echo "1 Thread"
./homework 'in/highresolution_color.pnm' 'out/highresolution3.pnm' 3 1
echo "2 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution3.pnm' 3 2
echo "4 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution3.pnm' 3 4
echo "8 Threads"
./homework 'in/highresolution_color.pnm' 'out/highresolution3.pnm' 3 8

echo "\n\n\nSecond exercise"
##########################################
########### resolution 8000 ##############
##########################################
echo "*************Resolution 8000*********"
echo "1 Thread"
./homework1 'out/render.pgm' 8000 1
echo "2 Threads"
./homework1 'out/render.pgm' 8000 2
echo "4 Threads"
./homework1 'out/render.pgm' 8000 4
echo "8 Threads"
./homework1 'out/render.pgm' 8000 8
##########################################
########### resolution 10000 #############
##########################################
echo "*************Resolution 10000*********"
echo "1 Thread"
./homework1 'out/render.pgm' 10000 1
echo "2 Threads"
./homework1 'out/render.pgm' 10000 2
echo "4 Threads"
./homework1 'out/render.pgm' 10000 4
echo "8 Threads"
./homework1 'out/render.pgm' 10000 8

echo "\n\n!!!DONE!!!!";
make clean