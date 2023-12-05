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
			pthread_mutex_lock(&philo->vars->time_lock);
			philo->last_eating = get_time();
			pthread_mutex_unlock(&philo->vars->time_lock);
		}
	}
}

void	*philo_actions(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->num % 2 == 0)
		ft_usleep(2000, philo);
	while (!die(philo))
	{
		pthread_mutex_lock(philo->min_fork);
		action(philo, FORK);
		if (philo->vars->philos_num == 1)
			return (NULL);
		pthread_mutex_lock(philo->max_fork);
		action(philo, FORK);
		action(philo, EAT);
		ft_usleep(philo->vars->time_to_eat, philo);
		pthread_mutex_lock(&philo->vars->eating_lock);
		philo->ate++;
		pthread_mutex_unlock(&philo->vars->eating_lock);
		pthread_mutex_unlock(philo->min_fork);
		pthread_mutex_unlock(philo->max_fork);
		action(philo, SLEEP);
		ft_usleep(philo->vars->time_to_sleep, philo);
		action(philo, THINK);
	}
	return (NULL);
}

int	creating_threads(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->philos_num)
		if (pthread_create(&(vars->philos[i].philo), NULL,
				philo_actions, &vars->philos[i]) && destroy(vars, 0))
			return (1);
	while (1)
	{
		if (philo_is_dead(vars))
		{
			i = -1;
			while (++i < vars->philos_num)
				pthread_join(vars->philos[i].philo, NULL);
			destroy(vars, 0);
			return (0);
		}
	}
	destroy(vars, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		cond;

	cond = parse(argc, argv, &vars);
	if (err_mes(cond, 1))
		return (1);
	cond = ft_init(&vars);
	if (err_mes(cond, 2))
		return (2);
	cond = creating_threads(&vars);
	if (err_mes(cond, 3))
		return (3);
	return (0);
}
