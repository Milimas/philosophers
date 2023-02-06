/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 00:44:00 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/06 20:06:16 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_philosopher *philo)
{
	// printf("before %s: %d\n", philo->fork_sem_name, get_named_semaphore_value(philo->fork_sem_name));
	// printf("before %s: %d\n", philo->right->fork_sem_name, get_named_semaphore_value(philo->right->fork_sem_name));
	if ((philo->number_of_philosopher % 2))
	{
		sem_wait(philo->right->fork);
		log_life(*philo, "has taken a fork");
		sem_wait(philo->fork);
		log_life(*philo, "has taken a fork");
	}
	else
	{
		sem_wait(philo->fork);
		log_life(*philo, "has taken a fork");
		sem_wait(philo->right->fork);
		log_life(*philo, "has taken a fork");
	}
}

void	give_forks(t_philosopher *philo)
{
	if ((philo->number_of_philosopher % 2)
		&& philo->number_of_philosopher == philo->arg->number_of_philosophers)
	{
		sem_post(philo->fork);
		sem_post(philo->right->fork);
	}
	else
	{
		sem_post(philo->right->fork);
		sem_post(philo->fork);
	}
	// log_life(*philo, "has gave a fork");
	// printf("after post %s: %d\n", philo->fork_sem_name, get_named_semaphore_value(philo->fork_sem_name));
	// printf("after post %s: %d\n", philo->right->fork_sem_name, get_named_semaphore_value(philo->right->fork_sem_name));
}
