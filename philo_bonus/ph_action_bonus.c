/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_action_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:45:47 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/03/10 02:28:26 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ph_eat(t_philo *philo)
{
	take_forks(philo);
	gettimeofday(&philo->last_meal, NULL);
	print_status(philo, "is eating");
	philo->must_eat -= (philo->must_eat > 0);
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
