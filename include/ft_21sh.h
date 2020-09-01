/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:27:21 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:44:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H

# include "ft_printf.h"
# include <signal.h>
# include <term.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <stdbool.h>

# define GETCURSORPOS "\e[6n"

typedef struct s_column	t_column;

struct					s_column
{
	int			col;
	int			row;
	int			buf_size;
	int			max_width;
	int			width_column;
	int			col_got;
	int			row_got;
};

/*
** Struct for save of input before parsing.
*/

typedef struct s_input	t_input;

struct					s_input
{
	char	*line;
	int		flag;
	int		dflag;
	char	*word;
	int		list_size;
	int		tab_row;
	int		p_tab;
	int		p_tab_part;
	int		c;
	int		c2;
	int		qt;
	int		quote;
	int		dquote;
	int		x_quote;
	int		width_quote;
	int		x_dquote;
	int		width_dquote;
	int		width;
	int		len;
	int		len_x;
	int		x;
	int		y;
	int		row;
	int		col;
	int		li;
	int		old_row;
	int		old;
	int		o;
	int		f;
	int		lines_in_com;
	int		lines_in_qt;
	int		qlines_in_com;
	int		dqlines_in_com;
	int		sub_qt;
	int		save_x;
	int		len_qt;
	int		flag_qt;
	int		sx;
	int		sy;
	char	**path_dirs;
	t_input	*next;
	t_input	*prev;
	int		exec_firstword;
	int		hdoc;
	int		heredok;
	int		small_heredok;
	int		big_heredok;
	int		index;
	pid_t	killing_child_pid;
	int		pressed_ctrl_d;
	t_input	*input_original;
	char	*ctrl_d_line;
};

/*
** Struct for history of commands
*/

typedef struct s_story	t_story;

struct					s_story
{
	int		quotes;
	char	*line;
	t_story	*next;
};

typedef struct			s_init
{
	int				col;
	t_input			*input;
	struct termios	tr;
	struct termios	old_tr;
	int				nb;
	int				fd;
	int				call;
	int				row;
	int				bad_window;
	char			*terminal;
}						t_init;

void					ft_error_select(int x);
void					create_init(t_init *in);
t_input					*create_input();
t_story					*create_story();
void					free_init(t_init *in);
void					free_input(t_input *input);
void					free_story(t_story *story);
int						putchar_select(int c);
t_input					*read_input(t_init *in, t_input *input);
void					return_terminal(t_init *in);
void					signals(void);
void					sig_exit(int x);
t_init					*get_i(t_init *str);
char					*lineadd(char **line, char c, int index);
char					*lineremove(char *line, int index);
char					*lineremove_2(char*line, int index);
void					storyadd(t_init *in);
t_input					*copyinput(t_input *input);
t_input					*copylastinput(t_input *copy);
void					press_tab(t_input *input);
int						check_firstword(t_input *input);
int						check_partword(t_input *input);
char					*get_partword(t_input *input);
int						check_firstword_q(t_input *input);
int						check_partword_q(t_input *input);
int						check_tabparse(t_input *input, int x, int z);
int						get_firstword(t_input *input);
void					tab_list(t_input *input, char **buf);
void					tab_insert_word(t_input *input, char **buf);
void					tab_insert_word_q(t_input *input, char **buf);
char					**get_buf21sh(t_input *input);
char					**get_buf_path(t_input *input);
void					create_column(t_column **cl);
void					get_size_of_columns(char **buf, t_column *cl);
void					print_column(char **buf, t_column *cl);
void					qs(char **buf, int size, int first, int last);
void					clear_tab_output(t_init *in, t_input *input);
char					*cut_freestrend(char **line);
int						check_qfirstword(t_input *input, int x);
void					free_buf(char **buf);
int						get_curs_row(void);
int						get_curs_col(void);
int						check_quotes(t_input *input);
int						letterpress(t_init *in, t_input *input, char buf[7]);
int						check_letter(char buf[7]);
void					pressed_letter(t_input *input, char buf[7]);
void					pressed_letter_q(t_input *input, char buf[7]);
t_input					*arrowpress(t_input *input, char buf[7]);
t_input					*up_sub(t_input *input);
t_input					*down_sub(t_input *input);
void					up_sub_qt(t_input *input);
void					down_sub_qt(t_input *input);
int						sub_get_x(t_input *input, int flag);
int						get_curs_pos_inend(t_input *input);
void					return_curstostart_str(t_input *input, int x);
void					return_curstox(t_input *input);
void					return_curstox_qt(t_input *input);
void					print_suggestion(t_input *input);
int						check_point_slesh(t_input *input, char *line, int x);
void					fill_new_input(t_input *input);
t_input					*copy_struct_history(t_input *copy, t_input *input);
int						get_len_of_line(t_input *input);
int						specialletter_press(t_init *in, t_input *input,
							char buf[7]);
void					read_input_heredoc(t_init *in, t_input *input, int x,
							int ds);
int						delete_press(t_input *input, char buf[7]);
int						specialpress(t_input *input, char buf[7]);
int						enter_press(t_input *input, char buf[7]);
void					fill_input_params_hd(t_input *input);
int						check_flag_qt(t_input *input);
t_input					*insert_history_line(t_input *input);
void					print_history(t_input *input, char *str, int x);
void					return_cursor_when_ctrl_c(t_input *input);
t_input					*get_input(t_input *str);
void					main_cycle(t_init *in, t_input *input);
void					change_size_of_window(t_input *input);
t_input					*cycle_first_input(t_init *in);
t_input					*cycle_other_input(t_init *in, t_input *input);
int						check_command(t_input *input);
void					create_input_ctrl_c(t_input *input);
void					check_qt(t_input *input);
t_input					*arrow_substitution_up(t_input *input);
t_input					*arrow_substitution_down(t_input *input);
void					clear_last_input(t_input *input);
void					pressed_letter_q_history(t_input *input, char buf[7]);
void					pressed_clear_window(t_input *input);
void					pressed_home(t_input *input);
void					pressed_end(t_input *input);
void					pressed_prev_word(t_input *input);
void					pressed_second_word(t_input *input);
void					pressed_start_string(t_input *input);
void					pressed_end_string(t_input *input);
void					get_command_params_qt(t_input *input,
											t_input *old_input, int len);
void					enter_press_heredok(t_input *input);
void					press_left(t_input *input);
void					press_right(t_input *input);
int						pressed_ctrl_d_heredok(t_input *input);
void					insert_print_string(t_input *input);
void					print_letter_q(t_input *input, char buf[7]);
void					delete_history_qt_between(t_input *input);
void					delete_history_qt_between_x(t_input *input);
void					delete_letter(t_input *input);
void					delete_letter_x(t_input *input);
void					delete_letter_x_col(t_input *input);
void					delete_quote(t_input *input);
void					delete_dquote(t_input *input);
void					set_cursor_prev_line(t_input *input);
void					set_cursor_next_line(t_input *input);
int						get_len_next_line_qt(t_input *input);
void					insert_letter_betweenhistory(t_input *input,
												char buf[7]);

#endif
