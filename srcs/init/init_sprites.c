/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:34:31 by faventur          #+#    #+#             */
/*   Updated: 2022/11/08 15:06:04 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	init_hud_draw(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < 20)
	{
		mlx_image_to_window(data->mlx, data->hud.sprites[i].img, 0, 0);
		data->hud.sprites[i].img->enabled = 0;
		++i;
	}
	data->hud.sprites[0].img->enabled = 1;
}

void	init_hud(t_data *data)
{
	ssize_t	i;

	i = -1;
	data->hud.pos = 0;
	data->hud.sprites = malloc(sizeof(t_image) * 20);
	data->hud.sprites[0].texture = mlx_load_xpm42("images/hands/hands_01.xpm42");
	data->hud.sprites[1].texture = mlx_load_xpm42("images/hands/hands_02.xpm42");
	data->hud.sprites[2].texture = mlx_load_xpm42("images/hands/hands_03.xpm42");
	data->hud.sprites[3].texture = mlx_load_xpm42("images/hands/hands_04.xpm42");
	data->hud.sprites[4].texture = mlx_load_xpm42("images/hands/hands_05.xpm42");
	data->hud.sprites[5].texture = mlx_load_xpm42("images/hands/hands_06.xpm42");
	data->hud.sprites[6].texture = mlx_load_xpm42("images/hands/hands_07.xpm42");
	data->hud.sprites[7].texture = mlx_load_xpm42("images/hands/hands_08.xpm42");
	data->hud.sprites[8].texture = mlx_load_xpm42("images/hands/hands_09.xpm42");
	data->hud.sprites[9].texture = mlx_load_xpm42("images/hands/hands_10.xpm42");
	data->hud.sprites[10].texture = mlx_load_xpm42("images/hands/hands_11.xpm42");
	data->hud.sprites[11].texture = mlx_load_xpm42("images/hands/hands_12.xpm42");
	data->hud.sprites[12].texture = mlx_load_xpm42("images/hands/hands_13.xpm42");
	data->hud.sprites[13].texture = mlx_load_xpm42("images/hands/hands_14.xpm42");
	data->hud.sprites[14].texture = mlx_load_xpm42("images/hands/hands_15.xpm42");
	data->hud.sprites[15].texture = mlx_load_xpm42("images/hands/hands_16.xpm42");
	data->hud.sprites[16].texture = mlx_load_xpm42("images/hands/hands_17.xpm42");
	data->hud.sprites[17].texture = mlx_load_xpm42("images/hands/hands_18.xpm42");
	data->hud.sprites[18].texture = mlx_load_xpm42("images/hands/hands_19.xpm42");
	data->hud.sprites[19].texture = mlx_load_xpm42("images/hands/hands_20.xpm42");
	while (++i < 20)
	{
		data->hud.sprites[i].img = mlx_texture_to_image(data->mlx, &data->hud.sprites[i].texture->texture);
		data->hud.sprites[i].img->enabled = 0;
	}
}

void	init_enemy(t_data *data)
{
	t_vec	tmp;

	srand(time(NULL));
	data->enemy.disable_ai = 0;
	data->enemy.alive = 1;
	pathfinding_dist_check(data, MINDISTANCE);
	pathfinding_list_pos(data);
	data->enemy.pos = pathfinding_pos_dist(data, (t_vec2){0, 0},
		data->ray_data.pos, MINDISTANCE);
	if (data->enemy.pos.x == -1 && data->enemy.pos.y == -1)
	{
		tmp = pathfinding_get_pos(data);
		data->enemy.pos = (t_vec2){tmp.x + 0.5, tmp.y + 0.5};
		data->enemy.disable_ai = 1;
	}
	data->enemy.kill_countdown = KILLCOUNTDOWN;
	data->enemy.move_countdown = MOVECOUNTDOWN;
	if (data->enemy.disable_ai == 1)
		printf("Map too small ! Disabling AI...\n");
	data->enemy.warning_text = malloc(sizeof(t_image));
}

void	init_sprites_pos(t_data *data, t_ray *ray)
{
	size_t		i;
	t_s_caster	*sprite;

	i = 0;
	sprite = &data->ray_data.sprite;
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

void	init_sprites(t_data *data, t_ray *ray)
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
	sprite->sprites[1].x = 0;
	sprite->sprites[1].y = 0;
	sprite->sprites[1].texture = 7;
	sprite->sprites[2].x = 0;
	sprite->sprites[2].y = 0;
	sprite->sprites[2].texture = 8;
	init_sprites_pos(data, ray);
}
