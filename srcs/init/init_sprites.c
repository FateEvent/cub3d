/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:34:31 by faventur          #+#    #+#             */
/*   Updated: 2022/11/05 14:34:32 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	sprite_casting_init_pt2(t_ray *ray, t_s_caster *sprite)
{
	size_t	i;

	i = 0;
	while (i < NUMSPRITES)
	{
		sprite->sprite_order[i] = i;
		sprite->sprite_dist[i] = ((ray->pos.x - sprite->sprites[i].x)
				* (ray->pos.x - sprite->sprites[i].x)
				+ (ray->pos.y - sprite->sprites[i].y)
				* (ray->pos.y - sprite->sprites[i].y));
		i++;
	}
	sort_sprites(sprite->sprite_order, sprite->sprite_dist, NUMSPRITES);
}

void	sprite_casting_init(t_data *data, t_ray *ray)
{
	t_s_caster	*sprite;

	sprite = &ray->sprite;
	sprite->sprites = malloc(sizeof(t_sprite) * NUMSPRITES);
	sprite->sprite_order = malloc(sizeof(int) * NUMSPRITES);
	sprite->sprite_dist = malloc(sizeof(double) * NUMSPRITES);
	sprite->z_buffer = malloc(sizeof(double) * ray->resolution.x);
	if (!sprite->sprites || !sprite->z_buffer || !sprite->sprite_order
		|| !sprite->sprite_dist)
		return ;
	sprite->sprites[0].x = data->enemy.pos.x;
	sprite->sprites[0].y = data->enemy.pos.y;
	sprite->sprites[0].texture = 6;
	sprite->sprites[1].x = 3;
	sprite->sprites[1].y = 3;
	sprite->sprites[1].texture = 7;
	sprite->sprites[2].x = 3;
	sprite->sprites[2].y = 4;
	sprite->sprites[2].texture = 8;
	sprite_casting_init_pt2(ray, sprite);
}
