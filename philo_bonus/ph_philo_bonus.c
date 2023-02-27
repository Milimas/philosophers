/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:50:59 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/27 00:09:26 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philosopher(void *ph)
{
	t_philo	*philo;

	philo = ph;
	sem_wait(philo->rules->start_lock);
	philo->last_meal = ft_gettime(0);
	if (pthread_create(&philo->death_thid, NULL, &grim_reaper, ph))
		exit(1);
	philo->start_time = ft_gettime(0);
	pthread_detach(philo->death_thid);
	if (philo->index % 2)
		usleep(1000);
	while (philo->must_eat)
	{
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
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
		if (!philo[i].pid)
			philosopher(&philo[i]);
	}
	i = -1;
	while (++i < philo->rules->number_of_philos)
		sem_post(philo->rules->start_lock);
}
