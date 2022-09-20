/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:13:32 by faventur          #+#    #+#             */
/*   Updated: 2022/09/20 14:00:52 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

int	main(int argc, char *argv[])
{
	t_program	program;
	t_vector	size;
	int			i;

	i = 0;
	program.mlx = mlx_init(512, 512, "test", true);
	check_args(argc);
	check_map_extension(argv);
	program.map = ft_map_reader(argv[1]);
	if (!program.map || !ft_map_parser(program.map))
		ft_puterror("Error!");
	program.frame = 0;
	program.step_counter = 0;
	size = calculate_window_size(program.map);
	program.window = ft_new_window(program.mlx, size.x, size.y,
			"Befana!");
	program.pixies = ft_put_sprite(&program);
	ft_display_map(&program, program.map, program.pixies);
//	mlx_loop_hook(program.mlx, *ft_input, &program);
	mlx_loop_hook(program.mlx, *ft_update, &program);
	mlx_loop(program.mlx);
	mlx_terminate(program.mlx);
}
