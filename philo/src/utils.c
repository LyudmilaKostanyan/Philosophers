/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:12:15 by lykostan          #+#    #+#             */
/*   Updated: 2023/12/05 19:12:17 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "get_time error\n", 15);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t usec, t_philos *philo)
{
	size_t	start;

	(void)philo;
	start = get_time();
	while ((get_time() - start) < usec / 1000)
	{
		if (die(philo))
			break ;
		usleep(10);
	}
}

int	free_mem(t_vars *vars)
{
	free(vars->philos);
	free(vars->forks);
	return (1);
}

int	destroy(t_vars *vars, int cond)
{
	int	i;

	free_mem(vars);
	pthread_mutex_destroy(&vars->die_lock);
	pthread_mutex_destroy(&vars->eating_lock);
	pthread_mutex_destroy(&vars->time_lock);
	i = -1;
	while (!cond && ++i < vars->philos_num)
		pthread_mutex_destroy(&vars->forks[i]);
	while (++i < cond)
		pthread_mutex_destroy(&vars->forks[i]);
	return (1);
}

int	err_mes(int cond, int func)
{
	if (!cond)
		return (0);
	if (func == 1 && cond == 1)
		write(2, ARGS_COUNT_ERR, ft_strlen(ARGS_COUNT_ERR));
	if (func == 1 && cond == 2)
		write(2, ARGS_ERR, ft_strlen(ARGS_ERR));
	if (func == 1 && (cond == 3 || cond == 4))
		write(2, ARGS_LEN_ERR, ft_strlen(ARGS_LEN_ERR));
	if (func == 2 && (cond == 1 || cond == 2))
		write(2, MALL_ERR, ft_strlen(MALL_ERR));
	if (func == 2 && cond == 3)
		write(2, MUTX_ERR, ft_strlen(MUTX_ERR));
	if (func == 3 && cond == 1)
		write(2, THRD_ERR, ft_strlen(THRD_ERR));
	return (1);
}
