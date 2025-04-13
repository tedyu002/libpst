#include "define.h"

void
pst_item_list_init(struct pst_item_list *pstItemList)
{
    const size_t CAPACITY_INIT = 8;

    pstItemList->pstItems = malloc(CAPACITY_INIT * sizeof(struct pst_item_node));
    if (pstItemList->pstItems == NULL) {
        DIE(("Failed to malloc memory.\n"));
    }
    pstItemList->nzOffset = 0;
    pstItemList->nzLen = 0;
    pstItemList->nzCapacity = CAPACITY_INIT;
}

void
pst_item_list_push(struct pst_item_list *pstItemList, pst_item *pstItem, pst_desc_tree *d_ptr)
{
    if (pstItemList->nzLen == pstItemList->nzCapacity) {
        size_t nzNewCapacity = pstItemList->nzCapacity * 2;
        struct pst_item_node *pstNewItems = NULL;

        pstNewItems = realloc(pstItemList->pstItems, nzNewCapacity * sizeof(struct pst_item_node));
        if (pstNewItems == NULL) {
            DIE(("Failed to realloc memory.\n"));
        }

        pstItemList->pstItems = pstNewItems;
        pstItemList->nzCapacity = nzNewCapacity;
    }

    pstItemList->pstItems[pstItemList->nzLen].pst_item = pstItem;
    pstItemList->pstItems[pstItemList->nzLen].d_ptr = d_ptr;
    pstItemList->nzLen += 1;
}

int
pst_item_list_empty(struct pst_item_list *pstItemList)
{
    return pstItemList->nzLen == 0;
}

void
pst_item_list_shift(struct pst_item_list *pstItemList, pst_item **ppstItem, pst_desc_tree **pd_ptr)
{
    if (pstItemList->nzLen == 0) {
        return;
    }

    *ppstItem = pstItemList->pstItems[pstItemList->nzOffset].pst_item;
    *pd_ptr = pstItemList->pstItems[pstItemList->nzOffset].d_ptr;
    pstItemList->nzOffset += 1;
    pstItemList->nzLen -= 1;
    if (pstItemList->nzLen == 0) {
        pstItemList->nzOffset = 0;
    }
}

void
pst_item_list_free(struct pst_item_list *pstItemList)
{
    pst_desc_tree *d_ptr;

    if (pstItemList->pstItems == NULL) {
        return;
    }

    while (pstItemList->nzLen > 0) {
        pst_item *pst_item = NULL;
        pst_item_list_shift(pstItemList, &pst_item, &d_ptr);
        if (pst_item != NULL) {
            pst_freeItem(pst_item);
        }
    }
    free(pstItemList->pstItems);
    pstItemList->pstItems = NULL;
}
