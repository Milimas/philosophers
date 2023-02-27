/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:01 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/26 23:18:57 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	help(void)
{
	printf("philosophers nop ttd tte tts [notepme]\n"
		"\tnop:\t\tnumber of philosophers\n"
		"\tttd:\t\ttime to die\n"
		"\ttte:\t\ttime to eat\n"
		"\ttts:\t\ttime to sleep\n"
		"\tnotempe:\tnumber of times each philosopher must eat\n");
}

void	print_status(t_philo *philo, char *msg)
{
	sem_wait(philo->rules->write_lock);
	printf("%ld %d %s\n", ft_gettime(philo->start_time), philo->index, msg);
	if (*msg != 'd')
		sem_post(philo->rules->write_lock);
}
