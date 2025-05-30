/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:23:32 by adias-do          #+#    #+#             */
/*   Updated: 2024/11/05 11:55:38 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long n);
static void	ft_is_zero(char **result, long int *nbr);

char	*ft_itoa(int n)
{
	char	*loc;
	int		len;
	long	nbr;

	nbr = n;
	len = nbr_len(nbr);
	loc = malloc(sizeof(char) * len + 1);
	if (!loc)
		return (NULL);
	ft_is_zero(&loc, &nbr);
	loc[len] = '\0';
	if (nbr < 0)
	{
		loc[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		loc[len - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	return (loc);
}

static int	nbr_len(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_is_zero(char **result, long int *nbr)
{
	if (*nbr == 0)
	{
		**result = '0';
		*nbr = -*nbr;
	}
}
