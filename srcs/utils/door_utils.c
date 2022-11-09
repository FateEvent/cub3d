/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:48 by faventur          #+#    #+#             */
/*   Updated: 2022/11/09 15:28:29 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_door_arrays(t_ray *ray, size_t size)
{
	free_double_arr_index(ray->door.door_timers, size);
	free_double_arr_index(ray->door.door_offsets, size);
	free_int_arr_index(ray->door.door_states, size);
}

void	free_door_arrays_index(t_ray *ray, size_t index, size_t size)
{
	if (!ray->door.door_timers[index])
		free_double_arr_index(ray->door.door_timers, index);
	else
		free_double_arr_index(ray->door.door_timers, size);
	if (!ray->door.door_offsets[index])
		free_double_arr_index(ray->door.door_offsets, index);
	else
		free_double_arr_index(ray->door.door_offsets, size);
	if (!ray->door.door_states[index])
		free_int_arr_index(ray->door.door_states, index);
	else
		free_int_arr_index(ray->door.door_states, size);
}

void	ft_print_double_arr(double **map, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("%f ", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

void	ft_print_int_arr(double **map, size_t height, size_t width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ft_printf("%i ", map[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
}
