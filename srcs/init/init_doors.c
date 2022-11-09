/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:22:57 by faventur          #+#    #+#             */
/*   Updated: 2022/11/09 14:39:59 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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

static void	into_the_loop(t_data *data, t_ray *ray, t_var *var)
{
	var->i = 0;
	while (var->i < var->height)
	{
		ray->door.door_timers[var->i] = ft_calloc(var->width, sizeof(double));
		ray->door.door_offsets[var->i] = ft_memsalloc(var->width,
				sizeof(double), 1);
		ray->door.door_states[var->i] = ft_memsalloc(var->width,
				sizeof(int), 1);
		if (!ray->door.door_timers[var->i] || !ray->door.door_offsets[var->i]
			|| !ray->door.door_states[var->i])
			return (free_door_arrays_index(ray, var->i, var->height));
		var->j = 0;
		while (var->j < var->width)
		{
			if (data->map->map[var->i][var->j] == '2')
			{
				ray->door.door_timers[var->i][var->j] = 1;
				ray->door.door_offsets[var->i][var->j] = 0;
				ray->door.door_states[var->i][var->j] = 1;
			}
			var->j++;
		}
		var->i++;
	}
}

void	create_door_arrays(t_data *data)
{
	t_ray	*ray;
	t_var	var;

	ft_bzero(&var, sizeof(var));
	ray = &data->ray_data;
	var.width = data->map->size.x;
	var.height = data->map->size.y;
	ray->door.door_timers = ft_calloc(var.height, sizeof(double *));
	ray->door.door_offsets = ft_calloc(var.height, sizeof(double *));
	ray->door.door_states = ft_calloc(var.width, sizeof(int *));
	if (!ray->door.door_timers || !ray->door.door_offsets
		|| !ray->door.door_states)
	{
		if (ray->door.door_timers)
			free(ray->door.door_timers);
		if (ray->door.door_offsets)
			free(ray->door.door_offsets);
		if (ray->door.door_states)
			free(ray->door.door_states);
		ray->door.door_timers = NULL;
		ray->door.door_offsets = NULL;
		ray->door.door_states = NULL;
		return ;
	}
	into_the_loop(data, ray, &var);
}
