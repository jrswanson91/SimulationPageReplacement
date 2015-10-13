#include <stdio.h>
#include <stdlib.h>

int queuecounter = 0;

int pop(int queue[], int start);	
void push(int queue[], int number);

int main(){
	int i, pagefaultlru, oldest, start, temp, k, l, frame, j, random =0;
	int pagefaultopt = 0;
	int max = 5;
	int min = -1;
	int sequence[30]={0};
	int foundflag = 0;
//RANDOM SEQUENCE
	srand(time(NULL));
	for(i = 0; i < 30; i++){
		random = max + rand() / (RAND_MAX / (min - max + 1) + 1);
		sequence[i] = random;
		printf("%d..", sequence[i]);
	}
//FRAME INPUT
	printf("\nFrame Size:");
	scanf("%d", &frame);
	int pages[frame];
	for(i = 0; i < frame; i ++){
		pages[i] = 0;
	}
//LRU
	printf("*******LRU*******\n");
	queuecounter = 0;
	int queue[frame];
	for(i =0; i < frame; i++){
                queue[i] = 0;
        }
//fill first part of pages
	int seqcounter = 0;
	pagefaultlru = 0;
	for(i = 0; i < frame; i ++){
		if(i > 0){
			for(j =0; j < i; j ++){
				if(sequence[seqcounter]== pages[j]){
					printf("page is loaded \n");
					if(queuecounter>0){
						for(k = 0; k < queuecounter; k++){
							if(queue[k] == sequence[seqcounter]){
								start = k;
								pop(queue, start);
								push(queue, sequence[seqcounter]);

							}
						}
					}
					seqcounter++;
				}
			}
		}
		if(i>0){
			foundflag = 0;
			for(j = 0; j < frame; j++){
				if(pages[j] == sequence[seqcounter]){
					foundflag = 1;
					i--;
					printf("page is loaded\n");
					if(queuecounter>0){
						for(k = 0; k < queuecounter; k++){
               	                        		if(queue[k] == sequence[seqcounter]){
								start = k;
                       	        	             		pop(queue, start);
                        	                		push(queue, sequence[seqcounter]);

                                			}
                                		}
					}
				}
			}
		}if(foundflag == 0){
			pages[i] = sequence[seqcounter];
			push(queue, sequence[seqcounter]);
			pagefaultlru++;
			seqcounter++;
			printf("pages: ");
			for(j = 0; j < frame; j++){
				printf("%d ", pages[j]);
			}
			printf("\n");
		}
	}
	int oldestindex = 0;
	while(seqcounter < 30){
		foundflag = 0;
		for(i = 0; i < frame; i ++){
			if(pages[i]==sequence[seqcounter]){
				foundflag = 1;
				printf("page is loaded \n");
				for(j = 0; j < queuecounter; j++){
					if(queue[j]==sequence[seqcounter]){
						start = j;
						pop(queue, start);
						push(queue, sequence[seqcounter]);
					}
				}
			}
		}if(foundflag == 1){
			seqcounter++;
		}else{
			start = 0;
			oldest = pop(queue, start);
			push(queue, sequence[seqcounter]);
			pagefaultlru++;
			for(i = 0; i < frame; i++){
				if(pages[i] == oldest){
					pages[i] = sequence[seqcounter];
					seqcounter++;
				}
			}printf("pages: ");
                        for(j = 0; j < frame; j++){
                                printf("%d ", pages[j]);
                        }
                        printf("\n");
		};
	}
	printf("Number of page faults for LRU is : %d\n", pagefaultlru);
	printf("*******LRU*******\n");
//optimal
	int optfound = 0;
	int optreplacementvalue = 0;
	int optgreatestaway = 0;
	int currentspots;
	int optindex =0;
	printf("\n");
	printf("*******OPTIMAL*******\n");
	for(i = 0; i < frame; i++){
		pages[i] = 0;
	}
	seqcounter = 0;
        pagefaultopt = 0;
	foundflag = 0;
        for(i = 0; i < frame; i ++){
		 if(i>0){
                        for(j = 0; j < frame; j++){
                                if(pages[j] == sequence[seqcounter]){
                                        printf("page is loaded\n");
                                        seqcounter++;
                                }     
                        }
                }if(i>0){
                        foundflag = 0;
                        for(j = 0; j < frame; j++){
                                if(pages[j] == sequence[seqcounter]){
                                        foundflag = 1;
					i--;
                                        printf("page is loaded\n");
					seqcounter++;
                                }     
                        }
                }if(foundflag == 0){
                        pages[i] = sequence[seqcounter];
                        pagefaultopt++;
                        seqcounter++;
                        printf("pages: ");
                        for(j = 0; j < frame; j++){
                                printf("%d ", pages[j]);                  
                        }
                        printf("\n");
                }
        }
	while(seqcounter < 30){
		foundflag = 0;
                for(i = 0; i < frame; i ++){
                        if(pages[i]==sequence[seqcounter]){
                                foundflag = 1;
                                printf("page is loaded \n");
                        }      
                }if(foundflag == 1){
                        seqcounter++;         
                }else{   
                        pagefaultopt++;
			//optimize!
			for(j = 0; j < frame; j++){
				k = seqcounter;
				int steps = 0; 
				while(optfound == 0){
					if(pages[j] == sequence[k]){
						optfound = 1;
						if(steps > optgreatestaway){
							optgreatestaway = steps;
							optreplacementvalue = pages[j];
							optindex = j;
						}
					}
					steps++;
					k++;
				};
                        }
			pages[optindex] = sequence[seqcounter];
			seqcounter++;
			printf("pages: ");
			for(j = 0; j < frame; j++){
                                printf("%d ", pages[j]);
                        }
                        printf("\n");
		}		
	};
	printf("Number of page faults for OPTIMAL is : %d\n", pagefaultopt);
	printf("*******OPTIMAL*******\n");
	int difference = pagefaultlru - pagefaultopt; 
	printf("\n");
	printf("Optimal was better by: %d pagefault(s)\n", difference);
	printf("\n");
	return 0;
}

int pop(int queue[], int start){
	int revalue = queue[0];
	int g;
	for(g=start; g < queuecounter+1; g++){
		queue[g] = queue[g+1];
	}
	queue[queuecounter] = 0;
	queuecounter--;
	return revalue;
}

void push(int queue[], int number){
	if(queuecounter == 0){
		queue[0] = number;
		queuecounter++;
	}else{
		queue[queuecounter] = number;
		queuecounter++;
	}
}
