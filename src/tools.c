/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:34:42 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/20 19:02:39 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(t_data *data, char *msg)
{
	if (errno == 0)
		ft_printf("%s\n", msg);
	else
		ft_printf("%s: %s\n", msg, strerror(errno));
	quit(data);
}

void		free_double_tab(char ***tab)
{
	int		a;

	a = 0;
	while ((*tab)[a])
	{
		free((*tab)[a]);
		a++;
	}
	free(*tab);
	*tab = NULL;
}

float		modulo(float x)
{
	return (x - (int)x);
}

float		reverse_modulo(float x)
{
	return (1 - modulo(x));
}

void		ft_fabs(float *nbr)
{
	if (*nbr < 0)
		*nbr = -*nbr;
}
