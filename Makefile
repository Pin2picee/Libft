Name = minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra

GREEN = \033[32m
RESET = \033[0m

DIR = SRC_parsing . Utils

SRC = $(foreach directory, $(DIR), $(wildcard $(directory)/*c))

LIBFT = libft/*c libft/get_next_line/get_next_line.c libft/get_next_line/get_next_line_utils.c

PRINTF = libft/ft_printf/*c

SRC_OBJ = $(SRC:.c=.o)

define PRINT_LOADING_BY_ADIL
	@printf "$(GREEN)Minishell are Compiling ...["
	@for i in $(shell seq 0 10 20 30 40 50 60 70 80 90 100); do \
		printf "▓"; \
		sleep 0.01; \
	done
	@printf "] 100%$(RESET)\n"
endef

.SILENT:
all : $(Name)

$(Name): $(SRC_OBJ)
	$(CC) $(FLAGS) $(SRC_OBJ) $(LIBFT) $(PRINTF) -o $(Name)
	@echo -n "$(GREEN)CREATION DE L'EXECUTABLE ->  minishell ...$(RESET)\n"
	sleep 1
	@echo -n "$(GREEN)SUCESS $(RESET)\n"

clean :
	rm -rf $(SRC_OBJ)
	@echo -n "$(GREEN)cleaning up ...$(RESET)\n"
	sleep 2
	@echo -n "$(GREEN)Sucess$(RESET)\n"

fclean : clean
	rm -rf $(Name)
	@echo -n "$(GREEN)minishell are delete$(RESET)\n"

re : fclean all

.PHONY : all clean fclean re
