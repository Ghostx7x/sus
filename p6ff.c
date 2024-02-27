#include<stdio.h>
#define MAX 25

int main(void) {
    int frag[MAX], b[MAX], f[MAX], bf[MAX], ff[MAX];
    int i, j, nb, nf, temp;
    
    printf("\nMemory Management Scheme - First Fit\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &nb);
    printf("Enter the number of files: ");
    scanf("%d", &nf);
    
    printf("\nEnter the size of the blocks:\n");
    for(i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &b[i]);
        bf[i] = 0; // Initialize block flags
    }

    printf("Enter the size of the files:\n");
    for(i = 0; i < nf; i++) {
        printf("File %d: ", i + 1);
        scanf("%d", &f[i]);
    }

    for(i = 0; i < nf; i++) {
        for(j = 0; j < nb; j++) {
            if(bf[j] == 0 && b[j] >= f[i]) {
                ff[i] = j;
                bf[j] = 1;
                frag[i] = b[j] - f[i];
                break;
            }
        }
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragmentation\n");
    for(i = 0; i < nf; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, f[i], ff[i] + 1, b[ff[i]], frag[i]);
}