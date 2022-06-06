/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:37 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 13:35:04 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"
#include "libft/ft_printf/libftprintf.h"
#include <stdlib.h>

void	looplines(int i, int keycode, int a, t_mlx *mlx)
{
	while (i < mlx->nr_of_lines)
	{
		if (mlx->map[i][a] == 'P' && keycode == 13)
		{
			wup(mlx, i, a);
			if (mlx->map[i - 1][a] != '1')
				break ;
		}
		if (mlx->map[i][a] == 'P' && keycode == 1)
		{
			sdown(mlx, i, a);
			if (mlx->map[i + 1][a] != '1')
				if (i < mlx->nr_of_lines - 1)
					break ;
		}
		if (mlx->map[i][a] == 'P' && keycode == 0)
			aleft(mlx, i, a);
		if (mlx->map[i][a] == 'P' && keycode == 2)
			dright(mlx, i, a);
		i++;
	}
}

/*W is up, A is left, S is down, and D is right.*/
int	keypress(int keycode, t_mlx *mlx)
{
	int	i;
	int	a;

	mlx->breaky = 0;
	a = 0;
	i = 0;
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
	{
		while (a < mlx->len)
		{
			i = 0;
			looplines(i, keycode, a, mlx);
			if (mlx->breaky == 1)
				break ;
			a++;
		}
	}
	if (keycode == 53)
		mymlx_destroy_window(mlx);
	return (1);
}

t_wall	createwall(t_mlx *mlx, char *filename)
{
	int		tw;
	int		th;

	tw = 64;
	th = 64;
	mlx->wall1.image = mlx_xpm_file_to_image(mlx->mlx, filename, &tw, &th);
	mlx->wall1.address = mlx_get_data_addr(mlx->wall1.image,
			&mlx->wall1.bits_per_pixel, &mlx->wall1.line_size,
			&mlx->wall1.endian);
	return (mlx->wall1);
}

void	initialize(t_mlx *mlx)
{
	mlx->counter = 0;
	mlx->height = mlx->nr_of_lines * 64;
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, mlx->len * 64, mlx->height, "Title");
	mlx->image = mlx_new_image(mlx->mlx, mlx->len * 64, mlx->height);
	mlx->address = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel,
			&mlx->line_size, &mlx->endian);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.error = 0;
	mlx.taken = 0;
	if (argc == 2)
	{
		mlx.map_file = argv[1];
		mapparsing(&mlx);
		if (mlx.error == 1)
			return (0);
	}
	else
	{
		ft_printf("Error\n incorrect amount of arguments");
		return (0);
	}
	initialize(&mlx);
	mlx_hook(mlx.window, 2, 1L << 0, keypress, &mlx);
	mlx_hook(mlx.window, 17, 0L, mymlx_destroy_window, &mlx);
	displaymap(&mlx);
	mlx_loop(mlx.mlx);
	return (1);
}
