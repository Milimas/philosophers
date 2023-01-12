/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 09:04:19 by aminebeihaq      ###   ########.fr       */
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
}

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

unsigned long long	convert_time(struct timeval time)
{
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	wait_milliseconds(unsigned long long milliseconds)
{
	unsigned long long	start;

	start = get_time();
	usleep(milliseconds - milliseconds / 100);
	while (get_time() < start + milliseconds)
		;
}

void	log_life(int no, char *message, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	ft_putnbr_fd(get_time(), 1);
	ft_putchar_fd(' ', 1);
	ft_putnbr_fd(no, 1);
	ft_putchar_fd(' ', 1);
	ft_putstr_fd(message, 1);
	ft_putchar_fd('\n', 1);
	pthread_mutex_unlock(lock);
}

void	*philosopher(void *ph)
{
	t_philosopher	*philo;

	philo = ph;
	while (philo->is_alive && philo->number_of_times_must_eat)
	{
		// printf("%llu %d is thinking\n", get_time(), philo->number_of_philosopher);
		log_life(philo->number_of_philosopher, "is thinking", &philo->arg->write_lock);
		if (get_time() - philo->time_to_die > convert_time(philo->last_meal))
		{
			philo->right->is_alive = 0;
			log_life(philo->number_of_philosopher, "is dead", &philo->arg->write_lock);
			pthread_mutex_unlock(&philo->right->fork);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_destroy(&philo->fork);
			return (NULL);
		}
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->right->fork);
		if (get_time() - philo->time_to_die > convert_time(philo->last_meal))
		{
			// printf("%llu %d is dead\n", get_time(), philo->number_of_philosopher);
			// printf("%llu %d is dead =========================================================\n", get_time(), philo->number_of_philosopher);
			philo->right->is_alive = 0;
			log_life(philo->number_of_philosopher, "is dead", &philo->arg->write_lock);
			pthread_mutex_unlock(&philo->right->fork);
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_destroy(&philo->fork);
			return (NULL);
		}
		// printf("%llu %d is eating\n", get_time(), philo->number_of_philosopher);
		log_life(philo->number_of_philosopher, "is eating", &philo->arg->write_lock);
		wait_milliseconds(philo->time_to_eat);
		gettimeofday(&philo->last_meal, NULL);
		philo->number_of_times_must_eat -= philo->number_of_times_must_eat > 0;
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->fork);
		// printf("%llu %d is sleeping\n", get_time(), philo->number_of_philosopher);
		log_life(philo->number_of_philosopher, "is sleeping", &philo->arg->write_lock);
		wait_milliseconds(philo->time_to_sleep);
	}
	philo->right->is_alive = 0;
}

void	philosophers_birth(t_arguments *arg)
{
	int	i;

	i = 0;
	arg->philosophers = malloc(sizeof(t_philosopher) * arg->number_of_forks);
	pthread_mutex_init(&arg->write_lock, NULL);
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
		arg->philosophers[i].is_alive = !pthread_create(&arg->philosophers[i].thread, NULL, &philosopher, &arg->philosophers[i]);
		pthread_detach(arg->philosophers->thread);
		i++;
	}
	while (i--)
	{
		pthread_join(arg->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&arg->philosophers[i].fork);
		// printf("join: %d\n", i + 1);
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
