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

void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec * 1000000 + now.tv_usec) - (start.tv_sec * 1000000
		+ start.tv_usec) < usec)
	{
		usleep(10);
		gettimeofday(&now, NULL);
	}
}

int	philo_is_dead(t_vars *vars)
{
	int				i;
	struct timeval	time;

	i = -1;
	while (++i < vars->philos_num)
	{
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&vars->lock);
		if ((vars->philos[i].last_eating.tv_sec
			&& (time.tv_sec * 1000 + time.tv_usec / 1000)
			- (vars->philos[i].last_eating.tv_sec * 1000
			+ vars->philos[i].last_eating.tv_usec / 1000)
			> vars->time_to_die) || (vars->philos[i].ate == vars->must_eat
			&& vars->must_eat))
		{
			// printf("time now: %ld\n", (time.tv_sec * 1000 + time.tv_usec / 1000)
			// - (vars->philos[i].last_eating.tv_sec * 1000
			// + vars->philos[i].last_eating.tv_usec / 1000));
			pthread_mutex_lock(&vars->die_lock);
			vars->die = 1;
			pthread_mutex_unlock(&vars->die_lock);
			if (vars->must_eat && vars->philos[i].ate == vars->must_eat)
				printf("\e[31m%ld Philo %d ate %d times. Simulation stopped\n",
					(time.tv_sec * 1000 + time.tv_usec / 1000)
					- (vars->sim_start.tv_sec * 1000
					+ vars->sim_start.tv_usec / 1000), i + 1, vars->must_eat);
			else
				printf("\e[31m%ld Philo %d is die\n",
					(time.tv_sec * 1000 + time.tv_usec / 1000)
					- (vars->sim_start.tv_sec * 1000
					+ vars->sim_start.tv_usec / 1000), i + 1);
			pthread_mutex_unlock(&vars->lock);
			return (1);
		}
		pthread_mutex_unlock(&vars->lock);
	}
	return (0);
}

void	action(t_philos *philo, char *str)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->vars->die_lock);
	if (philo->vars->die)
	{
		// printf("asdasdasd\n");
		pthread_mutex_unlock(&philo->vars->die_lock);
		return ;
	}
	gettimeofday(&time, NULL);
	printf(str, (time.tv_sec * 1000 + time.tv_usec / 1000)
			- (philo->vars->sim_start.tv_sec * 1000
			+ philo->vars->sim_start.tv_usec / 1000), philo->num);
	pthread_mutex_unlock(&philo->vars->die_lock);
	pthread_mutex_lock(&philo->vars->lock);
	if (str[3] == '2' && philo->vars->must_eat)
		philo->ate++;
	pthread_mutex_unlock(&philo->vars->lock);
}

void	*philo_actions(void *data)
{
	t_philos	*philo;

	philo = (t_philos *)data;
	if (philo->num % 2 == 0)
		ft_usleep(10000);
	while (1)
	{
		// pthread_mutex_lock(&philo->vars->die_lock);
		// printf("asd: %d\n", philo->vars->die);
		// pthread_mutex_unlock(&philo->vars->die_lock);
		//

		action(philo, "\e[34m%d Philo %d is thinking\n");
		pthread_mutex_lock(philo->min_fork);
		action(philo, "\e[36m%d Philo %d has taken a min fork\n");
		pthread_mutex_lock(philo->max_fork);
		action(philo, "\e[36m%d Philo %d has taken a max fork\n");
		action(philo, "\e[32m%d Philo %d is eating\n");

		// pthread_mutex_lock(&philo->vars->die_lock);
		// if (!philo->vars->die)
			ft_usleep(philo->vars->time_to_eat);
		// pthread_mutex_unlock(&philos->vars->die_lock);
		gettimeofday(&philo->last_eating, NULL);
		// printf("last eat: %ld\n", philo->last_eating.tv_sec * 1000 - philo->last_eating.tv_usec / 1000);
		// printf("start: %ld\n", philo->vars->sim_start.tv_sec * 1000 - philo->vars->sim_start.tv_usec / 1000);
		pthread_mutex_unlock(philo->min_fork);
		action(philo, "\e[36m%d Philo %d put the min fork back\n");
		pthread_mutex_unlock(philo->max_fork);
		action(philo, "\e[36m%d Philo %d put the max fork back\n");
		action(philo, "\e[35m%d Philo %d is sleeping\n");
		// pthread_mutex_lock(&philos->vars->die_lock);
		// if (!philos->vars->die)
			ft_usleep(philo->vars->time_to_sleep);
		// pthread_mutex_unlock(&philos->vars->die_lock);
		//
		pthread_mutex_lock(&philo->vars->die_lock);
		if (philo->vars->die)
		{
			pthread_mutex_unlock(&philo->vars->die_lock);
			break;
		}
		pthread_mutex_unlock(&philo->vars->die_lock);
	}
	return (NULL);
}

int	ft_init(t_vars *vars)
{
	int		i;

	vars->philos = malloc(sizeof(t_philos) * vars->philos_num);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philos_num);
	if (!vars->philos || !vars->forks || pthread_mutex_init(&vars->die_lock, NULL) || pthread_mutex_init(&vars->lock, NULL))	//output and ide in another if -> destroy
		return (1);		//return 2???????!!!!!!!!
	vars->die = 0;
	i = -1;
	while (++i < vars->philos_num)
		if (pthread_mutex_init(&vars->forks[i], NULL))
			return (3);
	i = -1;
	while (++i < vars->philos_num)
	{
		// vars->philos[i].last_eating.tv_sec = 0;
		// vars->philos[i].last_eating.tv_usec = 0;
		vars->philos[i].vars = vars;
		vars->philos[i].num = i + 1;
		vars->philos[i].ate = 0;
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
	// sim_start
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
