#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
#include <stdbool.h>

#ifndef _WIN32
char *strtok_r(char *, const char *, char **);
#else
static inline char *strtok_r(char *const str, const char *const delim,
							 char **const context)
{
	return strtok_s(str, delim, context);
}
#endif

char *kth_word_in_mth_sentence_of_nth_paragraph(
        char ****const document, const int k, const int m, const int n)
{
    return document[n - 1][m - 1][k - 1];
}

char **kth_sentence_in_mth_paragraph(char ****const document,
                                     const int k, const int m)
{
    return document[m - 1][k - 1];
}

char ***kth_paragraph(char ****const document, const int k)
{
    return document[k - 1];
}

static void *xcalloc(const size_t count, const size_t size)
{
    void *const p = calloc(count, size);
    if (!p) abort();
    return p;
}

static inline void require(const bool condition)
{
    if (!condition) abort();
}

static int tokenize(char *const str, const char *const delim,
                    char **const out, const int outlen)
{
    int count = 0;

    for (char *q = NULL, *p = strtok_r(str, delim, &q); p;
            p = strtok_r(NULL, delim, &q)) {
        assert(0 <= count);
        require(count < outlen);
        out[count++] = p;
    }

    return count;
}

static char **get_words(char *const sentence)
{
    char **const words = xcalloc(MAX_CHARACTERS, sizeof *words);
    tokenize(sentence, " \t", words, MAX_CHARACTERS);
    return words;
}

static char ***get_sentences(char *const paragraph)
{
	char *sentences[MAX_CHARACTERS] = {0};
    const int count = tokenize(paragraph, ".", sentences, MAX_CHARACTERS);

    char ***const ret = xcalloc(count, sizeof *ret);
    for (int i = 0; i < count; ++i) ret[i] = get_words(sentences[i]);
    return ret;
}

char ****get_document(char *const text)
{
	char *paragraphs[MAX_PARAGRAPHS] = {0};
    const int count = tokenize(text, "\r\n\f\v", paragraphs, MAX_PARAGRAPHS);

    char ****const ret = xcalloc(count, sizeof *ret);
    for (int i = 0; i < count; ++i) ret[i] = get_sentences(paragraphs[i]);
    return ret;
}


char* get_input_text() {
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
}

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main()
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }
}
