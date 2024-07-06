/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mustyilm <mustyilm@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:30:45 by mustyilm          #+#    #+#             */
/*   Updated: 2024/02/16 18:34:06 by mustyilm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "library/ft_printf/ft_printf.h"
#include <stdlib.h>
#include "library/minilibx/mlx.h"

void	error_message(char *msg)
{
	ft_printf("%s", msg);
	exit(1);
}

void	escape_line(t_game *data)
{
	data->index.i = -1;
	data->index.j = -1;
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc == 2)
	{
		map_control(argv[1], &data);
		map_reading(&data);
		map_processing(&data);
		wall_control(&data);
		data.mlxpointer = mlx_init();
		data.winpointer = mlx_new_window(data.mlxpointer,
				(data.map_width * RES), (data.map_height * RES), "so_long");
		images_in_game(&data);
		data.player = data.player_img;
		data.collectables = 0;
		map_bug(&data);
		adding_graphics(&data);
		placeholder(&data, data.player_y, data.player_x);
		mlx_hook(data.winpointer, 17, 0, &exit_point, (void *)&data);
		data.counter = 0;
		mlx_hook(data.winpointer, 2, 0, &controls_working, &data);
		mlx_loop(data.mlxpointer);
	}
	else
		error_message("Error..!\nWrong Argument");
}
