#include "readwrite.h"


Board XMLformating(char* filename)
{
	int width,height,highScores;

  char c, c1, c2, c3, c4, c5, c6, c7, widthTag, heightTag, highscoresTag; //correction TP1
  int start=0, End=0, flag1=0, flag2=0, widthflag=0, heightflag=0, highscoresflag=0;
  FILE *file=NULL;
  file = fopen(filename, "r");
  if(file==NULL){
  	fprintf(stderr,"Impossible d'ouvrir le fichier %s.\n",filename);
  	exit(1);
  }
  fscanf(file,"< Configurations %c", &c);
  if(c=='>'){
  	flag1=1;
  	start=ftell(file);
  }
  else{
  	while(fscanf(file,"%c", &c1)!=EOF){
  		fscanf(file,"< Configurations %c", &c2);
  		if(c2=='>'){
  			flag1=1;
  			start=ftell(file);
  			break;
  		}
  	}
  }
  while(fscanf(file,"%c", &c3)!=EOF){
  	fscanf(file,"< / Configurations %c", &c4);
  	if(c4=='>'){
  		flag2=1;
  		End=ftell(file);
  		break;
  	}
  }
  if(flag1==1 && flag2==1)
  {
  	fseek(file,start,SEEK_SET);
  	while(fscanf(file,"%c", &c5)!=EOF){
  		fscanf(file,"< Width >%d < / Width %c", &width, &widthTag);
  		if( (widthTag=='>') && (width>=4) && ftell(file)<End ) {widthflag=1; break;}
  	}
  	fseek(file,start,SEEK_SET);
  	while(fscanf(file,"%c", &c6)!=EOF){
  		fscanf(file,"< Height >%d < / Height %c", &height, &heightTag);
  		if( (heightTag=='>') && (height>=4) && ftell(file)<End ) {heightflag=1; break;}
  	}
  	fseek(file,start,SEEK_SET);
  	while(fscanf(file,"%c", &c7)!=EOF){
  		fscanf(file,"< Highscores >%d < / Highscores %c", &highscores, &highscoresTag);
  		if( (highscoresTag=='>') && (highscores>=4) && ftell(file)<End ) {highscoresflag=1; break;}
  	}
  }
  if(width==0 || widthflag==0){
  	width=7;
  	printf("Incorrect file format, default value of width (7) is loaded\n");
  }
  if(height==0 || heightflag==0){
  	height=6;
  	printf("Incorrect file format, default value of height (6) is loaded\n");
  }
  if(highscores==0 || highscoresflag==0){
  	highscores=5;
  	printf("Incorrect file format, default value of highscore list (5) is loaded\n");
  }
  fclose(file);
  return board_new(width,height,highscores);
}
void highscore(int high,Board board)
{
	int i=0, n=0, temp;
	int highs=malloc(board.highScores*sizeof(int));
	FILE *highsc = NULL;
	highsc = fopen("highscores.text", "r");
	if(highsc!=NULL){
		fscanf(highsc, "%d", &highs[i]);
		do
		{
			i++;
			if(fscanf(highsc, "%d", &n)!=EOF){highs[i]=n;}
			else {break;}
		}while(i<board.highScores);
		while(board.highScores>i){highs[i]=0;i++;}
		i--;
		if(high>highs[i])
		{
			highs[i] = high;
		}
		while(highs[i]>highs[i-1] && i>0)
		{
			temp = highs[i-1];
			highs[i-1] = highs[i];
			highs[i] = temp;
			i--;
		}
		fclose(highsc);
	}
	highsc = fopen("highscores.text", "w");
	printf("\n\t      High Scores\n\t\t*****");
	for(i=0; i<board.highScores; i++)
	{
		fprintf(highsc,"%d ", highs[i]);
		printf("\n\t\t* %d *", highs[i]);
	}
	printf("\n\t\t*****");
	fclose(highsc);
	free(highs);
}
void saveLoad(int *num, Board board){
	FILE *pfile;
	int r, t;
	pfile = NULL;
	if(*num == -2){
		printf("Game Saved Successfully");
		pfile = fopen("save.txt", "w");
		for(r=board.height-1;r>=0;r--){
			for(t=board.width-1;t>=0;t--){
				fprintf(pfile, "%c", board.tab[r][t]);
			}
		}
		fclose(pfile);
	}
	if(*num == -1){
		pfile = fopen("save.txt", "r");
		if(pfile==NULL){
			fprintf(stderr,"Pas de fichier de sauvegarde.\n");
			return;
		}
		for(r=board.height-1;r>=0;r--){
			for(t=board.width-1;t>=0;t--){
				fscanf(pfile, "%c", &(board.tab[r][t]));
			}
		}
		fclose(pfile);
		print(board);
	}
}