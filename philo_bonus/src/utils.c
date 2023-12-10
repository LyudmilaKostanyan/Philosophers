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

	start = get_time();
	while ((get_time() - start) < usec / 1000)
	{
		die(philo);
		usleep(10);
	}
}

void	semaphors_unlink()
{
	sem_unlink("/die_lock");
	sem_unlink("/eating_lock");
	sem_unlink("/time_lock");
	sem_unlink("/forks");
}

int	destroy(t_vars *vars, t_table *table)
{
	sem_close(vars->die_lock);
	sem_close(vars->eating_lock);
	sem_close(vars->time_lock);
	sem_close(vars->forks);
	semaphors_unlink();
	free(table->philos);
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
	return (1);
}
