/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/02/27 02:04:23 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;

	if (argc < 5)
	{
		help();
		exit(2);
	}
	init_rules(argv, &rules);
	init_philos(argc, argv, &philo, &rules);
	start_philos(philo);
	wait_philos(philo, &rules);
	destroy_philos(philo);
	destroy_rules(&rules);
	return (0);
}
