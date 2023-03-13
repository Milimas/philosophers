/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:16 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/03/13 20:45:11 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philos(int argc, char **argv, t_philo **philo, t_rules *rules)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (!philo)
		return (1);
	i = -1;
	while (++i < rules->number_of_philos)
	{
		(*philo)[i].forks = rules->forks;
		(*philo)[i].index = i + 1;
		(*philo)[i].must_eat = -1;
		if (argc == 6)
			(*philo)[i].must_eat = ft_atoi(argv[5]);
		(*philo)[i].rules = rules;
		(*philo)[i].time_to_eat = ft_atoi(argv[3]);
		(*philo)[i].time_to_sleep = ft_atoi(argv[4]);
		(*philo)[i].forks = rules->forks;
	}
	return (0);
}

int	init_rules(char **argv, t_rules *rules)
{
	rules->number_of_philos = ft_atoi(argv[1]);
	if (rules->number_of_philos <= 0)
		exit(2);
	rules->time_to_die = ft_atoi(argv[2]);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		exit(1);
	sem_unlink("/ph_forks");
	sem_unlink("/ph_write");
	sem_unlink("/ph_death");
	rules->forks = sem_open("/ph_forks", O_CREAT, 0644,
			rules->number_of_philos);
	rules->write_lock = sem_open("/ph_write", O_CREAT, 0644, 1);
	rules->death_lock = sem_open("/ph_death", O_CREAT, 0644, 1);
	gettimeofday(&rules->start_time, NULL);
	return (0);
}
