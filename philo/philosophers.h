/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 03:52:35 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 09:01:40 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_arguments;

typedef struct s_philosopher
{
	pthread_t				thread;
	int						number_of_philosopher;
	pthread_mutex_t			fork;
	struct timeval			last_meal;
	unsigned long long		time_to_die;
	unsigned long long		time_to_eat;
	unsigned long long		time_to_sleep;
	int						number_of_times_must_eat;
	int						is_alive;
	struct s_philosopher	*right;
	struct s_arguments		*arg;
}	t_philosopher;

typedef struct s_arguments
{
	int					number_of_philosophers;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					number_of_forks;
	t_philosopher		*philosophers;
	struct timeval		program_start_time;
	pthread_mutex_t		write_lock;
}	t_arguments;

int		ft_atoi(const char *str);
void	ft_putnbr_fd(unsigned long long n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif
