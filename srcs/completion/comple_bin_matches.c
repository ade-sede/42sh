#include "completion.h"
#include "line_editing.h"
	#include <stdio.h>
#include <string.h>

char	**comple_bin_matches(t_line *line, t_comple *c, char *current_word)
