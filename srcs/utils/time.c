/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaur <albaur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:09:08 by albaur            #+#    #+#             */
/*   Updated: 2022/11/03 12:02:05 by albaur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include "mlx_utils.h"

double	get_time(void)
{
	return (glfwGetTime());
}

int	get_delay(int startnow, int min)
{
	static struct timeval	start;
	static struct timeval	stop;
	unsigned long			delta;

	if (startnow)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	else
		gettimeofday(&stop, NULL);
	delta = (stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec;
	if (delta < (unsigned long)min)
		usleep((min - delta) % 1000000);
	return (delta - min);
}
