/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   birth_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/06 14:49:39 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <sys/ipc.h>

void	init_philosopher(t_arguments *arg, int i)
{
	arg->philosophers[i].number_of_philosopher = i + 1;
	arg->philosophers[i].time_to_die = arg->time_to_die;
	arg->philosophers[i].time_to_eat = arg->time_to_eat;
	arg->philosophers[i].time_to_sleep = arg->time_to_sleep;
	arg->philosophers[i].number_of_times_must_eat
		= arg->number_of_times_each_philosopher_must_eat;
	arg->philosophers[i].right
		= &arg->philosophers[(i + 1) % arg->number_of_philosophers];
	arg->philosophers[i].arg = arg;
	arg->philosophers[i].fork_sem_name = ft_strjoin("/philo_sem_", ft_itoa(i + 1));
	sem_unlink(arg->philosophers[i].fork_sem_name);
	arg->philosophers[i].fork = sem_open(arg->philosophers[i].fork_sem_name, O_CREAT, 0644, 1);
	// printf("%s: %d\n", arg->philosophers[i].fork_sem_name, get_named_semaphore_value(arg->philosophers[i].fork_sem_name));
	// sem_wait(arg->gettime_lock);
	// gettimeofday(&arg->philosophers[i].last_meal, NULL);
	// sem_post(arg->gettime_lock);
}

void	philosophers_birth(t_arguments *arg)
{
	int	i;
	int	status;

	i = 0;
	arg->philosophers = malloc(sizeof(t_philosopher) * arg->number_of_forks);
	while (i < arg->number_of_philosophers)
	{
		init_philosopher(arg, i);
		i++;
	}
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		arg->philosophers[i].pid = fork();
		if (!arg->philosophers[i].pid)
			philosopher(&arg->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		sem_post(arg->birth_mutex);
		i++;
	}
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < arg->number_of_philosophers)
			{
				kill(arg->philosophers[i].pid, 9);
				i++;
			}
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < arg->number_of_philosophers)
	{
		sem_close(arg->philosophers[i].fork);
		sem_unlink(arg->philosophers[i].fork_sem_name);
		free(arg->philosophers[i].fork_sem_name);
		i++;
	}
}
