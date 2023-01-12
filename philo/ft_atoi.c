/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminebeihaqi <aminebeihaqi@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 04:03:18 by aminebeihaq       #+#    #+#             */
/*   Updated: 2023/01/10 04:03:48 by aminebeihaq      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	unsigned int	ch;

	ch = (unsigned int)c;
	if (ch >= '0' && ch <= '9')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		num = num * 10 + (*str++ - '0');
	return ((int)(sign * num));
}
