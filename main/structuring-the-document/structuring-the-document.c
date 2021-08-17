#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

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

static inline void require(const bool condition)
{
    if (!condition) abort();
}

static void *xcalloc(const size_t count, const size_t size)
{
    void *const p = calloc(count, size);
    require(p);
    return p;
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

static struct sentence get_sentence(char *const str)
{
    char *words[MAX_CHARACTERS] = {0};
    const int count = tokenize(str, " \t", words, MAX_CHARACTERS);

    const struct sentence sen = {xcalloc(count, sizeof *sen.data), count};
    for (int i = 0; i < count; ++i) sen.data[i] = (struct word){words[i]};
    return sen;
}

static struct paragraph get_paragraph(char *const str)
{
    char *sentences[MAX_CHARACTERS] = {0};
    const int count = tokenize(str, ".", sentences, MAX_CHARACTERS);

    const struct paragraph para = {xcalloc(count, sizeof *para.data), count};
    for (int i = 0; i < count; ++i) para.data[i] = get_sentence(sentences[i]);
    return para;
}

struct document get_document(char *const str)
{
    char *paragraphs[MAX_PARAGRAPHS] = {0};
    const int count = tokenize(str, "\r\n\f\v", paragraphs, MAX_PARAGRAPHS);

    const struct document doc = {xcalloc(count, sizeof *doc.data), count};
    for (int i = 0; i < count; ++i) doc.data[i] = get_paragraph(paragraphs[i]);
    return doc;
}

struct paragraph kth_paragraph(const struct document doc, const int k)
{
	assert(0 < k && k <= doc.paragraph_count);
	return doc.data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(const struct document doc,
                                              const int k, const int m)
{
	const struct paragraph para = kth_paragraph(doc, m);
	assert(0 < k && k <= para.sentence_count);
	return para.data[k - 1];
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(
	const struct document doc, const int k, const int m, const int n)
{
	const struct sentence sen = kth_sentence_in_mth_paragraph(doc, m, n);
	assert(0 < k && k <= sen.word_count);
	return sen.data[k - 1];
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main()
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
}
