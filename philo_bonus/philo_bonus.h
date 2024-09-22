/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:48:40 by yojin             #+#    #+#             */
/*   Updated: 2024/08/15 19:43:18 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <memory.h>
# include <sys/time.h>

typedef enum e_state {
	SLEEP,
	EAT,
	THINK,
	DIE
}	t_state;

typedef struct s_sema
{
	int		value;
	char	*name;
	sem_t	*sema;
}	t_sema;

typedef struct s_arg
{
	struct timeval	start_time;
	int				philo_num;
	int				die_time;
	int				sleep_time;
	int				eat_time;
	int				max_eat;
	t_sema			forks;
	t_sema			end_philo;
	t_sema			finish;
	t_sema			print;
}	t_arg;

typedef struct s_philo
{
	struct timeval	time;
	struct timeval	eat_time;
	int				eat_count;
	int				num;
	int				holding_fork;
	t_arg			*arg;
	t_sema			*fork;
	t_state			state;
}	t_philo;

int		init_arg(int argc, char **argv, t_arg *arg);
void	init_philo(t_philo *philo, t_arg *arg, int i);

char	*ft_strdup(const char *s);
int		ft_putstr_fd(char *s, int fd);
int		get_time_diff(struct timeval last_time);
void	print_philo(t_philo *philo, int type);
void	free_all(t_philo *philo, pthread_t *t);

void	destroy_semas(t_arg *arg);
int		init_semas(t_arg *arg);
int		access_sema(t_sema *s, int n);

void	wake_up(t_philo *philo);
void	try_eat(t_philo *philo);
int		sleep_philo(t_arg *arg, t_philo *philo);

void	print_philo_state(t_philo *philo);
void	f(void);

#endif