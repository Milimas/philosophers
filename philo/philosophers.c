/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/28 01:47:46 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse_arg(int argc, char **argv, t_arguments *arg)
{
	arg->number_of_philosophers = ft_atoi(argv[1]);
	arg->number_of_forks = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		arg->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	arg->number_of_philosophers_done_eating = 0;
	arg->is_philosopher_dead = 0;
	gettimeofday(&arg->program_start_time, NULL);
	pthread_mutex_init(&arg->write_lock, NULL);
	pthread_mutex_init(&arg->death_check_lock, NULL);
}

void	log_life(t_philosopher ph, char *message)
{
	pthread_mutex_lock(&ph.arg->write_lock);
	if (!ph.arg->is_philosopher_dead)
	{
		ft_putnbr_fd(get_time() - convert_time(ph.arg->program_start_time), 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(ph.number_of_philosopher, 1);
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(message, 1);
		ft_putchar_fd('\n', 1);
	}
	pthread_mutex_unlock(&ph.arg->write_lock);
}

void	*philosopher(void *ph)
{
	t_philosopher	*philo;

	philo = ph;
	while (!philo->arg->is_philosopher_dead && philo->number_of_times_must_eat)
	{
		pthread_mutex_lock(&philo->fork);
		log_life(*philo, "has taken left a fork");
		pthread_mutex_lock(&philo->right->fork);
		log_life(*philo, "has taken right a fork");
		pthread_mutex_lock(&philo->arg->death_check_lock);
		log_life(*philo, "is eating");
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&philo->arg->death_check_lock);
		wait_milliseconds(philo->time_to_eat, philo->arg->is_philosopher_dead);
		gettimeofday(&philo->last_meal, NULL);
		philo->number_of_times_must_eat -= philo->number_of_times_must_eat > 0;
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->fork);
		log_life(*philo, "is sleeping");
		wait_milliseconds(philo->time_to_sleep,
			philo->arg->is_philosopher_dead);
		log_life(*philo, "is thinking");
	}
	philo->arg->number_of_philosophers_done_eating++;
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_arguments	arg;

	if (argc < 5 || argc > 6)
	{
		help();
		return (EXIT_SUCCESS);
	}
	parse_arg(argc, argv, &arg);
	philosophers_birth(&arg);
	return (EXIT_SUCCESS);
}
