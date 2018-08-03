
;;====================================================
;; CS 2110
;; Timed Lab 2: Binary Tree Search
;;====================================================
;; Name: Ruiyang Qin
;; Semester: Summer 2018
;;====================================================

.orig x3000

;; Don't try to run this code directly, since only contains
;; subroutines that need to be invoked using the LC-3 calling
;; convention. Use Debug > Setup Test or Simulate Subroutine
;; Call in complx instead
;;
;; Do not remove this line or you will break...
;; "Simulate Subroutine Call"

HALT

STACK .fill xF000
ROOT  .fill x6000
QUERY .fill 3

;;====================================================
;; @todo This is where you will implement:
;;   btree_search(root, query)
;;====================================================
;; btree_search is called with two arguments:
;;    root  : the address of the root tree node
;;    query : the value to be compared to the data
;;            word in each node
;;
;; The function searches the binary tree for a node
;; with a 4th (data) word that matches the 2nd argument
;; (query).
;;
;; If it finds an exact match, the function:
;;    (1) returns the address of the matching node
;;    (2) prints "Found the data at " and
;;    (3) prints the name of the node
;;
;; If it doesn’t find an exact match, the function:
;;    (1) returns NULL (0x0000) and
;;    (2) prints “Did not find the data”



;;====================================================
;;btree_search(root, query)
;;{
;;	ans
;;	if (root == 0) {
;;		puts("Did not find the data")
;;		ans = root;
;;
;;	} else if (query == (root -> data)) {
;;		puts("Found the data at ")
;;		puts(root -> name)
;;		ans = root;
;;
;;	} else if (query < (root -> data)) {
;;		ans = btree_search(root -> left, query);
;;	} else {
;;		ans = btree_search(root -> right, query);
;;	}
;;	return ans
;;}
;;====================================================

;;============================================
;;===============damn stack===================
;;============================================
;;	R1		<- R6 final location
;;	R0
;;0	ans		<- R6 new location | R5
;;1	old frame pointer
;;2	return address
;;3	return value
;;----------------------
;;4	arg1 (root)	<- R6 (starting point)
;;5	arg2 (query)
;;============================================

    ;; YOUR CODE HERE! :D
btree_search	
	ADD	R6, R6, -4	;; allocate space
	STR	R7, R6, 2	;; save return address
	STR	R5, R6, 1	;; save old FP
	ADD	R5, R6, 0	;; copy SP to FP
	ADD	R6, R6, -2	;; room for 2 registers
	STR	R0, R5, -1	
	STR	R1, R5, -2

	LDR	R1, R5, 4	;; R1 -> root
	ADD	R1, R1, 0	;; R1 = R1 + 0
	BRZ	GOROOTISZERO	;; if (root == 0)

	LDR	R1, R5, 4	;; R1 -> root
	LDR	R0, R5, 5	;; R0 -> query
	ADD	R1, R1, 3	;; R1 -> (root -> data)
	LDR	R1, R1, 0
	NOT	R1, R1
	ADD	R1, R1, 1
	ADD	R1, R1, R0	;; R1 -> query - (root -> data)
	BRZ	EQUAL		;; query == (root -> data)
	BRN	LESS		;; query < (root -> data)
;;query > (root -> data)
	;;ans = btree_search(root -> right, query);
	LDR	R1, R5, 4	;; R1 -> root
	LDR	R0, R5, 5	;; R0 -> query
	LDR	R1, R1, 2	;; R1 -> (root -> right)
	ADD	R6, R6, -2	;; room for arg1(root) and arg2(query)
	STR	R1, R6, 0	;; push (root -> right)
	STR	R0, R6, 1	;; push query
	JSR	btree_search
	LDR	R1, R6, 0	;; R1 -> btree_search(root -> left, query)
	STR	R1, R5, 0
	LDR	R1, R5, 0
	STR	R1, R5, 3
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET


LESS
;;ans = btree_search(root -> left, query);
	LDR	R1, R5, 4	;; R1 -> root
	LDR	R0, R5, 5	;; R0 -> query
	LDR	R1, R1, 1	;; R1 -> (root -> left)
	
	ADD	R6, R6, -2	;; room for arg1(root) and arg2(query)
	STR	R1, R6, 0	;; push (root -> left)
	STR	R0, R6, 1	;; push query
	JSR	btree_search
	LDR	R1, R6, 0	;; R1 -> btree_search(root -> left, query)
	STR	R1, R5, 0
	LDR	R1, R5, 0
	STR	R1, R5, 3
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET

EQUAL
;;puts("Found the data at ")
;;puts(root -> name)
;;ans = root;
	LEA	R0, STR_FOUND
	PUTS
	LDR	R0, R5, 4	;; R1 -> root
	;;LDR	R1, R1, 0	;; R1 -> (root -> name)
	LDR	R0, R0, 0
	PUTS
	LDR	R1, R5, 4	;; R1 -> root
	STR	R1, R5, 0	;; ans = root
	STR	R1, R5, 3
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET

GOROOTISZERO
	LEA	R0, STR_NOT_FOUND
	PUTS			;; puts("Did not find the data")
	LDR	R1, R5, 4	;; R1 -> root
	STR	R1, R5, 0	;; ans = root
	STR	R1, R5, 3
	LDR	R0, R5, -1	; Restore R0
	LDR	R1, R5, -2	; Restore R1
	ADD	R6, R5, 0	; Restore SP
	LDR	R5, R6, 1	; Restore FP
	LDR	R7, R6, 2	; Restore RA
	ADD	R6, R6, 3	; Pop ra,fp,lv1
	RET
	


    
;;====================================================
;; Some useful strings for printing to the console
;;====================================================
STR_NOT_FOUND .stringz "Did not find the data"
STR_FOUND     .stringz "Found the data at "

.end

;;====================================================
;; This is where the nodes of the binary tree are
;; stored
;;====================================================
.orig x6000
  ;;==================================================
  ;; NODE: A                                     x6000
  ;;==================================================
  .fill x7000
  .fill x6004
  .fill x6008
  .fill x000B
  ;;==================================================
  ;; NODE: B                                     x6004
  ;;==================================================
  .fill x7007
  .fill x600C
  .fill x0000
  .fill x0006
  ;;==================================================
  ;; NODE: C                                     x6008
  ;;==================================================
  .fill x700E
  .fill x6010
  .fill x0000
  .fill x007B
  ;;==================================================
  ;; NODE: D                                     x600C
  ;;==================================================
  .fill x7015
  .fill x0000
  .fill x0000
  .fill x0002
  ;;==================================================
  ;; NODE: E                                     x6010
  ;;==================================================
  .fill x701C
  .fill x6018
  .fill x6014
  .fill x004B
  ;;==================================================
  ;; NODE: F                                     x6014
  ;;==================================================
  .fill x7023
  .fill x0000
  .fill x0000
  .fill x0066
  ;;==================================================
  ;; NODE: G                                     x6018
  ;;==================================================
  .fill x702A
  .fill x0000
  .fill x601C
  .fill x0011
  ;;==================================================
  ;; NODE: H                                     x601C
  ;;==================================================
  .fill x7031
  .fill x0000
  .fill x0000
  .fill x003B
.end

;;====================================================
;; This is where the name strings for each of the
;; binary tree nodes are stored
;;====================================================
.orig x7000
  .stringz "Node A" ; at x7000
  .stringz "Node B" ; at x7007
  .stringz "Node C" ; at x700E
  .stringz "Node D" ; at x7015
  .stringz "Node E" ; at x701C
  .stringz "Node F" ; at x7023
  .stringz "Node G" ; at x702A
  .stringz "Node H" ; at x7031
.end
