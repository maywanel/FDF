CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./minilibx -lmlx -lXext -lX11 -lm
INCLUDES = -I./minilibx -I./
SRC = src/color.c src/clean.c src/draw.c src/get_next_line.c src/get_next_line_utils.c src/key.c src/parsing.c src/projection.c src/projection_2.c src/utils.c src/init.c src/split.c
OBJ = $(SRC:.c=.o)
NAME = fdf

GREY     = \033[0;30m
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
BLUE     = \033[0;34m
PURPLE   = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
BOLD     = \033[1m
UNDER    = \033[4m
REV      = \033[7m
BLINK    = \033[5m
NC       = \033[0;0m
RESET    = \033[0m

NORM = $(shell if [ $$(norminette src fdf.h | wc -l) -eq 15 ]; then echo OK; else echo KO; fi)


all: $(NAME) clean
	@echo "$(YELLOW)norminette: $(NORM)$(RESET)"

$(NAME): src/main.c fdf.h $(OBJ)
	@make --no-print-directory start_message
	@$(CC) $(CFLAGS) $(OBJ) src/main.c -o $(NAME) $(LDFLAGS) $(INCLUDES)
	@make --no-print-directory end_message

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Cleaned executables.$(RESET)"

end_message:
	@echo "$(NC)╔══════════════════════════════════════════════╗"
	@echo "$(NC)║ $(GREEN)       $(BLINK)> $(WHITE)FdF successfully compiled! $(GREEN)$(BLINK)<        $(NC)║"
	@echo "$(NC)╚══════════════════════════════════════════════╝"
start_message:
	@echo "$(NC)╔══════════════════════════════════════════════╗"
	@echo "$(NC)║ $(GREEN)                 $(WHITE)Building FDF $(GREEN)$(BLINK).$(BLINK).$(BLINK).            $(NC)║"
	@echo "$(NC)╚══════════════════════════════════════════════╝"

re: fclean all

.PHONY: all clean fclean re
