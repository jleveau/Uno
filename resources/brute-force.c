#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int max;

struct card {
	int color;
	int number;
	int played;
};

//~ int next_card(int num_card, struct card* cards, int* played_cards, int num_last_played_card, int deck_length){
	//~ if (card_can_be_played(num_card, cards, played_cards[num_last_played_card]){
		//~ num_last_played_card++;
		//~ played_cards[num_last_played_card] = cards[num_card];
		//~ if (num_last_played_card == deck_length){
			//~ return num_last_played_card;
		//~ }
		//~ if (num_last_played_card > max)
			//~ max = num_last_played_card;
		//~ next_card
		//~ cards[num_card].played = 1;
		//~ next_card
	//~ }
//~ }

int can_be_add(struct card curr_card, int* played_cards, int cursor, struct card* cards){
	return cursor == 0 ||  (curr_card.played == 0 && (cards[played_cards[cursor - 1]].number == curr_card.number || cards[played_cards[cursor - 1]].color == curr_card.color));
}

int main (int argc, char **argv){
	FILE * file;
	FILE * output;
    	file = fopen (argv[1], "r");
    	output = fopen(argv[2],"a");
	int n,p,q;
	int i;
	int* played_cards;
	int* max_played_card;
	max = 0;
	
	fscanf(file, "%d %d %d\n", &n,&p,&q);
	played_cards = malloc(n * sizeof(int));
	
	struct card* cards = malloc(n*sizeof(struct card));
	for (i=0; i<n;i++){
		fscanf(file, "%d %d\n", &cards[i].color,&cards[i].number);
		cards[i].played = 0;
	}

	clock_t begin = clock();
	
	int max = 0;
	int* max_played = malloc(n*sizeof(int));
	int cursor = 0;
	int iterator = 0;
	int cond=1;
	while (cond){
		if (iterator < n && can_be_add(cards[iterator], played_cards, cursor, cards)){
			played_cards[cursor] = iterator;
			cards[iterator].played = 1;
			cursor++;
			iterator = 0;
			if (cursor == n){
				max = cursor;
				memcpy(max_played, played_cards, max * sizeof(int));
				cond = 0;
			}
			else if(cursor > max){
				max = cursor;
				memcpy(max_played, played_cards, max * sizeof(int));
			}
		}
		else{
			iterator++;
			if (iterator >= n){
				if(cursor){
					//cards[played_cards[cursor]].played = 0;
					cursor--;
					if (cursor >= 0)
						cards[played_cards[cursor]].played = 0;
					iterator = played_cards[cursor] + 1;
				}
				else{
					cond=0;
				}

			}
		}
		//for(i = 0; i < cursor; i++){
		//	printf("%d, ", played_cards[i]);
		//}
		
	}

	/*
	printf("%d \n",max);
	for(i = 0; i < max; i++){
			printf("%d, ", max_played[i]);
	}*/
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	fprintf(output,"%d %f \n",p,time_spent);
	return 0;
}
