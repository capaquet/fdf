/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2019/07/31 14:32:55 by cpaquet          ###   ########.fr       */
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

static void		ft_draw_point_p(t_data *data, int x, int y, float intens)
{
	int		index;
	int		color;
	int		start_x;
	int		start_y;

	start_x = SIZE_IMAGE / 2 - (data->center_p_x * data->coef);
	start_y = SIZE_IMAGE / 2 - (data->center_p_y * data->coef);
	index = (start_y + y + data->move_y) * (4 * SIZE_IMAGE)
	+ (start_x + x + data->move_x) * 4;
	if (index <= 0 || index >= SIZE_IMAGE * SIZE_IMAGE * 4
	|| (start_x + x + data->move_x) >= SIZE_IMAGE
	|| (start_x + x + data->move_x) < 0)
		return ;
	//color = ft_color(data->min_p_y, data->max_p_y, y);
	color = 0xFFFFFF;
	data->image[index] = (color & 0xFF);
	data->image[index + 1] = (color & 0xFF00) >> 8;
	data->image[index + 2] = (color & 0xFF0000) >> 16;
	data->image[index + 3] = 255 * intens;
}

/*
** Delta X = la difference de X entre le point1 et le point2.
** Delta Y = la difference de Y entre le point1 et le point2.
** MOVE_X = 1 si la DELTA_X est positive, cad, si le point1 est plus haut que
** le point2
** MOVE_Y = 1 si la DELTA_Y est positive, cad, si le point1 est plus a a droite
** que le point2
** les 4 combinaisons de MOVE indiquent donc les 4 directions
*/

static void		ft_line_p_x(t_data *data, float tab[], int Yend)
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
		ft_draw_point_p(data, X, Y, 0);
		//ft_draw_point_p(data, (int)X, (int)Y, reverse_modulo(Y));
		if ((int)Y != Yend)
			ft_draw_point_p(data, (int)X, (int)Y + MOVE_Y, modulo(Y));
		i++;
	}
}

static void		ft_line_p_y(t_data *data, float tab[], int Yend)
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
		//ft_draw_point_p(data, X, Y, 0);
		//ft_draw_point_p(data, X, Y, reverse_modulo(Y));
		//ft_draw_point_p(data, X + MOVE_X, Y, modulo(Y));
		i++;
	}
}

void			ft_draw_line_p(t_data *data, t_point *point1, t_point *point2)
{
	float	tab[7];

	ft_bzero(&tab, sizeof(float) * 7);
	X = point1->p_x;
	Y = point1->p_y;
	DELTA_X = point2->p_x - point1->p_x;
	DELTA_Y = point2->p_y - point1->p_y;
	MOVE_X = (DELTA_X > 0) ? 1 : -1;
	MOVE_Y = (DELTA_Y > 0) ? 1 : -1;
	ft_fabs(&DELTA_X);
	ft_fabs(&DELTA_Y);
	//ft_draw_point_p(data, (int)X, (int)Y, reverse_modulo(Y));
	printf("max y = %f \n", point2->p_y);
	if (DELTA_X > DELTA_Y)
		ft_line_p_x(data, tab, (int)(point2->p_y * MOVE_Y));
	else
		ft_line_p_y(data, tab, (int)(point2->p_y * MOVE_Y));
}
