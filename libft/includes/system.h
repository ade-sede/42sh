#ifndef SYSTEM_H
# define SYSTEM_H

size_t				get_ws_col(void);
size_t				get_ws_row(void);
void	put_termcap(char *capacity);
void	put_ntermcap(char *capacity, int n);
void	goto_termcap(char *capacity, int co, int li);

#endif
