NAME = 21sh

LIB = -lft -L./libft

SRCS_DIR = ./srcs/

FLAGS = -Wall -Wextra -Werror

SRCS = lexer \
		lexer_state \
		lexer_state_great \
		lexer_state_less \
		lexer_state_more \
		lexer_state_word \
		lexer_misk \
		parser \
		parser_misk \
		parser_node_work \
		parser_cmd_suffix \
		parser_command \
		exec_start \
		exec_job_misk \
		print_tree \
		launch_job \
		fork_job \
		prepare_argv_proc \
		handle_exp_misk \
		handle_expansions \
		search_spec \
		tilde_expansion \
		dollar_expansion \
		check_binary \
		handle_nonforked \
		handle_errors \
		misk_functions \
		is_builtin \
		handle_exit_status \
		launch_child_proc \
		handle_redirect \
		redirect_routine \
		env_routine \
		executing \
		builtin_echo \
		builtin_exit \
		builtin_cd \
		builtin_cd_chgdir \
		builtin_cd_create_newpath \
		builtin_cd_error \
		builtin_cd_two_arg \
		builtin_setenv \
		builtin_unsetenv \
		builtin_env \
		builtin_type


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