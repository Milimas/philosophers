/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:45:47 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/03/10 03:41:27 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_eat(t_philo *philo)
{
	take_forks(philo);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_lock(&philo->rules->death_lock);
	philo->must_eat -= (philo->must_eat > 0);
	pthread_mutex_unlock(&philo->rules->death_lock);
	print_status(philo, "is eating");
	ft_sleep(philo->time_to_eat, ft_gettime(0));
	give_forks(philo);
}

void	ph_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo->time_to_sleep, ft_gettime(0));
}

void	ph_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
