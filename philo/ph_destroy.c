/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:55:36 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/03/10 03:20:55 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_rules(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->number_of_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
	}
	pthread_mutex_destroy(&rules->death_lock);
	pthread_mutex_destroy(&rules->write_lock);
	free(rules->forks);
	return (0);
}

int	destroy_philos(t_philo *philo)
{
	free(philo);
	return (0);
}
