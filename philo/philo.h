/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:09:18 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/26 05:26:43 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_rules
{
	long			time_to_die;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	*forks;
	int				number_of_philos;
}	t_rules;

typedef struct s_philo
{
	pthread_t		thid;
	int				index;
	pthread_mutex_t	*forks;
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
int		start_philos(t_philo *philo);
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
int		grim_reaper(t_philo *philo, t_rules *rules);

// destroy
int		destroy_rules(t_rules *rules);
int		destroy_philos(t_philo *philo);

// atoi
int		ft_atoi(const char *str);

#endif