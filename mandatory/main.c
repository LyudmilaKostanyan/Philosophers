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

int	philo_is_dead(t_vars *vars)
{
	int				i;
	struct timeval	time;

	i = -1;
	while (++i < vars->philos_num)
	{
		gettimeofday(&time, NULL);
		// printf("%ld\n", (time.tv_sec * 1000 + time.tv_usec / 1000)
		// 	- (vars->philos[i].last_eating.tv_sec * 1000
		// 	+ vars->philos[i].last_eating.tv_usec / 1000));
		if ((time.tv_sec * 1000 + time.tv_usec / 1000)
			- (vars->philos[i].last_eating.tv_sec * 1000
			+ vars->philos[i].last_eating.tv_usec / 1000)
			> vars->time_to_die)
		{
			printf("\e[31mPhilo %d is die\n", i + 1);
			return (1);
		}
	}
	return (0);
}

void	*philo_actions(void *data)
{
	t_philos	*philos;

	philos = (t_philos *)data;
	while (1)
	{
		printf("\e[34mPhilo %d is thinking\n", philos->num);
		pthread_mutex_lock(philos->min_fork);
		printf("\e[36mPhilo %d has taken a min fork\n", philos->num);
		pthread_mutex_lock(philos->max_fork);
		printf("\e[36mPhilo %d has taken a max fork\n", philos->num);
		printf("\e[32mPhilo %d is eating\n", philos->num);
		usleep(philos->vars->time_to_eat);
		gettimeofday(&philos->last_eating, NULL);
		// printf("%ld\n", philos->last_eating.tv_sec * 1000 - philos->last_eating.tv_usec / 1000);
		pthread_mutex_unlock(philos->min_fork);
		printf("\e[36mPhilo %d put the min fork back\n", philos->num);
		pthread_mutex_unlock(philos->max_fork);
		printf("\e[36mPhilo %d put the max fork back\n", philos->num);
		printf("\e[35mPhilo %d is sleeping\n", philos->num);
		usleep(philos->vars->time_to_sleep);
	}
	return (NULL);
}

int	ft_init(t_vars *vars)
{
	int		i;

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
		vars->philos[i].vars = vars;
		vars->philos[i].num = i + 1;
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
	vars->time_to_eat *= 1000;
	vars->time_to_sleep *= 1000;
	i = -1;
	while (++i < vars->philos_num)
	{
		if (pthread_create(&(vars->philos[i].philo), NULL, philo_actions, &vars->philos[i]))
			return (4);
	}
	while (1)
	{
		if (philo_is_dead(vars))
		{
			i = -1;
			while (++i < vars->philos_num)
				if (pthread_join(vars->philos[i].philo, NULL))
					return (5);
			// printf("asd\n");
			return (0);
		}
	}
	// i = -1;
	// while (++i < vars->philos_num)
	// 	if (pthread_mutex_destroy(&vars->forks[i]))
	// 		return (6);
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
