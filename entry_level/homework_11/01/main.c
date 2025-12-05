#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 64
#define EXTRA_CHARS 5

/**
 * @brief ASCII codes for punctuation characters used in the greeting.
 * 
 * @enum  Ascii.
 */
typedef enum Ascii {
    COMMA = 44,
    SPACE = 32,
    EXCL  = 33
} Ascii;

/**
 * @brief Predefined dialog messages used in the program.
 */
static const char *dialog[] = {
    "Insert your name: ",
    "Insert your surname: ",
    "Memory allocation failed",
    "Hello"
};

/* --- Function declarations --- */

static inline char *AllocateBuffer(size_t capacity);
static inline char *ReallocateBuffer(char *buffer, size_t capacity);
char               *ReadValue(char *buffer, size_t capacity, const char *prompt);
void                ExitWithError(char *buffer, const char *prompt);
static inline void  CatChar(char *buffer, char ch, size_t *index);
static inline void  CatStr(char *buffer, const char *str, size_t *index);
char               *StrConstruct(char *buffer, const char *name, const char *surname, const char *greeting);
void                CleanMemory(char **pointer);

/*
 *     --- Main program ---
 * 
 * Yeah, I know there are still a lot of bugs in this code.
 * But I'll make it better in the future :)
 */

/**
 * @brief Entry point of the program.
 * 
 * The program reads user's name and surname,
 * constructs a greeting message, and prints it to stdout.
 */
int main(void) {

    size_t capacity = INITIAL_BUFFER_SIZE;
    char *buffer = AllocateBuffer(capacity);

    if (!buffer) ExitWithError(NULL, dialog[2]);

    ReadValue(buffer, capacity, dialog[0]);
    char *name = strdup(buffer);

    ReadValue(buffer, capacity, dialog[1]);
    char *surname = strdup(buffer);

    if (!name || !surname) ExitWithError(buffer, dialog[2]);

    capacity = strlen(dialog[2]) + strlen(name) + strlen(surname) + EXTRA_CHARS;
    buffer = ReallocateBuffer(buffer, capacity);

    if (!buffer) ExitWithError(NULL, dialog[2]);

    printf("%s\n", StrConstruct(buffer, name, surname, dialog[3]));

    CleanMemory(&name);
    CleanMemory(&surname);
    CleanMemory(&buffer);

    return EXIT_SUCCESS;
}

/* --- Function definitions --- */

/**
 * @brief Allocates a new memory buffer of the given capacity.
 *
 * @param capacity Size of memory block to allocate in bytes.
 * @return         Pointer to allocated buffer or NULL if allocation fails.
 * 
 * @warning The returned pointer must be released before program execution terminates.
 */
static inline char *AllocateBuffer(size_t capacity) {

    return (char*)malloc(capacity);
}

/**
 * @brief Reallocates an existing buffer to a new capacity.
 *
 * @param buffer   Pointer to previously allocated memory.
 * @param capacity New desired size of the buffer.
 * @return         Pointer to reallocated buffer or NULL if allocation fails.
 * 
 * @warning The old pointer becomes invalid.
 *          Always assign the return value back to your temporary variable.
 */
static inline char *ReallocateBuffer(char *buffer, size_t capacity) {

    return (char*)realloc(buffer, capacity);
}

/**
 * @brief Reads and write a line of text from standard input to buffer.
 * 
 * @param buffer   Pointer to destination buffer.
 * @param capacity Maximum number of characters (including terminator).
 * @param prompt   Message to display before reading.
 * @return         Pointer to the buffer containing the read string.
 * 
 * @warning This function modifies the contents of @p buffer.
 */
char *ReadValue(char *buffer, size_t capacity, const char *prompt) {

    printf("%s", prompt);

    size_t length = 0;
    int ch = 0;

    while ((ch = getchar()) != '\n' && ch != EOF) {

        if (length < capacity - 1) buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    return buffer;
}

/**
 * @brief Appends a single character to a characters buffer.
 *
 * @param buffer Destination buffer.
 * @param ch     Character to append.
 * @param index  Pointer to current position index (auto-incremented).
 * 
 * @warning This function modifies the contents of @p buffer and @p index.
 */
static inline void CatChar(char *buffer, char ch, size_t *index) {

    buffer[(*index)++] = ch;
}

/**
 * @brief Appends a string to a destination buffer.
 *
 * @param buffer Destination buffer.
 * @param str    Source string to append.
 * @param index  Pointer to current position index (auto-incremented).
 * 
 * @warning This function modifies the contents of @p buffer and @p index.
 */
static inline void CatStr(char *buffer, const char *str, size_t *index) {

    for (size_t i = 0; str[i] != '\0'; i++) {

        CatChar(buffer, str[i], index);
    }
}

/**
 * @brief Constructs a greeting message in the given buffer.
 * 
 * Example output format: "<greeting>, <name> <surname>!"
 * 
 * @param buffer      Destination buffer.
 * @param name        User’s name.
 * @param surname     User’s surname.
 * @param greeting    Greeting word ("Hello").
 * @return            Pointer to the constructed string.
 * 
 * @warning This function modifies @p buffer contents.
 */
char *StrConstruct(char *buffer, const char *name, const char *surname, const char *greeting) {

    size_t index = 0;

    CatStr(buffer, greeting, &index); CatChar(buffer, COMMA, &index);
    CatChar(buffer, SPACE, &index);
    CatStr(buffer, name, &index); CatChar(buffer, SPACE, &index);
    CatStr(buffer, surname, &index); CatChar(buffer, EXCL, &index);

    buffer[index] = '\0';
    return buffer;
}

/**
 * @brief Prints an error message, releases memory, and terminates program.
 *
 * @param buffer Pointer to allocated memory (may be NULL).
 * @param prompt Error message to display.
 * 
 * @warning After calling this function, the original pointer of @p buffer becomes NULL.
 *          This function does not return — it terminates the program.       
 */
void ExitWithError(char *buffer, const char *prompt) {

    if (buffer) CleanMemory(&buffer);

    fprintf(stderr, "%s\n", prompt);
    exit(EXIT_FAILURE);
}

/**
 * @brief Safely frees allocated memory and sets pointer to NULL.
 *
 * @param pointer Address of pointer to allocated memory.
 * 
 * @warning After calling this function, the original pointer becomes NULL.
 */
void CleanMemory(char **pointer) {

    if (*pointer) {

        free(*pointer);
        *pointer = NULL;
    }
}