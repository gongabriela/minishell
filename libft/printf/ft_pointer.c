/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:04:24 by adias-do          #+#    #+#             */
/*   Updated: 2024/11/22 16:11:19 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_phex(unsigned long long dec, char t)
{
	int		c;

	c = 0;
	if (dec >= 16)
		c += ft_phex(dec / 16, t);
	if (dec % 16 < 10)
		c += pf_putchar((dec % 16) + 48);
	else
	{
		if (t == 'x')
			c += pf_putchar((dec % 16) + 87);
		if (t == 'X')
			c += pf_putchar((dec % 16) + 55);
	}
	return (c);
}

int	pf_pointer(void *ptr)
{
	unsigned long long	address;
	int					count;

	if (!ptr)
		return (pf_putstr("(nil)"));
	address = (unsigned long long)ptr;
	count = 0;
	count += pf_putstr("0x");
	count += ft_phex(address, 'x');
	return (count);
}
