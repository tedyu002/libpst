#ifndef _FOLDER_LIST_H
#define _FOLDER_LIST_H

struct folder_list {
    char **ppszFolders;
    size_t nzLen;
    size_t nzCapacity;
};

void folder_list_init(struct folder_list *pstFolderList);
void folder_list_pop(struct folder_list *pstFolderList);
void folder_list_push(struct folder_list *pstFolderList, const char *pszName);
void folder_list_free(struct folder_list *pstFolderList);
void folder_list_print(struct folder_list *pstFolderList, FILE *fp);
char *folder_list_get(struct folder_list *pstFolderList);

#endif
