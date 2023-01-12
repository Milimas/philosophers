/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   birth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 15:09:07 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(t_arguments *arg, int i)
{
	arg->philosophers[i].number_of_philosopher = i + 1;
	gettimeofday(&arg->philosophers[i].last_meal, NULL);
	arg->philosophers[i].time_to_die = arg->time_to_die;
	arg->philosophers[i].time_to_eat = arg->time_to_eat;
	arg->philosophers[i].time_to_sleep = arg->time_to_sleep;
	arg->philosophers[i].number_of_times_must_eat
		= arg->number_of_times_each_philosopher_must_eat;
	arg->philosophers[i].right
		= &arg->philosophers[(i + 1) % arg->number_of_philosophers];
	pthread_mutex_init(&arg->philosophers[i].fork, NULL);
	arg->philosophers[i].arg = arg;
}

void	philosophers_birth(t_arguments *arg)
{
	int	i;

	i = 0;
	arg->philosophers = malloc(sizeof(t_philosopher) * arg->number_of_forks);
	while (i < arg->number_of_philosophers)
	{
		init_philosopher(arg, i);
		pthread_create(
			&arg->philosophers[i].thread,
			NULL,
			&philosopher,
			&arg->philosophers[i]
			);
		pthread_detach(arg->philosophers->thread);
		i++;
	}
	check_death(arg);
	while (i--)
	{
		pthread_join(arg->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&arg->philosophers[i].fork);
	}
}
