/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:52:11 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 14:53:57 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

long long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	wait_milliseconds(long long milliseconds, int is_dead)
{
	long long	start;

	if (is_dead)
		return ;
	start = get_time();
	usleep((milliseconds - milliseconds / 2) * 1000);
	while (get_time() < start + milliseconds)
		;
}
