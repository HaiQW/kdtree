#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <algorithm>

#include "kdtree.h" //customized difined

#define square(x)         ((x)*(x))
static int DIMENSION = 0;

static void clear_rect(struct kdnode *node, void(*destr)(void*));
static int insert_rect(struct kdnode **node, const double *pos,void *data,
                       int dir, int dim);

static int kd_build(kdtree *tree, int min, int max, int depth);
static struct kdhyperrect* hyperrect_create(int dim, const double *min,
                                            const double *max);
static void hyperrect_extend(struct kdhyperrect *rect, const double *pos);


int cmp(const void *pa, const void *pb)
{

    double  a = ((kdnode*)pa)->data_[DIMENSION];
    double  b = ((kdnode*)pb)->data_[DIMENSION];

    return (a < b) ? -1 : ((a > b) ? 1 : 0);
}

/*
 * Hyperrectangle Helpers
 **/
static struct kdhyperrect* hyperrect_create(int dim, const double *min,
                                            const double *max)
{
  size_t size = dim * sizeof(double);//size of range data
  struct kdhyperrect *rect = NULL;

  /* memory allocate*/
  if(!(rect = new kdhyperrect))
    {
      return 0;
    }

  rect->dim = dim;
  if(!(rect->min = new double[dim]))
    {
      delete rect;
      return 0;
    }
  if(!(rect->max = new double[dim]))
    {
      delete rect->min;
      delete rect;
      return 0;
    }

  memcpy(rect->max, min, size);
  memcpy(rect->max, max, size);

  return rect;
}



struct kdtree *kd_create(int k, int len, double** pos)
{
  struct kdtree *tree;

  if( !(tree = new kdtree) ||!pos)
    {
      return 0;
    }


  tree->dim_ = k;
  tree->root_ = 0;
  tree->len_ = len;

  if(!(tree->nodes_ = new kdnode[len]))
    {
      return 0;
    }
  /*memory allocate*/
  for(int i = 0; i < len; i++)
    {
       tree->nodes_[i].data_ = (double*)malloc(sizeof(double)*k);
       memcpy(&(tree->nodes_[i].data_), pos[i], sizeof(double)*k);
    }

  return tree;
}

void kd_free(struct kdtree *tree)
{
  if(tree)
    {
      //kd_clear(tree);
      delete tree;
    }
}



/*
 * The function in to build a kdtree when a set of data point is given
 */
static int kd_build(kdtree *tree, int min, int max, int depth)
{
  struct kdnode *m;
  int median = 0, dir;

  if( max <= min)
    {
      return -1;
    }

  dir = (depth + 1) % tree->dim_;
  DIMENSION = dir;
  /*sort nodes form min to max*/
  qsort(tree->nodes_+min, max-min, sizeof(struct kdnode), cmp);
  m = tree->nodes_ + median; //m is the address of the median point
  m->dir_ = dir;

  m->left_ = kd_build(tree, min, median, depth + 1);
  m->right_ = kd_build(tree, median + 1, max, depth + 1);
  return median;
}

static int kd_nearest(kdtree *tree, int i, const double *pos)
{
   struct kdnode *node;
   int dir = -1;

   if( i == -1)
     {
       return 0;
     }

   node = tree->nodes_ + i;
   dir = node->dir_;

   if(pos[dir] - node->pos_[dir])
     {
       /*search the right child node*/
       kd_nearest(tree, node->right_, pos);
     }
   else
     {
       /*search the left child node*/
       kd_nearest(tree, node->left_, pos);
     }

}
