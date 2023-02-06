/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:52:11 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/06 19:34:09 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

long long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	wait_milliseconds(long long milliseconds, int is_dead, t_arguments *arg)
{
	long long	start;

	if (is_dead)
		return ;
	start = get_time(arg);
	usleep((milliseconds * 1000L) - ((milliseconds * 1000L) >> 5));
	while (get_time(arg) < start + milliseconds)
		usleep(1000);
}
