/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/09/21 12:03:17 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_new_window() function returns a <window> structure containing all the
** coordinates of the new window created.
*/

#include "mlx_utils.h"

int	ft_close(void)
{
	exit(0);
}

t_vector	calculate_window_size(char **map)
{
	t_vector	size;

	size.x = 0;
	size.y = 0;
	while (map[size.y])
	{
		while (map[size.y][size.x])
		{
			size.x++;
		}
		size.y++;
	}
	size.x *= 63;
	size.y *= 63;
	return (size);
}
