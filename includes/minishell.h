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

typedef struct s_lexer t_lexer;

typedef enum e_token
{
    GREATER = 1,
    GREATER_DOUBLE = 2,
    LESS = 3,
    LESS_DOUBLE = 4,
    PIPE = 5,
    WORD = 6
}   t_token;

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
void sigint_handling(int signal);

/* ENV */

char    *get_env_path(char **envp);

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

/* ERROR */

int	ft_error(int error);

#endif
