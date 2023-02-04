/*
 * Copyright (c) 1988,1990,1993,1994,2021 by Paul Vixie ("VIXIE")
 * Copyright (c) 2004 by Internet Systems Consortium, Inc. ("ISC")
 * Copyright (c) 1997,2000 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND VIXIE DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL VIXIE BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#if !defined(lint) && !defined(LINT)
static char rcsid[] = "$Id: job.c,v 1.6 2004/01/23 18:56:43 vixie Exp $";
#endif

#include <stdbool.h>
#include "cron.h"


//  TODO : Rename definitions

typedef entry Entry;
typedef user User;


typedef	struct _job {

	struct _job	* next ;
	Entry * entry ;
	User * user ;

} Job;


static Job
    * head = NULL ,
    * tail = NULL ;


/**
 * @brief Creates a new job with the given config
 */

Job * job_new ( Entry * entry , User * user ){

    Job * job = (Job *) malloc(sizeof(Job));

    if( job == NULL )
		return NULL;

	job -> entry = entry;
	job -> user = user;
    job -> next = NULL;

    return job;
}


/**
 * @brief Checks if the given configuration is already queued
 */

bool job_isQueued ( Entry * entry , User * user ){

    for ( Job * job = head ; job != NULL ; job = job -> next )
		if( job -> entry == entry && job -> user == user )
			return true;

    return false;
}


/**
 * @brief Adds the given job to the queue
 */

void job_queue ( Job * job ){

    if( head == NULL )
		head = job;
	else
		tail -> next = job;

	tail = job;
}


/**
 * @brief Creates a job and queues it
 * @details Does nothing if a job with the
 * same configuration has already been queued
 */

void job_add ( Entry * entry , User * user ){

    if( job_isQueued(entry,user) )
        return;

    Job * job = job_new(entry,user);

	if( job == NULL )
		return;

    job_queue(job);
}


/**
 * @brief Runs all queued jobs
 * @return The count of jobs that have been run
 */

int job_runqueue (){

	Job * next ;

    int runs = 0;

	for ( Job * job = head ; job ; job = next ){

		do_command(
            job -> entry ,
            job -> user
        );

		next = job -> next;

		free(job);

        runs++;
	}

	head = tail = NULL;

	return runs;
}
