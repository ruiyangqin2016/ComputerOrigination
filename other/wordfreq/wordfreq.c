#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

int getword(char *p, int i);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void treeprint2(struct tnode *p);
void treeprint2a(struct tnode *p, int n, char *s);
void treefree(struct tnode *p);

int main(int argc, char *argv[]) {
	char word[MAXWORD];
	struct tnode *root = NULL;

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
//	treeprint(root);
	treeprint2(root);

	treefree(root);

	return 0;
}

// treefree --- free a binary tree
void treefree(struct tnode *p) {
	if (p != NULL) {
		treefree(p->left);
		treefree(p->right);
		free(p->word);
		free(p);
	}
}

// addtree --- add a node with w at or below p
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	
	// New segment: add a node
	if (p == NULL) {
		assert((p = (struct tnode *)malloc(sizeof(*p))) != NULL);
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	// Old word: increment the count
	} else if ((cond = strcmp(w, p->word)) == 0) 
		p->count++;
	// Word is less than left: add it to the left subtree
	else if (cond < 0) 
		p->left = addtree(p->left, w);
	// Add to right subtree
	else
		p->right = addtree(p->right, w);

	return p;
}

// treeprint --- in-order print of tree p
void treeprint (struct tnode *p) {
    if (p != NULL) {
        treeprint (p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint (p->right);
    }
}
// treeprint2 --- in-order print of tree p
void treeprint2 (struct tnode *p) {
    treeprint2a(p, 0, "");
}
// treeprint2a -- pre-order print of tree p with tree borders
void treeprint2a (struct tnode *p, int n, char *s) {
	char *buf;
	int sl;
	if (p != NULL) {
		printf("%s+%4d %s\n", s, p->count, p->word);
		sl = strlen(s);
		assert((buf = (char *)malloc(sl + 6)) != NULL);
		strcpy(buf, s);
		strcpy(&buf[sl], "    |");
		treeprint2a (p->left, n+1, buf);
		strcpy(&buf[sl], "     ");
		treeprint2a (p->right, n+1, buf);
		free(buf);
	}
}


/* getword:  get next word or character from input */
//int getword(char *word, int lim) {
//       int c;
//       char *w = word;
//       while (isspace(c = getchar()))
//           ;
//       if (c != EOF)
//           *w++ = c;
//       if (!isalpha(c)) {
//           *w = '\0';
//           return c;
//       }
//       for ( ; --lim > 0; w++)
//           if (!isalnum(*w = getchar())) {
//               ungetc(*w, stdin);
//               break;
//           }
//       *w = '\0';
//       return word[0];
//}
