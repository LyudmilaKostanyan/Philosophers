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

# define ARGS_COUNT_ERR "\e[31mIncorrect number of arguments\n\033[0m"
# define ARGS_ERR "\e[31mThe arguments contain invalid characters\n\033[0m"
# define LEN_ERR "\e[31mThe arguments are too long or equal to zero\n\033[0m"
# define MALL_ERR "\e[31mMalloc error\n\033[0m"
# define MUTX_ERR "\e[31mMutex initialization error\n\033[0m"
# define THRD_ERR "\e[31mTread creation error\n\033[0m"
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
	int				philos_num;
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

typedef struct s_table
{
	pthread_mutex_t	*forks;
	t_philos		*philos;
}	t_table;

int			ft_isdigit(int c);
int			ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
int			parse(int argc, char **argv, t_vars *vars);
long int	get_time(void);
void		ft_usleep(size_t usec, t_philos *philo);
int			free_mem(t_table *table);
int			destroy(t_vars *vars, t_table *table, int cond);
int			err_mes(int cond, int func);
int			ft_init(t_vars *vars, t_table *table);
int			die(t_philos *philo);
int			philo_is_dead(t_vars *vars, t_table *table);

#endif
