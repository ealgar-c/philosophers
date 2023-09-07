# COMPILER INFO
CC = cc
FLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g3 # (data races)
RM = rm -f

# GENERAL INFO
NAME = philo
SRC_DIR = src/
SRC = main.c checker.c initialize.c routine.c states.c time.c utils.c
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

# COLOR CODES
GREEN_CODE=\033[0;32m
RED_CODE=\033[0;31m
CEND_CODE=\033[0m

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(EXTRAFLAGS) -o $(NAME) $(OBJ)
	@ echo "-->$(GREEN_CODE) $(NAME) compiled ✅ $(CEND_CODE)<--"

clean:
	@$(RM) $(OBJ)
	@ echo "-->$(RED_CODE) $(NAME) cleaned 🗑  $(CEND_CODE)<--"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
