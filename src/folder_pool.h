#ifndef _FOLDER_POOL_H
#define _FOLDER_POOL_H

struct folder_pool {
    const char **ppszFolderPool;
    size_t nzLen;
    size_t nzCapacity;
};

void folder_pool_init(struct folder_pool *pstFolderPool);
int folder_pool_empty(struct folder_pool *pstFolderPool);
void folder_pool_add(struct folder_pool *pstFolderPool, const char *pszFolder);
int folder_pool_contains(struct folder_pool *pstFolderPool, const char *pszFolder);
int folder_pool_contains_or_parent(struct folder_pool *pstFolderPool, const char *pszFolder);
void folder_pool_free(struct folder_pool *pstFolderPool);

#endif
