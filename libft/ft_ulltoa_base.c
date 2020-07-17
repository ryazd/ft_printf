/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshamika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 12:54:19 by gshamika          #+#    #+#             */
/*   Updated: 2019/11/29 12:56:40 by gshamika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(unsigned long long n, int base)
{
	int		digits;

	digits = 0;
	while (n > 0)
	{
		digits++;
		n /= base;
	}
	return (digits);
}

static int	type_to_base(char type)
{
	if (type == 'u')
		return (10);
	if (type == 'o')
		return (8);
	if (type == 'x' || type == 'X')
		return (16);
	else
		return (0);
}

char		*ft_ulltoa_base(unsigned long long n, char type)
{
	char	*result;
	size_t	len;
	int		base;

	base = type_to_base(type);
	if (n == 0)
		return (ft_strdup("0"));
	len = count_digits(n, base);
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len--] = '\0';
	while (n > 0)
	{
		if (n % base > 9)
			result[len--] = (n % base) - 10 + (type == 'x' ? 'a' : 'A');
		else
			result[len--] = (n % base) + '0';
		n /= base;
	}
	return (result);
}
