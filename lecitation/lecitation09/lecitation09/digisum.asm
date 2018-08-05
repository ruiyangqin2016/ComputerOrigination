;;======================================================================
;; CS2110                    Lecitation 09                   Summer 2018
;;======================================================================
;; Author:
;; Date:
;; Assignment: Lecitation 09
;; Description: An assembly subroutine that sums the digits in a decimal
;;              number
;;======================================================================

;@plugin filename=lc3_udiv vector=x80

;; Main
;; Do not edit this function!

.orig x3000

;; Initialize stack
LD R6, STACK

;; Call digisum(n)
LD R0, N
ADD R6, R6, -1
STR R0, R6, 0
JSR DIGISUM

;; Pop return value and arg off stack
LDR R0, R6, 0
ADD R6, R6, 2

;; Save the answer
ST R0, ANSWER

HALT

STACK  .fill xF000
N      .fill 45
ANSWER .blkw 1

;;=====================================
;; Pseudocode
;;=====================================
;;
;; var digisum(n) {
;;   var div = n / 10;
;;   var mod = n % 10;
;;
;;   if (n == 0) {
;;     return 0;
;;   } else {
;;     return mod + digisum(div);
;;   }
;; }

;; To call UDIV, use TRAP x80
;; Preconditions:
;;    R0 = X
;;    R1 = Y
;; Postconditions:
;;    R0 = X / Y
;;    R1 = X % Y

DIGISUM

;; YOUR CODE HERE :D

RET

.end
