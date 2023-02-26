/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/26 05:03:50 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(int argc, char **argv, t_philo **philo, t_rules *rules)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (!philo)
		return (1);
	i = -1;
	while (++i < rules->number_of_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		(*philo)[i].index = i + 1;
		(*philo)[i].must_eat = -1;
		if (argc == 6)
			(*philo)[i].must_eat = atoi(argv[5]);
		(*philo)[i].rules = rules;
		(*philo)[i].time_to_eat = atoi(argv[3]);
		(*philo)[i].time_to_sleep = atoi(argv[4]);
		(*philo)[i].forks = rules->forks;
		(*philo)[i].start_time = ft_gettime(0);
		(*philo)[i].last_meal = ft_gettime(0);
	}
	return (0);
}

int	init_rules(char **argv, t_rules *rules)
{
	rules->number_of_philos = atoi(argv[1]);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philos);
	if (rules->number_of_philos < 2)
		return (1);
	rules->time_to_die = atoi(argv[2]);
	pthread_mutex_init(&rules->death_lock, NULL);
	pthread_mutex_init(&rules->write_lock, NULL);
	return (0);
}
