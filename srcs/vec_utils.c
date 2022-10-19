/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:36:35 by faventur          #+#    #+#             */
/*   Updated: 2022/10/19 14:10:39 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

double	ft_vect2_distance_calc(t_vector2 start, t_vector2 finish)
{
	double	distance;

	distance = sqrtf(powf(start.x - finish.x, 2) + powf(start.y - finish.y, 2));
	return (distance);
}

t_vector	ft_inttovec(int x, int y)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector2	ft_doubletovec2(double x, double y)
{
	t_vector2	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

void	ft_vec_swap(t_vector *start, t_vector *finish)
{
	t_vector	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = finish->x;
	start->y = finish->y;
	finish->x = tmp.x;
	finish->y = tmp.y;
}

void	ft_vec2_swap(t_vector2 *start, t_vector2 *finish)
{
	t_vector2	tmp;

	tmp.x = start->x;
	tmp.y = start->y;
	start->x = finish->x;
	start->y = finish->y;
	finish->x = tmp.x;
	finish->y = tmp.y;
}
