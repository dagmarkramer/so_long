/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:49 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 12:38:50 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"
#include  <stdlib.h>
#include "libft/ft_printf/libftprintf.h"

void	normalsit(t_mlx *mlx, int i, int a)
{
	mlx->map[i][a] = '0';
	mlx->counter++;
	ft_printf("cur. nr. of moves: %d\n", mlx->counter);
}

void	aleft(t_mlx *mlx, int i, int a)
{
	if (mlx->map[i][a - 1] != '1')
	{
		clearscreen(mlx);
		if (mlx->map[i][a - 1] != 'E')
		{
			if (mlx->map[i][a - 1] == 'C')
				mlx->taken++;
			mlx->map[i][a - 1] = 'P';
		}
		if (mlx->map[i][a - 1] == 'E' && mlx->coll == mlx->taken)
		{
			ft_printf("you reached the exit!\n start over\n");
			mymlx_destroy_window(mlx);
		}
		if (mlx->map[i][a - 1] == 'E' && mlx->coll != mlx->taken)
			ft_printf("you didn't collect all collectibles yet!\n");
		else
			normalsit(mlx, i, a);
		displaymap(mlx);
		mlx->breaky = 1;
	}
}

void	dright(t_mlx *mlx, int i, int a)
{
	if (mlx->map[i][a + 1] != '1')
	{
		if (a < mlx->len - 1)
		{
			clearscreen(mlx);
			if (mlx->map[i][a + 1] != 'E')
			{
				if (mlx->map[i][a + 1] == 'C')
					mlx->taken++;
				mlx->map[i][a + 1] = 'P';
			}
			if (mlx->map[i][a + 1] == 'E' && mlx->coll == mlx->taken)
			{
				ft_printf("you reached the exit!\n start over\n");
				mymlx_destroy_window(mlx);
			}
			if (mlx->map[i][a + 1] == 'E' && mlx->coll != mlx->taken)
				ft_printf("you didn't collect all collectibles yet!\n");
			else
				normalsit(mlx, i, a);
			displaymap(mlx);
			mlx->breaky = 1;
		}
	}
}

void	sdown(t_mlx *mlx, int i, int a)
{
	if (mlx->map[i + 1][a] != '1')
	{
		if (i < mlx->nr_of_lines - 1)
		{
			clearscreen(mlx);
			if (mlx->map[i + 1][a] != 'E')
			{
				if (mlx->map[i + 1][a] == 'C')
					mlx->taken++;
				mlx->map[i + 1][a] = 'P';
			}
			if (mlx->map[i + 1][a] == 'E' && mlx->coll == mlx->taken)
			{
				ft_printf("you reached the exit!\n start over\n");
				mymlx_destroy_window(mlx);
			}
			if (mlx->map[i + 1][a] == 'E' && mlx->coll != mlx->taken)
				ft_printf("you didn't collect all collectibles yet!\n");
			else
				normalsit(mlx, i, a);
			displaymap(mlx);
		}
	}
}

void	wup(t_mlx *mlx, int i, int a)
{
	if (mlx->map[i - 1][a] != '1')
	{
		clearscreen(mlx);
		if (mlx->map[i - 1][a] != 'E')
		{
			if (mlx->map[i - 1][a] == 'C')
				mlx->taken++;
			mlx->map[i - 1][a] = 'P';
		}
		if (mlx->map[i - 1][a] == 'E' && mlx->coll == mlx->taken)
		{
			ft_printf("you reached the exit!\n start over\n");
			mymlx_destroy_window(mlx);
		}
		if (mlx->map[i - 1][a] == 'E' && mlx->coll != mlx->taken)
			ft_printf("you didn't collect all collectibles yet!\n");
		else
			normalsit(mlx, i, a);
		displaymap(mlx);
	}
}
