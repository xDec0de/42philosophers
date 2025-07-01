/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniema3 <daniema3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2025/07/01 20:21:27 by daniema3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*print_fork_taken(char *msg, t_philo *philo)
{
	int	dead;

	mutex_lock(philo->m_ended);
	dead = philo->ended;
	mutex_unlock(philo->m_ended, false);
	if (dead)
		return (NULL);
	mutex_lock(philo->prog_info->m_print);
	printf(msg, get_current_ms(philo->prog_info), philo->id);
	mutex_unlock(philo->prog_info->m_print, false);
	return (philo);
}

void	*take_forks(t_philo *philo, t_philo *left)
{
	if (philo->id % 2 == 0)
	{
		lock_fork(left);
		if (print_fork_taken(PHILO_TAKE_LFORK, philo) == NULL)
			return (NULL);
		if (lock_fork(philo) == NULL)
			return (NULL);
		return (print_fork_taken(PHILO_TAKE_RFORK, philo));
	}
	else
	{
		lock_fork(philo);
		if (print_fork_taken(PHILO_TAKE_RFORK, philo) == NULL)
			return (NULL);
		if (lock_fork(left) == NULL)
			return (NULL);
		return (print_fork_taken(PHILO_TAKE_LFORK, philo));
	}
}

void	*p_eat(t_philo *philo)
{
	t_philo	*left;

	if (philo->id == 1)
		left = philo->prog_info->philo_lst[philo->prog_info->amount - 1];
	else
		left = philo->prog_info->philo_lst[(philo->id - 2)];
	if (take_forks(philo, left) == NULL)
		return (NULL);
	if (set_philo_state(philo, EATING, true) == NULL)
		return (NULL);
	mutex_lock(philo->m_meal);
	philo->last_meal = get_current_ms(philo->prog_info);
	mutex_unlock(philo->m_meal, false);
	if (pause_philo(philo, philo->prog_info->eat_time) == NULL)
		return (NULL);
	mutex_unlock(philo->m_fork, false);
	mutex_unlock(left->m_fork, false);
	philo->meals += 1;
	return (philo);
}

t_philo	*await_ready(void *philo_ptr)
{
	t_philo	*philo;
	bool	prog_ready;

	philo = (t_philo *) philo_ptr;
	mutex_lock(philo->m_ready);
	philo->ready = true;
	mutex_unlock(philo->m_ready, false);
	prog_ready = false;
	while (!prog_ready)
	{
		mutex_lock(philo->prog_info->m_ready);
		prog_ready = philo->prog_info->ready;
		mutex_unlock(philo->prog_info->m_ready, false);
		usleep(100);
	}
	return (philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = await_ready(philo_ptr);
	while (1)
	{
		if (set_philo_state(philo, THINKING, true) == NULL)
			break ;
		if (p_eat(philo) == NULL)
			break ;
		if (philo->meals == philo->prog_info->eat_num)
			break ;
		if (set_philo_state(philo, SLEEPING, true) == NULL)
			break ;
		if (pause_philo(philo, philo->prog_info->sleep_time) == NULL)
			break ;
	}
	mutex_unlock(philo->m_fork, false);
	mutex_lock(philo->m_ended);
	philo->ended = true;
	mutex_unlock(philo->m_ended, false);
	return (philo_ptr);
}
