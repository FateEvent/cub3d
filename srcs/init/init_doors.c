/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:22:57 by faventur          #+#    #+#             */
/*   Updated: 2022/11/14 17:10:53 by albaur           ###   ########.fr       */
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
		ray->door.door_map[var->i] = ft_calloc(sizeof(t_door_data) * data->map->size_arr[var->i], sizeof(t_door_data));
		var->j = 0;
		while (var->j < var->width && data->map->map[var->i][var->j])
		{
			if (data->map->map[var->i][var->j] == '2')
			{
				ray->door.door_map[var->i][var->j].map_pos = (t_vec){var->i, var->j};
				ray->door.door_map[var->i][var->j].is_door = 1;
				++ray->door.nb_doors;
			}
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
	ray->door.door_map = malloc(sizeof(t_door_data *) * data->map->size.y);
	ray->door.nb_doors = 0;
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	into_the_loop(data, ray, &var);
}
