/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:39:50 by cpaquet           #+#    #+#             */
/*   Updated: 2018/09/19 12:13:04 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			ft_check_char(t_data *data, char *line)
{
	int		index;
	char	c;

	index = 0;
	c = line[index];
	while (line[index])
	{
		if (ft_strchr(CHAR_OK, c) == NULL)
		{
			ft_strdel(&line);
			ft_error(data, "Error data : Wrong character");
		}
		c = line[++index];
	}
}

static void			ft_exploit_line(t_data *data, char *line, int y)
{
	int			index;
	char		**line_split;
	t_list		*new_list;
	t_point		new_point;

	index = 0;
	ft_bzero(&new_point, sizeof(t_point));
	if (!(line_split = ft_split_whitespaces(line)))
		ft_error(data, "Error system in ft_split_whitespaces");
	while (line_split[index])
	{
		new_point.y = y;
		new_point.z = ft_atoi(line_split[index++]);
		if (!(new_list = ft_lstnew(&new_point, sizeof(t_point))))
			ft_error(data, "Error system in ft_lstnew");
		ft_lstaddend(&data->map, new_list);
		new_point.x++;
	}
	if (data->nbr_x == 0)
		data->nbr_x = new_point.x;
	else if (data->nbr_x != new_point.x)
		ft_error(data, "Error input - Line unequals");
	free_double_tab(&line_split);
}

static void			reset_coord(t_list *map)
{
	while (map)
	{
		((t_point*)map->content)->new_x = ((t_point*)map->content)->x;
		((t_point*)map->content)->new_y = ((t_point*)map->content)->y;
		((t_point*)map->content)->new_z = ((t_point*)map->content)->z;
		map = map->next;
	}
}

int					ft_read_file(t_data *data)
{
	int			nbr_y;
	int			ret;
	char		*line;

	nbr_y = 0;
	line = NULL;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_check_char(data, line);
		ft_exploit_line(data, line, nbr_y);
		ft_strdel(&line);
		nbr_y++;
	}
//	if (line)
//		ft_strdel(&line);
	if (nbr_y == 0)
		ft_error(data, "Error data - File empty");
	if (ret == -1)
		ft_error(data, "Error system in GNL");
	reset_coord(data->map);
	return (1);
}
