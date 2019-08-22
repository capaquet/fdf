/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/21 14:54:00 by cpaquet          ###   ########.fr       */
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

void				ft_draw_point(t_data *data, int x, int y)
{
	int		index;
	int		color;
	int		start_x;
	int		start_y;

	start_x = SIZE_IMAGE / 2 - (data->center_x);
	start_y = SIZE_IMAGE / 2 - (data->center_y);
	index = (start_y + y + data->move_y) * (4 * SIZE_IMAGE)
	+ (start_x + x + data->move_x) * 4;
	if (index <= 0 || index >= SIZE_IMAGE * SIZE_IMAGE * 4
	|| (start_x + x + data->move_x) >= SIZE_IMAGE
	|| (start_x + x + data->move_x) < 0)
		return ;
	if (data->max_y - data->min_y != 0)
		color = ft_color(data->min_y, data->max_y, y);
	else
		color = 0xFFFFFFFF;
	data->image[index] = (color & 0xFF);
	data->image[index + 1] = (color & 0xFF00) >> 8;
	data->image[index + 2] = (color & 0xFF0000) >> 16;
	data->image[index + 3] = 0;
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
		ft_draw_point(data, X, Y);
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
		ft_draw_point(data, X, Y);
		i++;
	}
}

void				ft_draw_line(t_data *data, t_point *point1, t_point *point2)
{
	float	tab[7];

	ft_bzero(&tab, sizeof(float) * 7);
	X = point1->final_x;
	Y = point1->final_y;
	DELTA_X = point2->final_x - point1->final_x;
	DELTA_Y = point2->final_y - point1->final_y;
	MOVE_X = (DELTA_X > 0) ? 1 : -1;
	MOVE_Y = (DELTA_Y > 0) ? 1 : -1;
	ft_fabs(&DELTA_X);
	ft_fabs(&DELTA_Y);
	ft_draw_point(data, X, Y);
	if (DELTA_X > DELTA_Y)
		ft_line_x(data, tab);
	else
		ft_line_y(data, tab);
}
