/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/19 14:13:31 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int		calcul_color(t_data *data, int y)
{
	int		color;

	color = 0xFFFFFF / SIZE_WIN;
	return (color * y);
}

static  void		line (t_data *data, int xi, int yi, int xf, int yf)
{
	int dx,dy,i,xinc,yinc,cumul,x,y ;
	x = xi ;
	y = yi ;
	dx = xf - xi ;
	dy = yf - yi ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = abs(dx) ;
	dy = abs(dy) ;
		mlx_pixel_put(data->mlx_ptr, data->win_i_ptr, x, y, calcul_color(data, y));
	if ( dx > dy )
	{
		cumul = dx / 2 ;
		for ( i = 1 ; i <= dx ; i++ )
		{
			x += xinc ;
			cumul += dy ;
			if ( cumul >= dx ) {
				cumul -= dx ;
				y += yinc ; }
				mlx_pixel_put(data->mlx_ptr, data->win_i_ptr, x, y, calcul_color(data, y));
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
				mlx_pixel_put(data->mlx_ptr, data->win_i_ptr, x, y, calcul_color(data, y)) ;
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
	while (point)
	{
		if (nbr_point_line == 0)
			nbr_point_line = data->nbr_x;
		under = select_points(data->nbr_x, point);
		if (point && under)
			line(data, ((t_point*)point->content)->iso_x, ((t_point*)point->content)->iso_y, ((t_point*)under->content)->iso_x, ((t_point*)under->content)->iso_y);
		
		right  = point->next;
		if (point && right && nbr_point_line > 1)
			line(data, ((t_point*)point->content)->iso_x, ((t_point*)point->content)->iso_y, ((t_point*)right->content)->iso_x, ((t_point*)right->content)->iso_y);
		point = point->next;
		nbr_point_line--;
	}
}
