/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:08:44 by albaur            #+#    #+#             */
/*   Updated: 2022/11/09 16:30:25 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	update_doors(t_data *data, t_ray *ray)
{
	t_var	var;

	ft_bzero(&var, sizeof(var));
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	while (var.i < var.height && ray->map->map[var.i])
	{
		var.j = 0;
		while (var.j < var.width && ray->map->map[var.i][var.j])
		{
			//0: Closed, 1: Opening, 2: Open, 3: Closing
			if (ray->map->map[var.i][var.j] == 2) { //Standard door
				if (ray->door.door_states[var.i][var.j] == 1){//Open doors
//					ray->door.door_offsets[var.i][var.j] += deltaTime / 100;

//				if (ray->door.door_offsets[var.i][var.j] > 1) {
//					ray->door.door_offsets[var.i][var.j] = 1;
						ray->door.door_states[var.i][var.j] = 2;//Set state to open
//						setTimeout(function(stateX, stateY){ray->door.door_states[stateX][stateY] = 3;}, 5000, x, y);//TO DO: Don't close when player is in tile
					}
//				}
				else if (ray->door.door_states[var.i][var.j] == 3)
				{//Close doors
//					ray->door.door_offsets[var.i][var.j] -= deltaTime / 100;
					
//					if (ray->door.door_offsets[var.i][var.j] < 0) {
//						ray->door.door_offsets[var.i][var.j] = 0;
						ray->door.door_states[var.i][var.j] = 0;//Set state to closed
//					}
				}
			}
			var.j++;
		}
		var.i++;
	}
}
