/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/06 20:05:16 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"


#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

// int get_named_semaphore_value(const char *name)
// {
//     sem_t	*sem;
//     int value = 0;
// 	int i = -1;
	
// 	sem = sem_open(name, O_EXCL);
//     if (sem == SEM_FAILED) {
//         perror("get_named_sem: sem_open");
//         return -1;
//     }
//     while (sem_trywait(sem) == 0) 
//         value++;
// 	printf("vlaue :%d\n", value);
//     if (errno != EAGAIN) {
//         perror("get_named_sem: sem_trywait");
//         sem_close(sem);
//         return -1;
//     }
//     while (i++ < value)
//         sem_post(sem);
//     sem_close(sem);
//     return value;
// }

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
	sem_wait(arg->gettime_lock);
	gettimeofday(&arg->program_start_time, NULL);
	sem_post(arg->gettime_lock);
	sem_unlink("write_lock");
	sem_unlink("check_death");
	sem_unlink("gettime");
	sem_unlink("birth_mutex");
	arg->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	arg->birth_mutex = sem_open("birth_mutex", O_CREAT, 0644, 0);
	// arg->death_check_lock = sem_open("check_death", O_CREAT, 0644, 1);
	// arg->gettime_lock = sem_open("gettime", O_CREAT, 0644, 1);
}

void	log_life(t_philosopher ph, char *message)
{
	sem_wait(ph.arg->write_lock);
		ft_putnbr_fd(get_time(ph.arg) - convert_time(ph.arg->program_start_time), 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(ph.number_of_philosopher, 1);
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(message, 1);
		ft_putchar_fd('\n', 1);
	sem_post(ph.arg->write_lock);
}

void	*philosopher(void *ph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ph;
	sem_wait(philo->arg->birth_mutex);
	gettimeofday(&philo->arg->program_start_time, NULL);
	gettimeofday(&philo->last_meal, NULL);
	if (pthread_create(&philo->death_check, NULL, &check_death, philo) == -1)
		exit(1);
	if (!(philo->number_of_philosopher % 2))
		wait_milliseconds(philo->time_to_eat >> 1, 0, philo->arg);
	while (!philo->arg->is_philosopher_dead && philo->number_of_times_must_eat)
	{
		take_forks(philo);
		// sem_wait(philo->arg->death_check_lock);
		log_life(*philo, "is eating");
		gettimeofday(&philo->last_meal, NULL);
		// sem_post(philo->arg->death_check_lock);
		wait_milliseconds(philo->time_to_eat, philo->arg->is_philosopher_dead, philo->arg);
		// gettimeofday(&philo->last_meal, NULL);
		philo->number_of_times_must_eat -= philo->number_of_times_must_eat > 0;
		give_forks(philo);
		log_life(*philo, "is sleeping");
		wait_milliseconds(philo->time_to_sleep,
			philo->arg->is_philosopher_dead, philo->arg);
		log_life(*philo, "is thinking");
	}
	philo->arg->number_of_philosophers_done_eating++;
	exit(0);
	return (philo);
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
}

// int	main1(int argc, char **argv)
// {
// 	t_arguments arg;
	
// 	if (argc < 5 || argc > 6)
// 	{
// 		return (EXIT_FAILURE);
// 	}

// 	// int arg
// 	arg.number_of_philosophers = ft_atoi(argv[1]);
// 	arg.number_of_forks = ft_atoi(argv[1]);
// 	arg.time_to_die = ft_atoi(argv[2]);
// 	arg.time_to_eat = ft_atoi(argv[3]);
// 	arg.time_to_sleep = ft_atoi(argv[4]);
// 	arg.number_of_times_each_philosopher_must_eat = -1;
// 	if (argc == 6)
// 		arg.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
// 	arg.number_of_philosophers_done_eating = 0;
// 	arg.is_philosopher_dead = 0;
// 	arg.philosophers = malloc(sizeof(t_philosopher) * arg.number_of_philosophers);
// 	sem_unlink("write_lock");
// 	sem_unlink("check_death");
// 	sem_unlink("gettime");
// 	arg.write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
// 	arg.death_check_lock = sem_open("check_death", O_CREAT, 0644, 1);
// 	arg.gettime_lock = sem_open("gettime", O_CREAT, 0644, 1);
	
// 	// init philosophers
// 	int i = 0;
// 	while (i < arg.number_of_philosophers)
// 	{
// 		t_philosopher	*philo = &arg.philosophers[i];
// 		arg.philosophers[i].number_of_philosopher = i;
// 		arg.philosophers[i].time_to_die = arg.time_to_die;
// 		arg.philosophers[i].time_to_eat = arg.time_to_eat;
// 		arg.philosophers[i].time_to_sleep = arg.time_to_sleep;
// 		arg.philosophers[i].number_of_times_must_eat
// 			= arg.number_of_times_each_philosopher_must_eat;
// 		arg.philosophers[i].right
// 			= &arg.philosophers[(i + 1) % arg.number_of_philosophers];
// 		arg.philosophers[i].arg = &arg;
// 		arg.philosophers[i].fork_sem_name = ft_strjoin("/philo_sem_", ft_itoa(i + 1));
// 		sem_unlink(philo->fork_sem_name);
// 		arg.philosophers[i].fork = sem_open(arg.philosophers[i].fork_sem_name, O_CREAT, 0644, 1);
// 		printf("philosopher number: %d is alive\tsem_addr: %p\n",
// 				philo->number_of_philosopher,
// 				&philo->fork);
// 		i++;
// 	}

// 	i = 0;
// 	while (i < arg.number_of_philosophers)
// 	{
// 		gettimeofday(&arg.program_start_time, NULL);
// 		if (fork() == 0) // child
// 		{
// 			t_philosopher	*philo = &arg.philosophers[i];
// 			gettimeofday(&philo->last_meal, NULL);
// 			log_life(*philo, "is born");
// 			while (1)
// 			{
// 				// take forks
// 				sem_wait(arg.write_lock);
// 				if (!(philo->number_of_philosopher % 2))
// 				{
// 					ft_putnbr_fd((unsigned long long)&philo->fork, 1);
// 					ft_putchar_fd('\n', 1);
// 					ft_putnbr_fd((unsigned long long)&philo->right->fork, 1);
// 					ft_putchar_fd('\n', 1);
// 				}
// 				if (philo->number_of_philosopher % 2)
// 				{
// 					ft_putnbr_fd((unsigned long long)&philo->right->fork, 1);
// 					ft_putchar_fd('\n', 1);
// 					ft_putnbr_fd((unsigned long long)&philo->fork, 1);
// 					ft_putchar_fd('\n', 1);
// 				}
// 				sem_post(arg.write_lock);
// 				take_forks(philo);
				
// 				// eating
// 				gettimeofday(&philo->last_meal, NULL);
// 				log_life(*philo, "is eating");
// 				wait_milliseconds(philo->time_to_eat, 0, &arg);
// 				gettimeofday(&philo->last_meal, NULL);
// 				//done eating
				
// 				// give forks
// 				give_forks(philo);

// 				// sleeping
// 				wait_milliseconds(arg.time_to_sleep, 0, &arg);
// 				log_life(*philo, "is sleeping");
// 				// done sleeping
				
// 				// thinking
// 				log_life(*philo, "is thinking");
// 				// done thinking
// 			}
// 			exit(0);
// 		}
// 		i++;
// 	}
	
// 	i = 0;
// 	while (i < arg.number_of_philosophers)
// 	{
// 		waitpid(-1, NULL, 0);
// 		i++;
// 	}
// 	return (0);
// }



