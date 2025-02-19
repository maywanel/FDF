CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./minilibx -lmlx -lXext -lX11 -lm
INCLUDES = -I./minilibx -I./
SRC = src/clean.c src/draw.c src/get_next_line.c src/get_next_line_utils.c src/key.c src/parsing.c src/projection.c src/utils.c
OBJ = $(SRC:.c=.o)
NAME = fdf

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) src/main.c -o $(NAME) $(LDFLAGS) $(INCLUDES)
	@echo "$(GREEN)Building $(NAME)...$(RESET)"
	@echo "$(BLUE)FDF is created.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Cleaned executables.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
