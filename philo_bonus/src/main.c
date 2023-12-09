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

void	action(t_philos *philo, char *str)
{
	if (!die(philo))
	{
		printf(str, get_time() - philo->vars->sim_start, philo->num);
		if (!ft_strcmp(str, EAT))
		{
			sem_wait(philo->vars->time_lock);
			//pthread_mutex_lock(&philo->vars->time_lock);
			philo->last_eating = get_time();
			sem_post(philo->vars->time_lock);
			//pthread_mutex_unlock(&philo->vars->time_lock);
		}
	}
}

void	philo_actions(t_philos *philo)
{
	if (philo->num % 2 == 0)
		ft_usleep(2000, philo);
	while (!die(philo))
	{
		sem_wait(philo->vars->forks);
		//pthread_mutex_lock(philo->min_fork);
		action(philo, FORK);
		if (philo->vars->philos_num == 1)
			break ;
		sem_wait(philo->vars->forks);
		//pthread_mutex_lock(philo->max_fork);
		action(philo, FORK);
		action(philo, EAT);
		ft_usleep(philo->vars->time_to_eat, philo);
		sem_wait(philo->vars->eating_lock);
		//pthread_mutex_lock(&philo->vars->eating_lock);
		philo->ate++;
		sem_post(philo->vars->eating_lock);
		//pthread_mutex_unlock(&philo->vars->eating_lock);
		sem_post(philo->vars->forks);
		//pthread_mutex_unlock(philo->min_fork);
		sem_post(philo->vars->forks);
		//pthread_mutex_unlock(philo->max_fork);
		action(philo, SLEEP);
		ft_usleep(philo->vars->time_to_sleep, philo);
		action(philo, THINK);
	}
}

int	creating_processes(t_vars *vars, t_table *table)
{
	int		i;

	i = -1;
	while (++i < vars->philos_num)
	{
		table->philos[i].philo = fork();
		if (table->philos[i].philo == -1 && destroy(vars, table))	//change destroy
		{
			//waitpid
			return (1);
		}
	}
	i = -1;
	while (++i < vars->philos_num)
		if (table->philos[i].philo == 0)
			philo_actions(&table->philos[i]);
	while (1)
		if (philo_is_dead(vars, table))
			break ;
	i = -1;
	while (++i < vars->philos_num)
		waitpid(table->philos[i].philo, NULL, 0);
	destroy(vars, table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		cond;
	t_table	table;

	cond = parse(argc, argv, &vars);
	if (err_mes(cond, 1))
		return (1);
	cond = ft_init(&vars, &table);
	if (err_mes(cond, 2))
		return (2);
	cond = creating_processes(&vars, &table);
	if (err_mes(cond, 3))
		return (3);
	return (0);
}
