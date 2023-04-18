/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:29:01 by lykostan          #+#    #+#             */
/*   Updated: 2023/04/17 17:29:04 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	k;

	k = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == 48)
		i++;
	if (ft_strlen(str + i) > 10)
		return (-1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		k = k * 10 + (str[i] - 48);
		i++;
	}
	if (k > 2147483647)
		return (-1);
	return ((int)k);
}

int	*parse(int argc, char **argv)
{
	int	i;
	int	j;
	int	*args;

	i = 0;
	while (++i < argc)
		if (ft_strlen(argv[i]) == 0)
			return (NULL);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (++j < ft_strlen(argv[i]))
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != ' ')
				return (NULL);
	}
	args = (int *)malloc(sizeof(int) * (argc - 1));
	if (!args)
		return (NULL);
	i = 0;
	while (++i < argc)
	{
		args[i - 1] = ft_atoi(argv[i]);
		if (args[i - 1] < 0)
			return (NULL);
	}
	return (args);
}
