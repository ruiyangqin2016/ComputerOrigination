;;===============================
;; CS 2110 Summer 2018
;; Homework 7 - Recursion
;; Name:
;;===============================


;;================================================
;;	fib(n):
;;	   ans1
;;	   ans2
;;	   if n <= 1:
;;		ans1 = n
;;		ans2 = 0
;;	   else:
;;		ans1 = fib(n - 2)
;;		ans2 = fib(n - 1)
;;	   return ans1 + ans2
;;================================================
.orig x3000
    LD  R6, STACK
	LD	R0, n
	ADD	R6, R6, -1
	STR	R0, R6, 0
    ; TODO: Setup your first call here

    JSR fib

	LDR	R0, R6, 0
	ADD	R6, R6, 2

    ; TODO: Don't forget to store your return value in answer!

    HALT


n .fill 5
ANSWER  .blkw 1
STACK   .fill xF000
		

fib
; TODO: Implement fib here
;;=======================================================
;;	 R1					<- R6 (Point 3)
;;	 R0					
;;0	 answer1			<- R5 (Point 2)| R6 (Point 2)
;;1	 answer0
;;2	 old f 				<- R5 (Point 1)
;;3	 return address		<- R7
;;4	 return value
;;-------------------------------------------------------
;;5	 leftmost arg(n)	<- R6 (Point 1)
;;=======================================================
	ADD	R6, R6, -5	;; Allocate space for rv, va, old fp, ans1, ans2
	STR	R7, R6, 3	;; Save ra
	STR	R5, R6, 2	;; Save old fp
	ADD	R5, R6, 0	;; Save save pointer to frame pointer
	ADD	R6, R6, -2	;; Room for 2 regs
	STR	R0, R5, -1
	STR	R1, R5, -2

;; if n <= 1
	LDR	R0, R5, 5	;; R0 gain arg1 which is n
	ADD	R0, R0, -1	;; R0 = n - 1
	BRP	ELSE		;; n > 1, go else
	
;; 	ans1 = n
;;	ans2 = 0
	LDR	R0, R5, 5
	STR	R0, R5, 1	;; ans1 = n
	AND	R0, R0, 0
	STR	R0, R5, 0	;; ans2 = 0
	
	BR	ENDIF
	
ENDIF	NOP
	LDR	R0, R5, 1	;; R0 -> ans1
	LDR	R1, R5, 0	;; R1 -> ans2
	ADD	R0, R0, R1	;; R0 = R0 + R1
	STR	R0, R5, 4	;; put ans1 + ans2 in rv 
	LDR	R0, R5, -1	;; restore R0
	LDR	R1, R5, -2	;; restore R1
	ADD	R6, R5, 0	;; RESTORE sp
	LDR	R5, R6, 2	;; restore FP
	LDR	R7, R6, 3	;; restore ra
	ADD	R6, R6, 4	;; pop
	RET

ELSE	LDR	R0, R5, 5	;; gain n
	ADD	R0, R0, -1
	ADD	R6, R6, -1
	STR	R0, R6, 0
	JSR	fib		;; fib(n - 1)
	LDR	R0, R6, 0	;; R0 = rv
	ADD	R6, R6, 2	;; pop rv and arg1
	
	ADD	R6, R6, -1
	STR	R0, R6, 0	;; push fib(n - 1)
	ADD	R6, R6, -1
	LDR	R0, R5, 5	;; R0 -> n
	ADD	R0, R0, -2	;; n = n - 2
	ADD	R6, R6, -1
	STR	R0, R6, 0
	JSR	fib		;; fib(n - 2)

	LDR	R0, R6, 0	;; R0 = rv
	ADD	R6, R6, 2	;; pop rv and arg1
	
	ADD	R6, R6, -1
	STR	R0, R6, 0	;; push fib(n - 2)

	LDR	R0, R6, 0	
	STR	R0, R5, 0	;; ans2 = fib(n - 2)
	LDR	R1, R6, 1
	STR	R1, R5, 1	;; ans1 = fib(n - 1)
	ADD	R0, R0, R1	;; ans1 + ans2
	STR	R0, R5, 4	;; put ans1 + ans2 in rv
	
	LDR	R0, R5, -1	;; restore R0
	LDR	R1, R5, -2	;; restore R1
	ADD	R6, R5, 0	;; RESTORE sp
	LDR	R5, R6, 2	;; restore FP
	LDR	R7, R6, 3	;; restore ra
	ADD	R6, R6, 4	;; pop
	RET

.end
