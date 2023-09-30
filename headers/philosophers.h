/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danimart <danimart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:36:41 by danimart          #+#    #+#             */
/*   Updated: 2023/09/30 20:39:35 by danimart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_philo_info;

/* Struct used to represent an actual philosopher

Here is all the data stored in this struct:
- *prog_info: Program information, available forks are stored here.
- th_id: The thread id of this philosopher.
- id: The internal id of this philosopher.
- fork: The fork state of this philosopher (FK_X constants).
- state: The state of this philosopher (DEAD, INACTIVE, EATING...).
- meals: The amount of times this philosopher ate so far.
- last_interaction: The date of the last interaction of this philosopher (millis)
*/
typedef struct s_philo {
	struct s_philo_info	*prog_info;
	pthread_t			th_id;
	int					id;
	int					fork;
	int					state;
	int					meals;
	u_int64_t			last_interacion;
}			t_philo;

/* Struct used to store program information such as parameters and philosophers

Here is all the data stored in this struct:
- amount: The amount of philosophers, this is final.
- die_time: The time to die for philosophers, this is final.
- eat_time: The time to eat for philosophers, this is final.
- sleep_time: The time to sleep for philosophers, this is final.
- eat_num: The amount of times every philosopher must eat, this is final.
- *forks: The amount of forks currently available at the center of the table.
- philo_lst[MAX_PHILOSOPHERS]: An array of all existing philosophers.
- start_date: The date (In milliseconds) when the program started.
*/
typedef struct s_philo_info {
	int				amount;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	pthread_mutex_t	*forks;
	t_philo			*philo_lst[MAX_PHILOSOPHERS];
	u_int64_t		start_date;
}				t_philo_info;

/* Error messages */

// Invalid argument count.
# define ARGC_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid input\
\e[1;30m.\e[0m\n"
// Invalid amount of philosophers.
# define AMOUNT_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid number\
 of philosophers \e[1;30m(\e[1;33mMax is %d\e[1;30m)\e[0m\n"
// Warn philosophers over 200 if a higher amount is allowed.
# define AMOUNT_WARN "\e[0;33mWarning\e[1;30m: \e[1;33mUsing over\
 200 philosophers is not recommended\e[1;30m.\e[0m\n"
// Invalid time to die.
# define DIE_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to die\e[1;30m.\e[0m\n"
// Invalid time to eat.
# define EAT_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to eat\e[1;30m.\e[0m\n"
// Invalid time to sleep.
# define SLEEP_TIME_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid time\
 to sleep\e[1;30m.\e[0m\n"
// Invalid amount of times to eat.
# define EAT_NUM_ERR "\e[0;31mError\e[1;30m: \e[1;31mInvalid amount\
 of times to eat\e[1;30m.\e[0m\n"
// Error creating a thread.
# define THREAD_ERR "\e[0;31mError\e[1;30m: \e[1;31mCould not create\
 a new thread\e[1;30m.\e[0m\n"

/* Debug messages, debug should be disabled on evaluation just in case */

// Notication message sent if debug mode is on
# define DEBUG_NOTE "\e[1;37mDebug \e[1;32menabled\e[1;37m, run\
 \e[1;33mmake re DEBUG=0 \e[1;37mto disable\e[1;30m.\e[0m\n"
// Header of the program info
# define INFO_HEADER "\n\e[0;37m|-------------------------->\e[0m\n"
// Info slot about the program with a numeric value
# define INFO_NUM "\e[1;31m* \e[1;37m%s\e[1;30m: \e[0;33m%d\e[0m\n"
// Footer of the program info
# define INFO_FOOTER "\e[0;37m|-------------------------->\e[0m\n\n"
// Prefix used for debug messages
# define DEBUG_PREFIX "\e[1;30m[\e[1;37mDEBUG\e[1;30m]\e[0m"
// Philosopher state debug message
# define PHILO_STATE " \e[0;37mPhilosopher \e[0;33m%i\e[0;37m\
 is %s\e[1;30m.\e[0m\n"

/* Philosopher log messages */

// A philosopher takes a fork (Right hand).
# define PHILO_TAKE_RFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mRight\e[1;30m)\e[0m\n"
// A philosopher takes a fork (Left hand).
# define PHILO_TAKE_LFORK "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
has taken a \e[1;33mfork \e[1;30m(\e[1;34mLeft\e[1;30m)\e[0m\n"
// A philosopher is eating
# define PHILO_EATING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;35mmeating\e[1;30m.\e[0m\n"
// A philosopher is sleeping.
# define PHILO_SLEEPING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;36msleeping\e[1;30m.\e[0m\n"
// A philosopher is thinking.
# define PHILO_THINKING "\e[1;30m[\e[0;33m%d\e[1;30m] \e[1;33m%d \e[1;37m\
is \e[1;32mthinking\e[1;30m.\e[0m\n"
// A philosopher died :(
# define PHILO_DIED "\e[1;30m[\e[0;31m%llu\e[1;30m] \e[1;31m%d \
died\e[1;30m.\e[0m\n"

/* Fork state constants, saved on s_philo::fork */

// Philosopher doesn't have any fork, oh no.
# define FK_NONE -1
// Philosopher has a fork on it's RIGHT hand.
# define FK_RIGHT 1
// Philosopher has a fork on it's LEFT hand.
# define FK_LEFT 2
// Philosopher has a fork on BOTH hands, READY TO EAT!
# define FK_BOTH 3

/* Philosopher state constants, saved on s_philo::state */

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

/* philosophers.c */

// Exits the program and prints the err message, freeing all program info.
void			exit_error(char *err, t_philo_info *info);

/* input_parser.c */

// Parses program arguments to create a t_philo_info struct
t_philo_info	*parse_arguments(int argc, char **argv);

/* philo_builder.c */

// Gets the current timestamp of the program
u_int64_t		get_current_ms(t_philo_info *info);
// Builds all required philosophers and creates a thread for each one
t_philo_info	*build_philosophers(t_philo_info *info);

/* debug_helper.c */

// Test method to debug philosopher states, may be removed.
t_philo_info	*test_philosophers(t_philo_info *info);

#endif