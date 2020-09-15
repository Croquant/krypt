////////////////////////////////////////////////////////////////////////////////
// krypter - simple file encryption with password
// copryright 2020 - Maxime Desmet Vanden Stock
// file: word.c
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "word.h"

#define OPT_STRING "hf:p:"
#define KEY_LENGTH 256

char *filename;
char *password;
FILE *file;

char key[KEY_LENGTH];

void printhelp(void);

void complete_key (char *key)
{
	key[KEY_LENGTH - 1] = 0;
	int len = strlen(key);
	printf("LENGTH: %d\n", len);
	int i;
	for (i = len; i < KEY_LENGTH; i++)
	{
		key[i] = key[i - 1] + key[i - 2];
	}
	key[KEY_LENGTH - 1] = 0;
	key[KEY_LENGTH - 1] = get_checksum(key);
}

void shift_key (char *key, int n)
{
	int i;
	for (i = 0; i < n; i ++)
	{
		char temp = key[0];
		int j;
		for (j = 0; j < KEY_LENGTH; j++)
		{
			key[j] = key[j + 1];
		}
		key[j] = temp;
	}
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "ERROR: wrong number of arguments\n");
    printhelp();
    exit(EXIT_FAILURE);
  }

  // manual input with getopt
  int opt;
  while ((opt = getopt(argc, argv, OPT_STRING)) != -1)
  {
    switch (opt)
    {
    case 'h':
      printhelp();
      exit(EXIT_SUCCESS);
      break;
    case 'f':
      filename = optarg;
      break;
    case 'p':
      password = optarg;
      break;
    default:
      printhelp();
      exit(EXIT_FAILURE);
      break;
    }
  }

  // if only filename given as arguments
  if (filename == NULL)
  {
    filename = argv[optind];
  }
  if ((file = fopen(filename, "w")) == NULL)
  {
    fprintf(stderr, "ERROR: cannot open file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  // if opt not used prompt user
  if (password == NULL)
  {
    password = getpass("Please enter a password: ");
  }

  printf("FILE: %s\n", filename);
  printf("PASS: %s\n", password);

	// 14/09/2020 test for making key
	strcpy(key, password);
	complete_key(key);
	shift_key(key, key[KEY_LENGTH - 1]);
	fwrite(key, KEY_LENGTH, 1, file);

  fclose(file);

  return 0;
}

void printhelp(void)
{
  printf("\nKrypter: Simple file encryption with password\n");
  printf("Usage:\n  krypter [OPTIONS]... [FILE]\n");
  printf("Options:\n");
  printf("  -h             help message\n");
  printf("  -f [filename]  file to encrypt (single file only no directories)\n");
  printf("  -p [password]  password for encryption/decryption\n\n");
  printf("Report bugs to: krypter@max1.me\n\n");
}
