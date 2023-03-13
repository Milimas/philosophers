/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:50:59 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/03/12 17:50:38 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *ph)
{
	t_philo	*philo;

	philo = ph;
	if (!(philo->index % 2))
		ft_sleep(philo->time_to_eat,
			ft_convtime(philo->rules->start_time) - 30);
	while (1)
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (philo);
}

int	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->rules->number_of_philos)
	{
		if (pthread_create(&philo[i].thid, NULL, &philosopher, &philo[i]))
			return (1);
		if (pthread_detach(philo[i].thid))
			return (1);
	}
	return (0);
}
