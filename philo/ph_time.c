/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:52:11 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/26 05:05:02 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(long time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000) - time);
}

long	ft_sleep(long time, long from)
{
	if (time > 60)
		usleep((time * .9) * 1000);
	while (ft_gettime(from) < time)
		usleep(50);
	return (ft_gettime(from) - time);
}
