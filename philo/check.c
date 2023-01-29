/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:59 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/28 06:32:41 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_death(t_arguments *arg)
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
				> arg->time_to_die
				&& arg->philosophers[i].number_of_times_must_eat)
			{
				log_life(arg->philosophers[i], "is dead");
				arg->is_philosopher_dead = 1;
			}
			pthread_mutex_unlock(&arg->death_check_lock);
			usleep(1000 / arg->number_of_philosophers);
		}
		if (arg->is_philosopher_dead)
			break ;
	}
}
