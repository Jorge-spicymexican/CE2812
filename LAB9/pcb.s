.section .data
//https://stackoverflow.com/questions/22396214/understanding-this-part-arm-assembly-code

//.word directive is used to allocate and initialize space for a variable
// group of data should be crecided by this command
.global task //directive is NASM specific
//used for exporting symbols in your code to where it points
// in the object code generated. This will be added to the o
// to the oject code

//writting the function name tasks
task:
	//first word in SP for task 0
	// second sp for task 1,
	// third is which task is running
	.word 0,0,0


.syntax unified //signals the use of unified ARM/thumb assembly syntax
.thumb
//store the assemly code to the text sections
//text sections is used for keeping the actual code.
//this section must always start for the declatation global_start
// this tells the kernal where the program execution begins
.section .text

//create a global variable named sysTick handler
.global SysTick_Handler
.thumb_func //stats thumb mode function for ARM MCU
SysTick_Handler:
	//creating a function named Systock hadnler
	//already stacked -PSR, PC, LW, R12, R3, R1, R0
//https://www.quora.com/
//What-is-the-difference-between-LDR-and-STR-Assembly-Language-instruction-of-ARM

	//LDR (Load Register): -move data into processor from memory. Loads a data
	//value to a specific register. Takes 2 arguements, one specifying the
	//register, other the location/address of the data value

	//Eg. LDR R1,[R2,#400] → load data value at (R2+4*400) location to R1.
	//(multiplies by 4 assuming the memory is word-addressable)

	//STR(Store Register):- moves data out of the processor to memory locations
	//from a specified register. Takes 2 arguments, 1. register which value is
	//to be stored, 2. the memory location where value will be stored


	//push -  means writing it to the stack
	//pop - restoring whatever is on top of the stack into a register.

	//stacked the rest of the registers
	push {r4-r11,lr}

	//swap SP
	ldr r0, =task
	ldr r1,[r0, #8] // check which task is running
	subs r1, r1, #1
	beq 1f // If equal, 2nd task running

	// short branch if equals too
	// was task 0
	// store current SP to dseg
	str SP, [r0,#0] // the firs of r0 into the SP register
	// get other tasks SP
	ldr SP, [r0,#4] //load
	//set flag to task 1
	mov r1,#1
	str r1,[r0,#8]
	//done
	b finish

1: //was task 1
   //store current SP to desged
   str SP, [r0,#4]
   // get other task SP
   ldr SP, [r0,#0]
   // set flag to task 0
   mov r1,#0
   str r1,[r0,#8]
   //done
   b finish

finish:
	//from "new" stack
	pop {r4-r11, lr}

	//return from interrupt
	bx lr

