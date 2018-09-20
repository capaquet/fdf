/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 11:01:48 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/19 12:05:59 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define DATA_SIZ_IMG  data->size_image

static void			ft_correct_coord(t_data *data)
{
	int		border_x;
	int		border_y;
	t_list	*tmp_list;

	if (data->coef == 0 || data->key == 69 || data->key == 78)
		data->coef = data->min_max_iso[1] > data->min_max_iso[3]
		? DATA_SIZ_IMG / data->min_max_iso[1]
		: DATA_SIZ_IMG / data->min_max_iso[3];
	border_x = (SIZE_WIN - (data->coef * data->min_max_iso[1])) / 2;
	border_y = (SIZE_WIN - (data->coef * data->min_max_iso[3])) / 2;
	tmp_list = data->map;
	while (tmp_list)
	{
		((t_point*)tmp_list->content)->iso_x =
		(((t_point*)tmp_list->content)->iso_x
		* data->coef + border_x + data->move_x);
		((t_point*)tmp_list->content)->iso_y =
		(((t_point*)tmp_list->content)->iso_y
		* data->coef + border_y + data->move_y);
		tmp_list = tmp_list->next;
	}
	return ;
}

static void			ft_negative_coord(t_data *data, t_list *map)
{
	int		tmp;

	tmp = 0;
	while (map)
	{
		if (data->min_max_iso[0] < 0)
			((t_point*)map->content)->iso_x += -(data->min_max_iso[0]);
		if (data->min_max_iso[2] < 0)
			((t_point*)map->content)->iso_y += -(data->min_max_iso[2]);
		map = map->next;
	}
	if (data->min_max_iso[0] < 0)
	{
		tmp = data->min_max_iso[0];
		data->min_max_iso[0] += -tmp;
		data->min_max_iso[1] += -tmp;
	}
	if (data->min_max_iso[2] < 0)
	{
		tmp = data->min_max_iso[2];
		data->min_max_iso[2] += -tmp;
		data->min_max_iso[3] += -tmp;
	}
}

static void			ft_iso_point(t_data *data, t_point *point)
{
	point->iso_x = point->new_x - point->new_y;
	point->iso_y = (point->new_x + point->new_y - point->new_z) / 2;
	point->iso_z = point->new_z;
	point->iso_x < data->min_max_iso[0]
	? data->min_max_iso[0] = point->iso_x : 0;
	point->iso_x > data->min_max_iso[1]
	? data->min_max_iso[1] = point->iso_x : 0;
	point->iso_y < data->min_max_iso[2]
	? data->min_max_iso[2] = point->iso_y : 0;
	point->iso_y > data->min_max_iso[3]
	? data->min_max_iso[3] = point->iso_y : 0;
}

void				ft_isometric(t_data *data)
{
	t_list *map;

	map = data->map;
	data->min_max_iso[0] = SIZE_WIN + 1;
	data->min_max_iso[1] = -SIZE_WIN - 1;
	data->min_max_iso[2] = SIZE_WIN + 1;
	data->min_max_iso[3] = -SIZE_WIN - 1;
	while (map)
	{
		ft_iso_point(data, ((t_point*)map->content));
		map = map->next;
	}
	if (data->min_max_iso[0] < 0 || data->min_max_iso[2] < 0)
		ft_negative_coord(data, data->map);
	ft_correct_coord(data);
	draw_fdf(data, data->map);
}
