/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 09:44:36 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	help(void)
{
	printf("philosophers ttd tte tts [notepme]\n"
		"\tttd:\t\ttime to die\n"
		"\ttte:\t\ttime to eat\n"
		"\ttts:\t\ttime to sleep\n"
		"\tnotempe:\tnumber of times each philosopher must eat\n");
}

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
	pthread_mutex_init(&arg->write_lock, NULL);
	pthread_mutex_init(&arg->death_check_lock, NULL);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

long long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	wait_milliseconds(long long milliseconds, int is_dead)
{
	long long	start;

	if (is_dead)
		return ;
	start = get_time();
	usleep(milliseconds - milliseconds / 100);
	while (get_time() < start + milliseconds)
		;
}

void	log_life(t_philosopher ph, char *message)
{
	pthread_mutex_lock(&ph.arg->write_lock);
	if (!ph.arg->is_philosopher_dead)
	{
		ft_putnbr_fd(get_time(), 1);
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
		pthread_mutex_lock(&philo->right->fork);
		pthread_mutex_lock(&philo->arg->death_check_lock);
		log_life(*philo, "is eating");
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&philo->arg->death_check_lock);
		wait_milliseconds(philo->time_to_eat, philo->arg->is_philosopher_dead);
		philo->number_of_times_must_eat -= philo->number_of_times_must_eat > 0;
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->fork);
		log_life(*philo, "is sleeping");
		wait_milliseconds(philo->time_to_sleep, philo->arg->is_philosopher_dead);
		log_life(*philo, "is thinking");
	}
	philo->arg->number_of_philosophers_done_eating++;
	return (NULL);
}

int		check_death(t_arguments *arg)
{
	int	i;

	while (arg->number_of_philosophers_done_eating
		!= arg->number_of_philosophers)
	{
		i = -1;
		while (++i < arg->number_of_philosophers && !arg->is_philosopher_dead
			&& arg->number_of_philosophers_done_eating
			!= arg->number_of_philosophers)
		{
			pthread_mutex_lock(&arg->death_check_lock);
			if (get_time() - convert_time(arg->philosophers[i].last_meal)
				> arg->time_to_die)
			{
				log_life(arg->philosophers[i], "is dead");
				arg->is_philosopher_dead = 1;
			}
			pthread_mutex_unlock(&arg->death_check_lock);
			usleep(50);
		}
		if (arg->is_philosopher_dead)
			break ;
	}
}

void	philosophers_birth(t_arguments *arg)
{
	int	i;

	i = 0;
	arg->philosophers = malloc(sizeof(t_philosopher) * arg->number_of_forks);
	while (i < arg->number_of_philosophers)
	{
		arg->philosophers[i].number_of_philosopher = i + 1;
		gettimeofday(&arg->philosophers[i].last_meal, NULL);
		arg->philosophers[i].time_to_die = arg->time_to_die;
		arg->philosophers[i].time_to_eat = arg->time_to_eat;
		arg->philosophers[i].time_to_sleep = arg->time_to_sleep;
		arg->philosophers[i].number_of_times_must_eat = arg->number_of_times_each_philosopher_must_eat;
		arg->philosophers[i].right = &arg->philosophers[(i + 1) % arg->number_of_philosophers];
		pthread_mutex_init(&arg->philosophers[i].fork, NULL);
		arg->philosophers[i].arg = arg;
		pthread_create(&arg->philosophers[i].thread, NULL, &philosopher, &arg->philosophers[i]);
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
