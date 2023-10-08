/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 20:31:30 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*print_fork_taken(char *msg, t_philo *philo, pthread_mutex_t *m_print)
{
	int	dead;

	pthread_mutex_lock(philo->m_dead);
	dead = philo->dead;
	pthread_mutex_unlock(philo->m_dead);
	pthread_mutex_lock(m_print);
	if (!dead)
		printf(msg, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(m_print);
	if (!dead)
		return (philo);
	return (NULL);
}

void	*take_forks_l(t_philo *philo, t_philo *left)
{
	pthread_mutex_t	*m_print;

	m_print = philo->prog_info->m_print;
	if (lock_fork(left) == NULL)
		return (NULL);
	if (print_fork_taken(PHILO_TAKE_LFORK, philo, m_print) == NULL)
		return (NULL);
	if (lock_fork(philo) == NULL)
		return (NULL);
	return (print_fork_taken(PHILO_TAKE_RFORK, philo, m_print));
}

void	*take_forks_r(t_philo *philo, t_philo *left)
{
	pthread_mutex_t	*m_print;

	m_print = philo->prog_info->m_print;
	if (lock_fork(philo) == NULL)
		return (NULL);
	if (print_fork_taken(PHILO_TAKE_RFORK, philo, m_print) == NULL)
		return (NULL);
	if (lock_fork(left) == NULL)
		return (NULL);
	return (print_fork_taken(PHILO_TAKE_LFORK, philo, m_print));
}

void	*p_eat(t_philo *philo)
{
	t_philo	*left;

	if (philo->id == 0)
		left = philo->prog_info->philo_lst[philo->prog_info->amount - 1];
	else
		left = philo->prog_info->philo_lst[(philo->id - 1)];
	if (philo->id % 2 == 0)
	{
		if (take_forks_r(philo, left) == NULL)
			return (NULL);
	}
	else
		if (take_forks_l(philo, left) == NULL)
			return (NULL);
	pthread_mutex_lock(philo->m_meal);
	philo->meals += 1;
	philo->last_meal = get_current_ms(philo->prog_info);
	pthread_mutex_unlock(philo->m_meal);
	if (set_philo_state(philo, EATING, 1) == NULL)
		return (NULL);
	if (pause_philo(philo, philo->prog_info->eat_time) == NULL)
		return (NULL);
	pthread_mutex_unlock(philo->m_fork);
	pthread_mutex_unlock(left->m_fork);
	return (philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	while (1)
	{
		if (set_philo_state(philo, THINKING, 1) == NULL)
			return (NULL);
		if (p_eat(philo) == NULL)
			return (NULL);
		if (set_philo_state(philo, SLEEPING, 1) == NULL)
			return (NULL);
		if (pause_philo(philo, philo->prog_info->sleep_time) == NULL)
			return (NULL);
	}
	return (philo_ptr);
}
