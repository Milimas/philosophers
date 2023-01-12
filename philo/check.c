/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:55:59 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/12 14:56:17 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_arguments *arg)
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
			usleep(50000 / arg->number_of_philosophers);
		}
		if (arg->is_philosopher_dead)
			break ;
	}
}
