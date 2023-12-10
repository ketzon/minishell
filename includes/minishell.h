/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:41:02 by fgonzale          #+#    #+#             */
/*   Updated: 2023/12/10 17:15:56 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define NOT_FIND  1
# define PROMPT "\001\e[45m\002>>> \001\e[0m\e[33m\002 Minishell>$ \001\e[0m\002"
//# define BUFFER_SIZE 42
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

typedef struct s_cmd	t_cmd;
typedef struct s_lexer	t_lexer;
typedef struct s_var	t_var;
typedef struct s_data	t_data;

extern int				g_exit_code;

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
}	t_token;

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
	int		(*func)(t_data *data, char **args);
}	t_builtin;

typedef struct s_var
{
	int				index;
	int				id;
	char			*name;
	char			*infos;
	struct s_var	*prev;
	struct s_var	*next;
}	t_var;

typedef struct s_data
{
	bool		overwrite_exit_code;
	char		*line;
	char		**env;
	char		*wd;
	char		*old_wd;
	t_lexer		*lexer_head;
	t_cmd		*cmd_head;
	t_var		*env_head;
	pid_t		pid;
	t_builtin	builtins[8];
}	t_data;

typedef struct s_lexer
{
	char		*word;
	char		*word_backup;
	bool		var_exists;
	bool		join;
	t_token		token;
	t_lexer		*previous;
	t_lexer		*next;
}	t_lexer;

typedef struct s_cmd
{
	char		*command;
	char		*path;
	char		**args;
	bool		pipe_output;
	int			*pipe_fd;
	t_io_data	*io_struct;
	t_cmd		*previous;
	t_cmd		*next;
}	t_cmd;

/* MAIN */

bool	parse_input(t_data *data);
void	reset_loop(t_data *data);

/* INIT */

void	initialise_io(t_cmd *cmd_node);
bool	init_data(t_data *data, char **envp);
void	init_builtins(t_data *data);
bool	init_wds(t_data *data);

/* SIGNALS */

void	signals_handling(void);
void	sigint_handling(int signal);
void	sigint_process(int signal);

/* BUILTIN */

int		execute_builtin(t_data *data, t_cmd *cmd);
int		builtin_cd(t_data *data, char **args);
int		builtin_echo(t_data *data, char **args);
int		builtin_env(t_data *data, char **args);
int		builtin_exit(t_data *data, char **args);
int		builtin_pwd(t_data *data, char **args);
int		builtin_unset(t_data *data, char **args);
int		builtin_export(t_data *data, char **args);

/* ENV */

char	**realloc_env_vars(t_data *data, int size);
bool	set_env_var(t_data *data, char *key, char *value);
bool	is_valid_var_key(char *var);
bool	is_valid_var_key(char *var);
char	**create_env_arr(char **envp);
t_var	*init_env(char **env_array);
t_var	*init_env_var(char *name, char *infos, int id);
void	create_env_list(t_var **env_head, char **env_arr);
char	*get_env_var_value(char **env, char *var);
int		get_env_var_index(char **env, char *var);
char	*get_env_path(char **envp);
char	*get_home_path(char **envp);
char	*malloc_each_line(char *line);
char	**create_malloc_line(char *line);
void	create_list(t_var **env_head, t_var *node);
void	connect_node(t_var *curr_node, t_var *next_node);
char	*get_line_infos(char *line);
char	*extract_content(char *line, int start, int end);
char	*get_line_name(char *line);

/* FREE */

void	free_strs(char **strs);
void	free_reset_ptr(void	*ptr);
void	free_data(t_data *data, bool clear_history);
void	free_ptr(void *ptr);
void	free_env_array(char **env_arr);
void	free_env_struct(t_var *env_head);
void	clear_lexer_head(t_lexer **lexer_head);
void	clear_cmd_head(t_cmd **cmd_head);
void	free_io_struct(t_io_data *io);
void	delete_token(t_lexer *node, void (*del)(void *));

/* UTILS */

//void close_fds(t_command *cmds, bool close_backups);
int		line_count(char **envp);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
int		ws(char c);
int		ft_skip_white_spaces(char *str);
int		ft_isspace(int c);
void	stack_add_bottom(t_lexer **head, t_lexer *new);
t_lexer	*new_node(char *input, char *input_backup, t_token token);
int		count_len(char *str, int count, int i);

/* QUOTES */

int		handle_quotes(t_data *data);
int		delete_quotes(t_lexer **node);
int		delete_quotes_2(t_lexer **token_node, char *new_line);

/* IS */

int		is_index(char **env, char *var);
bool	cmd_is_dir(char *cmd);
bool	is_quotes(char *str);
int		is_null(char *str);
int		is_value_null(char *str);

/* LEXER */

void	debugger_lexer(t_data *data);

int		token_parse(t_data *data);
char	*token_word(t_token token);
int		is_sep(char *str, int i);
void	add_token(char *input, int i, t_lexer **head);
int		get_status(int status, char c);
void	add_token_part1(char *input, t_lexer **head,
			t_token *token, char **str);
void	add_token_part2(char *input, t_lexer **head,
			t_token *token, char **str);

/* VARIABLE CHECK*/

int		variable_check(t_data *data);
void	variable_expander(t_data *data);

/* EXPANDER UTILS */

bool	var_in_quotes(char *word, int i);
int		var_word_len(char *str);
bool	var_exist(t_data *data, char *var_name);
char	*get_var_value(t_data *data, char *var_name);
bool	invalid_next_char(char c);
char	*find_matching_var(t_data *data, char *word, t_lexer *node);

/* EXPANDER REPLACE*/

int		replace_value(t_lexer *node, char *var_value, int index);
int		delete_var_name(t_lexer *node, int index);
char	*delete_var_name_and_replace(t_lexer *node, char *var_value, int index);
char	*malloc_new_string(t_lexer *node, int var_name_len, char *var_value);
void	write_new_string(t_lexer *node, int index,
			char *var_value, char *new_string);

/* CREATE COMMANDS*/

void	debugger_cmds(t_data *data);

/* REDIRECTIONS */
void	close_fds(t_cmd *cmds, bool close_backups);
void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd);
bool	check_infile_outfile(t_io_data *io);
bool	set_pipe_fds(t_cmd *cmds, t_cmd *cmd);
bool	restore_io(t_io_data *io);
bool	redirect_io(t_io_data *io);
bool	create_pipes(t_data *data);

/* EXECUTE */
int		execute(t_data *data);
int		execute_command(t_data *data, t_cmd *cmd);
char	*get_cmd_path(t_data *data, char *name);
int		check_command_not_found(t_data *data, t_cmd *cmd);
void	free_str_tab(char **tab);

/* COMMANDS */

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
char	**fill_args_tab(t_cmd *last_cmd, t_lexer **lexer_lst,
			char **new_args_tab, int old_args_count);
int		count_cmd_args(t_lexer *lexer_lst);
int		count_args(t_lexer *tmp);

int		create_args_echo_mode(t_lexer **lexer_lst, t_cmd *last_cmd);
int		add_args_echo_mode(t_lexer **lexer_lst, t_cmd *last_cmd);
void	delete_empty_var_args(t_lexer **lexer_lst);
char	**copy_to_new_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_lexer *tmp);
char	*join_variables(t_lexer **lexer_lst);

/* HEREDOC*/

int		replace_value_heredoc(char **line, char *var_value, int index);
char	*delete_var_name_and_replace_heredoc(char **line,
			char *var_value, int index);
int		delete_var_name_heredoc(char **line, int index);
char	*malloc_new_string_heredoc(char **line, int var_name_len,
			char *var_value);
void	write_new_string_heredoc(char **line, int index,
			char *var_value, char *new_string);
/* ERROR */

int		ft_error(int error);
int		errmsg_cmd(char *command, char *detail,
			char *error_message, int error_nb);
void	exit_shell(t_data *data, int exit_number);
void	errmsg(char *errmsg, char *detail, int quotes);
bool	add_detail_quotes(char *command);
char	*join_strs(char *str, char *add);

#endif
