/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2018/10/08 17:32:02 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#define RED color_rgb[0]
#define GREEN color_rgb[1]
#define BLUE color_rgb[2]

static unsigned char	ft_calcul_rgb(float lvl, unsigned char *full,
												unsigned char *empty, char code)
{
	unsigned char varying;

	*full = 0xFF;
	*empty = 0x00;
	if (code == 0)
		varying = (char)(modulo(lvl) * 255);
	else
		varying = (char)(reverse_modulo(lvl) * 255);
	return (varying);
}

int						ft_color(float y_min, float y_max, float y)
{
	int				color;
	float			lvl;
	unsigned char	color_rgb[3];

	lvl = (y - y_min) * 10 / (y_max - y_min);
	ft_bzero(&color_rgb, sizeof(unsigned char) * 3);
	if (lvl >= 0 && lvl < 1.5)
		GREEN = ft_calcul_rgb(lvl / 1.5, &RED, &GREEN, 0);
	else if (lvl >= 1.5 && lvl < 3)
		RED = ft_calcul_rgb((lvl - 1.5) / 1.5, &GREEN, &BLUE, 1);
	else if (lvl >= 3 && lvl < 4.5)
		BLUE = ft_calcul_rgb((lvl - 3) / 1.5, &GREEN, &RED, 0);
	else if (lvl >= 4.5 && lvl < 6)
		GREEN = ft_calcul_rgb((lvl - 4.5) / 1.5, &BLUE, &RED, 1);
	else if (lvl >= 6 && lvl < 7.5)
		RED = ft_calcul_rgb((lvl - 6) / 1.5, &BLUE, &GREEN, 0);
	else if (lvl >= 7.5 && lvl < 9)
		BLUE = ft_calcul_rgb((lvl - 7.5) / 1.5, &RED, &GREEN, 1);
	else
	{
		RED = ft_calcul_rgb((lvl - 4.5) / 1.5, &GREEN, &GREEN, 1);
		BLUE = 0;
	}
	color = (RED << 16) + (GREEN << 8) + BLUE;
	return (color);
}
