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
		builtin_type \
		main \
		create_init \
		create_input \
		create_story \
		free_init \
		free_input \
		putchar_select \
		input_read \
		return_terminal \
		sig_exit \
		ft_error_select \
		lineadd \
		lineremove \
		copyinput \
		copylastinput \
		press_tab \
		check_tab \
		check_tab_q\
		tab_list \
		tab_insert_word \
		tab_insert_word_q \
		get_buf21sh \
		get_buf_path \
		create_column \
		get_size_of_columns \
		print_column \
		qs \
		return_cursor \
		return_cursor_2 \
		clear_tab_output \
		cut_freestrend \
		free_buf \
		get_cursor_row \
		get_cursor_col \
		check_quotes \
		keypress \
		letterpress \
		check_letters \
		pressed_letter \
		arrowpress \
		arrow_substitution \
		arrow_substitution_qt \
		sub_get_x \
		fill_new_input \
		read_input_heredoc \
		fill_input_params_hd \
		specialpress \


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
	@gcc $(OBJ) $(HEADER) -o $(NAME) $(LIB) -ltermcap
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