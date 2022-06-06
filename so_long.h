/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 12:39:13 by dkramer       #+#    #+#                 */
/*   Updated: 2021/12/13 13:33:27 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_wall
{
	int		width;
	int		height;
	void	*mlx;
	char	*window;
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}				t_wall;

typedef struct s_mlx
{
	char			*map_file;
	char			**map;
	int				nr_of_lines;
	int				len;
	int				width;
	int				height;
	void			*mlx;
	char			*window;
	void			*image;
	char			*address;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	t_wall			wall;
	t_wall			collectible;
	t_wall			exit;
	t_wall			player;
	int				counter;
	int				offset;
	int				offset2;
	unsigned int	trgbcolor;
	int				x;
	int				y;
	int				i;
	int				a;
	t_wall			needed;
	int				exit_found;
	int				collectible_found;
	int				start_found;
	int				b;
	int				ret;
	int				fd;
	t_wall			wall1;
	int				error;
	int				breaky;
	int				coll;
	int				taken;
}				t_mlx;

void	mapparsing(t_mlx *mlx);
int		mymlx_destroy_window(t_mlx *mlx);
int		keypress(int keycode, t_mlx *mlx);
int		create_trgb(int t, int r, int g, int b);
void	my_pixel_put(t_mlx *mlx, int x, int y, unsigned int colour);
void	displaymap(t_mlx *mlx);
t_wall	createwall(t_mlx *mlx, char *filename);
void	clearscreen(t_mlx *mlx);
void	looplines(int i, int keycode, int a, t_mlx *mlx);
void	checkmap(t_mlx *mlx);
void	wup(t_mlx *mlx, int i, int a);
void	sdown(t_mlx *mlx, int i, int a);
void	dright(t_mlx *mlx, int i, int a);
void	aleft(t_mlx *mlx, int i, int a);
void	returnft(t_mlx *mlx);

#endif
