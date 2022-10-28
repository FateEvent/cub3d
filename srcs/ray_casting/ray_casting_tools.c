/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:24:46 by faventur          #+#    #+#             */
/*   Updated: 2022/10/28 11:10:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ray_casting(t_data *data)
{
	t_ray		*ray;
	size_t		x;

	x = 0;
	ray = &data->ray_data;
	ray->map = data->map;
//	if ()	
		floor_casting(data, ray);
	while (x < ray->resolution.x)
	{
		ray_data_init(ray, x);
		rayside_calculator(ray);
		ray_launcher(ray);
		wall_distance_calculator(ray);
		wall_line_calculator(ray);
		texture_x_pos_calculator(data, ray);
		texture_y_pos_calculator(data, ray);
//		if ()
//			draw_ceiling(data, x);
		draw_walls(data, x);
//		if ()
//			draw_floor(data, x);
		++x;
	}
}
