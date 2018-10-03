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




/*
static void			ft_draw_point(t_data *data, int x, int y)
{
	int		index;
	int		color;
	int		start_x;
	int		start_y;

	start_x = SIZE_IMAGE /2 - (data->center_iso_x * data->coef);
	start_y = SIZE_IMAGE /2 - (data->center_iso_y * data->coef);
	index = (start_y + y) * (4 * SIZE_IMAGE) + (start_x + x) * 4;
	if (index < 0 || index >= SIZE_IMAGE * SIZE_IMAGE * 4)
		return;
	color = 0xFFFFFF / (SIZE_IMAGE * SIZE_IMAGE* 4);
	color *= index;
	data->image[index] = (color & 0xFF);
	data->image[index + 1] = (color & 0xFF00) >> 8;
	data->image[index + 2] = (color & 0xFF0000) >> 16;
	data->image[index + 3] = 0;
	// data->image[index] = (255 / data->nbr_x) * x;
	// data->image[index + 1] = (255 / data->nbr_y) * y;
	// data->image[index + 2] = (255 / data->nbr_z) * data->nbr_z;
	// data->image[index + 3] = 0;
}

static  void		line (t_data *data, int xi, int yi, int xf, int yf)
{
	int dx,dy,i,xinc,yinc,cumul,x,y;
	x = xi ;
	y = yi ;
	dx = xf - xi ;
	dy = yf - yi ;
	xinc = ( dx > 0 ) ? 1 : -1 ;
	yinc = ( dy > 0 ) ? 1 : -1 ;
	dx = abs(dx) ;
	dy = abs(dy) ;
	ft_draw_point(data, x, y);
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
			ft_draw_point(data, x, y);
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
			ft_draw_point(data, x, y);
		}
	}
}
*/

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
	// data->image[index] = (255 / data->nbr_x) * x;
	// data->image[index + 1] = (255 / data->nbr_y) * y;
	// data->image[index + 2] = (255 / data->nbr_z) * data->nbr_z;
	// data->image[index + 3] = 0;
}
/*
static int			arrondi(float x)
{
	return(x + 0.5);
}
*/
static float			modulo(float x)
{
	return(x - (int)x);
}

static float		reverse_modulo(float x)
{
	return(1 - modulo(x));
}
/*
static void				swap(int *x1, int *x2)
{
	int tmp;

	tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
}
*/
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
			ft_draw_point(data, x, y + 1, reverse_modulo(y));
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
			ft_draw_point(data, x + 1, y, reverse_modulo(y));
		}
	}
}

/*
static void			line2(t_data *data, int x1, int x2, int y1, int y2)
{
	float	delta_x;
	float	delta_y;

	float	xend;
	float	yend;

	float	xgap;

	float	xpxl1;
	float	ypxl1;

	float	xpxl2;
	float	ypxl2;
	
	float	gradient;

	float	croisement;

	float	x;

	delta_x = x2 -x1;
	delta_y = y2 - y1;


	if (ABS(delta_x) > ABS(delta_y))
	{
		x2 > x1 ? swap(&x1, &x2) : 0;
		gradient = delta_y / delta_x;
		xend = arrondi(x1); //c'est un int. Besoin d'arrondir ?
		yend = y1 + gradient * (xend - x1);
		xgap = inverse_modulo(x1 + 0.5); //c'est un int. Besoin d'arrondir ?
		xpxl1 = xend;
		ypxl1 = (int)(yend);
		ft_draw_point(data, xpxl1, ypxl1, inverse_modulo(yend) * xgap);
		ft_draw_point(data, xpxl1, ypxl1 + 1, modulo(yend) * xgap);
		croisement = yend + gradient;


		xend = arrondi(x2); //c'est un int. Besoin d'arrondir ?
		yend = y2 + gradient * (xend - x2);
		xgap = inverse_modulo(x2 + 0.5); //c'est un int. Besoin d'arrondir ?
		ypxl2 = (int)(yend);
		ft_draw_point(data, xpxl2, ypxl2, inverse_modulo(yend) * xgap);
		ft_draw_point(data, xpxl2, ypxl2 + 1, modulo(yend) * xgap);

		while (xpxl1 != xpxl2)
		{
			x = xpxl1;

			printf("x1= %d    y1=%d \n", (int)croisement, inverse_modulo(croisement));
			ft_draw_point(data, x, (int)croisement, inverse_modulo(croisement));
			printf("x2= %d    y2=%d \n",(int)croisement + 1, modulo(croisement));
			ft_draw_point(data, x, (int)croisement + 1, modulo(croisement));
			xpxl1++;
			xpxl2--;
		}
	}
	else
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
		x2 > x1 ? swap(&x1, &x2) : 0;

printf("delta x = %f   delta y = %f \n", delta_x, delta_y);
		gradient = delta_y / delta_x;
printf("gradient = %f\n", gradient);
		xend = arrondi(x1); //c'est un int. Besoin d'arrondir ?
		yend = y1 + gradient * (xend - x1);
		xgap = inverse_modulo(x1 + 0.5); //c'est un int. Besoin d'arrondir ?
		xpxl1 = xend;
		ypxl1 = (int)(yend);
		ft_draw_point(data, xpxl1, ypxl1, inverse_modulo(yend) * xgap);
		ft_draw_point(data, xpxl1, ypxl1 + 1, modulo(yend) * xgap);

printf("yend = %f\n", yend);
		croisement = yend + gradient;
printf("croisement = %f\n", croisement);

		xend = arrondi(x2); //c'est un int. Besoin d'arrondir ?
		yend = y2 + gradient * (xend - x2);
		xgap = inverse_modulo(x2 + 0.5); //c'est un int. Besoin d'arrondir ?
		ypxl2 = (int)(yend);
		ft_draw_point(data, xpxl2, ypxl2, inverse_modulo(yend) * xgap);
		ft_draw_point(data, xpxl2, ypxl2 + 1, modulo(yend) * xgap);

		while (xpxl1 != xpxl2)
		{
			x = xpxl1;
			printf("x1= %f    y1=%f \n", (int)croisement, inverse_modulo(croisement));
			ft_draw_point(data, x, (int)croisement, inverse_modulo(croisement));
			printf("x2= %f    y2=%f \n",(int)croisement + 1, modulo(croisement));
			ft_draw_point(data, x, (int)croisement + 1, modulo(croisement));
			xpxl1++;
			xpxl2--;
			sleep(1);
		}


	}


}
*/

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
//line3(data, 600, 800, 800, 1200);
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
