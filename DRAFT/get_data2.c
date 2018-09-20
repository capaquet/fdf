/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:39:50 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/12 16:57:21 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			ft_check_char(t_data *data)
{
	int		index;
	char	c;

	index = 0;
	c = data->line[index];
	while (data->line[index])
	{
		if (ft_strchr(CHAR_OK, c) == NULL)
			ft_error("Error data : Wrong character");
		c = data->line[++index];
	}
}

static void			ft_exploit_line(t_data *data, int y)
{
	int			index;
	char		**line;
	t_list		*new_list;
	t_point		new_point;

	index = 0;
	ft_bzero(&new_point, sizeof(t_point));
	if (!(line = ft_split_whitespaces(data->line)))
		ft_error("Error system in ft_split_whitespaces");
	while (line[index])
	{
		new_point.y = y;
		new_point.z = ft_atoi(line[index++]);
//		data->min_max[0] = new_point.x < data->min_max[0] ? new_point.x : data->min_max[0];
//		data->min_max[1] = new_point.x > data->min_max[1] ? new_point.x : data->min_max[1];
//		data->min_max[2] = new_point.y < data->min_max[2] ? new_point.y : data->min_max[2];
//		data->min_max[3] = new_point.y > data->min_max[3] ? new_point.y : data->min_max[3];
		if (!(new_list = ft_lstnew(&new_point, sizeof(t_point))))
			ft_error("Error system in ft_lstnew");
		ft_lstaddend(&data->map, new_list);
		new_point.x++;
	}
//	data->coeff_x = data->size_image / (new_point.x - 1);
	free_double_tab(&line);
}

/*
static void			ft_correct_coord(t_data *data)
{
	int		border;
	t_list	*tmp_list;

	border = (SIZE_WIN - data->size_image)/2;
	tmp_list = data->map;
	while (tmp_list)
	{
//		((t_point*)tmp_list->content)->x = (((t_point*)tmp_list->content)->x * data->coeff_x) + border;
//		((t_point*)tmp_list->content)->y = (((t_point*)tmp_list->content)->y * data->coeff_y) + border;
		tmp_list = tmp_list->next;
	}
	return;
}
*/

int					ft_read_file(t_data *data)
{
	int			ret;
	int			y;

	y = 0;
	while ((ret = get_next_line(0, &data->line)) > 0)
	{
		ft_check_char(data);
		ft_exploit_line(data, y);
		ft_strdel(&data->line);
		y++;
	}
//	data->coeff_y = data->size_image / (y - 1);
	if (ret == -1)
		ft_error("Error system in GNL");
//	ft_correct_coord(data);
	return (1);
}
