/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:28:54 by lykostan          #+#    #+#             */
/*   Updated: 2023/04/17 17:28:56 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_actions(t_vars *vars)
{
	(void)vars;
}

int	ft_init(t_vars *vars)
{
	int		i;
	void	*f = philo_actions;

	vars->philos = malloc(sizeof(t_philos) * vars->philos_num);
	if (!vars->philos)
		return (1);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!vars->forks)
		return (2);
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (3);
	i = -1;
	while (++i < vars->philos_num)
	{
		if (i < (i + 1) % vars->philos_num)
		{
			vars->philos->min_fork = &vars->forks[i];
			vars->philos->max_fork = &vars->forks[(i + 1) % vars->philos_num];
		}
		else
		{
			vars->philos->min_fork = &vars->forks[i];
			vars->philos->max_fork = &vars->forks[(i + 1) % vars->philos_num];
		}
		if (pthread_create(&vars->philos->philo, NULL, f, vars))
			return (4);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		printf("Args error\n");
		return (1);
	}
	if (parse(argc, argv, &vars))
	{
		printf("Parse error\n");
		return (2);
	}
	ft_init(&vars);
	return (0);
}
