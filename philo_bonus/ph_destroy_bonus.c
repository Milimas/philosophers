/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_destroy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 04:55:36 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/26 05:45:00 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	destroy_rules(t_rules *rules)
{
	sem_close(rules->forks);
	sem_close(rules->write_lock);
	sem_close(rules->death_lock);
	sem_unlink("/ph_forks");
	sem_unlink("/ph_write");
	sem_unlink("/ph_death");
	return (0);
}

int	destroy_philos(t_philo *philo)
{
	free(philo);
	return (0);
}
