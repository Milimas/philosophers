/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:44:00 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/01/29 00:46:50 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	if ((philo->number_of_philosopher % 2))
	{
		pthread_mutex_lock(&philo->fork);
		log_life(*philo, "has taken a fork");
		pthread_mutex_lock(&philo->right->fork);
		log_life(*philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->fork);
		log_life(*philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
		log_life(*philo, "has taken a fork");
	}
}

void	give_forks(t_philosopher *philo)
{
	if ((philo->number_of_philosopher % 2))
	{
		pthread_mutex_unlock(&philo->right->fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->right->fork);
	}
}
