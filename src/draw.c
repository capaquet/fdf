/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2018/10/12 16:15:01 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#define DELTA_X	tab[0]
#define DELTA_Y	tab[1]
#define MOVE_X	tab[2]
#define MOVE_Y	tab[3]
#define CUMUL	tab[4]
#define X		tab[5]
#define Y		tab[6]

static void			ft_draw_point(t_data *data, int x, int y, float intens)
{
	int		index;
	int		color;
	int		start_x;
	int		start_y;

	start_x = SIZE_IMAGE / 2 - (data->center_iso_x * data->coef);
	start_y = SIZE_IMAGE / 2 - (data->center_iso_y * data->coef);
	index = (start_y + y + data->move_y) * (4 * SIZE_IMAGE)
	+ (start_x + x + data->move_x) * 4;
	if (index <= 0 || index >= SIZE_IMAGE * SIZE_IMAGE * 4
	|| (start_x + x + data->move_x) >= SIZE_IMAGE
	|| (start_x + x + data->move_x) < 0)
		return ;
	color = ft_color(data->min_iso_y, data->max_iso_y, y);
	data->image[index] = (color & 0xFF);
	data->image[index + 1] = (color & 0xFF00) >> 8;
	data->image[index + 2] = (color & 0xFF0000) >> 16;
	data->image[index + 3] = 255 * intens;
}

static void			ft_line_x(t_data *data, float tab[])
{
	float i;

	i = 1;
	CUMUL = DELTA_X / 2;
	while (i <= DELTA_X)
	{
		X += MOVE_X;
		CUMUL += DELTA_Y;
		if (CUMUL >= DELTA_X)
		{
			CUMUL -= DELTA_X;
			Y += MOVE_Y;
		}
		ft_draw_point(data, X, Y, modulo(Y));
		ft_draw_point(data, X, Y + MOVE_Y, reverse_modulo(Y));
		i++;
	}
}

static void			ft_line_y(t_data *data, float tab[])
{
	float i;

	i = 1;
	CUMUL = DELTA_Y / 2;
	while (i <= DELTA_Y)
	{
		Y += MOVE_Y;
		CUMUL += DELTA_X;
		if (CUMUL >= DELTA_Y)
		{
			CUMUL -= DELTA_Y;
			X += MOVE_X;
		}
		ft_draw_point(data, X, Y, modulo(Y));
		ft_draw_point(data, X + MOVE_X, Y, reverse_modulo(Y));
		i++;
	}
}

void				ft_draw_line(t_data *data, t_point *point1, t_point *point2)
{
	float	tab[7];

	ft_bzero(&tab, sizeof(float) * 7);
	X = point1->iso_x;
	Y = point1->iso_y;
	DELTA_X = point2->iso_x - point1->iso_x;
	DELTA_Y = point2->iso_y - point1->iso_y;
	MOVE_X = (DELTA_X > 0) ? 1 : -1;
	MOVE_Y = (DELTA_Y > 0) ? 1 : -1;
	ft_fabs(&DELTA_X);
	ft_fabs(&DELTA_Y);
	ft_draw_point(data, X, Y, 0);
	if (DELTA_X > DELTA_Y)
		ft_line_x(data, tab);
	else
		ft_line_y(data, tab);
}
