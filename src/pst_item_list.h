#ifndef _PST_ITEM_LIST_H
#define _PST_ITEM_LIST_H

#include "libpst.h"

struct pst_item_node {
    pst_item *pst_item;
    pst_desc_tree *d_ptr;
};

struct pst_item_list {
    struct pst_item_node *pstItems;
    size_t nzOffset;
    size_t nzLen;
    size_t nzCapacity;
};

void pst_item_list_init(struct pst_item_list *pstItemList);
void pst_item_list_push(struct pst_item_list *pstItemList, pst_item *pstItem, pst_desc_tree *d_ptr);
int pst_item_list_empty(struct pst_item_list *pstItemList);
/* Cannot push after shift */
void pst_item_list_shift(struct pst_item_list *pstItemList, pst_item **ppstItem, pst_desc_tree **pd_ptr);
void pst_item_list_free(struct pst_item_list *pstItemList);

#endif
