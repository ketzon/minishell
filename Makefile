BIN = bin
FLAGS = -Wall -Wextra -Werror -g -Iincludes
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS = main.c signals.c env.c utils.c quotes.c error.c

MANDATORY = minishell
OBJ_BOTH = $(foreach src,$(SRCS),$(BIN)/$(src:.c=.o))

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
	@mkdir -p $(BIN)
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
