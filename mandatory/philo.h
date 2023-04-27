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

typedef struct s_vars
{
	char			*forks;
	int				philos_num;
	useconds_t		time_to_die;
	useconds_t		time_to_eat;
	useconds_t		time_to_sleep;
	int				must_eat;
	int				i;
	pthread_t		*philo;
	pthread_mutex_t	*mutex;
}	t_vars;

int	parse(int argc, char **argv, t_vars *vars);
int	ft_strlen(const char *s);

#endif
