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

void	*philo_actions(t_philos *philo)
{
	while (1)
	{
		printf("\e[34mPhilo %d is thinking\n", philo->num + 1);
		pthread_mutex_lock(philo->min_fork);
		printf("\e[33mPhilo %d has taken a min fork\n", philo->num + 1);
		pthread_mutex_lock(philo->max_fork);
		printf("\e[33mPhilo %d has taken a max fork\n", philo->num + 1);
		printf("\e[32mPhilo %d is eating\n", philo->num + 1);
		usleep(1000000);
		pthread_mutex_unlock(philo->min_fork);
		printf("\e[33mPhilo %d put the min fork back\n", philo->num + 1);
		pthread_mutex_unlock(philo->max_fork);
		printf("\e[33mPhilo %d put the max fork back\n", philo->num + 1);
		printf("\e[35mPhilo %d is sleeping\n", philo->num + 1);
		usleep(1000000);
	}
	return (NULL);
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
		vars->philos[i].num = i;
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
		if (pthread_create(&(vars->philos[i].philo), NULL, f, &vars->philos[i]))
			return (4);
	}
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_join(vars->philos[i].philo, NULL))
			return (5);
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_destroy(&vars->forks[i]))
			return (5);
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
