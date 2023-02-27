/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 05:38:53 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/26 05:41:06 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_philos(t_philo *philo, t_rules *rules)
{
	int	i;
	int	status;

	i = 0;
	while (i < rules->number_of_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < rules->number_of_philos)
			{
				kill(philo[i].pid, 9);
				i++;
			}
			exit(1);
		}
		i++;
	}
}
