#include <stdio.h>
#include <editline/readline.h>
#include <histedit.h>


#include "mpc.h"

int main(int argc, char **argv) {
  mpc_parser_t *Program = mpc_new("program");
  mpc_parser_t *Form = mpc_new("form");
  mpc_parser_t *Expression = mpc_new("expression");
  mpc_parser_t *Constant = mpc_new("constant");
  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Symbol = mpc_new("symbol");

  mpca_lang(MPCA_LANG_DEFAULT, 
    " number     : /-?[0-9]+/ ; "
    " symbol     : '+' | '-' | '*' | '/' ; "
    " constant   : <number> | <symbol> ; "
    " expression : <constant> ;"
    " form       : <expression> ; "
    " program    : /^/ <form>* /$/ ;",
    Number, Symbol, Constant, Expression, Form, Program);

  while (1) {
    char* input = readline("gengo > ");
    add_history(input);

    mpc_result_t r;

    if (mpc_parse("<stdin>", input, Program, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(6, Number, Symbol, Constant, Expression, Form, Program);
}