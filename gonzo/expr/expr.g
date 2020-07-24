{
#include <stdio.h>
#include <stdlib.h>
#include "expr.h"
}

expr:
    integer                  { $$.value = $0.value; }
  | expr '+' expr  $left 10  { $$.value = $0.value + $2.value; }
  | expr '-' expr  $left 10  { $$.value = $0.value - $2.value; }
  | expr '*' expr  $left 20  { $$.value = $0.value * $2.value; }
  | expr '/' expr  $left 20  { $$.value = $0.value / $2.value; }
  | '(' expr ')'             { $$.value = $1.value; }
  ;

integer: "-?[0-9]+"          { $$.value = atoi($n0.start_loc.s); }
  ;
