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
# include <fcntl.h>

# define NOT_FIND  1
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
//# define BUFFER_SIZE 42

typedef struct s_cmd	t_cmd;
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

typedef struct s_io
{
	char	*infile;
	char	*outfile;
	char	*heredoc_eof;
	bool	heredoc_quotes;
	int		input_fd;
	int		output_fd;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_data;

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
	t_cmd		*cmd_head;
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

typedef struct s_cmd
{
	char	*command;
	char	*path;
	char	**args;
	bool	pipe_output;
	int		*pipe_fd;
	t_io_data	*io_struct;
	t_cmd	*previous;
	t_cmd	*next;
}	t_cmd;

/* MAIN */

bool    parse_input(t_data *data);
void    reset_loop(t_data *data);

/* INIT */

void	initialise_io(t_cmd *cmd_node);

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

void	free_strs(char **strs);

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
t_lexer *new_node(char *input, char *input_backup, t_token token);
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
char    *find_matching_var(t_data *data, char *word);

/* EXPANDER REPLACE*/

int    replace_value(t_lexer *node, char *var_value, int index);
int     delete_var_name(t_lexer *node, int index);
char    *delete_var_name_and_replace(t_lexer *node, char *var_value, int index);

/* CREATE COMMANDS*/

void	debugger_cmds(t_data *data);

void	create_commands(t_data *data);
void	cmd_lst_addback(t_cmd **cmd_head, t_cmd *new_node);
t_cmd	*new_node_cmd(bool value);
t_cmd	*get_last_cmd(t_cmd *cmd_lst);
void	parse_words(t_cmd **cmd_head, t_lexer **lexer_lst);
bool	erase_previous_file(t_io_data *io, bool infile);
void	parse_input_cmd(t_cmd **cmd_head, t_lexer **lexer_head);
void	open_input(t_io_data *io, char *input_name, char *og_name);
void	parse_output(t_cmd **cmd_head, t_lexer **lexer_head);
void	parse_output_append(t_cmd **cmd_head, t_lexer **lexer_head);
void	parse_pipe(t_cmd **cmd_head, t_lexer **lexer_head);
void	parse_heredoc(t_data *data, t_cmd **cmd_head, t_lexer **lexer_head);
bool	fill_heredoc(t_data *data, t_io_data *io, int temp_fd);

void	split_var_cmd(char *var_str, t_cmd *last_cmd);
int		fill_cmd_args(t_lexer **lexer_lst, t_cmd *last_cmd);
int		create_args(t_cmd *last_cmd, t_lexer **lexer_lst);
int		add_new_args(t_cmd *last_cmd, t_lexer **lexer_lst);
char	**fill_args_tab(t_cmd *last_cmd, t_lexer **lexer_lst, char **new_args_tab, int old_args_count);

/* HEREDOC*/

int   replace_value_heredoc(char **line, char *var_value, int index);
char    *delete_var_name_and_replace_heredoc(char **line, char *var_value, int index);
int     delete_var_name_heredoc(char **line, int index);
/* ERROR */

int	ft_error(int error);

#endif
