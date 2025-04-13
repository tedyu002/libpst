#include "define.h"
#include "folder_pool.h"

static int is_parent_or_same_folder(const char *pszParent, const char *pszChild);

void
folder_pool_init(struct folder_pool *pstFolderPool)
{
    const size_t CAPACITY_INIT = 8;

    pstFolderPool->ppszFolderPool = malloc(CAPACITY_INIT * sizeof(const char *));
    if (pstFolderPool->ppszFolderPool == NULL) {
        DIE(("Failed to malloc memory.\n"));
    }

    pstFolderPool->nzLen = 0;
    pstFolderPool->nzCapacity = CAPACITY_INIT;
}

int
folder_pool_empty(struct folder_pool *pstFolderPool)
{
    return pstFolderPool->nzLen == 0;
}

void
folder_pool_add(struct folder_pool *pstFolderPool, const char *pszFolder)
{
    if (pstFolderPool->nzLen == pstFolderPool->nzCapacity) {
        const char **ppszNewFolderPool = NULL;
        size_t nzNewCapacity = pstFolderPool->nzCapacity * 2;

        ppszNewFolderPool = realloc(pstFolderPool->ppszFolderPool, nzNewCapacity * sizeof(const char *));
        if (ppszNewFolderPool == NULL) {
            DIE(("Failed to malloc memory.\n"));
        }

        pstFolderPool->ppszFolderPool = ppszNewFolderPool;
        pstFolderPool->nzCapacity = nzNewCapacity;
    }

    pstFolderPool->ppszFolderPool[pstFolderPool->nzLen] = pszFolder;
    pstFolderPool->nzLen += 1;
}

int
folder_pool_contains(struct folder_pool *pstFolderPool, const char *pszFolder)
{
    size_t i = 0;

    for (i = 0; i < pstFolderPool->nzLen; ++i) {
        if (strcmp(pstFolderPool->ppszFolderPool[i], pszFolder) == 0) {
            return 1;
        }
    }

    return 0;
}

int
folder_pool_contains_or_parent(struct folder_pool *pstFolderPool, const char *pszFolder)
{
    size_t i = 0;

    for (i = 0; i < pstFolderPool->nzLen; ++i) {
        if (is_parent_or_same_folder(pszFolder, pstFolderPool->ppszFolderPool[i])) {
            return 1;
        }
    }

    return 0;
}

void
folder_pool_free(struct folder_pool *pstFolderPool)
{
    if (pstFolderPool->ppszFolderPool != NULL) {
        free(pstFolderPool->ppszFolderPool);
        pstFolderPool->ppszFolderPool = NULL;
    }
}

static int
is_parent_or_same_folder(const char *pszParent, const char *pszChild)
{
    size_t nzParentLen = 0;

    nzParentLen = strlen(pszParent);
    if (strncmp(pszParent, pszChild, nzParentLen) != 0) {
        return 0;
    }

    if (pszChild[nzParentLen] != '/' && pszChild[nzParentLen] != '\0') {
        return 0;
    }

    return 1;
}
