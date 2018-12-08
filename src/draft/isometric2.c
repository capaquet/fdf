/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:01:48 by cpaquet           #+#    #+#             */
/*   Updated: 2018/10/24 12:41:52 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				ft_isometric(t_data *data)
{
	t_list *map;

	map = data->map;
	data->min_iso_y = 0;
	data->max_iso_y = 0;
	while (map)
	{
		((t_point*)map->content)->iso_x = (((t_point*)map->content)->new_x
		- ((t_point*)map->content)->new_y) * data->coef;
		((t_point*)map->content)->iso_y = ((((t_point*)map->content)->new_x
		+ ((t_point*)map->content)->new_y - ((t_point*)map->content)->new_z)
		/ 2) * data->coef;
		data->min_iso_y > ((t_point*)map->content)->z
		? data->min_iso_y = ((t_point*)map->content)->z : 0;
		data->max_iso_y < ((t_point*)map->content)->z
		? data->max_iso_y = ((t_point*)map->content)->z : 0;
		map = map->next;
	}
}

void				ft_calcul_center_iso(t_data *data)
{
	t_list	*map;
	int		nbr;

	map = data->map;
	nbr = 0;
	while (map)
	{
		data->center_iso_x += (((t_point*)map->content)->new_x
		- ((t_point*)map->content)->new_y);
		data->center_iso_y += ((((t_point*)map->content)->new_x
		+ ((t_point*)map->content)->new_y - ((t_point*)map->content)->new_z)
		/ 2) + data->move_y;
		nbr++;
		map = map->next;
	}
	nbr != 0 ? data->center_iso_x /= nbr : 0;
	nbr != 0 ? data->center_iso_y /= nbr : 0;
}
