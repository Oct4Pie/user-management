#include <stdio.h>

typedef struct _user {
    int user_id;
    char name[64];
    char passwd[64];
} User;

char user_file[50] = "users.dat";

User get_user(int user_id) {
    FILE* u_file = fopen(user_file, "rb");
    if (!u_file) {
        u_file = fopen(user_file, "wb");
    }
    if (!u_file) {
        printf("cannot access/create user file\n");
    }
    User user;
    while (feof(u_file) != 0) {
        fread(&user, sizeof(user), 1, u_file);
        if (user.user_id == user_id) {
            return user;
        }
    }
    user.user_id = -1;
    return user;
}

void add_user(User* user) {
    FILE* u_file = fopen(user_file, "rb");
    if (!u_file) {
        u_file = fopen(user_file, "wb");
    }
    if (!u_file) {
        printf("cannot access/create user file\n");
    }
    fwrite(user, sizeof(*user), 1, u_file);
    fclose(u_file);
}