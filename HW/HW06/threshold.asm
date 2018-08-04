;;===============================
;; Name: Ruiyang Qin
;;===============================
.orig x3000

;;=====================================
;; Pseudocode
;;=====================================
;; array = [0, 5, 2, 10, 14]
;; length = 5
;; threshold = 5
;; counter = 0
;; while (counter < length) {
;;   if (array[counter] == threshold) {
;;     print "NO"
;;   } else if (array[counter] == threshold) {
;;     print "EQUAL"
;;   } else {
;;     print "YES"
;;   }
;;   counter ++
;; }

LD	R1, LENGTH
LD	R2, ARRAY
LD	R3, THRESHOLD
LD	R4, COUNTER


WHILE 	NOT	R5, R1
       	ADD	R5, R5, 1	;;-length by 2's complement
       	ADD	R6, R4, R5	;;counter - length < 0


       	BRZP	DONE

       	;;=============================================
       	;; ---------------- LOOP BODY -----------------
       	;;=============================================
       
   	;; -- figure out array[counter] + threshold --

       	NOT	R5, R3
       	ADD	R5, R5, 1	;;-threshold by 2's complement
       	ADD	R6, R2, R4	;; array[counter]
	LDR	R6, R6, 0	;; get data from array
	
	ADD	R4, R4, 1	;; counter ++

       	ADD	R7, R5, R6 	;; array[counter] - threshold


	BRP	BIG	;; else if (array[counter] > threshold)

       	BRZ	EQUAL	;; if (array[counter] == threshold)
       
       	BRN	SMALL	 ;; else //array[counter] < threshold

EQUAL
	LEA	R0, EQUALM
	PUTS
	BRNZP	WHILE
BIG
	LEA	R0, YESM
	PUTS
	BRNZP	WHILE

SMALL	
	LEA	R0, NOM
	PUTS
	BRNZP	WHILE

DONE
	HALT

NOM	.STRINGZ "NO\n"
YESM	.STRINGZ "YES\n"
EQUALM	.STRINGZ "EQUAL\n"
	

LENGTH .fill 5
ARRAY .fill x6000
THRESHOLD  .fill 5

COUNTER .fill 0

.end

.orig x6000
.fill 0
.fill 5
.fill 2
.fill 10
.fill 14
.end
