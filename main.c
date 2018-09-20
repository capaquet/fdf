#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;
	int i = 0;
	int		ret;

	ret = 0;
	if (argc != 2)
		return (0);
	if ((fd = open(argv[1], O_RDONLY)) != -1)
	{
		while ((ret =get_next_line(fd, &line)))
		{
			ft_putstr("---------------------- Line vaut : ");
			ft_putendl(line);
			ft_strdel(&line);
		}
	printf("ret = %d   line = %s \n", ret, line);
//		ft_strdel(&line);
	}
	else
		return (0);
	if (close(fd == -1))
		return (0);
}
