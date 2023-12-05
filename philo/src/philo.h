/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:29:13 by lykostan          #+#    #+#             */
/*   Updated: 2023/04/17 17:29:15 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define EAT "\e[32m%d Philo %d is eating\n\033[0m"
# define FORK "\e[36m%d Philo %d has taken a fork\n\033[0m"
# define SLEEP "\e[35m%d Philo %d is sleeping\n\033[0m"
# define THINK "\e[34m%d Philo %d is thinking\n\033[0m"
# define DIE "\e[31m%ld Philo %d is die\n\033[0m"

typedef struct s_philos
{
	struct s_vars	*vars;
	pthread_t		philo;
	pthread_mutex_t	*min_fork;
	pthread_mutex_t	*max_fork;
	size_t			last_eating;
	int				ate;
	int				num;
}	t_philos;

typedef struct s_vars
{
	t_philos		*philos;
	int				philos_num;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	time_lock;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			sim_start;
	int				must_eat;
	int				die;
}	t_vars;

int	parse(int argc, char **argv, t_vars *vars);
int	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);

#endif