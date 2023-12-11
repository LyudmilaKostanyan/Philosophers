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

void	die(t_philos *philo)
{
	sem_wait(philo->vars->time_lock);
	if ((philo->last_eating && get_time()
			- philo->last_eating > philo->vars->time_to_die)
		|| (!philo->last_eating && get_time()
			- philo->vars->sim_start > philo->vars->time_to_die)
		|| (philo->vars->must_eat && philo->ate >= philo->vars->must_eat))
	{
		usleep(1000);
		if (!philo->vars->must_eat || philo->ate < philo->vars->must_eat)
			printf(DIE, get_time() - philo->vars->sim_start, philo->num);
		sem_post(philo->vars->time_lock);
		exit(1);
	}
	sem_post(philo->vars->time_lock);
}

int	semaphors_init(t_vars *vars)
{
	semaphors_unlink();
	vars->die_lock = sem_open("/die_lock", O_CREAT, 0644, 1);
	vars->eating_lock = sem_open("/eating_lock", O_CREAT, 0644, 1);
	vars->time_lock = sem_open("/time_lock", O_CREAT, 0644, 1);
	vars->forks = sem_open("/forks", O_CREAT, 0644, vars->philos_num);
	if (vars->die_lock == SEM_FAILED || vars->eating_lock == SEM_FAILED
		|| vars->time_lock == SEM_FAILED || vars->forks == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_init(t_vars *vars, t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philos) * vars->philos_num);
	if (!table->philos)
		return (1);
	if (semaphors_init(vars))
		return (2);
	vars->die = 0;
	vars->sim_start = get_time();
	i = -1;
	while (++i < vars->philos_num)
	{
		table->philos[i].vars = vars;
		table->philos[i].num = i + 1;
		table->philos[i].ate = 0;
		table->philos[i].last_eating = 0;
	}
	return (0);
}
