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

int	die(t_philos *philo)
{
	int	cond;

	cond = 0;
	pthread_mutex_lock(&philo->vars->die_lock);
	if (philo->vars->die)
		cond++;
	pthread_mutex_unlock(&philo->vars->die_lock);
	return (cond);
}

void	ft_usleep(unsigned long usec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	// printf("%lu\t%lu\t%lu\n", (now.tv_sec * 1000000 + now.tv_usec), (start.tv_sec * 1000000
	// + start.tv_usec), usec);
	while ((unsigned long)((now.tv_sec * 1000000 + now.tv_usec) - (start.tv_sec * 1000000
		+ start.tv_usec)) < usec)
	{
		usleep(10);
		gettimeofday(&now, NULL);
	}
}

int	philo_is_dead(t_vars *vars)
{
	int	i;
	int	cond;

	i = -1;
	cond = 0;
	while (++i < vars->philos_num)
	{
		if (vars->must_eat && vars->philos[i].ate == vars->must_eat)
			cond++;
		gettimeofday(&vars->time, NULL);
		// printf("%ld\n", vars->philos[i].last_eating.tv_sec);
		pthread_mutex_lock(&vars->time_lock);
		if (vars->philos[i].last_eating.tv_sec &&
			(vars->time.tv_sec * 1000000 + vars->time.tv_usec)
			- (vars->philos[i].last_eating.tv_sec * 1000000
			+ vars->philos[i].last_eating.tv_usec) > vars->time_to_die)
		{
			printf("???%d\n", vars->time_to_die);
			printf("asd = %ld\n", (vars->time.tv_sec * 1000000 + vars->time.tv_usec)
				- (vars->philos[i].last_eating.tv_sec * 1000000
				+ vars->philos[i].last_eating.tv_usec));
			pthread_mutex_unlock(&vars->time_lock);
			pthread_mutex_lock(&vars->die_lock);
			vars->die = 1;
			pthread_mutex_unlock(&vars->die_lock);
			printf("\e[31m%ld Philo %d is die\n",
				(vars->time.tv_sec * 1000 + vars->time.tv_usec / 1000)
				- (vars->sim_start.tv_sec * 1000
				+ vars->sim_start.tv_usec / 1000), i + 1);
			return (1);
		}
		pthread_mutex_unlock(&vars->time_lock);
	}
	if (vars->must_eat && cond == vars->philos_num)
	{
		pthread_mutex_lock(&vars->die_lock);
		vars->die = 1;
		pthread_mutex_unlock(&vars->die_lock);
		return (1);
	}
	return (0);
}

void	action(t_philos *philo, char *str)
{
	struct timeval	time;

	if (!die(philo))
	{
		gettimeofday(&time, NULL);
		printf(str, (time.tv_sec * 1000 + time.tv_usec / 1000)
			- (philo->vars->sim_start.tv_sec * 1000
			+ philo->vars->sim_start.tv_usec / 1000), philo->num);
	}
}

void	*philo_actions(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->num % 2 == 0)
		ft_usleep(2000);
	while (!die(philo))
	{
		pthread_mutex_lock(philo->min_fork);
		action(philo, "\e[36m%d Philo %d has taken a min fork\n");
		pthread_mutex_lock(philo->max_fork);
		action(philo, "\e[36m%d Philo %d has taken a max fork\n");
		action(philo, "\e[32m%d Philo %d is eating\n");
		pthread_mutex_lock(&philo->vars->time_lock);
		gettimeofday(&philo->last_eating, NULL);
		pthread_mutex_unlock(&philo->vars->time_lock);
		ft_usleep(philo->vars->time_to_eat);
		pthread_mutex_lock(&philo->vars->eating_lock);
		philo->ate++;
		pthread_mutex_unlock(&philo->vars->eating_lock);
		pthread_mutex_unlock(philo->min_fork);
		pthread_mutex_unlock(philo->max_fork);
		action(philo, "\e[35m%d Philo %d is sleeping\n");
		ft_usleep(philo->vars->time_to_sleep);
		action(philo, "\e[34m%d Philo %d is thinking\n");
	}
	return (NULL);
}

int	ft_init(t_vars *vars)
{
	int		i;

	vars->philos = malloc(sizeof(t_philos) * vars->philos_num);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!vars->philos || !vars->forks || pthread_mutex_init(&vars->die_lock, NULL)
		|| pthread_mutex_init(&vars->eating_lock, NULL) || pthread_mutex_init(&vars->time_lock, NULL))	//output and ide in another if -> destroy
		return (1);		//return 2???????!!!!!!!!
	vars->die = 0;
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (3);
	i = -1;
	while (++i < vars->philos_num)
	{
		vars->philos[i].vars = vars;
		vars->philos[i].num = i + 1;
		vars->philos[i].ate = 0;
		vars->philos[i].last_eating.tv_sec = 0;
		vars->philos[i].last_eating.tv_usec = 0;
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
	// printf("%d\n", vars->time_to_die);
	vars->time_to_die *= 1000;
	// printf("%d\n", vars->time_to_die);
	vars->time_to_eat *= 1000;
	vars->time_to_sleep *= 1000;
	i = -1;
	gettimeofday(&vars->sim_start, NULL);
	while (++i < vars->philos_num)
		if (pthread_create(&(vars->philos[i].philo), NULL, philo_actions, &vars->philos[i]))
			return (4);
	while (1)
	{
		if (philo_is_dead(vars))
		{
			i = -1;
			while (++i < vars->philos_num)
				if (pthread_join(vars->philos[i].philo, NULL))
					return (5);
			return (0);
		}
		// ft_usleep(1000);
	}
	// i = -1;
	// while (++i < vars->philos_num)
	// 	if (pthread_mutex_destroy(&vars->forks[i]))	//output_lock, die_lock
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
