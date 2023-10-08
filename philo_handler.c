/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:54:31 by danimart          #+#    #+#             */
/*   Updated: 2023/10/08 17:05:19 by danimart         ###   ########.fr       */
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
	pthread_mutex_lock(right->m_l_fork);
	if (right->l_fork == 1)
	{
		pthread_mutex_unlock(right->m_l_fork);
		return (0);
	}
	pthread_mutex_unlock(right->m_l_fork);
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
	pthread_mutex_lock(left->m_r_fork);
	if (left->r_fork == 1)
	{
		pthread_mutex_unlock(left->m_r_fork);
		return (0);
	}
	pthread_mutex_unlock(left->m_r_fork);
	pthread_mutex_lock(philo->prog_info->m_print);
	printf(PHILO_TAKE_LFORK, get_current_ms(philo->prog_info), philo->id);
	pthread_mutex_unlock(philo->prog_info->m_print);
	return (1);
}

void	*try_eat(t_philo *philo)
{
	while (philo->state != EATING && philo->state != DEAD)
	{
		pthread_mutex_lock(philo->m_r_fork);
		philo->r_fork = get_right_fork(philo);
		pthread_mutex_lock(philo->m_l_fork);
		philo->l_fork = get_left_fork(philo);
		if (philo->r_fork == 1 && philo->l_fork == 1)
		{
			pthread_mutex_unlock(philo->m_r_fork);
			pthread_mutex_unlock(philo->m_l_fork);
			if (set_philo_state(philo, EATING) == NULL)
				return (NULL);
		}
		pthread_mutex_unlock(philo->m_r_fork);
		pthread_mutex_unlock(philo->m_l_fork);
	}
	return (philo);
}

void	*p_eat(t_philo *philo)
{
	if (set_philo_state(philo, THINKING) == NULL)
		return (NULL);
	if (try_eat(philo) == NULL)
		return (NULL);
	if (pause_philo(philo, philo->prog_info->eat_time) == NULL)
		return (NULL);
	pthread_mutex_lock(philo->m_r_fork);
	philo->r_fork = 0;
	pthread_mutex_unlock(philo->m_r_fork);
	pthread_mutex_lock(philo->m_l_fork);
	philo->l_fork = 0;
	pthread_mutex_unlock(philo->m_l_fork);
	pthread_mutex_lock(philo->m_meal);
	philo->meals += 1;
	philo->last_meal = get_current_ms(philo->prog_info);
	pthread_mutex_unlock(philo->m_meal);
	return (philo);
}

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;
	void	*result;

	philo = (t_philo *) philo_ptr;
	result = philo_ptr;
	while (result != NULL)
	{
		result = p_eat(philo);
		if (set_philo_state(philo, SLEEPING) == NULL)
			break ;
		if (pause_philo(philo, philo->prog_info->sleep_time) == NULL)
			return (NULL);
	}
	return (philo_ptr);
}
