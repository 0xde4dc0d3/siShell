#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include "ss_builtin.h"
#include "ss_visual.h"

const char *ss_builtin[] = {"ls", "clear", "exit", "whoami"};
void (*ss_builtin_func[])(void *arg) = {ss_ls, ss_clear, ss_whoami};

int ss_is_builtin(const char *command) {
    for (int i = 0; i < SS_BUILTIN_LEN; ++i)
        if (strcmp(command, ss_builtin[i]) == 0) return i;
    return -1;
}

void ss_ls(void *arg) {
    struct dirent   *de;
    struct stat     file_stat;

    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd error");
        exit(EXIT_FAILURE);
    }

    DIR *dir;
    if ((dir = opendir(cwd)) == NULL) {
        perror("opendir error");
        exit(EXIT_FAILURE);
    }

    while ((de = readdir(dir))) {
        char file_path[256];
        char file_type;
        char *permissions;
        const char *file_name = de->d_name;

        snprintf(file_path, sizeof(file_path), "%s/%s", cwd, file_name);
        if (stat(file_path, &file_stat) == -1) {
            perror("stat error");
            continue;
        }

        // Determine the file type
        switch (file_stat.st_mode & S_IFMT) {
            case S_IFREG:   file_type = '.';    break;
            case S_IFDIR:   file_type = 'd';    break;
            case S_IFSOCK:  file_type = 's';    break;
            case S_IFIFO:   file_type = 'p';    break;
            default:        file_type = '?';    break; 
        }

        // Don't show hidden files
        // NOTE: in future use strcmp(file_name, "." or "..") to shows
        //      hidden files but not . and ..
        if (file_name[0] == '.') {
            continue;
        } else {
            printf("%c", file_type);

            // Determine user permissions
            printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");

            // Determine group permissions
            printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");

            // Determine other permissions
            printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
            printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

            // Correct file size
            float file_size = file_stat.st_size;
            float fixed_size = (file_size > 1000.f) ? file_size/1000.f : file_size;

            // FIXME: this spacing method is not too good
            printf(" %10.1f%c\t%s\n", fixed_size, (file_size > 1000.f) ? 'k' : 'b', file_name);
        }
    }
    closedir(dir);
    (void)arg;
}

void ss_clear(void *arg) {
    printf("\x1b[3J\x1b[H\x1b[2J");
    (void)arg;
}

void ss_whoami(void *arg) {
    SS_INFO *s = (SS_INFO*)arg;
    printf("%s\n", s->pw->pw_name);
}
