/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:26:48 by faventur          #+#    #+#             */
/*   Updated: 2022/11/11 19:03:18 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	free_door_arrays(t_ray *ray, size_t size)
{
	free_double_arr_index(ray->door.door_offsets, size);
}

void	free_door_arrays_index(t_ray *ray, size_t index, size_t size)
{
	if (!ray->door.door_offsets[index])
		free_double_arr_index(ray->door.door_offsets, index);
	else
		free_double_arr_index(ray->door.door_offsets, size);
}
