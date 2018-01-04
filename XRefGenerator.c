#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_ARRAY_SIZE	200
#define MAX_WORD_SIZE		100
#define MAX_FILENAME_SIZE	100
#define MAX_LINE_SIZE		100


int wordInLine(char *line, char *word) 
{
   char const *ret = line;
   int found = 0;

   while (*ret != '\0')
   {
      if (strncmp(ret, word, strlen(word)) == 0)
      {
         found = 1;
      
         return found;
      }
      
      else
      {
         found = 0;
         ret++;
      }
   }

   return found;
}

int wordFound(char word[][MAX_WORD_SIZE], char *tempWord, int wc)
{
   int i = 0;

   for (i = 0; i < wc; i++)
   {
      if (!strcmp(word[i], tempWord))
      {
         return 1;
      }
   }

   return 0;
}

int main(int argc, char *argv[])
{
   char filename[MAX_FILENAME_SIZE];
   char line[MAX_LINE_SIZE];
   char tempWord[MAX_WORD_SIZE];
   char wordList[MAX_WORD_ARRAY_SIZE][MAX_WORD_SIZE] = {0};
   int wc = 0;
   int i = 0;
   int j = 0;
   int lineNum = 0;
   int wordCount[MAX_WORD_ARRAY_SIZE] = {0};
   int foundInLine[MAX_WORD_ARRAY_SIZE][MAX_WORD_ARRAY_SIZE] = {0};
   int count = 0;

   printf("Please enter the name of the file.\n"  );
   scanf("%s", filename);

   FILE *fp = fopen(filename, "rt");

   if (!fp)
   {
      printf("File cannot be opened for reading.\n\n");
      exit(1);
   }

   while (!feof(fp))
   {
      fscanf(fp, "%s", tempWord);
   
      if (!wordFound(wordList, tempWord, wc))
      {
         strcpy(wordList[wc], tempWord);
         wc++;
      }
   }

   fclose(fp);

   fp = fopen(filename, "rt");

   printf("\n\nThere are %d words in the file:\n\n", wc);

   for (i = 0; i < wc; i++)
   {
      lineNum = 0;
      count = 0;
   
      fp = fopen(filename, "rt");
   
      while (fgets(line, sizeof(line), fp))
      {
         lineNum++;
      
         if (wordInLine(line, wordList[i]))
         {
            wordCount[i] = wordCount[i] + 1;
         
            if (foundInLine[i][count] > 0)
            {
               count = count + 1;
            }
         
            foundInLine[i][count] = lineNum;
         }
      }
   
      fclose(fp);
   }

   for (i = 0; i < wc; i++)
   {
      printf("WORD: %s \n", wordList[i]);
      printf("WORD COUNT: %d      ", wordCount[i]);
      printf("LINE NUMBER(S): ");
   
      for (j = 0; j < wordCount[i]; j++)
      {
         printf("%d", foundInLine[i][j]);
      
         if (j < wordCount[i] - 1)
         {
            printf(", ");
         }
      }
   
      printf("\n\n");
   }

   return 0;
}
