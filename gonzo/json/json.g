{
#include <stdio.h>
#include <stdlib.h>
#include "json.h"
}

element: hash | array | scalar;

hash: '{' hash_elements '}';
hash_elements: hash_element hash_elements_tail | /* empty */;
hash_elements_tail: ',' hash_elements | /* empty */;
hash_element: string ':' element;

array: '[' array_elements ']';
array_elements: array_element array_elements_tail | /* empty */;
array_elements_tail: ',' array_elements | /* empty */;
array_element: element;

scalar: integer | string | boolean | null;

integer: "-?[0-9]+";
string: '"' "[^\"\n]*" '"';
boolean: "true" | "false";
null: "null";
