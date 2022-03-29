
/*
Name: Abhiraj Mengade
Roll no: 201CS102
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j, num_blocks, num_process, temp, top = 0;
    int frag[10], size[10], process[10];
    static int block_arr[10], file_arr[10];
    
    printf("Enter the Total Number of Blocks: ");
    scanf("%d", &num_blocks);

    printf("Enter the Total Number of process: ");
    scanf("%d", &num_process);

    printf("\nEnter the Size of the Blocks: \n");
    for(i = 0; i < num_blocks; i++){
        printf("Block No.%d: ", i + 1);
        scanf("%d", &size[i]);
    }

    printf("Enter the Size of the process:\n");
    for(i = 0; i < num_process; i++){
        printf("Process No.%d: ", i + 1);
        scanf("%d", &process[i]);
    }

    for(i = 0; i < num_process; i++){
        for(j = 0; j < num_blocks; j++){
            if(block_arr[j] != 1){
                temp = size[j] - process[i];
                if(temp >= 0){
                    if(top < temp){
                        file_arr[i] = j;
                        top = temp;
                    }
                }
            }
        }

        frag[i] = top;
        block_arr[file_arr[i]] = 1;
        top = 0;
    }

    printf("\nFile Number\tFile Size\tBlock Number\tBlock Size\tFragment");
    for(i = 0; i < num_process; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, process[i], file_arr[i], size[file_arr[i]], frag[i]);
    }

    printf("\n");
    return 0;
}
