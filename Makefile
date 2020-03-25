NAME = 21sh

LIB = -lft -L./libft

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS = lexer \
		parser \
		exec_start \
		print_tree \
		launch_job \
		builtin_echo \
		builtin_exit \
		builtin_cd \
		builtin_cd_chgdir \
		builtin_cd_create_newpath \
		builtin_cd_error \
		builtin_cd_two_arg \
		builtin_setenv \
		builtin_unsetenv

HEADER = 	-I./include \
			-I./libft \
			
OBJ =	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: srcs/%.c
	@gcc -c $< $(HEADER) -o $@
	
$(NAME): obj $(OBJ)
	@tput setaf 7; tput bold; echo "Compiling LIB"
	@make -C libft
	@tput setaf 7; tput bold; echo "Compiling 21sh"
	@gcc $(OBJ) $(HEADER) -o $(NAME) $(LIB)
	@tput setaf 2; tput bold; echo "DONE 21sh"

obj:
	@mkdir obj

clean:
	@make -C libft clean
	@rm -rf obj
	@tput setaf 6; tput bold; echo "DONE Clean!"
	
fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@tput setaf 6; tput bold; echo "DONE Fclean!"

re: fclean all
.PHONY: all clean fclean re