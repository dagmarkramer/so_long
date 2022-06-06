/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:26 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 13:43:05 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include "libft/ft_printf/libftprintf.h"
#include <fcntl.h>

void	lengthloop(t_mlx *mlx, int i)
{
	int	a;

	a = 0;
	while (a < mlx->len)
	{
		if (mlx->map[i][a] == 'E')
			mlx->exit_found = 1;
		if (mlx->map[i][a] == 'C')
		{
			mlx->coll++;
			mlx->collectible_found = 1;
		}
		if (mlx->map[i][a] == 'P')
			mlx->start_found = 1;
		a++;
	}
}

/*check if surrounded by walls*/
void	wallchecker(t_mlx *mlx)
{
	int	i;
	int	a;

	a = 0;
	i = 0;
	while (i < mlx->nr_of_lines)
	{
		if (mlx->map[i][0] != '1' || mlx->map[i][mlx->len - 1] != '1')
		{
			ft_printf("%s", "Error\n map not surrounded be walls");
			return (returnft(mlx));
		}
		i++;
	}
	while (a < mlx->len)
	{
		if (mlx->map[0][a] != '1' || mlx->map[mlx->nr_of_lines - 1][a] != '1')
		{
			ft_printf("%s", "Error\n map not surrounded be walls");
			return (returnft(mlx));
		}
		a++;
	}
}

/*check if exit, collectible & starting possition*/
void	ecpchecker(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->exit_found = 0;
	mlx->collectible_found = 0;
	mlx->start_found = 0;
	mlx->coll = 0;
	while (i < mlx->nr_of_lines)
	{
		lengthloop(mlx, i);
		i++;
	}
	if (!mlx->start_found || !mlx->exit_found || !mlx->collectible_found)
	{
		ft_printf("%s", "Error\n no start, exit or collectible found");
		return (returnft(mlx));
	}
}

/*check if map is rectangular*/
void	checkmap(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->len = (int)ft_strlen(mlx->map[0]);
	while (i < mlx->nr_of_lines)
	{
		if (mlx->map[i] && (int)ft_strlen(mlx->map[i]) != mlx->len)
		{
			ft_printf("%s", "Error\n non-rectangular map given");
			return (returnft(mlx));
		}
		i++;
	}
	ecpchecker(mlx);
	wallchecker(mlx);
}
