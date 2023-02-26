/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/26 05:04:21 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;

	if (argc < 5)
		return (2);
	if (init_rules(argv, &rules))
		return (1);
	if (init_philos(argc, argv, &philo, &rules))
		return (1);
	if (start_philos(philo))
		return (1);
	usleep(rules.time_to_die * 900);
	if (grim_reaper(philo, &rules))
		return (1);
	return (0);
}
