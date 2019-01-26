/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:28:06 by cpaquet           #+#    #+#             */
/*   Updated: 2019/01/26 15:45:16 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void				free_point(void *point, size_t size)
{
	size = 0;
	if (point)
		free(point);
}

static int				key(int key, t_data *data)
{
	static int proj = 0;

	if (key == 53)
		quit(data);
	if (key == 81 || key == 75)
		altitude(data, key);
	else if (key == 69 || key == 78)
		zoom(data, key);
	else if (key == 126 || key == 125 || key == 123 || key == 124)
		mouvement(data, key);
	rotate(data, &key);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == 87)
		proj = proj == 0 ? 1 : 0;
	if (proj == 0)
	{
		ft_isometric(data);
		draw_fdf(data, data->map);
	}
	else
	{
		ft_parallel(data);
		draw_fdf_p(data, data->map);
	}
	return (1);
}

static void				ft_window(t_data *data)
{
	if (!(data->mlx_ptr = mlx_init()))
		ft_error(data, "Error system in mlx_init");
	if (!(data->win_ptr =
	mlx_new_window(data->mlx_ptr, SIZE_WIN, SIZE_WIN, "FDF")))
		ft_error(data, "Error system in new_window");
}

void					quit(t_data *data)
{
	if (data->win_ptr)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	if (data->map != NULL)
		ft_lstdel(&data->map, free_point);
	exit(EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	t_data	data;

	errno = 0;
	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
		ft_error(&data, "Invalid parameter");
	ft_read_file(&data, argv);
	data.coef = (float)(SIZE_IMAGE / 4) / (data.nbr_y > data.nbr_x ?
	(float)data.nbr_y : (float)data.nbr_x);
	ft_calcul_center_iso(&data);
	ft_calcul_center_p(&data);
	ft_window(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key, &data);
	mlx_do_key_autorepeaton(data.mlx_ptr);
	mlx_loop(data.mlx_ptr);
	exit(EXIT_SUCCESS);
}
