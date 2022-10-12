/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:03:57 by faventur          #+#    #+#             */
/*   Updated: 2022/10/12 14:37:55 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	check_args(char argc)
{
	if (argc != 2)
		throw_err_ex("Error: Invalid number of arguments.");
}

t_map	*check(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	check_args(argc);
	check_map_extension(argv);
	map = check_map_integrity(argv[1]);
	return (map);
}
