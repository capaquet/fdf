/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2019/01/26 15:59:28 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_list		*select_points(int nbr_x, t_list *point1)
{
	t_list	*under;

	under = point1->next;
	while (under && nbr_x > 1)
	{
		under = under->next;
		nbr_x--;
	}
	return (under);
}

static void			image(t_data *data)
{
	if (data->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx_ptr, SIZE_IMAGE, SIZE_IMAGE);
	data->image = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel,
	&data->size, &data->endian);
}

void				draw_fdf(t_data *data, t_list *map)
{
	int		nbr_point_line;
	t_list	*point;
	t_list	*under;
	t_list	*right;

	nbr_point_line = data->nbr_x;
	point = map;
	image(data);
	while (point)
	{
		if (nbr_point_line == 0)
			nbr_point_line = data->nbr_x;
		under = select_points(data->nbr_x, point);
		if (point && under)
			ft_draw_line(data, ((t_point*)point->content),
			((t_point*)under->content));
		right = point->next;
		if (point && right && nbr_point_line > 1)
			ft_draw_line(data, ((t_point*)point->content),
			((t_point*)right->content));
		point = point->next;
		nbr_point_line--;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->img_ptr, 100, 100);
}

void				draw_fdf_p(t_data *data, t_list *map)
{
	int		nbr_point_line;
	t_list	*point;
	t_list	*under;
	t_list	*right;

	nbr_point_line = data->nbr_x;
	point = map;
	image(data);
	while (point)
	{
		if (nbr_point_line == 0)
			nbr_point_line = data->nbr_x;
		under = select_points(data->nbr_x, point);
		if (point && under)
			ft_draw_line_p(data, ((t_point*)point->content),
			((t_point*)under->content));
		right = point->next;
		if (point && right && nbr_point_line > 1)
			ft_draw_line_p(data, ((t_point*)point->content),
			((t_point*)right->content));
		point = point->next;
		nbr_point_line--;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->img_ptr, 100, 100);
}
