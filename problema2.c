#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//structura fiecarui cuvant din dictionar
struct dictionary_entry {
    char* word;
    int priority;
};

//functie de autocompletare
void autocompletare(int n, int m, char (*v)[22], struct dictionary_entry *c) {
    int i, j, g, k, aux, nr;
    int gasit[5000];
    //parcurgerea fiecarui cuvant introdus
    for(j = 0 ; j < m ; j++) {
        g = 0;
        //parcurgerea fiecarui cuvant din dictionar
        for(i = 0 ; i < n; i++) {
            //verificarea daca la finalul cuvantului introdus este "*"
            if(v[j][strlen(v[j]) - 1] == '*') {
                if(strncmp(v[j], c[i].word, strlen(v[j]) - 1) == 0 ) {
                    //vectorul "gasit" retine indicii cuvintelor din dictionar care pot fi completarea cuvantului introdus
                    gasit[g] = i;
                    //contorizarea numarului de cuvinte din dictionar pot fi completarea cuvantului introdus
                    g++;
                }
            }
            else {
                if(strncmp(v[j], c[i].word , strlen(v[j])) == 0 ) {
                    //vectorul "gasit" retine indicii cuvintelor din dictionar care pot fi completarea cuvantului introdus
                    gasit[g] = i;
                    //contorizarea numarului de cuvinte din dictionar pot fi completarea cuvantului introdus
                    g++;
                }
            }
        }
        //realizarea sortarii vectorului gasit in functie de prioritare
        for(i = 0 ; i < g - 1 ; i++) {
            for(k = i + 1; k < g; k++) {
                if(c[gasit[i]].priority < c[gasit[k]].priority) {
                        aux = gasit[i];
                        gasit[i] = gasit[k];
                        gasit[k] = aux;
                }
            }
        }
        k = 1;
        //parcurgerea tuturor cuvintelor care pot fi completarea cuvantului introdus astfel incat gasit[0] sa fie cel mai aproape in ordine lexicografica
        while(k < g && c[gasit[k]].priority == c[gasit[0]].priority) {
            if(strcmp(c[gasit[0]].word, c[gasit[k]].word) > 0) {
                aux = gasit[0];
                gasit[0] = gasit[k];
                gasit[k] = aux;
            }
            k++;
        }
        //cazul cand la finalul cuvantului introdus este "*"
        if(v[j][strlen(v[j]) - 1] == '*') {
            //cazul cand nu are cuvinte in dictionar care pot fi completarea cuvantului introdus
            if(g == 0) {
                n = n + 1;
                //realocarea dinamica a dictionarului
                c = realloc(c, (n + 1) * sizeof(struct dictionary_entry));
                //initializarea noului cuvant cu prioritatea 1
                c[n - 1].priority = 1;
                //alocarea dinamica noula cuvant in dictionar
                c[n - 1].word = calloc((strlen(v[j]) + 1), sizeof(char));
                //copierea in dictionar a noului cuvant
                strncpy(c[n - 1].word, v[j], strlen(v[j]) - 1);
                //afisarea cuvantului
                printf("%s ", c[n - 1].word);
            }
            //cazul cand are cuvinte in dictionar care pot fi completarea cuvantului introdus
            else {
                nr = 0;
                //parcurgere a tuturor cuvintelor care pot fi completarea cuvantului
                for(i = 0; i < g; i++) {
                    //verificare daca exista un cuvant in dictionar sa fie la fel cu cuvantul introdus
                    if(strlen(v[j]) == strlen(c[gasit[i]].word) + 1) {
                        c[gasit[i]].priority++;
                        //daca exista, il afisam
                        printf("%s ", c[gasit[i]].word);
                        break;
                    }
                    //in caz contrar, marim variabila nr
                    else {
                        nr++;
                    }
                }
                //verificarea daca toate cuvintele din dictionar nu sunt exact la fel cu cuvantul introdus
                if(nr == g) {
                    n = n + 1;
                    //realocarea dinamica a dictionarul
                    c = realloc(c, (n + 1) * sizeof(struct dictionary_entry));
                    //initializarea noului cuvant cu prioritatea 1
                    c[n - 1].priority = 1;
                    //alocarea dinamica a noului cuvant in dictionar
                    c[n - 1].word = calloc((strlen(v[j]) + 1), sizeof(char));
                    //copierea in dictionar noului cuvant
                    strncpy(c[n - 1].word, v[j], strlen(v[j]) - 1);
                    //afisarea cuvantului
                    printf("%s ", c[n - 1].word);
                }
            }
        }
        //cazul cand la finalul cuvantului introdus nu este "*"
        else {
            //cazul cand nu are cuvinte in dictionar care pot fi completarea cuvantului introdus
            if(g == 0) {
                n = n + 1;
                //realocarea dinamica a dictionarului
                c = realloc(c, (n + 1) * sizeof(struct dictionary_entry));
                //initializarea noului cuvant cu prioritatea 1
                c[n - 1].priority = 1;
                //alocarea dinamica a noului cuvant in dictionar
                c[n - 1].word = calloc((strlen(v[j]) + 1), sizeof(char));
                //copierea in dictionar noul cuvant
                strcpy(c[n - 1].word, v[j]);
                //afisarea cuvantului
                printf("%s ", c[n - 1].word);
            }
            //cazul cand are cuvinte in dictionar care pot fi completarea cuvantului introdus
            else {
                //cresterea prioritatii cuvantului din dictionar
                c[gasit[0]].priority++;
                //afisarea cuvantului completat
                printf("%s ", c[gasit[0]].word);
            }
        }
    }
}

int main() {
    struct dictionary_entry *c;
    int n, m, i;
    char s[22];
    char v[5000][22];
    //citirea numarului de cuvinte din dictionar
    scanf("%d", &n);
    getchar();
    //alocarea dinamica a structurii
    c = malloc((n + 1) * sizeof(struct dictionary_entry));
    for(i = 0; i < n; i++) {
        //initializarea tuturor prioritatilor cu 0
        c[i].priority = 0;
        scanf("%s", s);
        //alocarea dinamica a cuvintelor din dictionar
        c[i].word = calloc((strlen(s) + 1), sizeof(char));
        //copierea cuvintele in dictionar
        strcpy(c[i].word, s);
    }
    //citirea numarului de cuvinte introduse
    scanf("%d",&m);
    getchar();
    //citirea cuvintelor introduse
    for(i = 0; i < m; i++) {
        scanf("%s", v[i]);
    }
    //apelarea functiei
    autocompletare(n, m, v, c);

    return 0;
}