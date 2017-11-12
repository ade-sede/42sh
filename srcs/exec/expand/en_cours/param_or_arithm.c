	
	if (words[1 + *offset] == '(')
	{
		if (words[2 + *offset] == '(')
		{
			/* Differentiate between $((1+3)) and $((echo);(ls)) */
			int i = 3 + *offset;
			int depth = 0;
			while (words[i] && !(depth == 0 && words[i] == ')'))
			{
				if (words[i] == '(')
					++depth;
				else if (words[i] == ')')
					--depth;

				++i;
			}

			if (words[i] == ')' && words[i + 1] == ')')
			{
				(*offset) += 3;
				/* Call parse_arith -- 0 is for "no brackets" */
				return parse_arith (word, word_length, max_length, words, offset,
						flags, 0);
			}
		}

		(*offset) += 2;
		return parse_comm (word, word_length, max_length, words, offset, flags,
				quoted? NULL : pwordexp, ifs, ifs_white);
	}

