/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/07 15:23:52 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/philosophers.h"

void	*p_eat(t_philo *philo);
void	*p_sleep(t_philo *philo);

int	get_right_fork(t_philo *philo)
{
	t_philo	*right;

	if (philo->state == DEAD || philo->r_fork == 1)
		return (1);
	if (philo->id == (philo->prog_info->amount - 1))
		right = philo->prog_info->philo_lst[0];
	else
		right = philo->prog_info->philo_lst[(philo->id + 1)];
	pthread_mutex_lock(right->m_fork);
	if (right->l_fork == 1)
	{
		pthread_mutex_unlock(right->m_fork);
		return (0);
	}
	pthread_mutex_unlock(right->m_fork);
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(PHILO_TAKE_RFORK, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (1);
}

int	get_left_fork(t_philo *philo)
{
	t_philo	*left;

	if (philo->state == DEAD || philo->l_fork == 1)
		return (1);
	if (philo->id == 0)
		left = philo->prog_info->philo_lst[philo->prog_info->amount - 1];
	else
		left = philo->prog_info->philo_lst[(philo->id - 1)];
	pthread_mutex_lock(left->m_fork);
	if (left->r_fork == 1)
	{
		pthread_mutex_unlock(left->m_fork);
		return (0);
	}
	pthread_mutex_unlock(left->m_fork);
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(PHILO_TAKE_LFORK, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (1);
}

void	*p_eat(t_philo *philo)
{
	if (set_philo_state(philo, THINKING) == NULL)
		return (NULL);
	while (philo->state != EATING)
	{
		pthread_mutex_lock(philo->m_fork);
		philo->r_fork = get_right_fork(philo);
		philo->l_fork = get_left_fork(philo);
		if (philo->r_fork == 1 && philo->l_fork == 1)
			if (set_philo_state(philo, EATING) == NULL)
				return (NULL);
		pthread_mutex_unlock(philo->m_fork);
	}
	usleep(philo->prog_info->eat_time * 1000);
	pthread_mutex_lock(philo->m_fork);
	philo->r_fork = 0;
	philo->l_fork = 0;
	pthread_mutex_unlock(philo->m_fork);
	pthread_mutex_lock(philo->m_meal);
	philo->meals += 1;
	philo->last_meal = get_current_ms(philo->prog_info);
	pthread_mutex_unlock(philo->m_meal);
	if (p_sleep(philo) == NULL)
		return (NULL);
	return (NULL);
}

void	*p_sleep(t_philo *philo)
{
	if (set_philo_state(philo, SLEEPING))
		return (NULL);
	usleep(philo->prog_info->sleep_time * 1000);
	if (p_eat(philo) == NULL)
		return (NULL);
	return (NULL);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *) philo_ptr;
	p_eat(philo);
	pthread_mutex_lock(philo->prog_info->m_print);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (philo_ptr);
}
