/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:42:10 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/18 18:40:58 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

# include <stdio.h>
# include <mlx.h>
# include <errno.h>
# include <math.h>

// A modifier apres l integration de la libft
# include "libft.h"
# include "get_next_line.h"

#define CHAR_OK		" -0123456789\n\0"
#define SIZE_WIN	900
#define SIZE_IMAGE	750
#define PI			3.14159265358979323846 * 2

typedef struct		s_data
{
	int			nbr_x;
	int			nbr_y;

	int			size_image;
	int			key;
	int			coef;

	int			move_x;
	int			move_y;

	t_list		*map;
	int			min_max_iso[4];

	void		*win_i_ptr;
	void		*mlx_ptr;
	void		*win_ptr;

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
	float		iso_z;
}					t_point;

int					ft_read_file(t_data *data);

/*
** Functions in tools.c
*/
void				ft_error(t_data *data, char *msg);
void				ft_free_map(t_list *map);
void				free_double_tab(char ***tab);
void				ft_copy_min_max(int tab1[], int tab2[]);

void				altitude(t_data *data);
void				zoom(t_data *data);
void				rotate(t_data *data, int *key);
void				mouvement(t_data *data);
void				quit(t_data *data);

void				ft_isometric(t_data *data);

void	draw_fdf(t_data *data, t_list *map);


#endif
