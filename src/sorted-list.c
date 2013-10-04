#include <stdlib.h>
#include <stdio.h>

#include "sorted-list.h"

node create_node(void *v) {
  node n = malloc(sizeof(struct node_));
  n->next = NULL;
  n->prev = NULL;
  n->val = v;

  return n;
}

void destroy_node(node n) {
  free(n);
}

SortedListPtr SLCreate(CompareFuncT cf) {
  SortedListPtr lp = malloc(sizeof(struct SortedList));

  lp->cmp = cf;
  lp->ll  = NULL;
  lp->iters = NULL;

  return lp;
}

void SLDestroy(SortedListPtr list) {
  node ptr, t;

  for (ptr = list->ll; ptr != NULL; ) {
    t = ptr->next;
    free(ptr);
    ptr = t;
  }

  free(list);
}


int SLInsert(SortedListPtr list, void *value) {
  node new_node = create_node(value),
       ptr      = list->ll,
       prev     = NULL;

  if (list->ll == NULL) {
    list->ll = new_node;
  }

  else {
    for (ptr = list->ll; ptr != NULL; ptr = ptr->next) {
      if ( list->cmp(value, ptr->val) >= 0) {
        if (prev == NULL)
        {
          new_node->next = ptr;
          list->ll = new_node;
        } else {
          new_node->next = ptr;
          prev->next = new_node;
        }
        return 1;
      } else {
        prev = ptr;
      }
    }
    prev->next = new_node;
  }

  return 1;
}


int SLRemove(SortedListPtr list, void *newObj) {
  node ptr;
  node prev = NULL;

  for (ptr = list->ll; ptr != NULL; ptr = ptr->next) {
    if (list->cmp(ptr->val, newObj) == 0) {
      if (prev == NULL) {
        list->ll = ptr->next;
        destroy_node(ptr);
      } else {
        prev->next = ptr->next;
        destroy_node(ptr);
      }
      return 1;
    }
    prev = ptr;
  }

  return 0;
}

//do we need anything else?
SortedListIteratorPtr SLCreateIterator(SortedListPtr list) {
  node t;
  node head;
  SortedListIteratorPtr slip = malloc(sizeof(struct SortedListIterator));
  head = create_node(NULL);
  head->next = list->ll;
  slip->head = head;
  slip->curr = head;
  if (list->iters == NULL) {
    list->iters = create_node(slip);
  } else {
    t = create_node(slip);
    t->next = list->iters;
  }

  return slip;
}


void SLDestroyIterator(SortedListIteratorPtr iter) {
  free(iter->head);
  free(iter);
}


void *SLNextItem(SortedListIteratorPtr iter) {
  iter->curr = iter->curr->next;

  return iter->curr->val;
}

void printList(SortedListPtr list) {
  node ptr;

  for (ptr = list->ll; ptr != NULL; ptr = ptr->next) {
    printf("%d\n", *(int*)ptr->val);
  }
}
