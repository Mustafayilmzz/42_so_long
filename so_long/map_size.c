/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustyilm <mustyilm@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:30:22 by mustyilm          #+#    #+#             */
/*   Updated: 2024/02/16 18:34:24 by mustyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>
#include <fcntl.h>
#include "library/get_next_line/get_next_line.h"

void	wall_control(t_game *data)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = 0;
	j = 0;
	width = data->map_width - 1;
	height = data->map_height - 1;
	while (i <= height)
	{
		if (data->map[i][0] != '1' || data->map[i][width] != '1')
			error_message("Faulty map");
		i++;
	}
	while (j <= width)
	{
		if (data->map[0][j] != '1' || data->map[height][j] != '1')
			error_message("Faulty map");
		j++;
	}
}

static void	line_control(t_game *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (i != data->map_width)
		error_message("Line in text is wrong");
}

void	map_processing(t_game *data)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	data->map = (char **)malloc(sizeof(char *) * data->map_height);
	if (data->map == NULL)
	{
		error_message("Place could not be reserved");
		exit_point((void *)data);
	}
	fd = open(data->maplocation, O_RDONLY);
	while (i < data->map_height)
	{
		line = get_next_line(fd);
		line_control(data, line);
		data->map[i] = ft_strdup(line);
		if (data->map[i] == NULL)
			break ;
		i++;
		free(line);
	}
	close(fd);
}

static int	width_of_map(char *str)
{
	int	width;

	width = 0;
	while (str[width] != '\n' && str[width] != '\0')
		width++;
	return (width);
}

void	map_reading(t_game *data)
{
	int		fd;
	char	*line;

	data->index.i = 0;
	data->index.j = 0;
	fd = open(data->maplocation, O_RDONLY);
	line = get_next_line(fd);
	if (!line || line[data->index.i] == 32
		|| line[data->index.i] == '\t')
	{
		free(line);
		close(fd);
		error_message("Map is empty");
	}
	data->index.j = width_of_map(line);
	while (line)
	{
		free(line);
		data->index.i++;
		line = get_next_line(fd);
	}
	data->map_height = data->index.i;
	data->map_width = data->index.j;
	close(fd);
}
