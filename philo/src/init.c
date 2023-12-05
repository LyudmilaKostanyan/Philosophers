/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:16:36 by lykostan          #+#    #+#             */
/*   Updated: 2023/12/05 19:16:38 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init(t_vars *vars)
{
	int	i;

	if (pthread_mutex_init(&vars->die_lock, NULL) && free_mem(vars))
		return (1);
	if (pthread_mutex_init(&vars->eating_lock, NULL) && free_mem(vars))
	{
		pthread_mutex_destroy(&vars->die_lock);
		return (2);
	}
	if (pthread_mutex_init(&vars->time_lock, NULL) && free_mem(vars))
	{
		pthread_mutex_destroy(&vars->die_lock);
		pthread_mutex_destroy(&vars->eating_lock);
		return (3);
	}
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_init(&vars->forks[i], NULL) && destroy(vars, i))
			return (4);
	return (0);
}

void	forks_init(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->philos_num)
	{
		vars->philos[i].vars = vars;
		vars->philos[i].num = i + 1;
		vars->philos[i].ate = 0;
		vars->philos[i].last_eating = 0;
		if (i < (i + 1) % vars->philos_num)
		{
			vars->philos[i].min_fork = &vars->forks[i];
			vars->philos[i].max_fork = &vars->forks[(i + 1) % vars->philos_num];
		}
		else
		{
			vars->philos[i].min_fork = &vars->forks[(i + 1) % vars->philos_num];
			vars->philos[i].max_fork = &vars->forks[i];
		}
	}
}

int	ft_init(t_vars *vars)
{
	vars->philos = malloc(sizeof(t_philos) * vars->philos_num);
	if (!vars->philos)
		return (1);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!vars->forks && free_mem(vars))
		return (2);
	if (mutex_init(vars))
		return (3);
	forks_init(vars);
	vars->die = 0;
	vars->sim_start = get_time();
	return (0);
}
