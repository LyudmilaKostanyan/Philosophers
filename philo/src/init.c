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

int	mutex_init(t_vars *vars, t_table *table)
{
	int	i;

	if (pthread_mutex_init(&vars->die_lock, NULL) && free_mem(table))
		return (1);
	if (pthread_mutex_init(&vars->eating_lock, NULL) && free_mem(table))
	{
		pthread_mutex_destroy(&vars->die_lock);
		return (2);
	}
	if (pthread_mutex_init(&vars->time_lock, NULL) && free_mem(table))
	{
		pthread_mutex_destroy(&vars->die_lock);
		pthread_mutex_destroy(&vars->eating_lock);
		return (3);
	}
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_init(&table->forks[i], NULL)
			&& destroy(vars, table, i))
			return (4);
	return (0);
}

void	forks_init(t_vars *vars, t_table *table)
{
	int	i;

	i = -1;
	while (++i < vars->philos_num)
	{
		table->philos[i].vars = vars;
		table->philos[i].num = i + 1;
		table->philos[i].ate = 0;
		table->philos[i].last_eating = 0;
		if (i < (i + 1) % vars->philos_num)
		{
			table->philos[i].min_fork = &table->forks[i];
			table->philos[i].max_fork = &table->forks[(i + 1)
				% vars->philos_num];
		}
		else
		{
			table->philos[i].min_fork = &table->forks[(i + 1)
				% vars->philos_num];
			table->philos[i].max_fork = &table->forks[i];
		}
	}
}

int	ft_init(t_vars *vars, t_table *table)
{
	table->philos = malloc(sizeof(t_philos) * vars->philos_num);
	if (!table->philos)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!table->forks && free_mem(table))
		return (2);
	if (mutex_init(vars, table))
		return (3);
	forks_init(vars, table);
	vars->die = 0;
	vars->sim_start = get_time();
	return (0);
}
