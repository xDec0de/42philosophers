/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:13:27 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 19:09:42 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "philosophers.h"

// Struct used to represent an actual philosopher
typedef struct s_philo {
	int			id;
	int			fork;
	int			state;
	pthread_t	th;
}			t_philo;

/* Fork state constants */

// Philosopher doesn't have any fork, oh no.
# define FK_NONE -1
// Philosopher has a fork on it's RIGHT hand.
# define FK_RIGHT 1
// Philosopher has a fork on it's LEFT hand.
# define FK_LEFT 2
// Philosopher has a fork on BOTH hands, READY TO EAT!
# define FK_BOTH 3

/* Philosopher state constants */

// Philosopher is dead and must stay like that :)
# define DEAD -1
/* Philosopher is inactive, this state should only apply
 when the program is initializating philosophers */
# define INACTIVE 0
// Philosopher is currently EATING, next action is F(inished)_EATING.
# define EATING 1
// Philosopher has finished EATING and should start SLEEPING.
# define F_EATING 2
// Philosopher is currently SLEEPING, next action is F(inished)_SLEEPING.
# define SLEEPING 3
// Philosopher has finished SLEEPING and should start THINKING.
# define F_SLEEPING 4
// Philosopher is currently THINKING, next action is EATING.
# define THINKING 5

#endif