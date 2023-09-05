#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>


/* SIGNALS */

void    signals_handling(void);
void sigint_handling(int signal);

/* ENV */

char    *get_env_path(char **envp);

/* UTILS */

int ft_skip_white_spaces(char *str);

/* QUOTES */

int	handle_quotes(int i, char *str, char del);
int	find_matching_quote(char *line, int i, int *num_del, int del);
int	count_quotes(char *line);

/* ERROR */

int	ft_error(int error);

#endif
