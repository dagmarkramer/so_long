/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapparsing.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:38:44 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 13:42:24 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"
#include "libft/ft_printf/libftprintf.h"
#include <fcntl.h>

void	returnft(t_mlx *mlx)
{
	mlx->error = 1;
	return ;
}

void	othercharacters(t_mlx *mlx)
{
	int	i;
	int	a;

	i = 0;
	mlx->len = (int)ft_strlen(mlx->map[0]);
	while (i < mlx->nr_of_lines)
	{
		a = 0;
		while (a < mlx->len)
		{
			if (!ft_strrchr("E01CP", mlx->map[i][a]))
			{
				ft_printf("Error\n wrong characters included");
				return (returnft(mlx));
			}
			a++;
		}
		i++;
	}
}

void	fillmap(t_mlx *mlx, char *line, char *line2)
{
	mlx->ret = 1;
	mlx->b = 0;
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (returnft(mlx));
		if (line)
		{
			line2 = line;
			line = ft_strtrim(line2, "\t\n\v\f\r ");
			if (!line)
				return (returnft(mlx));
			free (line2);
		}
		if (ft_strncmp(line, "", 1) != 0)
		{
			mlx->map[mlx->b] = line;
			mlx->b++;
		}
		else
			free (line);
	}
	close (mlx->fd);
}

void	countlines(t_mlx *mlx, char *line, char *line2)
{
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (returnft(mlx));
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (returnft(mlx));
		if (line)
		{
			line2 = line;
			line = ft_strtrim(line2, "\t\n\v\f\r ");
			if (!line)
				return (returnft(mlx));
			free (line2);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
			mlx->nr_of_lines++;
		if (line)
			free (line);
	}
	close (mlx->fd);
}

void	mapparsing(t_mlx *mlx)
{
	char	*line;
	char	*line2;

	mlx->ret = 1;
	mlx->nr_of_lines = 0;
	line = NULL;
	line2 = NULL;
	countlines(mlx, line, line2);
	mlx->map = malloc(sizeof(char *) * (mlx->nr_of_lines + 1));
	if (!mlx->map)
		return (returnft(mlx));
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (returnft(mlx));
	fillmap(mlx, line, line2);
	othercharacters(mlx);
	if (mlx->error == 1)
		return ;
	checkmap (mlx);
}
