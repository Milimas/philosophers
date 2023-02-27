/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:59 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/27 00:16:15 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*grim_reaper(void *ph)
{
	t_philo	*philo;

	philo = ph;
	while (1)
	{
		sem_wait(philo->rules->death_lock);
		if (!philo->must_eat)
			break ;
		if (ft_gettime(philo->last_meal) >= philo->rules->time_to_die)
		{
			print_status(philo, "died");
			exit(1);
		}
		sem_post(philo->rules->death_lock);
		usleep(1000);
	}
	sem_post(philo->rules->death_lock);
	return (0);
}
