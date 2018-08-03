;;======================================================================
;; CS2110                    Lecitation 08                   Summer 2018
;;======================================================================
;; Author:
;; Date:
;; Assignment: Lecitation 08 (Part 3)
;; Description: A TRAP subroutine that makes a character string pointed
;;              to by R0 all lowercase
;;======================================================================

.orig x40
  .fill x5000
.end

;; Main
;; Do not edit this function!

.orig x3000

LD R0, STRING
TRAP x40
PUTS

HALT
;; R0 - R6 should still contain their original values

STRING .fill x4000
.end

.orig x4000
  .stringz "Hello, World! 123456789 !@#$%^&*"
.end

;;=====================================
;; Pseudocode
;;=====================================
;; var c = str[0];
;; while (c != 0) {
;;   if (c >= 'A' && c <= 'Z') {
;;     c += 32;
;;     str[0] = c;
;;   }
;;
;;   string++;
;;   c = str[0];
;; }

.orig x5000

  ST R0, SaveR0   ; Store R0
  ST R1, SaveR1   ; Store R1
  ST R2, SaveR2   ; Store R2
  ST R3, SaveR3   ; Store R3

WHILE 
  LDR R1, R0, #0  ; R1 = c = str[0]
  BRZ DONE        ; if (c == 0) we reached the end of the string

  LD R2, Char_A   ; R2 = 'A'
  NOT R2, R2      ; 
  ADD R2, R2, #1  ; R2 = - 'A'
  ADD R3, R1, R2  ; R3 = c - 'A'
  BRN INCREMENT   ; if (c - 'A') < 0 continue to next iteration

  LD R2, Char_Z   ; R2 = 'Z'
  NOT R2, R2      ; 
  ADD R2, R2, #1  ; R2 = - 'Z'
  ADD R3, R1, R2  ; R3 = c - 'Z'
  BRP INCREMENT   ; if (c - 'Z') > 0 continue to next iteration

  LD R2, Offset   ; R2 = 32
  ADD R1, R1, R2  ; R1 = c + 32
  STR R1, R0, #0  ; Store c at str[0]

INCREMENT
  ADD R0, R0, #1  ; R1 = string++
  BR WHILE

DONE  
  LD R0, SaveR0   ; Restore R0
  LD R1, SaveR1   ; Restore R1
  LD R2, SaveR2   ; Restore R2
  LD R3, SaveR3   ; Restore R3

  RET             ; i.e. JMP R7

SaveR0 .blkw 1
SaveR1 .blkw 1
SaveR2 .blkw 1
SaveR3 .blkw 1

Char_A .fill 'A'
Char_Z .fill 'Z'
Offset .fill 32

.end
