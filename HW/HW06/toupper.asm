;;===============================
;; Name: Ruiyang Qin
;;===============================


;;=====================================
;; Pseudocode by c++
;;=====================================
;; string a = "Hell to Georiga Tech ^_^"
;; string newA = ""
;; int counter = 0
;; 
;; while (!a[counter] == null) {
;;   if a[i] is lower case {
;;     a[i] = a[i] to upper case
;;   } 
;; }
;; newA = a
;; print newA

.orig x3000

LD	R2, STRING
LD	R6, UPPERBOUND
LD	R7, LOWERBOUND
LD	R0, ZERO

WHILE   LDR     R3, R2, 0

	BRZ	DONE		;;id is null, goes to done

	;; ---ELSE--- 

	ADD	R4, R3, 0

	;; ascii code: a -> 97 || z -> 122. a -> A = 97 - 32 = 65 

	NOT	R4, R4		;;not R4
	ADD	R4, R4, 1	;;2'S complement
	ADD	R5, R4, R6	;;122 - string[counter]

	BRN	ELSE		;; if string[counter] > 122, goes else
	
	ADD	R5, R4, R7	;; 97 - string[counter]

	BRP	ELSE            ;; if string[counter] < 97, goes else

	;; get 122 >= string[counter] >= 97
	
	ADD	R3, R3, R0	;; lowercase to uppercase
	STR     R3, R2, 0
	ADD     R2, R2, 1

	BR      WHILE
	
ELSE    
        ADD     R2, R2, 1
        BR      WHILE


DONE	HALT

STRING .fill x6000
COUNTER         .fill 0
UPPERBOUND      .fill 122	;;ascii code z
LOWERBOUND      .fill 97	;;ascii code a
ZERO            .fill -32

.end

.orig x6000
.stringz "to hell with georgia\n"
.end
