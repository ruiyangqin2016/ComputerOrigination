;;===============================
;; CS 2110 Summer 2018
;; Homework 7 - Recursion
;; Name:Ruiyang Qin
;;===============================

;;=========================================
;;findmax(array, n):
;;   if n == 1:
;;      return array[0]
;;   else:
;;      currentMax = findmax(array, n-1)
;;      return max(currentMax, array[n-1])
;;=========================================

;;=========================================
;;findmax(array, n):
;;   ans0
;;   ans1
;;   if n == 1:
;;	ans0 = array[0]
;;      ans1 = 0
;;   else:
;;	ans0 = array[n - 1]
;;	ans1 = findmax(array, n-1)
;;
;;   	ans0 = max(ans1, ans2)
;;      ans1 = 0
;;
;;   return answer + currentMax
;;=========================================

.orig x3000
	LD	R6, STACK

	; TODO: Setup your first call here
	ADD	R6, R6, -1
	STR	R0, R6, 0

	JSR	findmax

	; TODO: Don't forget to store your return value in answer!
	LDR	R0, R6, 0
	ADD	R6, R6, 2 
	HALT


ARRAY .fill x5000
LENGTH .fill 3
ANSWER  .blkw 1
STACK   .fill xF000



	; TODO: Implement findmax here!

;;============================================
;;===============damn stack===================
;;============================================
;;	R1
;;	R0
;;0	ans1
;;1	ans0
;;2	old frame pointer
;;3	return address
;;4	return value
;;----------------------
;;5	arg1 (array)	<- R6 (starting point)
;;6	arg2 (n)
;;============================================

findmax	ADD	R6, R6, -5	;; R6 -> ans1
	STR	R7, R6, 3	;; save return address
	STR	R5, R6, 2	;; save old fp
	ADD	R5, R6, 0	;; R5 -> ans1
	ADD	R6, R6, -2	;; R6 -> R1
	STR	R0, R5, -1
	STR	R1, R5, -2
;;============================================
;;	R1		<- R6
;;	R0
;;0	ans1		<- R5
;;1	ans0
;;2	old frame pointer
;;3	return address
;;4	return value
;;----------------------
;;5	arg1 (array)	
;;6	arg2 (n)
;;============================================


;; if n = 1
	LDR	R0, R5, 6	;; R0 gain arg2 which is n
	ADD	R0, R0, -1	;; R0 = n - 1
	BRP	ELSE		;; n > 0, go else

;;ans0 = array[0]
;;ans1 = 0
	LDR	R1, R5, 5	;; R1 = address of array
	LDR	R1, R1, 0	;; R1 = array[0]
	LDR	R0, R5, 6	;; R0 = n
	AND	R0, R0, 0	;; R0 = 0
	STR	R1, R5, 0	;; ans1 = array[0]
	STR	R0, R5, 1	;; ans0 = 0
	BR	ENDIF

ENDIF NOP
	LDR	R1, R5, 0	;; R1 -> ans1
	LDR	R0, R5, 1	;; R0 -> ans0
	ADD	R0, R0, R1	;; R0 -> ans1 + ans0
	STR	R0, R5, 4	;; return ans1 + ans0
	LDR	R0, R5, -1	;; restore R0
	LDR	R1, R5, -2	;; restore R1
	ADD	R6, R5, 0	;; restore sp
	LDR	R5, R6, 2	;; restore fp
	LDR	R7, R6, 3	;; restore ra
	ADD	R6, R6, 4	;; R6 -> RV
	RET

;;========================================
;;   else:
;;	ans0 = array[n - 1]
;;	ans1 = findmax(array, n-1)
;;
;;   	ans0 = max(ans1, ans2)
;;      ans1 = 0
;;
;;   return answer + currentMax
;;=========================================

;;============================================
;;	R1		<- R6
;;	R0
;;0	ans1		<- R5
;;1	ans0
;;2	old frame pointer
;;3	return address
;;4	return value
;;----------------------
;;5	arg1 (array)	
;;6	arg2 (n)
;;============================================

ELSE	
	LDR	R1, R5, 5	;; R1 -> array
	LDR	R0, R5, 6	;; R0 -> n
	ADD	R0, R0, -1	;; R0 -> n - 1
	ADD	R1, R1, R0
	LDR	R1, R1, 0	;; R1 -> array[n - 1]
	STR	R1, R5, 1	;; ans0 = array[n - 1]
	ADD	R6, R6,-2	;; room for arg1 and arg2
	LDR	R1, R5, 5	;; R1 -> array
	STR	R1, R6, 0	;; arg1 -> array
	STR	R0, R6, 1	;; arg2 -> n - 1
	JSR	findmax		;; findmax(array, n - 1)
;;============================================
;;	findmax(array, n - 1)	<- R6
;;	array		
;;	(n - 1)
;;___________________________
;;	R1		
;;	R0
;;0	ans1		<- R5
;;1	ans0
;;2	old frame pointer
;;3	return address
;;4	return value
;;---------------------------
;;5	arg1 (array)	
;;6	arg2 (n)
;;============================================
	LDR	R0, R6, 0	;; R0 -> findmax(array, n - 1)
	STR	R0, R5, 0	;; ans1 = findmax(array, n - 1)

	;;===================================================
	;;===================================================
	;; compare ans0 = array[n - 1] and ans1 = findmax(array, n - 1)
	LDR	R0, R5, 0	;; R0 -> ans0 = findmax(array, n - 1)
	LDR	R1, R5, 1	;; R1 -> ans1 = array[n - 1]
	NOT	R2, R0
	ADD	R2, R2, 1
	ADD	R2, R2, R1	;; findmax(array, n - 1) - array[n - 1]
	
	BRP	P		;; findmax(array, n - 1) > array[n - 1]
;;========================================
;;   else:
;;	ans0 = array[n - 1]
;;	ans1 = findmax(array, n-1)
;;
;;   	ans0 = max(ans1, ans2)
;;      ans1 = 0
;;
;;   return answer + currentMax
;;=========================================
;; array[n - 1] < findmax(array, n - 1)
	STR	R0, R5, 1	;; ans0 = array[n - 1], ans0 = R0 -> array[n - 1]
	AND	R1, R1, 0
	STR	R0, R5, 0	;; ans1 = 0
	LDR	R0, R5, 1
	ADD	R0, R0, R1
	STR	R0, R5, 4
	LDR	R0, R5, -1	;; restore R0
	LDR	R1, R5, -2	;; restore R1
	ADD	R6, R5, 0	;; RESTORE sp
	LDR	R5, R6, 2	;; restore FP
	LDR	R7, R6, 3	;; restore ra
	ADD	R6, R6, 4	;; pop
	RET
	
	;;====================================================
	;;====================================================
	
P	STR	R1, R5, 1	;; ans0 = max(ans1, ans2), ans0 = R1 -> findmax(array, n - 1)
	AND	R0, R0, 0
	STR	R0, R5, 0	;; ans1 = 0
	LDR	R1, R5, 0
	LDR	R0, R5, 1
	ADD	R0, R0, R1
	STR	R0, R5, 4
	LDR	R0, R5, -1	;; restore R0
	LDR	R1, R5, -2	;; restore R1
	ADD	R6, R5, 0	;; RESTORE sp
	LDR	R5, R6, 2	;; restore FP
	LDR	R7, R6, 3	;; restore ra
	ADD	R6, R6, 4	;; pop
	RET	
	
.end

.orig x500
.fill 2
.fill 3
.fill 1
.end
