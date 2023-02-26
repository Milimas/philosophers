/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:44:00 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/26 05:04:07 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->index - 1]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->forks[philo->index
		% philo->rules->number_of_philos]);
	print_status(philo, "has taken a fork");
}

void	give_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[philo->index
		% philo->rules->number_of_philos]);
	pthread_mutex_unlock(&philo->forks[philo->index - 1]);
}
