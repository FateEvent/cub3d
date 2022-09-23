/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/09/23 16:16:39 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void ft_hook(void* param)
{
	const mlx_t* mlx;

	mlx = param;
//	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	init_struct(t_program *data)
{
	data->screen->width = 640;
	data->screen->height = 480;
	data->render->delay = 30;
	data->rc->precision = 64;
	data->player->fov = 60;
	data->player->x = 2;
	data->player->y = 2;
	data->player->angle = 90;
	data->screen->half_width = data->screen->width / 2;
	data->screen->half_height = data->screen->height / 2;
	data->rc->increment_angle = data->player->angle / data->screen->width;
	data->player->half_fov = data->player->fov / 2;
}

int	main(int argc, char *argv[])
{
	t_program	program;
	t_image		*pixies;
	int			i;

	i = 0;
	check_args(argc);
//	check_map_extension(argv);
	program.map = ft_map_reader(argv[1]);
//	if (!program.map || !ft_map_parser(program.map))
//		ft_puterror("Error!");
	if (!program.map)
		ft_puterror("Error!");
	init_struct(&program);
	program.frame = 0;
	program.mlx = mlx_init(HEIGHT, WIDTH, "cub3d", true);
	program.img.img = mlx_new_image(program.mlx, HEIGHT, WIDTH);
	if (!program.img.img) //|| (mlx_image_to_window(program.mlx,
			//	program.img.img, 0, 0) < 0))
		ft_puterror("Error!");
	pixies = ft_put_sprite(&program);
	ft_display_map(&program, pixies);
	mlx_image_to_window(program.mlx, program.img.img, 0, 0);
	mlx_loop_hook(program.mlx, ft_hook, program.mlx);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
