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

void	action(int time, char *s, int index)
{
	printf("Philo %d is %s\n", index, s);
	usleep(time);
}

void	*thread_func(void *a)
{
	int	index;
	t_vars	*vars;

	vars = a;
	index = vars->i;
	printf("in func %d\n", index);
	// printf("in func %d\n", vars->i);
	// printf("Philo %d is thinking\n", index);
	pthread_mutex_lock(&vars->mutex[index]);
	pthread_mutex_lock(&vars->mutex[(index + 1) % 5]);
	action(vars->args[2], "eating", index);
	pthread_mutex_unlock(&vars->mutex[index]);
	pthread_mutex_unlock(&vars->mutex[(index + 1) % 5]);
	// printf("Philo %d is finished eating\n", index);
	return (NULL);
}

int	ft_init(t_vars *vars)
{
	void	*f;

	f = thread_func;
	vars->philo = malloc(sizeof(pthread_t) * vars->args[0]);
	vars->mutex = malloc(sizeof(pthread_mutex_t) * vars->args[0]);
	if (!vars->philo || !vars->mutex)
		return (1);
		
	vars->i = -1;
	while (++vars->i < vars->args[0])
		if (pthread_mutex_init(&vars->mutex[vars->i], NULL))
			return (2);
	vars->i = -1;
	while (++vars->i < vars->args[0])
	{
		printf("%d\n", vars->i);
		if (pthread_create(&vars->philo[vars->i], NULL, f, (void *)vars))
			return (3);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Args error\n");
		return (1);
	}
	vars.args = parse(argc, argv);
	if (vars.args == NULL)
	{
		printf("Parse error\n");
		return (2);
	}
	if (ft_init(&vars))
	{
		printf("Init error\n");
		return (3);
	}
	i = -1;
	while (++i < argc - 1)
		pthread_join(vars.philo[i], NULL);
	i = -1;
	while (++i < argc - 1)
		pthread_mutex_destroy(&vars.mutex[i]);
	return (0);
}
