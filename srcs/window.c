/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 12:13:29 by faventur          #+#    #+#             */
/*   Updated: 2022/10/15 22:30:17 by faventur         ###   ########.fr       */
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

t_window	ft_new_window(void *mlx, int width, int height, char *name)
{
	t_window	window;

	window.reference = mlx_new_window(mlx, width, height, name);
	window.size.x = width;
	window.size.y = height;
	mlx_hook(window.reference, 17, 0, ft_close, 0);
	return (window);
}
