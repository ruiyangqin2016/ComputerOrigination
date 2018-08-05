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

;; WHAT SHOULD GO HERE?

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

;; CODE GOES HERE :D
ST R0, SaveR0
ST R1, SaveR1


RET

;; WHAT SHOULD GO HERE?

SaveR0 .blkw 1
SaveR1 .blkw 1

.end
