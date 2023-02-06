/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 03:52:35 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/06 14:42:11 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>

struct	s_arguments;

typedef struct s_philosopher
{
	pid_t					pid;
	char					*fork_sem_name;
	pthread_t				death_check;
	int						number_of_philosopher;
	struct timeval			last_meal;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	int						number_of_times_must_eat;
	struct s_philosopher	*right;
	sem_t					*fork;
	struct s_arguments		*arg;
}	t_philosopher;

typedef struct s_arguments
{
	int					number_of_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					number_of_forks;
	t_philosopher		*philosophers;
	struct timeval		program_start_time;
	sem_t				*birth_mutex;
	sem_t				*write_lock;
	sem_t				*death_check_lock;
	sem_t				*gettime_lock;
	int					is_philosopher_dead;
	int					number_of_philosophers_done_eating;
}	t_arguments;

int			ft_atoi(const char *str);
void		ft_putnbr_fd(unsigned long long n, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		help(void);
long long	get_time(t_arguments *arg);
void		wait_milliseconds(long long milliseconds, int is_dead, t_arguments *arg);
long long	convert_time(struct timeval time);
void		philosophers_birth(t_arguments *arg);
void		*check_death(void *arg);
void		philosophers_birth(t_arguments *arg);
void		*philosopher(void *ph);
void		log_life(t_philosopher ph, char *message);
void		take_forks(t_philosopher *philo);
void		give_forks(t_philosopher *philo);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char *s2);

// debug
int get_named_semaphore_value(const char *name);

#endif
