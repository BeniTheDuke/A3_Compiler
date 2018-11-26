#!/bin/bash

prog_name=$0
input_file=$1
output_file=${input_file::-5}
s_output_file="$output_file.s"


echo ".data" > $s_output_file

#Allocate space for all variables (a-z)
for x in {a..z}
do
	        echo ".global $x" >> $s_output_file
	done

	#Add lines that are needed just before the actual code
	echo ".text" >> $s_output_file
	echo ".global main" >> $s_output_file
	echo "main:" >> $s_output_file

	#Add the code to the File
	#cat $input_file | ./calc3i.exe >> $s_output_file


	#Compile .s-File and output it as executable file
	#gcc $s_output_file -no-pie >> $output_file
