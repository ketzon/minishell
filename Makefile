BIN = bin
FLAGS = -Wall -Wextra -Werror  -g
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libft
LEXER_DIR = lexer/
ENV_DIR = env/
EXPANDER_DIR = expander/
EXECUTION_DIR = execution/
REDIRECTIONS_DIR = redirections/
BUILTIN_DIR = builtin/
SRCS_DIR = srcs/
CMD_DIR = command/
CC = clang

SRCS = main.c signals.c srcs_utils.c srcs_utils2.c error.c free.c free2.c handle_quotes.c delete_quotes.c debuggers.c init.c \

EXPANDER = var_expander.c var_expander_utils.c variables_check.c var_replace.c heredoc_expander.c \

LEXER = token_parse.c token_parse_utils.c\

REDIRECTIONS = file_io.c pipe.c \

EXECUTION = execute.c execute_cmd.c execute_utils.c parse_path.c\


ENV = chained.c env.c init.c is.c list.c \

BUILTIN = env.c echo.c builtin.c pwd.c exit.c unset.c export.c cd.c \

COMMAND =  create_commands.c lst_cmd.c parse_word.c fill_cmd_args.c split_var_cmd.c parse_input.c parse_output.c parse_output_append.c parse_pipe.c parse_heredoc.c heredoc_utils.c echo_args.c echo_args2.c\

EXPANDER_FILES = $(addprefix $(EXPANDER_DIR), $(EXPANDER))
LEXER_FILES = $(addprefix $(LEXER_DIR), $(LEXER))
ENV_FILES = $(addprefix $(ENV_DIR), $(ENV))
SRCS_FILES = $(addprefix $(SRCS_DIR), $(SRCS))
BUILTIN_FILES = $(addprefix $(BUILTIN_DIR), $(BUILTIN))
EXECUTION_FILES = $(addprefix $(EXECUTION_DIR), $(EXECUTION))
REDIRECTIONS_FILES = $(addprefix $(REDIRECTIONS_DIR), $(REDIRECTIONS))
CMD_FILES = $(addprefix $(CMD_DIR), $(COMMAND))

ALL_FILES = $(SRCS_FILES) $(ENV_FILES) $(LEXER_FILES) $(EXPANDER_FILES) $(CMD_FILES) $(EXECUTION_FILES) $(BUILTIN_FILES) $(REDIRECTIONS_FILES)

MANDATORY = minishell
ALL_OBJ = $(foreach src,$(ALL_FILES),$(BIN)/$(src:.c=.o))

NAME = $(MANDATORY)

ECHO = echo
RED = \033[31m
GRE = \033[32m
GRA = \033[37m
BLU = \033[34m
EOC = \033[0m

all: $(NAME)

bin/%.o: %.c
	@$(ECHO) "$(BLU)● Compiling $^ 🔧$(EOC)"
	@mkdir -p $(dir $(BIN)/$*)
	@gcc $(FLAGS) -c $^ -o $@ -s

$(LIBFT):
	@$(ECHO) "$(GRE)● Adding libft to Minishell ⚙️ $(EOC)"
	@make -C $(LIBFT_DIR) -s

$(NAME): $(ALL_OBJ) $(LIBFT)
	@$(ECHO) "$(GRE)● Minishell ready ⚙️ $(EOC)"
	@gcc $(FLAGS) $(LIBFT) $^ -o $@ -lreadline

clean:
	@$(ECHO) "$(RED)● Removing /$(BIN) 📁$(EOC)"
	@rm -rf $(BIN)
	@make -C $(LIBFT_DIR) clean -s

fclean: clean
	@$(ECHO) "$(RED)● Removing binary ⚙️ $(EOC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean -s

re: fclean all
