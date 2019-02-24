#!/bin/bash

prog_name=$0
input_file=$1
output_executable_file=${input_file::-5}
output_object_file="$output_executable_file.o" 
output_assembly_file="$output_executable_file.s"


echo ".data" > $output_assembly_file

#Allocate space for all variables (a-z)
echo "symtab:" >> $output_assembly_file
echo -e "\t.zero 208" >> $output_assembly_file # 26 * 8 = 208



#Add lines that are needed just before the actual code
echo ".text" >> $output_assembly_file
echo ".global main" >> $output_assembly_file
echo "main:" >> $output_assembly_file

#Add the gcd function definition
write_gcd()
{
	output_str="
		gcd:
		push rax 		; save the registers we are modifying and aren't used for
		push rcx		; for a return value
		push rdx
		;;; compare rbx to rcx
		cmp rbx,rcx
		;;; check to see if these are equal
		je finish
		;;; check to see if rbx > rcx
		jg again
		;;; if not, swap rbx and rcx so that rbx > rcx
		xchg rbx,rcx
		again:
			;; shuffle rbx and rcx up to rax and rbx
			mov rax,rbx
			mov rbx,rcx
			;; zero out rdx in preparation for division rdx:rax by rcx
			xor rdx,rdx
			;; divide by rcx, remainder is in rdx
			div rcx
			cmp rdx,0
			je finish
			mov rbx,rcx
			mov rcx,rdx
			jmp again
		finish:
			pop rdx
			pop rcx
			pop rax
			ret"
	output_str+="gcd:\n"
}

#Add the code to the File
cat $input_file | bin/calc3i.exe >> $output_assembly_file

as "$output_assembly_file" -o "$output_object_file"

#Compile .s-File and output it as executable file
gcc $output_object_file -no-pie -o $output_executable_file
