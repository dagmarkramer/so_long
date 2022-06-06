/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   displaymap.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:32 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 12:38:33 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/ft_printf/libftprintf.h"
#include "mlx/mlx.h"
#include <stdlib.h>

int	color(int x, int y, t_wall needed)
{
	int				ct;
	int				cr;
	int				cg;
	int				cb;
	int				pos;

	pos = (y * needed.line_size + x * (needed.bits_per_pixel / 8));
	if (needed.endian == 1)
	{
		ct = (int)needed.address[pos];
		cr = (int)needed.address[pos + 1];
		cg = (int)needed.address[pos + 2];
		cb = (int)needed.address[pos + 3];
	}
	else
	{
		ct = (int)needed.address[pos + 3];
		cr = (int)needed.address[pos + 2];
		cg = (int)needed.address[pos + 1];
		cb = (int)needed.address[pos];
	}
	return (create_trgb(ct, cr, cg, cb));
}

void	linesloop(t_mlx *mlx)
{
	if (mlx->map[mlx->i][mlx->a] == '1')
		mlx->needed = mlx->wall;
	if (mlx->map[mlx->i][mlx->a] == 'E')
		mlx->needed = mlx->exit;
	if (mlx->map[mlx->i][mlx->a] == 'C')
		mlx->needed = mlx->collectible;
	if (mlx->map[mlx->i][mlx->a] == 'P')
		mlx->needed = mlx->player;
	while (mlx->x < 64)
	{
		mlx->y = 0;
		while (mlx->y < 64)
		{
			mlx->trgbcolor = color(mlx->x, mlx->y, mlx->needed);
			if (mlx->trgbcolor == 0xffffff)
				mlx->trgbcolor = create_trgb(0, 255, 255, 255);
			if (mlx->map[mlx->i][mlx->a] == '0')
				mlx->trgbcolor = create_trgb(0, 0, 0, 0);
			mlx->trgbcolor = (mlx->trgbcolor >> 1) & 8355711;
			my_pixel_put(mlx, mlx->offset + mlx->x, mlx->offset2
				+ mlx->y, mlx->trgbcolor);
			mlx->y++;
		}
		mlx->x++;
	}
}

void	displaymap(t_mlx *mlx)
{
	mlx->wall = createwall(mlx, "xpm/wood.xpm");
	mlx->collectible = createwall(mlx, "xpm/tree.xpm");
	mlx->exit = createwall(mlx, "xpm/barrel.xpm");
	mlx->player = createwall(mlx, "xpm/brick.xpm");
	mlx->x = 0;
	mlx->offset = 0;
	mlx->a = 0;
	while (mlx->a < mlx->len)
	{
		mlx->i = 0;
		mlx->offset2 = 0;
		while (mlx->i < mlx->nr_of_lines)
		{
			linesloop(mlx);
			mlx->x = 0;
			mlx->y = 0;
			mlx->offset2 = mlx->offset2 + 64;
			mlx->i++;
		}
		mlx->a++;
		mlx->offset = mlx->offset + 64;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image, 0, 0);
}
