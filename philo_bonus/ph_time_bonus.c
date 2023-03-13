/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:52:11 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/03/10 02:18:32 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_gettime(long time)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (ft_convtime(now) - time);
}

long	ft_convtime(struct timeval time)
{
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	ft_sleep(long time, long from)
{
	usleep(time * 900);
	while (ft_gettime(from) < time)
		usleep(50);
	return (ft_gettime(from) - time);
}
