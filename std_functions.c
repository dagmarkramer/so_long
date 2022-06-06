/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   std_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:55 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 12:38:56 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"
#include  <stdlib.h>
#include "libft/ft_printf/libftprintf.h"

void	my_pixel_put(t_mlx *mlx, int x, int y, unsigned int colour)
{
	char	*dst;
	int		offset;

	offset = y * mlx->line_size + x * (mlx->bits_per_pixel / 8);
	dst = mlx->address + offset;
	*(unsigned int *)dst = colour;
}

int	mymlx_destroy_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	exit(0);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	clearscreen(t_mlx *mlx)
{
	int				x;
	int				y;
	unsigned int	color;

	color = create_trgb(0, 0, 0, 0);
	x = 0;
	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->len * 64)
		{
			my_pixel_put(mlx, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image, 0, 0);
}
