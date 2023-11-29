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

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
		if (ft_strlen(argv[i]) == 0)
			return (1);
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (++j < ft_strlen(argv[i]))
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != ' ')
				return (2);
	}
	return (0);
}

int	parse(int argc, char **argv, t_vars *vars)
{
	int	tmp;

	if (check_args(argc, argv))
		return (1);
	vars->philos_num = ft_atoi(argv[1]);
	tmp = ft_atoi(argv[2]);
	// printf("%d\n", tmp);
	if (tmp < 0 || vars->philos_num < 0)
		return (2);
	vars->time_to_die = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp < 0)
		return (3);
	vars->time_to_eat = tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp < 0)
		return (4);
	vars->time_to_sleep = tmp;
	vars->must_eat = 0;
	if (argc == 6)
	{
		vars->must_eat = ft_atoi(argv[5]);
		if (vars->must_eat <= 0)
			return (5);
	}
	return (0);
}
