/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:08 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/21 14:29:16 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		altitude(t_data *data, int key)
{
	if (key == 81)
		data->zoom_coef++;
	else
	{
		if (data->zoom_coef != 1)
			data->zoom_coef--;
	}
}

void		zoom(t_data *data, int key)
{
	float coef;

	coef = (float)(SIZE_IMAGE / 200) / (data->nbr_y > data->nbr_x
	? (float)data->nbr_y : (float)data->nbr_x);
	if (key == 69)
		data->coef += coef;
	else
		data->coef -= data->coef - coef > 0 ? coef : 0;
}

void		mouvement(t_data *data, int key)
{
	if (key == 124)
		data->move_x += 25;
	else if (key == 123)
		data->move_x -= 25;
	else if (key == 125)
		data->move_y += 25;
	else if (key == 126)
		data->move_y -= 25;
}

int			projection(int proj)
{
	if (proj == 0)
	{
		ft_putstr("Changement: Projection parallèle.\n");
		return (1);
	}
	else
	{
		ft_putstr("Changement: Projection isometrique.\n");
		return (0);
	}
}

void		reset(t_data *data)
{
	data->coef = (float)(SIZE_IMAGE / 4) / (data->nbr_y > data->nbr_x
	? (float)data->nbr_y : (float)data->nbr_x);
	data->move_x = 0;
	data->move_y = 0;
	data->rotation_x = 0;
	data->rotation_y = 0;
	data->rotation_z = 0;
	data->zoom_coef = 1;
}
