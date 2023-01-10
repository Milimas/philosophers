/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 03:52:22 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/10 04:48:06 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_arguments(t_arguments arg)
{
	printf("number of philosophers:\t%d\n", arg.number_of_philosophers);
	printf("time to die:\t%d\n", arg.time_to_die);
	printf("time to eat:\t%d\n", arg.time_to_eat);
	printf("time to sleep:\t%d\n", arg.time_to_sleep);
	printf("number of times each philosopher must eat:\t%d\n",
		arg.number_of_times_each_philosopher_must_eat);
}

t_philosopher	*create_philosopher(int number_of_philosopher)
{
	t_philosopher	*ph;

	ph = malloc(sizeof(t_philosopher));
	ph->number_of_philosopher = number_of_philosopher;
	ph->fork = 0;
	ph->is_dead = 0;
	ph->is_eating = 0;
	ph->is_sleeping = 0;
	ph->is_thinking = 0;
	ph->right = NULL;
	return (ph);
}

t_philosopher	*ph_last_right(t_philosopher *ph)
{
	if (!ph)
		return (ph);
	while (ph->right != NULL)
		ph = ph->right;
	return (ph);
}

void	ph_add_right(t_philosopher **ph, t_philosopher *new)
{
	if (*ph == NULL)
		*ph = new;
	else
		ph_last_right(*ph)->right = new;
}

t_philosopher	*init_philisophers(t_arguments arg)
{
	t_philosopher	*ph;
	t_philosopher	*tmp;
	int				i;

	i = 1;
	ph = create_philosopher(i);
	while (++i <= arg.number_of_philosophers)
	{
		tmp = create_philosopher(i);
		ph_add_right(&ph, tmp);
	}
	tmp->right = ph;
	return (ph);
}

int	main(int argc, char **argv)
{
	t_arguments		arg;
	t_philosopher	*ph;

	if (argc < 5 || argc > 6)
		return (EXIT_SUCCESS);
	arg.number_of_philosophers = ft_atoi(argv[1]);
	arg.time_to_die = ft_atoi(argv[2]);
	arg.time_to_eat = ft_atoi(argv[3]);
	arg.time_to_sleep = ft_atoi(argv[4]);
	arg.number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		arg.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (arg.number_of_philosophers == 0)
		return (EXIT_SUCCESS);
	if (arg.time_to_die == 0)
		return (EXIT_FAILURE);
	if (arg.number_of_times_each_philosopher_must_eat == 0)
		return (EXIT_SUCCESS);
	ph = init_philisophers(arg);
	while (ph->right)
	{
		printf("%d\n", ph->number_of_philosopher);
		ph = ph->right;
	}
	print_arguments(arg);
	return (EXIT_SUCCESS);
}
