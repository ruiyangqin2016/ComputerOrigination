;;======================================================================
;; CS2110                    Lecitation 08                   Summer 2018
;;======================================================================
;; Author: Ruiyang Qin
;; Date: June 13th, 2018
;; Assignment: Lecitation 08 (Part 1)
;; Description: An assembly program that determines the absolute value
;;              of a given number
;;======================================================================

;;=====================================
;; Pseudocode
;;=====================================
;; if (U < 0) {
;;   ANSWER = -U
;; } else {
;;   ANSWER = U
;; }

.orig x3000

;; YOUR CODE HERE! :D

LD R0, U
BRZP DONE
NOT R0, R0
ADD R0, R0, 1

DONE


U      .fill -20
ANSWER .fill 0
.end
