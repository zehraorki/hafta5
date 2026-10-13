#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta {
    int id;
    char ad[50];
    char durum[20];
    struct Hasta *next;
} Hasta;

typedef struct {
    Hasta *front;
    Hasta *rear;
} Queue;

typedef struct {
    Hasta *top;
} Stack;

typedef struct {
    Hasta *head;
} LinkedList;

Hasta* hastaOlustur(int id, const char *ad, const char *durum) {
    Hasta *yeni = (Hasta*)malloc(sizeof(Hasta));
    if (yeni == NULL) {
        printf("Hata: Bellek ayrilamadi!\n");
        exit(1);
    }
    yeni->id = id;
    strcpy(yeni->ad, ad);
    strcpy(yeni->durum, durum);
    yeni->next = NULL;
    return yeni;
}

void enqueue(Queue *q, int id, const char *ad) {
    Hasta *yeni = hastaOlustur(id, ad, "bekliyor");

    if (q->rear == NULL) {
        q->front = yeni;
        q->rear = yeni;
    } else {
        q->rear->next = yeni;
        q->rear = yeni;
    }
}

Hasta* dequeue(Queue *q) {
    if (q->front == NULL) {
        return NULL;
    }

    Hasta *cikarilan = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    cikarilan->next = NULL;
    return cikarilan;
}

void push(Stack *s, Hasta *h) {
    if (h == NULL) return;

    strcpy(h->durum, "muayenede");
    h->next = s->top;
    s->top = h;
}

Hasta* pop(Stack *s) {
    if (s->top == NULL) {
        return NULL;
    }

    Hasta *cikarilan = s->top;
    s->top = s->top->next;

    cikarilan->next = NULL;
    return cikarilan;
}

void gecmiseEkle(LinkedList *list, Hasta *h) {
    if (h == NULL) return;

    strcpy(h->durum, "tamamlandi");
    h->next = NULL;

    if (list->head == NULL) {
        list->head = h;
    } else {
        Hasta *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = h;
    }
}

void bekleyenleriYazdir(Queue *q) {
    printf("--- Bekleyen Hastalar ---\n");
    if (q->front == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *temp = q->front;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

void muayenedekileriYazdir(Stack *s) {
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (s->top == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *temp = s->top;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

void tamamlananlariYazdir(LinkedList *list) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (list->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *temp = list->head;
    while (temp != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", temp->id, temp->ad, temp->durum);
        temp = temp->next;
    }
}

void bellegiTemizle(LinkedList *list, Queue *q, Stack *s) {
    Hasta *temp;

    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    while (q->front != NULL) {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    while (s->top != NULL) {
        temp = s->top;
        s->top = s->top->next;
        free(temp);
    }
}

int main() {
    Queue bekleyenKuyrugu = {NULL, NULL};
    Stack muayeneYigini = {NULL};
    LinkedList gecmisListesi = {NULL};

    enqueue(&bekleyenKuyrugu, 1, "Ahmet");
    enqueue(&bekleyenKuyrugu, 2, "Mehmet");
    enqueue(&bekleyenKuyrugu, 3, "Ayse");

    Hasta *h1 = dequeue(&bekleyenKuyrugu);
    if (h1 != NULL) {
        push(&muayeneYigini, h1);
        Hasta *biten1 = pop(&muayeneYigini);
        gecmiseEkle(&gecmisListesi, biten1);
    }

    Hasta *h2 = dequeue(&bekleyenKuyrugu);
    if (h2 != NULL) {
        push(&muayeneYigini, h2);
        Hasta *biten2 = pop(&muayeneYigini);
        gecmiseEkle(&gecmisListesi, biten2);
    }

    printf("=== Tum Islemler Sonrasi ===\n\n");
    bekleyenleriYazdir(&bekleyenKuyrugu);
    printf("\n");
    muayenedekileriYazdir(&muayeneYigini);
    printf("\n");
    tamamlananlariYazdir(&gecmisListesi);

    bellegiTemizle(&gecmisListesi, &bekleyenKuyrugu, &muayeneYigini);

    return 0;
}