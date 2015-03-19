#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>

#include "kdtree.h"

unsigned int get_msec(void)
{
  static struct timeval timeval, first_timeval;
  gettimeofday(&timeval,0);

  if(first_timeval.tv_sec == 0)
    {
      first_timeval = timeval;
      return 0;
    }
  return (timeval.tv_sec - first_timeval.tv_sec) * 1000 +
      (timeval.tv_usec - first_timeval.tv_usec) / 1000;
}

int main()
{
  int i, vcount = 10;
  kdtree *kd, *set;

  //kd = kd_create(3,3,pos);

  //starg = get_msec();
  double** pos = new double*[3];

  for(int i = 0 ; i < 3 ; i++)
    {
      pos[i] = new double[3];
      pos[i][0] = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
      pos[i][1] = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
      pos[i][1] = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
  }

  kd = kd_create(3,3,pos);

  //kd_build()

  //assert(kd_insert(kd, pos, 0) == 0);

  return 0;
}

