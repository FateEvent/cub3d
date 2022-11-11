/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:22:57 by faventur          #+#    #+#             */
/*   Updated: 2022/11/11 19:04:03 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** As concerning the state of the doors, 0 means closed, 1 that's opening, 2
** open and 3 closing.
*/

#include "mlx_utils.h"

static void	into_the_loop(t_data *data, t_ray *ray, t_var *var)
{
	var->i = 0;
	while (var->i < var->height)
	{
		ray->door.door_offsets[var->i] = ft_memsalloc(var->width,
				sizeof(double), 1);
		if (!ray->door.door_offsets[var->i])
			return (free_door_arrays_index(ray, var->i, var->height));
		var->j = 0;
		while (var->j < var->width && data->map->map[var->i][var->j])
		{
			if (data->map->map[var->i][var->j] == '2')
				ray->door.door_offsets[var->i][var->j] = 0;
			var->j++;
		}
		var->i++;
	}
}

void	init_doors(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	ray->door.door_offsets = ft_calloc(var.height, sizeof(double *));
	if (!ray->door.door_offsets)
		throw_err_ex("Malloc error");
	into_the_loop(data, ray, &var);
	if (!data->ray_data.door.door_offsets)
		throw_err_ex("Error : Malloc failed.");
	ray->door.index = 50;
	ray->door.opening_timer = 0;
}
