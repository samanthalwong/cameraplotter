#!/bin/bash

#echo "==================================="
echo "==================================="
echo "========= CAMERA PLOTTER =========="
echo "==================================="
#echo "=== BY SAMANTHA WONG ===="
#echo "============ (C) 2022 ============="
#echo "==================================="
#echo "==================================="

echo " "
echo " "


echo " "
echo "Please enter the path to your .cvbf file"
read filepath

echo "Would you like to plot all events? (yes/no)"
read all_ev

if [ $all_ev = "no" ]
then 
	echo "Please enter the event(s) you would like to display in the format [event] or [event1,event2,...]"
	read events
	echo "Plotting Events: $events"
	#g++ getCharges.cpp -o getCharges `vbfConfig --libs --ldflags`
	./getCharges $filepath $events
else
	#g++ getCharges.cpp -o getCharges `vbfConfig --libs --ldflags`
	./getCharges $filepath "all"
fi

python3 plotcharges.py

echo "Camera plotter wishes you a nice day :)"
