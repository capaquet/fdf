/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:42:10 by cpaquet           #+#    #+#             */
/*   Updated: 2019/07/31 14:00:32 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <mlx.h>
# include "X.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# define CHAR_OK		" -+0123456789\n\0"
# define SIZE_WIN		1200
# define SIZE_IMAGE		1000
# define PI				3.14159265358979323846 * 2
# define CSTE			0.5

typedef struct		s_data
{
	t_list		*map;

	int			nbr_x;
	int			nbr_y;
	int			nbr_z;
	double		coef;

	int			move_x;
	int			move_y;

	float		center_rotat_x;
	float		center_rotat_y;
	float		nbr_altitude;

	float		center_iso_x;
	float		center_iso_y;
	float		min_iso_y;
	float		max_iso_y;

	float		center_p_x;
	float		center_p_y;
	float		min_p_y;
	float		max_p_y;

	void		*mlx_ptr;
	void		*img_ptr;
	char		*image;
	void		*win_ptr;
	int			endian;
	int			size;
	int			bits_per_pixel;

}					t_data;

typedef struct		s_point
{
	float		x;
	float		y;
	float		z;

	float		new_x;
	float		new_y;
	float		new_z;

	float		iso_x;
	float		iso_y;
	float		p_x;
	float		p_y;
}					t_point;

/*
** Functions in get_data.c
*/
int					ft_read_file(t_data *data, char **file_name);

/*
** Functions in tools.c
*/
void				ft_error(t_data *data, char *msg);
void				free_double_tab(char ***tab);
float				modulo(float x);
float				reverse_modulo(float x);
void				ft_fabs(float *nbr);

/*
** Functions in key_effect.c
*/
void				altitude(t_data *data, int key);
void				zoom(t_data *data, int key);
void				rotate(t_data *data, int *key);
void				mouvement(t_data *data, int key);
void				quit(t_data *data);

/*
** Functions in isometric.c
*/
void				ft_isometric(t_data *data);
void				ft_parallel(t_data *data);
void				ft_calcul_center_iso(t_data *data);
void				ft_calcul_center_p(t_data *data);

/*
** Functions in color.c
*/
int					ft_color(float z_min, float z_max, float y);

/*
** Functions in draw.c
*/
void				draw_fdf(t_data *data, t_list *map);
void				draw_fdf_p(t_data *data, t_list *map);
void				ft_draw_line(t_data *data, t_point *point1,
															t_point *point2);
void				ft_draw_line_p(t_data *data, t_point *point1,
															t_point *point2);
#endif
