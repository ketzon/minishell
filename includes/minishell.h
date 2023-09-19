#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
//# define BUFFER_SIZE 42

typedef void t_unused;
typedef struct s_lexer t_lexer;

typedef enum e_token
{
    WORD = 1,
    VAR = 2,
    PIPE = 3,
    LESS = 4,
    LESS_DOUBLE = 5,
    GREATER = 6,
    GREATER_DOUBLE = 7
}   t_token;

typedef struct s_env
{
	int processing_error;
	int	parsing_error;
	char **env_vars;

}	t_env;
typedef struct s_data
{
    char        *line;
    char        *env_paths;
    t_lexer     *lexer_head;
}   t_data;

typedef struct s_lexer
{
    char        *word;
    t_token     token;
    t_lexer     *previous;
    t_lexer     *next;
}   t_lexer;


/* MAIN */

bool    parse_input(t_data *data);
void    reset_loop(t_data *data);

/* SIGNALS */

void    signals_handling(void);
void	sigint_handling(int signal);

/* ENV */

char    *get_env_path(char **envp);
char	*malloc_each_line(char *line);
char	**create_malloc_line(char *line);
char	**create_env_arr(char **envp, int ac, char **av);

/* UTILS */

int ft_skip_white_spaces(char *str);
void    stack_add_bottom(t_lexer **head, t_lexer *new);
t_lexer *new_node(char *input, t_token token);

/* QUOTES */

int	    find_matching_quote(char *line, int i, int *num_del, int del);
bool    closed_quotes(char *line);
int     quotes_handling(char *str, int start, char quote);

/* LEXER */

void    lexer(t_data *data);
t_lexer   *fill_lexer_struct(char *input);
int     add_word(char *input, int i, t_lexer **head);
int     add_token(char *input, int i, t_lexer **head);
bool    is_token(char c);

/* VARIABLE CHECK*/

int variable_check(t_data *data);

/* ERROR */

int	ft_error(int error);

#endif
