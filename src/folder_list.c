#include "define.h"

void
folder_list_init(struct folder_list *pstFolderList)
{
    const size_t CAPACITY_INIT = 8;

    pstFolderList->ppszFolders = malloc(CAPACITY_INIT * sizeof(char *));
    if (pstFolderList->ppszFolders == NULL) {
        DIE(("Failed to malloc memory.\n"));
    }
    pstFolderList->nzLen = 0;
    pstFolderList->nzCapacity = CAPACITY_INIT;
}

void
folder_list_pop(struct folder_list *pstFolderList)
{
    if (pstFolderList->nzLen == 0) {
        return;
    }

    pstFolderList->nzLen -= 1;
    free(pstFolderList->ppszFolders[pstFolderList->nzLen]);
}

void
folder_list_push(struct folder_list *pstFolderList, const char *pszName)
{
    if (pstFolderList->nzLen == pstFolderList->nzCapacity) {
        size_t nzNewCapacity = pstFolderList->nzCapacity * 2;
        char **ppszNewFolders = NULL;

        ppszNewFolders = realloc(pstFolderList->ppszFolders, nzNewCapacity * sizeof(char *));
        if (ppszNewFolders == NULL) {
            DIE(("Failed to realloc memory.\n"));
        }

        pstFolderList->ppszFolders = ppszNewFolders;
        pstFolderList->nzCapacity = nzNewCapacity;
    }

    pstFolderList->ppszFolders[pstFolderList->nzLen] = strdup(pszName);
    if (pstFolderList->ppszFolders[pstFolderList->nzLen] == NULL) {
        DIE(("Failed to dup memory.\n"));
    }
    pstFolderList->nzLen += 1;
}

void
folder_list_free(struct folder_list *pstFolderList)
{
    size_t i = 0;

    if (pstFolderList->ppszFolders == NULL) {
        return;
    }

    for (i = 0; i < pstFolderList->nzLen; ++i) {
        free(pstFolderList->ppszFolders[i]);
    }

    free(pstFolderList->ppszFolders);
    pstFolderList->ppszFolders = NULL;
}

void
folder_list_print(struct folder_list *pstFolderList, FILE *fp)
{
    size_t i = 0;
    const char *pszSep = "";

    for (i = 0; i < pstFolderList->nzLen; ++i) {
        fprintf(fp, "%s%s", pszSep, pstFolderList->ppszFolders[i]);
        pszSep = "/";
    }
}

char *
folder_list_get(struct folder_list *pstFolderList)
{
    FILE *fp = NULL;
    char *pszBuf = NULL;
    size_t nzBufLen = 0;
    char *pszRet = NULL;
    int nRes = 0;

    fp = open_memstream(&pszBuf, &nzBufLen);
    if (fp == NULL) {
        DIE(("Failed to malloc memory.\n"));
    }

    folder_list_print(pstFolderList, fp);
    nRes = fclose(fp);
    fp = NULL;
    if (nRes == EOF) {
        goto end;
    }

    pszRet = pszBuf;
    pszBuf = NULL;

end:
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }

    if (pszBuf != NULL) {
        free(pszBuf);
        pszBuf = NULL;
    }

	 return pszRet;
}
