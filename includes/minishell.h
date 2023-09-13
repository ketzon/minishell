#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

//# define BUFFER_SIZE 42

typedef void t_unused;
typedef struct s_lexer t_lexer;
typedef struct s_env t_env;
typedef struct s_var t_var;
typedef struct s_data t_data;

typedef enum e_token
{
    GREATER = 1,
    GREATER_DOUBLE = 2,
    LESS = 3,
    LESS_DOUBLE = 4,
    PIPE = 5
}   t_token;

typedef struct s_env
{
	char **env_vars;
	struct s_var *first_node;
}	t_env;

typedef struct s_var
{
	int index;
	int id;
	char *name;
	char *infos;
	struct s_var *prev;
	struct s_var *next;
}	t_var;

typedef struct s_data
{
    char        *env_paths;
    t_lexer     *lexer_head;
}   t_data;

typedef struct s_lexer
{
    char        *word;
    t_token     token;
    int         i;
    t_lexer     *previous;
    t_lexer     *next;
}   t_lexer;


/* SIGNALS */

void    signals_handling(void);
void	sigint_handling(int signal);

/* ENV */

char	**create_env_arr(char **envp);
t_env	*init_env(char **env_array);
t_var	*init_env_var(char *name, char *infos, int id);
void	create_env_list(t_env *env, char **env_arr);
char    *get_env_path(char **envp);
char	*malloc_each_line(char *line);
char	**create_malloc_line(char *line);
void	create_list(t_env *env, t_var *node);
void	connect_node(t_var *curr_node, t_var *next_node);
char	*get_line_infos(char *line);
char	*extract_content(char *line, int start, int end);
char	*get_line_name(char *line);

/* FREE */ 

void	free_env_array(char **env_arr);

/* UTILS */

int ft_skip_white_spaces(char *str);
void    stack_add_bottom(t_lexer **head, t_lexer *new);
t_lexer *new_node(char *input, t_token token, int index);

/* QUOTES */

int	find_matching_quote(char *line, int i, int *num_del, int del);
int	count_quotes(char *line);

/* IS */

int	is_null(char *str);
int	is_value_null(char *str);

/* LEXER */

void    lexer(t_data *data, char *argv);
t_lexer   *fill_lexer_struct(char *input);
int     add_word(char *input, int i, t_lexer **head);
int    add_token(char *input, int i, t_lexer **head);
bool    is_token(char c);

/* ERROR */

int	ft_error(int error);

#endif
