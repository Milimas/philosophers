/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:59 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/03/10 03:43:29 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full(t_philo *philo, t_rules *rules)
{
	int	i;
	int	number_of_full;

	i = -1;
	number_of_full = 0;
	while (++i < rules->number_of_philos)
	{
		pthread_mutex_lock(&rules->death_lock);
		if (philo[i].must_eat == 0)
			number_of_full++;
		pthread_mutex_unlock(&rules->death_lock);
	}
	if (number_of_full == rules->number_of_philos)
	{
		pthread_mutex_lock(&rules->write_lock);
		return (1);
	}
	return (0);
}

int	grim_reaper(t_philo *philo, t_rules *rules)
{
	int	i;

	i = -1;
	while (i)
	{
		i = -1;
		while (++i < rules->number_of_philos)
		{
			pthread_mutex_lock(&rules->death_lock);
			if (ft_gettime(ft_convtime(philo->last_meal)) >= rules->time_to_die)
			{
				print_status(&philo[i], "died");
				destroy_rules(rules);
				destroy_philos(philo);
				return (1);
			}
			pthread_mutex_unlock(&rules->death_lock);
		}
		usleep(200);
		if (check_full(philo, rules))
			return (0);
	}
	return (0);
}
