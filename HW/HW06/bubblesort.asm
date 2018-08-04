;;===============================
;; Name: Ruiyang Qin
;;===============================
.orig x3000
	
; Psuedocode from PDF
;======================================
;bubbleSort(array):
;    n = length(array)
;    
;    for i=n-1 to i=0:
;        for j=0 to j=i-1:
;            curr = arr[j]
;            next = arr[j+1]
;            if curr > next:
;                swap(array, j, j+1)
; =====================================
LD	R1, LENGTH	;; R1 -> n
LD	R2, ARRAY	;; R2 -> array
ADD	R1, R1, -1	;; R1 -> i = n - 1

FOR1	ADD	R1, R1, 0	;; when i > 0
	BRZ	DONE		;; done if i = 0
	AND	R3, R3, 0	;; j = 0
	FOR2	ADD	R4, R1, -1	;; R4 -> i - 1
		NOT	R4, R4
		ADD	R4, R4, 1	;; R4 -> -(i - 1)
		ADD	R4, R4, R3	;; j - (i - 1)
		BRP	DEI		;; back to FOR1 if j = i - 1

		ADD	R5, R2, R3
		LDR	R5, R5, 0	;; R5 -> curr = arr[j]
		ADD	R4, R3, 1	;; R4 -> j + 1
		ADD	R4, R2, R4	
		LDR	R4, R4, 0	;; R4 -> next = arr[j + 1]

		NOT	R6, R4
		ADD	R6, R6, 1
		ADD	R7, R5, R6	;; curr - next (curr > next)
		BRN	DEII		;; if curr == next || curr < next, keep looping
		
		ADD	R5, R2, R3	;; R5 -> address of arr[j]
		ADD	R4, R3, 1	;; R4 -> j + 1
		ADD	R4, R2, R4	;; R4 -> address of arr[j+1]
		LDR	R6, R5, 0	;; R6 = value of R5
		LDR	R7, R4, 0	;; R7 = value of R4
		STR	R7, R5, 0
		STR	R6, R4, 0
		
		ADD	R3, R3, 1	;; increment j
		BR	FOR2
DEI	ADD	R1, R1, -1	;; decrement i
	BR	FOR1
DEII	ADD	R3, R3, 1	;; INCREMENT j
	BR	FOR2
	


DONE	HALT

LENGTH	.fill 3
ARRAY 	.fill x6000

.end

.orig x6000
.fill 3
.fill 1
.fill 2
;;.fill 11
;;.fill 3
;;.fill 5
;;.fill 2
;;.fill 1
;;.fill 10
;;.fill 20
;;.fill 14
.end
