#ifndef DEFINES_H_
#define DEFINES_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GraphLib.h"
#include <string.h>
#include <pthread.h>
#include <float.h>

#define THREADSNUM 7
#define MAX_STRING_LENGTH 256	/*maximum string length*/
#define INTEGER_SIZE 4			/*integer size*/
#define PERSON_PROPERTIES_NUM 8
#define PERSON_REL_PROPERTIES_NUM 2
#define NUMBER_OF_TOP_N_FORUMS 6
#define JOBS_TO_BE_DONE 6
#define M 2
#define C 3
#define K 10
#define SUCCESS 0
#define INFINITY_REACH_NODE INT_MAX
#define perror2(s,e) fprintf(stderr,"%s:%s\n",s,strerror(e))
#endif /* DEFINES_H_ */
