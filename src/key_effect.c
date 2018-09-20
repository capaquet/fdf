/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:37:08 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/19 12:06:46 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		altitude(t_data *data)
{
	t_list *map;

	map = data->map;
	while (map)
	{
		if (((t_point*)map->content)->z != 0)
		{
			if (data->key == 81)
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

void		zoom(t_data *data)
{
	if (data->key == 69)
		data->size_image += 100;
	else
		data->size_image -= 100;
	data->size_image < 100 ? data->size_image = 100 : 0;
}

void		mouvement(t_data *data)
{
	if (data->key == 124)
		data->move_x += 25;
	else if (data->key == 123)
		data->move_x -= 25;
	else if (data->key == 125)
		data->move_y += 25;
	else if (data->key == 126)
		data->move_y -= 25;
}
