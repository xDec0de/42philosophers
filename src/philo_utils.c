/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:51:49 by danimart          #+#    #+#             */
/*   Updated: 2025/03/19 18:18:12 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

u_int64_t	get_current_ms(t_philo_info *info)
{
	return (get_current_time(info) - info->start_date);
}

u_int64_t	get_current_time(t_philo_info *info)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (*(int *) free_info(GET_TIME_ERR, info, NULL));
	return (((time.tv_sec * (u_int64_t) 1000) + (time.tv_usec / 1000)));
}

t_philo	*pause_philo(t_philo *philo, u_int64_t ms)
{
	useconds_t	to_match;

	to_match = get_current_ms(philo->prog_info) + ms;
	while (get_current_ms(philo->prog_info) < to_match)
	{
		mutex_lock(philo->m_ended);
		if (philo->ended == 1)
		{
			mutex_unlock(philo->m_ended, 0);
			return (NULL);
		}
		mutex_unlock(philo->m_ended, 0);
		usleep(100);
	}
	return (philo);
}

t_philo	*set_philo_state(t_philo *philo, int state, int print)
{
	char	*state_str;
	int		ended;

	mutex_lock(philo->m_ended);
	ended = philo->ended;
	mutex_unlock(philo->m_ended, 0);
	if (ended == 1)
		return (NULL);
	if (!print)
		return (philo);
	else if (state == THINKING)
		state_str = PHILO_THINKING;
	else if (state == SLEEPING)
		state_str = PHILO_SLEEPING;
	else if (state == EATING)
		state_str = PHILO_EATING;
	mutex_lock(philo->prog_info->m_print);
	printf(state_str, get_current_ms(philo->prog_info), philo->id);
	mutex_unlock(philo->prog_info->m_print, 0);
	return (philo);
}

void	free_philos(t_philo_info *info)
{
	int	id;

	id = 0;
	while (id < info->amount && info->philo_lst[id] != NULL)
	{
		pthread_join(info->philo_lst[id]->th_id, NULL);
		id++;
	}
	id = 0;
	while (id < info->amount && info->philo_lst[id] != NULL)
	{
		mutex_unlock(info->philo_lst[id]->m_fork, 1);
		mutex_unlock(info->philo_lst[id]->m_meal, 1);
		mutex_unlock(info->philo_lst[id]->m_ended, 1);
		mutex_unlock(info->philo_lst[id]->m_ready, 1);
		free(info->philo_lst[id]);
		id++;
	}
}
