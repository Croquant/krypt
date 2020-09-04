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

char *filename;
char *password;
FILE *file;

void printhelp(void);

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
  if ((file = fopen(filename, "r")) == NULL)
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

  fclose(file);

  return 0;
}

void printhelp(void)
{
  printf("\nKrypter: Simple file encryption with password\n");
  printf("Usage:\n  krypter [OPTIONS]... [FILE]\n");
  printf("Options:\n");
  printf("  -h               help message\n");
  printf("  -f [filename]    file to encrypt (single file only no directories)\n");
  printf("  -p [password]    password for encryption/decryption\n\n");
  printf("Report bugs to: krypter@max1.me\n\n");
}
