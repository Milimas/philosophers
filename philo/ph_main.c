/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 02:05:36 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/03/13 20:44:30 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_rules	rules;

	if (argc < 5)
	{
		help();
		return (2);
	}
	if (init_rules(argv, &rules))
		return (1);
	if (init_philos(argc, argv, &philo, &rules))
		return (1);
	if (start_philos(philo))
		return (1);
	ft_sleep(rules.time_to_die, ft_gettime(0));
	if (grim_reaper(philo, &rules))
		return (1);
	return (0);
}
