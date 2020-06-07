/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:27:21 by nriker            #+#    #+#             */
/*   Updated: 2020/05/24 10:52:08 by root             ###   ########.fr       */
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

# define	GETCURSORPOS	"\e[6n"
// # define	PRINT_COMMAND	1
// # define	PRINT_QT_HDOC	2
// # define	F_OK			0	/* test for existence of file */
// # define	X_OK			(1<<0)	/* test for execute or search permission */


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
	char	*line; //Строка с командой, вводимая пользователем
	int		flag;
	int		dflag;
	char	*word;
	int		list_size;
	int		tab_row;
	int		p_tab;
	int		p_tab_part;
	int		c; //Free const - you can use it anywhere
	int		c2;
	int		qt; //Флаг обозначает, что в данной команде исользуется либо ', либо "
	int		quote; //Флаг обозначает, что в команде используется '
	int		dquote; //Флаг обозначает, что в команде используется "
	int		x_quote; //Положение курсора в колонке в режиме с '
	int		width_quote;//Ширина (количество введенных символов) команды в режиме '
	int		x_dquote; //Положение курсора в колонке в режиме с "
	int		width_dquote; //Ширина (количество введенных символов) команды в режиме "
	int		width; //Ширина (количество введенных символов) команды
	int		len;
	int		len_x;
	int		x; //Положение курсора в колонке в терминале
	int		y; //Положение курсора в строке в терминале
	int		row; //Общее количество строк, задействованных при вводе одной команды
	int		col; //количество колонок в строке терминала
	int		li; // количество линий в терминале
	int		old_row;
	int		old;
	int		o;
	int		f;
	int		lines_in_com;
	int		lines_in_qt;
	int		qlines_in_com;
	int		dqlines_in_com;
	// int		qt_str; //количество строк в одной команде qt
	int		sub_qt;
	int		save_x; //Сохранить положение курсора при пролистывании истории - если курсор сместился от конца команды
	int		len_qt; //на сколько отступать при quotes 
	int		flag_qt;
	int		sx; //при получении части слова при TAB - координаты
	int		sy;
	char	**path_dirs; //Двойной массив из названий директорий/файлов - необходимо при TAB
	t_input	*next; //Следующий элемент в истории команд
	t_input	*prev; //Предыдущий элемент в истории команд
	int		exec_firstword; //Flag in TAB. First word if command begin with ./
	int		hdoc;  //flag for using heredoc
	// int		x_hdoc; //x for heredoc
	// int		width_hdoc;
	// int		lines_in_hdoc;
	int		index; //flag for lineadd
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
void					press_tab(t_init *in, t_input *input);
int						check_firstword(t_input *input);
int						check_partword(t_input *input);
char					*get_partword(t_input *input);
int						check_firstword_q(t_input *input);
int						check_partword_q(t_input *input);
char					*get_partword_q(t_input *input);
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
// void					return_cursor(t_init *in, t_input *input, t_column *cl);
void					clear_tab_output(t_init *in, t_input *input);
char					*cut_freestrend(char **line);
int						check_qfirstword(t_input *input, int x);
void					free_buf(char **buf);
int						get_curs_row(void);
int						get_curs_col(void);
int						check_quotes(t_input *input);
int						letterpress(t_init *in, t_input *input, char buf[7]);
int						check_letter(char buf[7]);
void					pressed_letter(t_init *in, t_input *input, char buf[7]);
void					pressed_letter_q(t_init *in, t_input *input, char buf[7]);
// int						keypress(t_init *in, t_input *input, char buf[7]);
t_input					*arrowpress(t_init *in, t_input *input, char buf[7]);
t_input					*up_sub(t_init *in, t_input *input, char buf[7]);
t_input					*down_sub(t_init *in, t_input *input, char buf[7]);
void					up_sub_qt(t_input *input);
void					down_sub_qt(t_input *input);
int						sub_get_x(t_input *input, int flag);
int						get_curs_pos_inend(t_input *input);
void					return_curstostart_str(t_input *input, int x);
void					return_curstox(t_input *input);
void					return_curstox_qt(t_input *input);
void					print_suggestion(t_input *input);
int						check_point_slesh(t_input * input, char *line, int x);
// void					curstostart_str(t_input *input);
// void					cursor_tostart_str(t_input *input);
void					fill_new_input(t_input *input);
t_input					*copy_struct_history(t_input *copy, t_input *input);
int						get_len_of_line(t_input *input);
int						specialletter_press(t_init *in, t_input *input, char buf[7]);
// void					ft_putnstr(char *line, int len);
char					*read_input_heredoc(t_init *in, t_input *input, int x);
int						delete_press(t_init *in, t_input *input, char buf[7]);
int						specialpress(t_init *in, t_input *input, char buf[7]);
int						enter_press(t_init *in, t_input *input, char buf[7]);
void					fill_input_params_hd(t_input *input);
int						specialpress(t_init *in, t_input *input, char buf[7]);
int						check_flag_qt(t_input *input);
t_input					*insert_history_line(t_input *input);

#endif
