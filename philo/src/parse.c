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

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			return (1);
		if (ft_strlen(argv[i]) > 10)
			return (2);
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (++j < ft_strlen(argv[i]))
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != ' ')
				return (3);
	}
	return (0);
}

int	parse(int argc, char **argv, t_vars *vars)
{
	int	cond;

	if (argc != 5 && argc != 6)
		return (1);
	cond = check_args(argc, argv);
	if (cond && cond != 2)
		return (2);
	else if (cond == 2)
		return (3);
	vars->philos_num = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]) * 1000;
	vars->time_to_sleep = ft_atoi(argv[4]) * 1000;
	vars->must_eat = 0;
	if (argc == 6)
		vars->must_eat = ft_atoi(argv[5]);
	if (vars->philos_num < 0 || vars->time_to_die < 0 || vars->must_eat < 0
		|| vars->time_to_eat < 0 || vars->time_to_sleep < 0)
		return (4);
	return (0);
}
