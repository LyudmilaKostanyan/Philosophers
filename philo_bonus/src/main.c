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

void	*check_death(void *philo)
{
	while (1)
		die(philo);
	return (NULL);
}

void	action(t_philos *philo, char *str)
{
	printf(str, get_time() - philo->vars->sim_start, philo->num);
	if (!ft_strcmp(str, EAT))
	{
		sem_wait(philo->vars->time_lock);
		philo->last_eating = get_time();
		sem_post(philo->vars->time_lock);
	}
}

void	philo_actions(t_philos *philo)
{
	pthread_t	check;

	pthread_create(&check, NULL, &check_death, philo);
	if (philo->num % 2 == 0)
		ft_usleep(2000, philo);
	while (1)
	{
		sem_wait(philo->vars->forks);
		action(philo, FORK);
		if (philo->vars->philos_num == 1)
			break ;
		sem_wait(philo->vars->forks);
		action(philo, FORK);
		action(philo, EAT);
		ft_usleep(philo->vars->time_to_eat, philo);
		sem_wait(philo->vars->eating_lock);
		philo->ate++;
		sem_post(philo->vars->eating_lock);
		sem_post(philo->vars->forks);
		sem_post(philo->vars->forks);
		action(philo, SLEEP);
		ft_usleep(philo->vars->time_to_sleep, philo);
		action(philo, THINK);
	}
	pthread_join(check, NULL);
}

void	creating_processes(t_vars *vars, t_table *table)
{
	int		i;

	i = -1;
	while (++i < vars->philos_num)
	{
		table->philos[i].philo = fork();
		if (table->philos[i].philo == -1)
		{
			write(2, FORK_ERR, ft_strlen(FORK_ERR));
			destroy(vars, table);
			exit(1);
		}
		if (table->philos[i].philo == 0)
			philo_actions(&table->philos[i]);
	}
	waitpid(-1, &i, 0);
	if (WEXITSTATUS(i) == 1)
	{
		i = -1;
		while (++i < vars->philos_num)
			kill(table->philos[i].philo, SIGKILL);
	}
	destroy(vars, table);
}

int	main(int argc, char **argv)
{
	int		cond;
	t_vars	vars;
	t_table	table;

	cond = parse(argc, argv, &vars);
	if (err_mes(cond, 1))
		return (1);
	cond = ft_init(&vars, &table);
	if (err_mes(cond, 2))
		return (2);
	creating_processes(&vars, &table);
	return (0);
}
