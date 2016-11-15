#!/bin/bash

#colors for print
RED=`tput setaf 1`
NC=`tput sgr0`
YELLOW=`tput setaf 3`
GREEN=`tput setaf 2`

DATE=`date +%Y-%m-%d-%H-%M-%S`

mkdir tests/$DATE
OUTFOLDER=tests/$DATE
REPORT=$OUTFOLDER/report.txt

#  |tee -a  $REPORT  create file with stdout and print stdout to console



echo "	${YELLOW} Start functional testing ${NC}"			|tee -a  $REPORT
./output <tests/test1.txt 	>$OUTFOLDER/out1
./output <tests/test2.txt 	>$OUTFOLDER/out2
./output <tests/test3.txt 	>$OUTFOLDER/out3
./output <tests/test4.txt 	>$OUTFOLDER/out4
./output <tests/test5.txt 	>$OUTFOLDER/out5
./output <tests/test6.txt 	>$OUTFOLDER/out6
./output <tests/test7.txt 	>$OUTFOLDER/out7
./output <tests/test8.txt 	>$OUTFOLDER/out8
./output <tests/test9.txt 	>$OUTFOLDER/out9
./output <tests/test10.txt 	>$OUTFOLDER/out10
./output <tests/test11.txt 	>$OUTFOLDER/out11
./output <tests/test12.txt 	>$OUTFOLDER/out12
./output <tests/test13.txt 	>$OUTFOLDER/out13
./output <tests/test14.txt 	>$OUTFOLDER/out14

ls $OUTFOLDER | grep '^out' | while read line
do
	diff -q $OUTFOLDER/$line tests/answers/$line  >/dev/null
	if [[ $? == "0" ]]
	then
  		echo "Test with file "$line" ${GREEN}pass ${NC}"  			|tee -a  $REPORT
	else
 		echo "Test with file "$line" ${RED} FAILED ${NC}"	|tee -a  $REPORT
		echo diff $OUTFOLDER/$line tests/answers/$line 		|tee -a  $REPORT
        	diff $OUTFOLDER/$line tests/answers/$line  		|tee -a  $REPORT

	fi
done

echo "  ${YELLOW} End functional testing ${NC}"                       	|tee -a  $REPORT

