/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2023/04/06 16:52:52 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>

/* Error messages */

// Invalid argument count.
# define ARGC_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid input\
\e[1;30m.\e[0m\n"
// Invalid amount of philosophers.
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid number\
 of philosophers \e[1;30m(\e[33;31mMax is %d\e[1;30m)\e[0m\n"
// Warn philosophers over 200 if a higher amount is allowed.
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[33;33mUsing over\
 200 philosophers is not recommended\e[1;30m.\e[0m\n"
// Invalid time to die.
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to die\e[1;30m.\e[0m\n"
// Invalid time to eat.
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"
// Invalid time to sleep.
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"
// Invalid amount of times to eat.
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[33;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"
// Error creating a thread.
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[33;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

/* Philosopher log messages */

// Invalid time to die.
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"
// Invalid time to die.
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"
// Invalid time to die.
# define PHILO_EATING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35meating\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_THINKING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"
// Invalid time to die.
# define PHILO_DIED "\e[1;30m[\e[0;31m%d\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

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

/* Fork state constants */

// Philosopher doesn't have any fork, oh no.
# define FK_NONE -1
// Philosopher has a fork on it's RIGHT hand.
# define FK_RIGHT 1
// Philosopher has a fork on it's LEFT hand.
# define FK_LEFT 2
// Philosopher has a fork on BOTH hands, READY TO EAT!
# define FK_BOTH 3

#endif