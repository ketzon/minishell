BIN = bin
FLAGS = -Wall -Wextra -Werror -g -Iincludes
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
<<<<<<< HEAD

SRCS_DIR = srcs/
SRCS = main.c signals.c env.c utils.c quotes.c error.c lexer.c variables.c
SRCS_FILES = $(addprefix $(SRCS_DIR), $(SRCS))

MANDATORY = minishell
OBJ_BOTH = $(foreach src,$(SRCS_FILES),$(BIN)/$(src:.c=.o))
=======
SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/signals.c $(SRCS_DIR)/env.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/quotes.c $(SRCS_DIR)/error.c

MANDATORY = minishell
OBJ_DIR = $(BIN)
OBJ_BOTH = $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
>>>>>>> 5684930f30fb02b89ff62a932172219cabebd101

NAME = $(MANDATORY)

ECHO = echo
RED = \033[31m
GRE = \033[32m
GRA = \033[37m
BLU = \033[34m
EOC = \033[0m

all: $(NAME)

<<<<<<< HEAD
bin/%.o: %.c
	@$(ECHO) "$(BLU)● Compiling $^ 🔧$(EOC)"
	@mkdir -p $(BIN)/srcs
	@gcc $(FLAGS) -c $^ -o $@
=======
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(ECHO) "$(BLU)● Compiling $< 🔧$(EOC)"
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@
>>>>>>> 5684930f30fb02b89ff62a932172219cabebd101

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
