BIN = bin
FLAGS = -Wall -Werror -Wextra  -g
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR = ./libft
BUILTIN_DIR = builtin/
SRCS_DIR = srcs/
BUILTIN = env.c cd.c echo.c builtin.c pwd.c exit.c unset.c export.c \

SRCS = main.c signals.c srcs_utils.c quotes.c error.c lexer.c free.c init.c is.c env.c \
chained.c list.c variables.c \

SRCS_FILES = $(addprefix $(SRCS_DIR), $(SRCS))
BUILTIN_FILES = $(addprefix $(BUILTIN_DIR), $(BUILTIN))
ALL_FILES = $(SRCS_FILES) $(BUILTIN_FILES)

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
