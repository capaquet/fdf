/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:34:42 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/19 12:09:06 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(t_data *data, char *msg)
{
	if (errno == 0)
		printf("%s\n", msg);
	else
		printf("%s: %s\n", msg, strerror(errno));
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
