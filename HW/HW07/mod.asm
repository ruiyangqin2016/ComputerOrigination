;;===============================
;; CS 2110 Summer 2018
;; Homework 7 - Recursion
;; Name: Ruiyang Qin
;;===============================

;;===============================
;;--Function to calculate x % y--
;; mod(x, y):
;;	if x < y:
;;	   return x
;;	else:
;;	   return mod(x - y, y)
;;===============================

;;===============================
;;--Function to calculate x % y--
;; mod(x, y):
;;	ans
;;	if x < y:
;;	   ans = x
;;	else:
;;	   ans = mod(x - y, y)
;;	return ans
;;===============================


.orig x3000
	LD	R6, STACK

	LD	R0, A
	LD	R1, B

    ; TODO: Setup your first mod call here

	ADD	R6, R6, -1
	STR	R0, R6, 0

	JSR	mod

    ; TODO: Don't forget to store your return value in answer!

	LDR	R0, R6, 0
	ADD	R6, R6, 2 
	HALT


A       .fill 20
B       .fill 16
ANSWER  .blkw 1
STACK   .fill xF000

;;============================================
;;	R1		<- R6
;;	R0		    ^
;;0	ans		<- R6  <- R5
;;1	old frame pointer
;;2	return address
;;3	return value
;;----------------------
;;4	arg1 (A)	
;;5	arg2 (B)
;;============================================


mod	ADD	R6, R6, -4	;; allocate space
	STR	R7, R6, 2	;; save return address
	STR	R5, R6, 1	;; save old FP
	ADD	R5, R6, 0	;; copy SP to FP
	ADD	R6, R6, -2	;; room for 2 registers
	STR	R0, R5, -1	;; save R0, A
	STR	R1, R5, -2	;; save R1, B


	LDR	R1, R5, 4	;; R1 -> A
	LDR	R0, R5, 5	;; R0 -> B
	NOT	R0, R0
	ADD	R0, R0, 1
	ADD	R0, R1, R0	;; A - B

	BRN	ANSISA		;; A < B
;; else (A >= B)
	LDR	R1, R5, 4	;; R1 -> A
	LDR	R0, R5, 5	;; R0 -> B
	NOT	R0, R0
	ADD	R0, R0, 1
	ADD	R1, R1, R0	;; R1 -> A - B
	LDR	R0, R5, 5	;; R0 -> B
	ADD	R6, R6, -2	;; room for arg1 and arg2
	STR	R1, R6, 0	;; arg1 -> A - B
	STR	R0, R6, 1	;; arg2 -> B
	JSR	mod

	LDR	R1, R6, 0	;; R1 -> mod(A - B, B)
	STR	R1, R5, 0
	LDR	R1, R5, 0
	STR	R1, R5, 3	;; mod(A - B, B) stored into rv
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET
;;============================================
;;	R1		<- R6
;;	R0		    
;;0	ans	        <- R5
;;1	old frame pointer
;;2	return address
;;3	return value
;;----------------------
;;4	arg1 (A)	
;;5	arg2 (B)
;;============================================
ANSISA	LDR	R1, R5, 4	;; R1 -> A
	STR	R1, R5, 0	;; ans = A
	LDR	R1, R5, 0	;; R1 -> A
	STR	R1, R5, 3	;; Sstore into rv
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET
	
	



;;mod	ADD	R6, R6, -4	;; allocate space
;;	STR	R7, R6, 2	;; save return address
;;	STR	R5, R6, 1	;; save old FP
;;	ADD	R5, R6, 0	;; copy SP to FP
;;	ADD	R6, R6, -3	;; room for 3 registers
;;	STR	R0, R5, -1	;; save R0, A
;;	STR	R1, R5, -2	;; save R1, B
;;	STR	R2, R5, -3
;;========================================================
	;; if (A < B) 

;;	LDR	R0, R5, 4	;; R0 -> A
;;	LDR	R1, R5, 5	;; R1 -> B
;;	NOT	R2, R1
;;	ADD	R2, R2, 1	;; R2 -> (-B)
;;	ADD	R2, R0, R2	;; R2 -> A = A - B
;;	
;;	BRN	DONE		;; A < B
;;
;; else
;;
;;	STR	R2, R5, -1	;; save (A - B) to R0
;;
;;	STR	R1, R5, -2	;; save B to R1
;;	STR	R2, R5, -3
;;
;;	BR	ENDIF
;;========================================================
;;ENDIF	LDR	R0, R5, 4	;; A
;;	LDR	R1, R5, 5	;; B
;;	NOT	R2, R1
;;	ADD	R2, R2, 1
;;	ADD	R2, R0, R1	;; A = A - B
;;	STR	R2, R5, -1
;;
;;	STR	R1, R5, -2	;; save R1, B
;;
;;	JSR	mod
;;
;;	LDR	R0, R6, 0
;;	ADD	R6, R6, 2
;;
;;DONE	STR	R0, R5, 3
;;	LDR	R0, R5, -1	;; restore R0
;;	LDR	R1, R5, -2	;; restore R1
;;	LDR	R2, R5, -3
;;	ADD	R6, R5, 0	;; restore SP
;;	LDR	R5, R6, 1	;; restore FP
;;	LDR	R7, R6, 2	;; restore RA
;;	ADD	R6, R6, 3	;; pop ra, fp, lvl
;;	RET 
;;
    ; TODO: Implement mod here!

.end
