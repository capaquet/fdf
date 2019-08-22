/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 09:15:22 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/21 14:10:07 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#define R color_rgb[0]
#define G color_rgb[1]
#define B color_rgb[2]

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
		G = ft_calcul_rgb(lvl / 1.5, &R, &G, 0);
	else if (lvl >= 1.5 && lvl < 3)
		R = ft_calcul_rgb((lvl - 1.5) / 1.5, &G, &B, 1);
	else if (lvl >= 3 && lvl < 4.5)
		B = ft_calcul_rgb((lvl - 3) / 1.5, &G, &R, 0);
	else if (lvl >= 4.5 && lvl < 6)
		G = ft_calcul_rgb((lvl - 4.5) / 1.5, &B, &R, 1);
	else if (lvl >= 6 && lvl < 7.5)
		R = ft_calcul_rgb((lvl - 6) / 1.5, &B, &G, 0);
	else if (lvl >= 7.5 && lvl < 9)
		B = ft_calcul_rgb((lvl - 7.5) / 1.5, &R, &G, 1);
	else
	{
		R = ft_calcul_rgb((lvl - 4.5) / 1.5, &G, &G, 1);
		B = 0;
	}
	color = (R << 16) + (G << 8) + B;
	return (color);
}
