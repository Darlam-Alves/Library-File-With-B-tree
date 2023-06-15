#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 150
#define TRUE 1
#define FALSE 0
#define DATA_SIZE 3
#define NUM_RECORDS 100
#define MAX_STRING_SIZE 100
#define MAX 3

typedef struct {
    int id;
    char* title;
    char* author;
} BookRecord;

struct BTreeNode {
    int count;
    BookRecord books[MAX + 1];
    struct BTreeNode* link[MAX + 1];
};

char *readString(char **element);
char *typeofOperations(char *operations);
void executeOperations(char **operations, char **datas, int size);
void readBuffer(char *buffer, int bufferSize);
BookRecord extractData(char *data);

int main() {
  char **data;
  int totalData = 0;

  data = malloc(sizeof(char *) * NUM_RECORDS); 
  readString(&data[totalData]);
  while (strcmp(data[totalData], "EXIT") != 0) {
    totalData++;
    readString(&data[totalData]);
  }
  char **operations = malloc(sizeof(char *) * totalData);
  for (int i = 0; i < totalData; i++)
		//[0] = SEARCH; [1] = ADD [2] ADD [3] SEARCH 
    operations[i] = typeofOperations(data[i]);
  executeOperations(operations, data, totalData);

  for (int i = 0; i < totalData; i++)
    free(data[i]);
  free(data);

  for (int i = 0; i < totalData; i++)
    free(operations[i]);
  free(operations);
}

char *readString(char **element) {
  char buffer[BUFFER_SIZE];
  readBuffer(buffer, BUFFER_SIZE);
  *element = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(*element, buffer);
  return *element;
}

void readBuffer(char *buffer, int bufferSize) {
  scanf(" %[^(\n|\r)]", buffer);
  buffer[strcspn(buffer, "\n")] = '\0';
}

char *typeofOperations(char *operations) {
  char buffer[BUFFER_SIZE];
  strcpy(buffer, operations);
  char *token = strtok(buffer, " ");

  if (token != NULL) {
    char *result = malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(result, token);
    return result;
  }

  return NULL;
}

void executeOperations(char **operations, char **data, int size) {
  for (int i = 0; i < size; i++) {
    if (strcmp(operations[i], "ADD") == 0) {
      BookRecord book = extractData(data[i]);
      //trecho para inserir na arvore B
      free(book.title);
      free(book.author);
    } else if (strcmp(operations[i], "SEARCH") == 0) {
      
			printf("buscando autor\n");
    }
  }
}

BookRecord extractData(char *data) {
  BookRecord book;
  char id[BUFFER_SIZE];
  char title[BUFFER_SIZE];
  char author[BUFFER_SIZE];
  sscanf(data, "ADD id = '%[^']' titulo = '%[^']' autor = '%[^']'", id, title,
         author);

  char **datas = malloc(sizeof(char *) * DATA_SIZE);
  book.id = atoi(id);
  book.title = malloc(sizeof(char) * (strlen(title) + 1));
  strcpy(book.title, title);
  book.author = malloc(sizeof(char) * (strlen(author) + 1));
  strcpy(book.author, author);
  return book;
}
