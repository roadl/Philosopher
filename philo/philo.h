/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:48:40 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 00:18:56 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <memory.h>
# include <sys/time.h>

typedef enum e_state {
	SLEEP,
	EAT,
	THINK,
	DIE
}	t_state;

typedef struct s_mutex
{
	int				value;
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_arg
{
	struct timeval	start_time;
	int				philo_num;
	int				die_time;
	int				sleep_time;
	int				eat_time;
	int				max_eat;
	t_mutex			*forks;
	t_mutex			end_philo;
	t_mutex			finish;
	t_mutex			print;
}	t_arg;

typedef struct s_philo
{
	struct timeval	time;
	struct timeval	eat_time;
	int				eat_count;
	int				num;
	t_arg			*arg;
	t_mutex			*l_fork;
	t_mutex			*r_fork;
	t_state			state;
}	t_philo;

int		init_arg(int argc, char **argv, t_arg *arg);
void	init_philo(t_philo *philo, t_arg *arg, int i);

int		ft_putstr_fd(char *s, int fd);
int		get_time_diff(struct timeval last_time);
void	print_philo(t_philo *philo, int type);
void	free_all(t_arg *arg, t_philo *philo, pthread_t *t);

void	destroy_mutexes(t_arg *arg);
int		access_mutex(t_mutex *m, int n);
int		init_mutexes(t_arg *arg);

void	wake_up(t_philo *philo);
void	try_eat(t_philo *philo);
int		sleep_philo(t_arg *arg, t_philo *philo);

void	print_philo_state(t_philo *philo);
void	f(void);

#endif