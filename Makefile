Name = minishell

CC = gcc -g

FLAGS = -Wall -Werror -Wextra 

GREEN = \033[32m
RESET = \033[0m

DIR = SRC_parsing . Utils SRC_env libft libft/ft_printf libft/get_next_line

SRC = $(foreach directory, $(DIR), $(wildcard $(directory)/*c))

LIBFT = libft/*c libft/get_next_line/get_next_line.c libft/get_next_line/get_next_line_utils.c

SRC_OBJ = $(SRC:.c=.o)

define PRINT_LOADING_BY_ADIL
	@printf "$(GREEN)Minishell are Compiling ...["
	@for i in $(shell seq 0 10 100); do \
		printf "▓"; \
		sleep 0.01; \
	done
	@printf "] 100%%$(RESET)\n"
endef

.SILENT:
all : $(Name)

$(Name): $(SRC_OBJ)
	$(CC) $(FLAGS) $(SRC_OBJ) -lreadline -o $(Name)
	@echo -n "$(GREEN)CREATION DE L'EXECUTABLE ->  minishell ...$(RESET)\n"
	sleep 1
	@$(PRINT_LOADING_BY_ADIL)
	@echo -n "$(GREEN)SUCESS $(RESET)\n"

clean :
	rm -rf $(SRC_OBJ)
	@echo -n "$(GREEN)cleaning up ...$(RESET)\n"
	sleep 1
	@echo -n "$(GREEN)Sucess$(RESET)\n"

fclean : clean
	rm -rf $(Name)
	@echo -n "$(GREEN)minishell are delete$(RESET)\n"

re : fclean all

.PHONY : all clean fclean re
