;;======================================================================
;; CS2110                    Lecitation 08                   Summer 2018
;;======================================================================
;; Author:
;; Date:
;; Assignment: Lecitation 08 (Part 2)
;; Description: An assembly program to search for a certain value in
;;              an array
;;======================================================================

;;=====================================
;; Pseudocode
;;=====================================
;; var counter = 0;
;; RESULT = 0;
;;
;; while (counter < LENGTH) {
;;   if (ARRAY[counter] == NUMBER) {
;;     RESULT = 1;
;;     break;
;;   }
;;   counter++;
;; }


.orig x3000

;; CODE GOES HERE! :D


AND R0, R0, 0     ;R0 = COUNTER = 0
AND R1, R1, 0     ;R1 = RESULT = 0

LD R2, LENGTH
LD R3, ARRAY
LD R4, NUMBER

WHILE   NOT R5, R2
        ADD R5, R5, 1
        ADD R5, R0, R5

        BRZP DONE

        ADD R5, R3, R0
        LDR R5, R5, 0
        ADD R5, R5, R4
        
        BRZ FOUND

        ADD R0, R0, 1

        BR WHILE
FOUND ADD R1, R1, 1

DONE ST R1, RESULT
   



ARRAY  .fill x6000
LENGTH .fill 20
NUMBER .fill 15
RESULT .fill 0
.end





.orig x6000
.fill 1
.fill 2
.fill 733
.fill 44
.fill 9
.fill 7
.fill 12
.fill 80
.fill 3
.fill 64
.fill 21
.fill 10
.fill 90
.fill 7
.fill 15
.fill 12
.fill 377
.fill 65
.fill 7
.fill 42
.end
