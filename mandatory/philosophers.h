/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 03:52:35 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/10 04:39:41 by aminebeihaq      ###   ########.fr       */
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

typedef struct s_arguments
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	number_of_forks;
}	t_arguments;

typedef struct s_philosopher
{
	int						number_of_philosopher;
	int						fork;
	int						is_eating;
	int						is_sleeping;
	int						is_thinking;
	int						is_dead;
	struct s_philosopher	*right;
}	t_philosopher;

int	ft_atoi(const char *str);

#endif
