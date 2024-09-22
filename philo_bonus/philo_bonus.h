/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:48:40 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 04:32:48 by yojin            ###   ########.fr       */
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
# include <signal.h>

typedef enum e_state {
	SLEEP,
	EAT,
	THINK,
	DIE
}	t_state;

typedef struct s_sema
{
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
	int				*test;
	t_sema			forks;
	t_sema			end_philo;
	t_sema			finish;
	t_sema			print;
	t_sema			check;
}	t_arg;

typedef struct s_philo
{
	struct timeval	time;
	struct timeval	eat_time;
	int				eat_count;
	int				num;
	t_arg			*arg;
	t_sema			*fork;
	t_state			state;
}	t_philo;

// init_bonus.c
int		init_arg(int argc, char **argv, t_arg *arg);
void	init_philo(t_philo *philo, t_arg *arg, int i);

// philo_util_bonus.c
char	*ft_strdup(const char *s);
int		ft_putstr_fd(char *s, int fd);
int		get_time_diff(struct timeval last_time);
void	print_philo(t_philo *philo, int type);
void	free_all(t_philo *philo, pid_t *pids);

// sem_bonus.c
void	end_check(t_arg *arg, t_philo *philo);
void	destroy_semas(t_arg *arg);
int		init_semas(t_arg *arg);
int		access_sema(t_sema *s, int n);

// philo_process.c
void	wake_up(t_philo *philo);
void	try_eat(t_philo *philo);
int		sleep_philo(t_arg *arg, t_philo *philo);

// debug_bonus.c
void	print_philo_state(t_philo *philo);
void	f(void);

#endif