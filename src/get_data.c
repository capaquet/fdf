/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:39:50 by cpaquet           #+#    #+#             */
/*   Updated: 2019/08/21 13:56:21 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			ft_check_char(t_data *data, char *line)
{
	char	c;
	int		ind;

	ind = 0;
	c = line[ind];
	while (line[ind])
	{
		if (ft_strchr(CHAR_OK, c) == NULL)
		{
			ft_strdel(&line);
			ft_error(data, "Error data : Wrong character");
		}
		c = line[++ind];
	}
}

static void			ft_center(t_data *data, t_point point)
{
	if (point.z != 0)
	{
		data->center_rotat_x += point.x;
		data->center_rotat_y += point.y;
		data->nbr_altitude += 1;
	}
}

static void			ft_exploit_line(t_data *data, char *line, int y)
{
	int			ind;
	char		**split;
	t_list		*new_list;
	t_point		new_point;

	ind = 0;
	ft_bzero(&new_point, sizeof(t_point));
	if (!(split = ft_split_whitespaces(line)))
		ft_error(data, "Error system in ft_split_whitespaces");
	while (split[ind])
	{
		new_point.y = y;
		if (ft_strchr(split[ind] + 1, '+') || ft_strchr(split[ind] + 1, '-'))
			ft_error(data, "Error input - Multiple sign for altitude");
		new_point.z = ft_atoi(split[ind++]);
		data->nbr_z = new_point.z > data->nbr_z ? new_point.z : data->nbr_z;
		if (!(new_list = ft_lstnew(&new_point, sizeof(t_point))))
			ft_error(data, "Error system in ft_lstnew");
		ft_lstaddend(&data->map, new_list);
		ft_center(data, new_point);
		new_point.x++;
	}
	data->nbr_x = (data->nbr_x == 0 ? new_point.x : data->nbr_x);
	data->nbr_x != new_point.x ? ft_error(data, "Error - Line unequals") : 0;
	free_double_tab(&split);
}

static void			copy_coord(t_list *map)
{
	while (map)
	{
		((t_point*)map->content)->new_x = ((t_point*)map->content)->x;
		((t_point*)map->content)->new_y = ((t_point*)map->content)->y;
		((t_point*)map->content)->new_z = ((t_point*)map->content)->z;
		map = map->next;
	}
}

int					ft_read_file(t_data *data, char **file_name)
{
	int			nbr_y;
	int			ret;
	int			fd;
	char		*line;

	nbr_y = 0;
	line = NULL;
	if ((fd = open(file_name[1], O_RDONLY)) <= 0)
		ft_error(data, "Error input - Read failed");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_check_char(data, line);
		ft_exploit_line(data, line, nbr_y);
		ft_strdel(&line);
		nbr_y++;
	}
	if (nbr_y == 0)
		ft_error(data, "Error data - File empty");
	if (ret == -1)
		ft_error(data, "Error system in GNL");
	data->nbr_y = nbr_y;
	data->nbr_altitude != 0 ? data->center_rotat_x /= data->nbr_altitude : 0;
	data->nbr_altitude != 0 ? data->center_rotat_y /= data->nbr_altitude : 0;
	copy_coord(data->map);
	return (1);
}
