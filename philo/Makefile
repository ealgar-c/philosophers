CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = philo
SRC_DIR = src/
SRC = main.c checker.c initialize.c routine.c states.c time.c
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ)
	@ echo "Philo compiled"

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
