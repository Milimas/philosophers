/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:59 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/06 20:04:10 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_death(void *ph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ph;
	while (philo->number_of_times_must_eat)
	{
		sem_wait(philo->arg->death_check_lock);
		sem_wait(philo->arg->write_lock);
		if (get_time(philo->arg) - convert_time(philo->last_meal)
			> philo->arg->time_to_die && philo->number_of_times_must_eat)
		{
			printf("%lld %d died\n",
				get_time(philo->arg) - convert_time(philo->arg->program_start_time),
				philo->number_of_philosopher);
			exit(1);
		}
		sem_post(philo->arg->write_lock);
		sem_post(philo->arg->death_check_lock);
		usleep(1000 / philo->arg->number_of_philosophers);
	}
	return (philo);
}
