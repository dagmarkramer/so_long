/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:26:48 by dkramer       #+#    #+#                 */
/*   Updated: 2021/02/26 20:10:06 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int		d;

	d = c;
	if (c >= 97 && c <= 122)
		d = c - 32;
	return (d);
}
