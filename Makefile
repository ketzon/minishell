BIN = bin
FLAGS = -Wall -Werror -Wextra  -g -I../includes/
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR = srcs/

SRCS = main.c signals.c utils.c quotes.c error.c lexer.c free.c init.c is.c env.c \
chained.c list.c variables.c \

SRCS_FILES = $(addprefix $(SRCS_DIR), $(SRCS))

MANDATORY = minishell
OBJ_BOTH = $(foreach src,$(SRCS_FILES),$(BIN)/$(src:.c=.o))

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
	@mkdir -p $(BIN)/srcs
	@gcc $(FLAGS) -c $^ -o $@

$(LIBFT):
	@$(ECHO) "$(GRE)● Adding libft to Minishell ⚙️ $(EOC)"
	@make -C $(LIBFT_DIR) -s

$(NAME): $(OBJ_BOTH) $(LIBFT)
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
