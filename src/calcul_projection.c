/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:01:48 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/21 13:59:28 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				ft_isometric(t_data *data)
{
	t_list *map;

	map = data->map;
	data->min_y = 0;
	data->max_y = 0;
	while (map)
	{
		((t_point*)map->content)->final_x = (((t_point*)map->content)->new_x
		- ((t_point*)map->content)->new_y) * data->coef;
		((t_point*)map->content)->final_y =
		((((t_point*)map->content)->new_z * (1 + ZOOM_VALUE * data->zoom_coef))
		+ ((((t_point*)map->content)->new_x + ((t_point*)map->content)->new_y))
		/ 2) * data->coef;
		data->min_y > ((t_point*)map->content)->final_y
		? data->min_y = ((t_point*)map->content)->final_y : 0;
		data->max_y < ((t_point*)map->content)->final_y
		? data->max_y = ((t_point*)map->content)->final_y : 0;
		map = map->next;
	}
}

void				ft_parallel(t_data *data)
{
	t_list *map;

	map = data->map;
	data->min_y = 0;
	data->max_y = 0;
	while (map)
	{
		((t_point*)map->content)->final_x = (((t_point*)map->content)->new_x
		+ ((t_point*)map->content)->new_z * (1 + ZOOM_VALUE * data->zoom_coef))
		* data->coef;
		((t_point*)map->content)->final_y =
		(((t_point*)map->content)->new_y + ((t_point*)map->content)->new_z
		* (1 + ZOOM_VALUE * data->zoom_coef) / 2) * data->coef;
		data->min_y > ((t_point*)map->content)->final_y
		? data->min_y = ((t_point*)map->content)->final_y : 0;
		data->max_y < ((t_point*)map->content)->final_y
		? data->max_y = ((t_point*)map->content)->final_y : 0;
		map = map->next;
	}
}

void				ft_calcul_center(t_data *data)
{
	t_list	*map;
	int		nbr;

	map = data->map;
	nbr = 0;
	while (map)
	{
		data->center_x += ((t_point*)map->content)->final_x;
		data->center_y += ((t_point*)map->content)->final_y;
		nbr++;
		map = map->next;
	}
	nbr != 0 ? data->center_x /= nbr : 0;
	nbr != 0 ? data->center_y /= nbr : 0;
}
