/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:08 by cpaquet           #+#    #+#             */
/*   Updated: 2019/07/31 14:35:00 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		altitude(t_data *data, int key)
{
	t_list *map;

	map = data->map;
	while (map)
	{
		if (((t_point*)map->content)->z != 0)
		{
			if (key == 81)
			{
				if (((t_point*)map->content)->z == -1)
					((t_point*)map->content)->z += 2;
				else
					((t_point*)map->content)->z += 1;
			}
			else
			{
				if (((t_point*)map->content)->z == 1)
					((t_point*)map->content)->z -= 2;
				else
					((t_point*)map->content)->z -= 1;
			}
		}
		map = map->next;
	}
}

void		zoom(t_data *data, int key)
{
	float coef;

	coef = (float)(SIZE_IMAGE / 50) / (data->nbr_y > data->nbr_x
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
