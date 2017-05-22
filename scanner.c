#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

enum {T_END, T_NUMBER, T_SYMBOL};

typedef struct token {
  int type;
  char sym;
  int val;
} token;

int peek(FILE *in) {
  int c = getc(in);
  ungetc(c, in);
  return c;
}

void advance(FILE *in) {
  getc(in);
}

int scan_number(FILE *in) {
  int n = 0;
  while (isdigit(peek(in))) {
    n *= 10;
    n += getc(in) - '0';
  }
  return n;
}

token* scanner(FILE *in) {
  token* t = malloc(sizeof(token));

  while (isspace(peek(in))) { advance(in); }

  if (peek(in) == EOF) {
    t->type = T_END;
  } else if (isdigit(peek(in))) {
    t->type = T_NUMBER;
    t->val = scan_number(in);
  }
  else {
    int c = getc(in);
    switch (c) {
      case '+':
      case '-':
      case '*':
      case '/':
        t->type = T_SYMBOL;
        t->sym = c;
        break;
    }
  }

  return t;
}