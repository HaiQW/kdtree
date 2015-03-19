#ifndef KDTREE_H
#define KDTREE_H

struct kdhyperrect
{
  int dim;
  double *min, *max; //n dimensional range
};

struct kdnode
{
  double *pos_;
  int dir_;// Pivot: dicision dimension
  double *data_;
  //struct kdnode *left, *right;//left and right child nodes
  int id_, left_, right_;
};

struct res_node
{
  struct kdnode *item;
  double dist_sq;
  struct res_node *nest;
};

/*The kd-tree itself, and all data nodes are stored in an array*/
struct kdtree
{
  //int dim;
  //struct kdnode *root;
  //struct kdhyperrect *rect;
  //struct kdnode *node;//store data point
  //void(*destr)(void*);
  int dim_;
  int root_;
  int len_;
  struct kdnode *nodes_;
};

struct kdres
{
  struct kdtree *tree;
  struct res_node *rlist, *riter;
  int size;

};

/*Create a kdtree for "k" dimensional data*/
struct kdtree *kd_create(int k, int len, double **pos);

/*free the struct kdtree*/
void kd_clear(struct kdtree *tree);

/*remove all the elements frome the tree*/
void kd_free(struct kdtree *tree);

/*
 * If called with non-null 2nd argument, the function provided will
 * be called on data pointers when nodes are to be removed from the
 * tree.
 **/
void kd_data_destructor(struct kdtree *tree, void (*destr)(void*));


/* Insert a node, specifying its position, and optional data*/
int kd_insert(struct kdtree *tree, const double *pos, void *data);


/*
 * Find the nearest node from a given point.
 * This function returns a pointer to a result set with at most one element.
 **/
struct kdtree *kd_nearest(struct kdtree *tree, const double *pos);


/*
 * Find any nearest nodes from a given point within a range.
 *
 * This functions returns a pointer to a result set, which can be manipulated
 * by the kd_res* function.
 **/
struct kdres *kd_nearest_range(struct kdtree *tree, const double *pos,
                               double range);


/* frees a result set return by kd_nearest_range()*/
void kd_res_free(struct kdres *set);


/* returns the size of the result set*/
int kd_res_size(struct kdres *set);


/* rewinds the result set iterator*/
void kd_res_rewind(struct kdres *set);


/* returns non-zero if the set iterator reached the end after last elements*/
int kd_res_end(struct kdres *set);


/*
 * Advances the result set iterator, returns non-zero on success, zero if there
 * are no more elements in the result set.
 **/
int kd_res_next(struct kdres *set);


/*
 * Returns the data pointer(can be null) of the current result set item and
 * optionally sets its position to the pointers if not null
 **/
void *kd_res_item(struct kdres *set, double *pos);

/* equivalent to kd_res_item(set,0)*/
void *kd_res_item_data(struct kdres* set);






#endif // KDTREE_H
