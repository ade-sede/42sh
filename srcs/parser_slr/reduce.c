#include "parser_slr.h"


#include <stdio.h>

/*
**PROGRAM -> SOMME
**SOMME -> SOMME + PRODUCT
**SOMME -> PRODUCT
**PRODUCT -> PRODUCT * FACTEUR
**PRODUCT -> FACTEUR
**FACTEUR -> ( SOMME )
**FACTEUR -> id
*/

/*a remplacer par un debug avec les regles posix*/
/*
**	const static char *rules[10] = {
**	"PROGRAM -> SOMME",
**	"SOMME -> SOMME + PRODUCT",
**	"SOMME -> PRODUCT",
**	"PRODUCT -> PRODUCT * FACTEUR",
**	"PRODUCT -> FACTEUR",
**	"FACTEUR -> ( SOMME )",
**	"FACTEUR -> id",
**	};
*/

