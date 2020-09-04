////////////////////////////////////////////////////////////////////////////////
// krypter - simple file encryption with password
// copryright 2020 - Maxime Desmet Vanden Stock
// file: word.h
////////////////////////////////////////////////////////////////////////////////

#ifndef WORD_H
#define WORD_H

int get_checksum(char *);
char *encrypt_password(char *, char *);

int get_checksum(char *str)
{
    uint64_t sum = 0;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        sum += str[i];
    }
    return (char)sum;
}

// !! password is overwritten, make copy !!
char *encrypt_password(char *password, char *key)
{
    int i;
    for (i = 0; i < strlen(password); i++)
    {
        password[i] = password[i] ^ key[i % 2];
    }
    return password;
}

#endif // WORD_H