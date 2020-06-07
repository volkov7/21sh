/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letterpress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 14:07:13 by nriker            #+#    #+#             */
/*   Updated: 2020/05/18 01:13:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void		insert_print_string_hd(t_input *input)
// {
// 	char	*str;
// 	int		len;

// 	if (input->flag)
// 	{
// 		len = ft_strlen(&input->line[input->x - 7] + 1);
// 		str = ft_strnew(len);
// 		ft_putstr(ft_strncpy(str, &input->line[input->x - 8] + 1, len));
// 		// ft_putstr(ft_strncpy(str, &input->line[input->x - 7], ft_strlen(len)));
// 		free(str);
// 	}
// 	else
// 	{
// 		ft_printf("%d", input->x);
// 		ft_putstr(&input->line[input->x - 7]);
// 	}
// }

// void		insert_letter_between_hd(t_init *in, t_input *input, char buf[7])
// {
// 	int		x;
// 	int		y;

// 	ft_putchar(buf[0]);
// 	input->row = get_curs_row();
// 	insert_print_string_hd(input);
// 	if (!(input->width_hdoc % input->col) && input->row == input->li)
// 	{
// 		ft_putchar('\n');
// 		input->y--;
// 	}
// 	else if (!((input->x_hdoc) % input->col))
// 		input->y++;
// 	input->row = get_curs_row();
// 	ft_printf("\e[%d;%dH", input->y, (input->x_hdoc % input->col) + 1);
// }

// void		pressed_letter_hd(t_init *in, t_input *input, char buf[7])
// {
// 	if (input->x_hdoc < input->width_hdoc)
// 		insert_letter_between_hd(in, input, buf);
// 	else
// 	{
// 		ft_putchar(buf[0]);
// 		if (!((input->x_hdoc) % input->col))
// 			ft_putchar('\n');
// 		else if (input->width_hdoc == input->col && input->row == input->li)
// 		{
// 			ft_putchar('\n');
// 			input->y--;
// 		}
// 	}
// 	input->width_hdoc++;
// 	input->x_hdoc++;
// 	input->y = get_curs_col();
// 	input->row = input->y;
// }

int			letterpress(t_init *in, t_input *input, char buf[7])
{
	if (!check_letter(buf))
	{
		input->line = lineadd(&input->line, buf[0], input->x - input->index);
		if (!((input->width) % input->col) && !input->qt) //!!!!!!!!!!!added !input->qt
			input->lines_in_com++;
		if ((!((input->width) % input->col)) && !input->qt) //!!!!!!!!!!added !input->qt
			if (input->row < input->li)
				input->row++;
		if (input->flag)
			input->flag_qt = 0;
		// if (!((input->x_quote) % input->col))
		// 	input->lines_in_com++;
		if (!input->qt/* && !input->hdoc*/)
			pressed_letter(in, input, buf);
		// else if (input->hdoc)
		// 	pressed_letter_hd(in, input, buf);
		else
			pressed_letter_q(in, input, buf);
		input->y = get_curs_row();
		input->width++;
		input->x++;
	}
	return (1);
}
