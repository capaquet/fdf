/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/27 18:24:05 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#define ABS(x) (x > 0 ? x : -x)

static void			ft_draw_point(t_data *data, int x, int y, float intens)
{
	int		index;
	int		color;
	int		start_x;
	int		start_y;

	start_x = SIZE_IMAGE /2 - (data->center_iso_x * data->coef);
	start_y = SIZE_IMAGE /2 - (data->center_iso_y * data->coef);
	index = (start_y + y) * (4 * SIZE_IMAGE) + (start_x + x) * 4;
	if (index < 0 || index >= SIZE_IMAGE * SIZE_IMAGE * 4 || (start_x + x) >= SIZE_IMAGE || (start_x + x) < 0)
		return;
//	color = 0xFFFFFF / (SIZE_IMAGE * SIZE_IMAGE* 4);
	color = 0xFFFFFF;
	data->image[index] = (color & 0xFF);
	data->image[index + 1] = (color & 0xFF00) >> 8;
	data->image[index + 2] = (color & 0xFF0000) >> 16;
	data->image[index + 3] = 255 * intens;

}

static float			modulo(float x)
{
	return(x - (int)x);
}

static float		reverse_modulo(float x)
{
	return(1 - modulo(x));
}

static  void		line3(t_data *data, float xi, float yi, float xf, float yf)
{
	float dx,dy,i,xinc,yinc,cumul,x,y;
	x = xi ;
	y = yi ;
	dx = xf - xi ;
	dy = yf - yi ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = fabs(dx) ;
	dy = fabs(dy) ;
	ft_draw_point(data, x, y, 0);

	if ( dx > dy )
	{
		cumul = dx / 2 ;
		for ( i = 1 ; i <= dx ; i++ )
		{
			x += xinc ;
			cumul += dy ;
			if ( cumul >= dx )
			{
				cumul -= dx ;
				y += yinc ;
			}
			ft_draw_point(data, x, y, modulo(y));
			ft_draw_point(data, x, y + yinc, reverse_modulo(y));
		}
	}
	else
	{
		cumul = dy / 2 ;
		for ( i = 1 ; i <= dy ; i++ )
		{
			y += yinc ;
			cumul += dx ;
			if ( cumul >= dy )
			{
				cumul -= dy ;
				x += xinc ;
			}
			ft_draw_point(data, x, y, modulo(y));
			ft_draw_point(data, x + xinc, y, reverse_modulo(y));
		}
	}
}

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

void	draw_fdf(t_data *data, t_list *map)
{
	int		nbr_point_line;
	t_list	*point;
	t_list	*under;
	t_list	*right;

	nbr_point_line = data->nbr_x;
	point = map;

int endian = 0;
int size = 0;
int bits_per_pixel = 0;

if (data->img_ptr)
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);
data->img_ptr = mlx_new_image(data->mlx_ptr, SIZE_IMAGE, SIZE_IMAGE);
data->image = mlx_get_data_addr(data->img_ptr, &bits_per_pixel, &size,  &endian);
	while (point)
	{
		if (nbr_point_line == 0)
			nbr_point_line = data->nbr_x;
		under = select_points(data->nbr_x, point);
		if (point && under)
			line3(data, ((t_point*)point->content)->iso_x, ((t_point*)point->content)->iso_y, ((t_point*)under->content)->iso_x, ((t_point*)under->content)->iso_y);
		right  = point->next;
		if (point && right && nbr_point_line > 1)
			line3(data, ((t_point*)point->content)->iso_x, ((t_point*)point->content)->iso_y, ((t_point*)right->content)->iso_x, ((t_point*)right->content)->iso_y);
		point = point->next;
		nbr_point_line--;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 100, 100);
}
