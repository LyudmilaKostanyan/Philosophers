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

void	*thread_func(t_vars *vars)
{
	pthread_mutex_lock(&vars->mutex);
	pthread_mutex_unlock(&vars->mutex);
	return (NULL);
}

int	ft_init(t_vars *vars, int argc)
{
	int		i;
	void	*f;

	f = thread_func;
	vars->philo = malloc(sizeof(pthread_t) * (argc - 1));
	if (!vars->philo)
		return (1);
	if (pthread_mutex_init(&vars->mutex, NULL))
		return (2);
	i = -1;
	while (++i < argc - 1)
		if (pthread_create(&vars->philo[i], NULL, f, vars))
			return (3);
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
	if (ft_init(&vars, argc))
	{
		printf("Init error\n");
		return (3);
	}
	i = -1;
	while (++i < argc - 1)
		pthread_join(vars.philo[i], NULL);
	pthread_mutex_destroy(&vars.mutex);
	return (0);
}
