/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:50:59 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/03/13 20:47:35 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher(void *ph)
{
	t_philo	*philo;

	philo = ph;
	gettimeofday(&philo->last_meal, NULL);
	if (pthread_create(&philo->death_thid, NULL, &grim_reaper, ph))
		exit(1);
	pthread_detach(philo->death_thid);
	if (!(philo->index % 2))
		ft_sleep(philo->time_to_eat, ft_convtime(philo->rules->start_time));
	gettimeofday(&philo->last_meal, NULL);
	while (philo->must_eat)
	{
		ph_eat(philo);
		ph_think(philo);
		ph_sleep(philo);
	}
	exit(0);
}

void	start_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->rules->number_of_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == -1)
			exit(1);
		if (philo[i].pid == 0)
			philosopher(&philo[i]);
	}
}
