/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:16:47 by lykostan          #+#    #+#             */
/*   Updated: 2023/12/05 19:16:49 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philos *philo)
{
	int	cond;

	cond = 0;
	sem_wait(philo->vars->die_lock);
	//pthread_mutex_lock(&philo->vars->die_lock);
	if (philo->vars->die)
		cond++;
	sem_post(philo->vars->die_lock);
	//pthread_mutex_unlock(&philo->vars->die_lock);
	return (cond);
}

int	check_dead(t_vars *vars, t_table *table, int i, int *cond)
{
	sem_wait(vars->eating_lock);
	//pthread_mutex_lock(&vars->eating_lock);
	if (vars->must_eat && table->philos[i].ate >= vars->must_eat)
		(*cond)++;
	sem_post(vars->eating_lock);
	//pthread_mutex_unlock(&vars->eating_lock);
	sem_wait(vars->time_lock);
	//pthread_mutex_lock(&vars->time_lock);
	if ((table->philos[i].last_eating && get_time()
			- table->philos[i].last_eating > vars->time_to_die)
		|| (!table->philos[i].last_eating && get_time()
			- vars->sim_start > vars->time_to_die))
	{
		sem_post(vars->time_lock);
		//pthread_mutex_unlock(&vars->time_lock);
		sem_wait(vars->die_lock);
		//pthread_mutex_lock(&vars->die_lock);
		vars->die = 1;
		sem_post(vars->die_lock);
		//pthread_mutex_unlock(&vars->die_lock);
		printf(DIE, get_time() - vars->sim_start, i + 1);
		return (1);
	}
	sem_post(vars->time_lock);
	//pthread_mutex_unlock(&vars->time_lock);
	return (0);
}

int	philo_is_dead(t_vars *vars, t_table *table)
{
	int	i;
	int	cond;

	i = -1;
	cond = 0;
	while (++i < vars->philos_num)
		if (check_dead(vars, table, i, &cond))
			return (1);
	if (vars->must_eat && cond == vars->philos_num)
	{
		sem_wait(vars->die_lock);
		//pthread_mutex_lock(&vars->die_lock);
		vars->die = 1;
		sem_post(vars->die_lock);
		//pthread_mutex_unlock(&vars->die_lock);
		return (1);
	}
	return (0);
}
