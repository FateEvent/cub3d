/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_items.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:21:42 by faventur          #+#    #+#             */
/*   Updated: 2022/11/17 11:21:43 by faventur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

void	ft_count_items(char **map)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '8')
				count++;
		}
	}
	if (count)
		ft_printf("%d items left.", count);
	else
		ft_printf("Wonderful, all the items have been collected!");
}
