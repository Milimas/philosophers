/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:09:18 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/26 23:25:19 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_rules
{
	long			time_to_die;
	sem_t			*write_lock;
	sem_t			*death_lock;
	sem_t			*forks;
	sem_t			*start_lock;
	int				number_of_philos;
}	t_rules;

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		death_thid;
	int				index;
	sem_t			*forks;
	long			start_time;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_meal;
	long			next_meal;
	int				must_eat;
	t_rules			*rules;
}	t_philo;

// init
int		init_philos(int argc, char **argv, t_philo **philo, t_rules *rules);
int		init_rules(char **argv, t_rules *rules);

// philo
void	start_philos(t_philo *philo);
void	*philosopher(void *ph);

// fork
void	take_forks(t_philo *philo);
void	give_forks(t_philo *philo);

// actions
void	ph_eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_think(t_philo *philo);

// print
void	help(void);
void	print_status(t_philo *philo, char *msg);

// time
long	ft_gettime(long time);
long	ft_sleep(long time, long from);

// check
void	*grim_reaper(void *philo);

// wait
void	wait_philos(t_philo *philo, t_rules *rules);

// destroy
int		destroy_rules(t_rules *rules);
int		destroy_philos(t_philo *philo);

// atoi
int		ft_atoi(const char *str);

#endif