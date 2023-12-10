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
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <pthread.h>

# define ARGS_COUNT_ERR "\e[31mIncorrect number of arguments\n\033[0m"
# define ARGS_ERR "\e[31mThe arguments contain invalid characters\n\033[0m"
# define ARGS_LEN_ERR "\e[31mThe arguments are too long\n\033[0m"
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
	pid_t			philo;
	long int		last_eating;
	int				ate;
	int				num;
}	t_philos;

typedef struct s_vars
{
	int			philos_num;
	sem_t		*eating_lock;
	sem_t		*die_lock;
	sem_t		*time_lock;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	long int	sim_start;
	int			must_eat;
	int			die;
	sem_t		*forks;
}	t_vars;

typedef struct s_table
{
	t_philos	*philos;
}	t_table;

int			ft_isdigit(int c);
int			ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_atoi(const char *str);
int			parse(int argc, char **argv, t_vars *vars);
long int	get_time(void);
void		ft_usleep(size_t usec, t_philos *philo);
void		semaphors_unlink();
int			destroy(t_vars *vars, t_table *table);
int			err_mes(int cond, int func);
int			ft_init(t_vars *vars, t_table *table);
void		die(t_philos *philo);

#endif
