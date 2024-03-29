/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/03/12 17:50:26 by abeihaqi         ###   ########.fr       */
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
			(*philo)[i].must_eat = ft_atoi(argv[5]);
		(*philo)[i].rules = rules;
		(*philo)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo)[i].time_to_sleep = ft_atoi(argv[4]);
		gettimeofday(&(*philo)[i].last_meal, NULL);
		(*philo)[i].right = &rules->forks[i];
		(*philo)[i].left = &rules->forks[(i + 1) % rules->number_of_philos];
	}
	return (0);
}

int	init_rules(char **argv, t_rules *rules)
{
	rules->number_of_philos = ft_atoi(argv[1]);
	if (rules->number_of_philos <= 0)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philos);
	if (!rules->forks)
		return (1);
	rules->time_to_die = ft_atoi(argv[2]);
	pthread_mutex_init(&rules->death_lock, NULL);
	pthread_mutex_init(&rules->write_lock, NULL);
	gettimeofday(&rules->start_time, NULL);
	return (0);
}
