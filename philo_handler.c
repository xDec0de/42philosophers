/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/17 11:18:16 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*print_fork_taken(char *msg, t_philo *philo)
{
	int	dead;

	mutex_lock(philo->m_ended);
	dead = philo->ended;
	mutex_unlock(philo->m_ended, 0);
	if (dead)
		return (NULL);
	mutex_lock(philo->prog_info->m_print);
	printf(msg, get_current_ms(philo->prog_info), philo->id + 1);
	mutex_unlock(philo->prog_info->m_print, 0);
	return (philo);
}

void	*take_forks(t_philo *philo, t_philo *left)
{
	if (philo->id % 2 == 0)
	{
		lock_fork(philo);
		if (print_fork_taken(PHILO_TAKE_RFORK, philo) == NULL)
			return (NULL);
		lock_fork(left);
		return (print_fork_taken(PHILO_TAKE_LFORK, philo));
	}
	else
	{
		lock_fork(left);
		if (print_fork_taken(PHILO_TAKE_LFORK, philo) == NULL)
			return (NULL);
		lock_fork(philo);
		return (print_fork_taken(PHILO_TAKE_RFORK, philo));
	}
}

void	*p_eat(t_philo *philo)
{
	t_philo	*left;

	if (philo->id == 0)
		left = philo->prog_info->philo_lst[philo->prog_info->amount - 1];
	else
		left = philo->prog_info->philo_lst[(philo->id - 1)];
	if (take_forks(philo, left) == NULL)
		return (NULL);
	if (set_philo_state(philo, EATING, 1) == NULL)
		return (NULL);
	mutex_lock(philo->m_meal);
	philo->last_meal = get_current_ms(philo->prog_info);
	mutex_unlock(philo->m_meal, 0);
	if (pause_philo(philo, philo->prog_info->eat_time) == NULL)
		return (NULL);
	mutex_unlock(philo->m_fork, 0);
	mutex_unlock(left->m_fork, 0);
	mutex_lock(philo->m_meal);
	philo->meals += 1;
	mutex_unlock(philo->m_meal, 0);
	return (philo);
}

t_philo	*await_ready(void *philo_ptr)
{
	t_philo	*philo;
	int		ready;

	philo = (t_philo *) philo_ptr;
	ready = 0;
	while (!ready)
	{
		mutex_lock(philo->prog_info->m_ready);
		ready = philo->prog_info->ready;
		mutex_unlock(philo->prog_info->m_ready, 0);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	return (philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	int		meals;

	philo = await_ready(philo_ptr);
	while (1)
	{
		if (set_philo_state(philo, THINKING, 1) == NULL)
			break ;
		if (p_eat(philo) == NULL)
			break ;
		mutex_lock(philo->m_meal);
		meals = philo->meals;
		mutex_unlock(philo->m_meal, 0);
		if (meals == philo->prog_info->eat_num)
			break ;
		if (set_philo_state(philo, SLEEPING, 1) == NULL)
			break ;
		if (pause_philo(philo, philo->prog_info->sleep_time) == NULL)
			break ;
	}
	mutex_unlock(philo->m_fork, 0);
	mutex_unlock(philo->m_ended, 0);
	mutex_unlock(philo->m_meal, 0);
	return (philo_ptr);
}
