/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeihaqi <abeihaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 00:14:26 by abeihaqi          #+#    #+#             */
/*   Updated: 2023/02/04 07:23:57 by abeihaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static size_t	ft_digits(int n)
{
	size_t	size;

	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*conv(int n, int is_signed)
{
	char	*s;
	size_t	size;

	size = ft_digits(n) + is_signed + 1;
	s = malloc(size * sizeof(char));
	if (!s)
		return (NULL);
	s[size - 1] = 0;
	if (is_signed)
		*s = '-';
	while (n)
	{
		s[--size - 1] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		is_signed;

	is_signed = 0;
	if (n < 0)
	{
		n = -n;
		is_signed = 1;
	}
	return (conv(n, is_signed));
}
