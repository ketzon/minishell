#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

# define NOT_FIND  1
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
//# define BUFFER_SIZE 42

typedef struct s_lexer t_lexer;
typedef struct s_var t_var;
typedef struct s_data t_data;


enum e_quoting_status
{
		DEFAULT,
		SQUOTE,
		DQUOTE
};

typedef enum e_token
{
	SPACES = 1,
    WORD = 2,
    VAR = 3,
    PIPE = 4,
    INPUT = 5,
    HEREDOC = 6,
    OUTPUT = 7,
    OUTAPPEND = 8,
	END = 9
}   t_token;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_data *data);
}	t_builtin;

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
    char        *line;
	char		**env;
    t_lexer     *lexer_head;
    t_var     	*env_head;
}   t_data;

typedef struct s_lexer
{
    char        *word;
	char		*word_backup;
	bool		var_exists;
	bool		join;
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

/* BUILTIN */

// int	execute_builtin(t_data *data);
// int	builtin_cd(t_data *data);
// int	builtin_echo(t_data *data);
// int	builtin_env(t_data *data);
// int builtin_exit(t_data *data);
// int builtin_pwd(t_data *data);
// int builtin_unset(t_data *data);
// int	builtin_export(t_data *data);

/* ENV */

char	**create_env_arr(char **envp);
t_var	*init_env(char **env_array);
t_var	*init_env_var(char *name, char *infos, int id);
void	create_env_list(t_var **env_head, char **env_arr);
char    *get_env_path(char **envp);
char    *get_home_path(char **envp);
char	*malloc_each_line(char *line);
char	**create_malloc_line(char *line);
void	create_list(t_var **env_head, t_var *node);
void	connect_node(t_var *curr_node, t_var *next_node);
char	*get_line_infos(char *line);
char	*extract_content(char *line, int start, int end);
char	*get_line_name(char *line);

/* FREE */

void	free_data(t_data *data);
void	free_reset_ptr(void	*ptr);
void	free_env_array(char **env_arr);
void	free_env_struct(t_var *env_head);
void	clear_lexer_head(t_lexer **lexer_head);

/* UTILS */

int	ft_strcmp(char *s1, char *s2);
char *ft_strcpy(char *dest, const char *src);
int	ws(char c);
int ft_skip_white_spaces(char *str);
void    stack_add_bottom(t_lexer **head, t_lexer *new);
t_lexer *new_node(char *input, t_token token);
int	count_len(char *str, int count, int i);

/* QUOTES */

int		handle_quotes(t_data *data);
int	delete_quotes(t_lexer **node);
int	    find_matching_quote(char *line, int i, int *num_del, int del);
bool    closed_quotes(char *line);
int     quotes_handling(char *str, int start, char quote);

/* IS */

bool is_quotes(char *str);
int	is_null(char *str);
int	is_value_null(char *str);

/* LEXER */

void	debugger_lexer(t_data *data);

int	token_parse(t_data *data);
char	*token_word(t_token token);
int	is_sep(char *str, int i);

void    lexer(t_data *data);
t_lexer   *fill_lexer_struct(char *input);
int     add_word(char *input, int i, t_lexer **head);
int     add_token(char *input, int i, t_lexer **head);
bool    is_token(char c);

/* VARIABLE CHECK*/

int     variable_check(t_data *data);
void    variable_expander(t_data *data);

/* EXPANDER UTILS */

void    quotes_check(int *single_quote, char c);
bool    var_in_quotes(char *word, int i);
int     var_word_len(char *str);
bool    var_exist(t_data *data, char *var_name);
char     *get_var_value(t_data *data, char *var_name);
bool    invalid_next_char(char c);

/* EXPANDER REPLACE*/

int    replace_value(t_lexer *node, char *var_value, int index);
int     delete_var_name(t_lexer *node, int index);
char    *delete_var_name_and_replace(t_lexer *node, char *var_value, int index);

/* CREATE COMMANDS*/

//void	create_commands(t_data *data);

/* ERROR */

int	ft_error(int error);

#endif
