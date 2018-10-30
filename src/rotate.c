/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:22:17 by cpaquet           #+#    #+#             */
/*   Updated: 2018/10/30 15:12:56 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define DATA_MAP ((t_point*)map->content)

static void		rotate_x(float *new_coord, int *key)
{
	double			tab[3];
	static int		rotation_x = 0;

	*key == 92 ? rotation_x++ : 0;
	*key == 89 ? rotation_x-- : 0;
	*key == 92 || *key == 89 ? *key = 0 : 0;
	ft_bzero(&tab, sizeof(tab));
	rotation_x = rotation_x == 181 ? 1 : rotation_x;
	rotation_x = rotation_x == -1 ? 179 : rotation_x;
	tab[0] = new_coord[0];
	tab[1] = 0 + cos((PI / 180) * rotation_x) * new_coord[1]
	- sin((PI / 180) * rotation_x) * new_coord[2];
	tab[2] = 0 + sin((PI / 180) * rotation_x) * new_coord[1]
	+ cos((PI / 180) * rotation_x) * new_coord[2];
	new_coord[0] = tab[0];
	new_coord[1] = tab[1];
	new_coord[2] = tab[2];
}

static void		rotate_y(float *new_coord, int *key)
{
	double			tab[3];
	static int		rotation_y = 0;

	*key == 84 ? rotation_y++ : 0;
	*key == 91 ? rotation_y-- : 0;
	*key == 84 || *key == 91 ? *key = 0 : 0;
	ft_bzero(&tab, sizeof(tab));
	rotation_y = rotation_y == 181 ? 1 : rotation_y;
	rotation_y = rotation_y == -1 ? 179 : rotation_y;
	tab[0] = cos((PI / 180) * rotation_y) * new_coord[0]
	+ sin((PI / 180) * rotation_y) * new_coord[2];
	tab[1] = new_coord[1];
	tab[2] = -sin((PI / 180) * rotation_y) * new_coord[0]
	+ cos((PI / 180) * rotation_y) * new_coord[2];
	new_coord[0] = tab[0];
	new_coord[1] = tab[1];
	new_coord[2] = tab[2];
}

static void		rotate_z(float *new_coord, int *key)
{
	float			tab[3];
	static int		rotation_z = 0;

	*key == 86 ? rotation_z++ : 0;
	*key == 88 ? rotation_z-- : 0;
	*key == 86 || *key == 88 ? *key = 0 : 0;
	ft_bzero(&tab, sizeof(tab));
	rotation_z = rotation_z == 181 ? 1 : rotation_z;
	rotation_z = rotation_z == -1 ? 179 : rotation_z;
	tab[0] = cos((PI / 180) * rotation_z) * new_coord[0]
	- sin((PI / 180) * rotation_z) * new_coord[1];
	tab[1] = sin((PI / 180) * rotation_z) * new_coord[0]
	+ cos((PI / 180) * rotation_z) * new_coord[1];
	tab[2] = new_coord[2];
	new_coord[0] = tab[0];
	new_coord[1] = tab[1];
	new_coord[2] = tab[2];
}

static void		copy_coord(t_list *point, float *new_coord, char code,
															t_data *data)
{
	if (code == 1)
	{
		new_coord[0] = ((t_point*)point->content)->x - data->center_rotat_x;
		new_coord[1] = ((t_point*)point->content)->y - data->center_rotat_y;
		new_coord[2] = ((t_point*)point->content)->z;
	}
	else if (code == 2)
	{
		((t_point*)point->content)->new_x = new_coord[0] + data->center_rotat_x;
		((t_point*)point->content)->new_y = new_coord[1] + data->center_rotat_y;
		((t_point*)point->content)->new_z = new_coord[2];
	}
}

void			rotate(t_data *data, int *key)
{
	t_list		*map;
	float		*coord;

	coord = NULL;
	map = data->map;
	if (!(coord = (float*)malloc(sizeof(float) * 3)))
		ft_error(data, "Error system in rotate function");
	while (map)
	{
		ft_bzero(coord, sizeof(float) * 3);
		copy_coord(map, coord, 1, data);
		rotate_x(coord, key);
		rotate_y(coord, key);
		rotate_z(coord, key);
		copy_coord(map, coord, 2, data);
		map = map->next;
	}
	if (coord)
		free(coord);
}
