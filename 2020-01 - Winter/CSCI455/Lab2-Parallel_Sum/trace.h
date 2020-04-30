/* trace.h
 * -------
 * Authors: Darwin Jacob Groskleg, Laurence T. Yang
 * CSCI 455
 * Lab #2: Parallel Sum
 */
#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#include <stdio.h>

/* on Windows we define debug mode to be when _DEBUG is set */
#ifdef _DEBUG
#define DEBUG_MODE 1
#endif

/* on UNIX we define debug mode to be when _GLIBCXX is set */
#ifdef _GLIBCXX_DEBUG
#define DEBUG_MODE 1
#endif

#ifdef DEBUG
#define DEBUG_MODE 1
#endif


/* Our assertion macros do nothing in production. */
#ifndef DEBUG_MODE

#define TRACE( X )
#define TRACEd(X, V)

#else /* DEBUG_MODE */

#define TRACE( X ) \
    fprintf(stderr,"\n[%d/%d]#%d: %s",myid,cluster_size,__LINE__,X)
#define TRACEd(X, V) \
    fprintf(stderr,"\n[%d/%d]#%d: %s%d",myid,cluster_size,__LINE__,X,V)

#endif /* DEBUG_MODE */


#endif /* TRACE_H_INCLUDED */
