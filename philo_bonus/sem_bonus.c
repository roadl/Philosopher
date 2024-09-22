/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojin <yojin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:01:09 by yojin             #+#    #+#             */
/*   Updated: 2024/09/23 04:16:04 by yojin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sema(t_sema *m, const char *name, int count)
{
	m->name = ft_strdup(name);
	if (!m->name)
		return (1);
	sem_unlink(m->name);
	m->sema = sem_open(name, O_CREAT, 0644, count);
	if (m->sema == SEM_FAILED)
	{
		perror("philo_bonus");
		return (1);
	}
	return (0);
}

int	init_semas(t_arg *arg)
{
	if (init_sema(&arg->finish, "finish", 1) \
		|| init_sema(&arg->print, "print", 1) \
		|| init_sema(&arg->forks, "forks", arg->philo_num)
		|| init_sema(&arg->end_philo, "end_philo", arg->philo_num - 1)
		|| init_sema(&arg->check, "check", 0))
		return (0);
	return (1);
}

void	destroy_sema(t_sema *sema)
{
	sem_unlink(sema->name);
	free(sema->name);
}

void	destroy_semas(t_arg *arg)
{
	destroy_sema(&arg->forks);
	destroy_sema(&arg->finish);
	destroy_sema(&arg->end_philo);
	destroy_sema(&arg->print);
	destroy_sema(&arg->check);
}
