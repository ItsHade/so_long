/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:11:00 by maburnet          #+#    #+#             */
/*   Updated: 2023/09/09 20:11:19 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_intlen(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
	{
		i++;
		num = num * -1;
	}
	while (num > 0)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

char	*ft_itoa(int num)
{
	int		i;
	char	*str;

	i = ft_intlen(num);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = 0;
	i--;
	while (i >= 0)
	{
		str[i] = (num % 10) + 48;
		num = num / 10;
		i--;
	}
	return (str);
}
