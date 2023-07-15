#include <stdio.h>
#include <ctype.h>
#define MAXMOVES 480

struct board 
{
	int row; // Y axis
	char col; // X axis
	char piece;
	char type; 
};

struct coord
{
	int c_row;
	char c_col;
};

struct verisin
{
	int yaxis;
	int xaxis;
};

void clear_input(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int castling = 0;
int checkeroo = 0;

int Wleftrook = 0;
int Wrightrook=  0;
int Wking = 0;

int Bleftrook = 0;
int Brightrook=  0;
int Bking = 0;


void showBoard(struct board brd[8][8])
{
	for(size_t rowi = 0; rowi < 9; rowi++) // iterates row
	{
		for(size_t coli = 0; coli < 9; coli++) // iterates collumn
		{
			
			if(rowi == 8)
			{

				if(coli == 0)
				{
					printf("   ");
				}
				else
				{
					printf("%c   ", brd[1][coli - 1].col);
				}				
			}
			else if(coli == 0)
			{
				printf("%i  ", brd[rowi][1].row);
			}
			else
			{
				printf("%c%c  ", brd[rowi][coli - 1].type, brd[rowi][coli - 1].piece);
			}
		}	
		printf("\n");
	}	
}

void createBd(struct board brd[8][8])
{		
	for(int rowi = 0; rowi < 2; rowi++)
	{
		for(int coli = 0; coli < 8; coli++)
		{
			brd[rowi][coli].row = 8 - rowi;
			brd[rowi][coli].col = 'A' + coli;
			brd[rowi][coli].type = 'B';
			
			if(rowi == 1)
			{
				brd[rowi][coli].piece = 'P';
			}
			else
			{
				brd[rowi][0].piece = 'R';
				brd[rowi][1].piece = 'H';
				brd[rowi][2].piece = 'B';
				brd[rowi][3].piece = 'Q';
				brd[rowi][4].piece = 'K';
				brd[rowi][5].piece = 'B';
				brd[rowi][6].piece = 'H';
				brd[rowi][7].piece = 'R';
			}			
		}
	}
	
	// ROW 6-3 //
	for(int rowi = 2; rowi < 7; rowi++)
	{
		for(int coli = 0; coli < 8; coli++)
		{
			brd[rowi][coli].row = 8 - rowi;
			brd[rowi][coli].col = coli + 'A';
			brd[rowi][coli].piece = 'S';
			brd[rowi][coli].type = 'S';		
		}	
	}
	
	for(int rowi = 6; rowi < 8; rowi++)
	{
		for(int coli = 0; coli < 8; coli++)
		{
			brd[rowi][coli].row = 8 - rowi;
			brd[rowi][coli].col = 'A' + coli;
			brd[rowi][coli].type = 'W';
			
			if(rowi == 6)
			{
				brd[rowi][coli].piece = 'P';
			}
			else
			{
				brd[rowi][0].piece = 'R';
				brd[rowi][1].piece = 'H';
				brd[rowi][2].piece = 'B';
				brd[rowi][3].piece = 'Q';
				brd[rowi][4].piece = 'K';
				brd[rowi][5].piece = 'B';
				brd[rowi][6].piece = 'H';
				brd[rowi][7].piece = 'R';
			}
			
			
		}
	}
}

int Wpawn(struct board brd[8][8], struct coord* cone, struct verisin* genMove )//works
{
	int count = 0;
	if((brd[(*cone).c_row - 1][((*cone).c_col - 'a') + 1].type) == 'B') // attack right indexes -->[(*cone).c_row - 1][((*cone).c_col - 'a') + 1]
	{
		genMove[count].yaxis = (*cone).c_row - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count += 1;
	}
	
	if((brd[(*cone).c_row - 1][((*cone).c_col - 'a') - 1].type) == 'B') // attack left
	{
		genMove[count].yaxis = (*cone).c_row - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count += 1;
	}
	
	if(brd[(*cone).c_row - 1][(*cone).c_col - 'a'].type == 'S') // move forward 1
	{
		genMove[count].yaxis = (*cone).c_row - 1;
		genMove[count].xaxis = (*cone).c_col - 'a';
		count += 1;
		
		if(brd[(*cone).c_row - 2][((*cone).c_col - 'a')].type == 'S') // move forward 2
		{
			genMove[count].yaxis = (*cone).c_row - 2;
			genMove[count].xaxis = (*cone).c_col - 'a';
			count += 1;
		}
	}
	return count;
}

int Bpawn(struct board brd[8][8], struct coord* cone, struct verisin* genMove)// prob works
{
	// HERE
	int count = 0;
	
	if((brd[(*cone).c_row + 1][((*cone).c_col - 'a') + 1].type) == 'B') // attack right indexes -->[(*cone).c_row - 1][((*cone).c_col - 'a') + 1]
	{
		genMove[count].yaxis = (*cone).c_row + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count += 1;
	}
	
	if((brd[(*cone).c_row + 1][((*cone).c_col - 'a') - 1].type) == 'B') // attack left
	{
		genMove[count].yaxis = (*cone).c_row + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count += 1;
	}
	
	if(brd[(*cone).c_row + 1][(*cone).c_col - 'a'].type == 'S') // move forward 1
	{
		genMove[count].yaxis = (*cone).c_row + 1;
		genMove[count].xaxis = (*cone).c_col - 'a';	
		count += 1;
		
		if(brd[(*cone).c_row + 2][((*cone).c_col - 'a')].type == 'S') // move forward 2
		{
			genMove[count].yaxis = (*cone).c_row + 2;
			genMove[count].xaxis = (*cone).c_col - 'a';
			count += 1;
		}
	}
	return count;
}

int rook(struct board brd[8][8], struct coord* cone, struct verisin* genMove)//works
{
	int count = 0;
	for(int i = 1; ((*cone).c_row) + i < 8; i++)
	{
		if(brd [((*cone).c_row) + i] [((*cone).c_col - 'a')] .type == 'S') // generate bottem moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;	
		}
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a')].type == 'B') //ATTACK BOTTEM
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_row) - i >= 0 ; i++) // switch i = 0 to i = 1
	{
		if(brd[((*cone).c_row) - i][((*cone).c_col - 'a')].type == 'S') // generate top moves
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
		}
		else if(brd[((*cone).c_row) - i][((*cone).c_col - 'a')].type == 'B') // attack top 
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') + i < 8; i++)
	{
		if(brd[((*cone).c_row)][((*cone).c_col - 'a') + i].type == 'S') // generate right moves
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a' + i);
			count++;
		}
		else if(brd[((*cone).c_row)][((*cone).c_col - 'a') + i].type == 'B') // attack right
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a' + i);
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row)][((*cone).c_col - 'a') - i].type == 'S') // generate left moves
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
		}
		else if(brd[((*cone).c_row)][((*cone).c_col - 'a') - i].type == 'B') // attack left
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
			break;
		}
		else
		{
			break;
		}
	}	
	return count;
}

int bishop(struct board brd[8][8], struct coord* cone, struct verisin* genMove)//works
{
	int count = 0;
	for(int i = 1; ((*cone).c_row) + i < 8 && ((*cone).c_col - 'a') + i < 8; i++)
	{	
		if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') + i].type == 'S') // generate bottem-right moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			
		}
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') + i].type == 'B') // attack bottem-right
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			break;	
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') + i < 8 && ((*cone).c_row) - i >= 0; i++)
	{
		if(brd[((*cone).c_row) - i][((*cone).c_col - 'a') + i].type == 'S') // generate top-right moves
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
		}
		else if(brd[((*cone).c_row) - i][((*cone).c_col - 'a') + i].type == 'B') // attack top-right 
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			break;
		}
		else
		{
			break;
		}	
	}
	
	for(int i = 1; ((*cone).c_row) + i < 8 && ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') - i].type == 'S') // generate top-left moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;		
			count++;	
		} 
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') - i].type == 'B') // attack top-left
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			break;
		}
		else
		{
			break;
		}	
		
	}
	
	for(int i = 0; ((*cone).c_row)- i >= 0 && ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row)- i][((*cone).c_col - 'a') - i].type == 'S') // generate bottem-left moves
		{
			genMove[count].yaxis = ((*cone).c_row)- i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
		}		
		else if(brd[((*cone).c_row)- i][((*cone).c_col - 'a') - i].type == 'B') // attack bottem-left
		{
			genMove[count].yaxis = ((*cone).c_row)- i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
			break;
		}
		else
		{
			break;
		}	
		
	}
	return count;
}

int knight(struct board brd[8][8], struct coord* cone, struct verisin* genMove)// prob works
{
	int count = 0;
	
	if((brd[(*cone).c_row + 2][((*cone).c_col - 'a') + 1].type == 'B' ||
   	   brd[(*cone).c_row + 2][((*cone).c_col - 'a') + 1].type == 'S') &&
	   ((*cone).c_row + 2 < 8 && ((*cone).c_col - 'a') + 1 < 8))						// 2 down 1 right
	{
		genMove[count].yaxis = (*cone).c_row + 2;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
	}
	
	if((brd[(*cone).c_row + 2][((*cone).c_col - 'a') - 1].type == 'B' ||
   	   brd[(*cone).c_row + 2][((*cone).c_col - 'a') - 1].type == 'S') &&
	   (*cone).c_row + 2 < 8 && ((*cone).c_col - 'a') - 1 >= 0)				// 2 down 1 left
	{
		genMove[count].yaxis = (*cone).c_row + 2;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count++;
	}
	
	if((brd[(*cone).c_row + 1][((*cone).c_col - 'a') - 2].type == 'B' ||
   	   brd[(*cone).c_row + 1][((*cone).c_col - 'a') - 2].type == 'S') &&
	   (*cone).c_row + 1 < 8 && ((*cone).c_col - 'a') - 2 >= 0)				// 2 left 1 down
	{
		genMove[count].yaxis = (*cone).c_row + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 2;
		count++;
	}
	
	if((brd[(*cone).c_row - 1][((*cone).c_col - 'a') - 2].type == 'B' ||
   	   brd[(*cone).c_row - 1][((*cone).c_col - 'a') - 2].type == 'S') &&
	   (*cone).c_row - 1 >= 0 && ((*cone).c_col - 'a') - 2 >= 0)				// 2 left 1 up
	{
		genMove[count].yaxis = (*cone).c_row - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 2;
		count++;
	}
	
	if((brd[(*cone).c_row - 2][((*cone).c_col - 'a') - 1].type == 'B' ||
   	   brd[(*cone).c_row - 2][((*cone).c_col - 'a') - 1].type == 'S') &&
	   (*cone).c_row - 2 >= 0 && ((*cone).c_col - 'a') - 1 >= 0)				// 2 up 1 left
	{
		genMove[count].yaxis = (*cone).c_row - 2;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count++;
	}	
	
	if((brd[(*cone).c_row - 2][((*cone).c_col - 'a') + 1].type == 'B' ||
   	   brd[(*cone).c_row - 2][((*cone).c_col - 'a') + 1].type == 'S') &&
	   (*cone).c_row - 2 >= 0 && ((*cone).c_col - 'a') + 1 < 8)			// 2 up 1 right
	{
		genMove[count].yaxis = (*cone).c_row - 2;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
	}
	
	if((brd[(*cone).c_row - 1][((*cone).c_col - 'a') + 2].type == 'B' ||
   	   brd[(*cone).c_row - 1][((*cone).c_col - 'a') + 2].type == 'S') &&
	   (*cone).c_row - 1 >= 0 && ((*cone).c_col - 'a') + 2 < 8)	// 2 right 1 up
	{
		genMove[count].yaxis = (*cone).c_row - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 2;
		count++;
	}
	
	if((brd[(*cone).c_row + 1][((*cone).c_col - 'a') + 2].type == 'B' ||
   	   brd[(*cone).c_row + 1][((*cone).c_col - 'a') + 2].type == 'S') &&
	   (*cone).c_row + 1 < 8 && ((*cone).c_col - 'a') + 2 < 8)	// 2 right 1 down
	{
		genMove[count].yaxis = (*cone).c_row + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 2;
		count++;
	}
	return count;
}

int queen(struct board brd[8][8], struct coord* cone, struct verisin* genMove)//updated
{
	int count = 0;
	for(int i = 1; ((*cone).c_row) + i < 8; i++)
	{
		if(brd [((*cone).c_row) + i] [((*cone).c_col - 'a')] .type == 'S') // generate bottem moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;	
		}
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a')].type == 'B') //ATTACK BOTTEM
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_row) - i >= 0 ; i++) // switch i = 0 to i = 1
	{
		if(brd[((*cone).c_row) - i][((*cone).c_col - 'a')].type == 'S') // generate top moves
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
		}
		else if(brd[((*cone).c_row) - i][((*cone).c_col - 'a')].type == 'B') // attack top 
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a');
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') + i < 8; i++)
	{
		if(brd[((*cone).c_row)][((*cone).c_col - 'a') + i].type == 'S') // generate right moves
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a' + i);
			count++;
		}
		else if(brd[((*cone).c_row)][((*cone).c_col - 'a') + i].type == 'B') // attack right
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a' + i);
			count++;
			break;
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row)][((*cone).c_col - 'a') - i].type == 'S') // generate left moves
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
		}
		else if(brd[((*cone).c_row)][((*cone).c_col - 'a') - i].type == 'B') // attack left
		{
			genMove[count].yaxis = ((*cone).c_row);
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
			break;
		}
		else
		{
			break;
		}
	}

	for(int i = 1; ((*cone).c_row) + i < 8 && ((*cone).c_col - 'a') + i < 8; i++)
	{	
		if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') + i].type == 'S') // generate bottem-right moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			
		}
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') + i].type == 'B') // attack bottem-right
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			break;	
		}
		else
		{
			break;
		}
	}
	
	for(int i = 1; ((*cone).c_col - 'a') + i < 8 && ((*cone).c_row) - i >= 0; i++)
	{
		if(brd[((*cone).c_row) - i][((*cone).c_col - 'a') + i].type == 'S') // generate top-right moves
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
		}
		else if(brd[((*cone).c_row) - i][((*cone).c_col - 'a') + i].type == 'B') // attack top-right 
		{
			genMove[count].yaxis = ((*cone).c_row) - i;
			genMove[count].xaxis = ((*cone).c_col - 'a') + i;
			count++;
			break;
		}
		else
		{
			break;
		}	
	}
	
	for(int i = 1; ((*cone).c_row) + i < 8 && ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') - i].type == 'S') // generate top-left moves
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;	
			count++;	
		} 
		else if(brd[((*cone).c_row) + i][((*cone).c_col - 'a') - i].type == 'B') // attack top-left
		{
			genMove[count].yaxis = ((*cone).c_row) + i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			break;
		}
		else
		{
			break;
		}	
		
	}
	
	for(int i = 1; ((*cone).c_row)- i >= 0 && ((*cone).c_col - 'a') - i >= 0; i++)
	{
		if(brd[((*cone).c_row)- i][((*cone).c_col - 'a') - i].type == 'S') // generate bottem-left moves
		{
			genMove[count].yaxis = ((*cone).c_row)- i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
		}		
		else if(brd[((*cone).c_row)- i][((*cone).c_col - 'a') - i].type == 'B') // attack bottem-left
		{
			genMove[count].yaxis = ((*cone).c_row)- i;
			genMove[count].xaxis = ((*cone).c_col - 'a') - i;
			count++;
			break;
		}
		else
		{
			break;
		}	
		
	}
	return count;
}

int king(struct board brd[8][8], struct coord* cone, struct verisin* genMove)// prob works
{
	int count = 0;
	if(brd [((*cone).c_row) + 1] [((*cone).c_col - 'a')] .type == 'S') // generate bottem moves
	{
		genMove[count].yaxis = ((*cone).c_row) + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a');
		count++;	
	}
	else if(brd[((*cone).c_row) + 1][((*cone).c_col - 'a')].type == 'B') //ATTACK BOTTEM
	{
		genMove[count].yaxis = ((*cone).c_row) + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a');
		count++;
	}

	if(brd[((*cone).c_row) - 1][((*cone).c_col - 'a')].type == 'S') // generate top moves
	{
		genMove[count].yaxis = ((*cone).c_row) - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a');
		count++;
	}
	else if(brd[((*cone).c_row) - 1][((*cone).c_col - 'a')].type == 'B') // attack top 
	{
		genMove[count].yaxis = ((*cone).c_row) - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a');
		count++;
	}

	if(brd[((*cone).c_row)][((*cone).c_col - 'a') + 1].type == 'S') // generate right moves
	{
		genMove[count].yaxis = ((*cone).c_row);
		genMove[count].xaxis = ((*cone).c_col - 'a' + 1);
		count++;
	}
	else if(brd[((*cone).c_row)][((*cone).c_col - 'a') + 1].type == 'B') // attack right
	{
		genMove[count].yaxis = ((*cone).c_row);
		genMove[count].xaxis = ((*cone).c_col - 'a' + 1);
		count++;
	}

	if(brd[((*cone).c_row)][((*cone).c_col - 'a') - 1].type == 'S') // generate left moves
	{
		genMove[count].yaxis = ((*cone).c_row);
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count++;
	}
	else if(brd[((*cone).c_row)][((*cone).c_col - 'a') - 1].type == 'B') // attack left
	{
		genMove[count].yaxis = ((*cone).c_row);
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;
		count++;
	}

	if(brd[((*cone).c_row) + 1][((*cone).c_col - 'a') + 1].type == 'S') // generate bottem-right moves
	{
		genMove[count].yaxis = ((*cone).c_row) + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
		
	}
	else if(brd[((*cone).c_row) + 1][((*cone).c_col - 'a') + 1].type == 'B') // attack bottem-right
	{
		genMove[count].yaxis = ((*cone).c_row) + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
	}

	if(brd[((*cone).c_row) - 1][((*cone).c_col - 'a') + 1].type == 'S') // generate top-right moves
	{
		genMove[count].yaxis = ((*cone).c_row) - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
	}
	else if(brd[((*cone).c_row) - 1][((*cone).c_col - 'a') + 1].type == 'B') // attack top-right 
	{
		genMove[count].yaxis = ((*cone).c_row) - 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') + 1;
		count++;
	}

	if(brd[((*cone).c_row) + 1][((*cone).c_col - 'a') - 1].type == 'S') // generate top-left moves
	{
		genMove[count].yaxis = ((*cone).c_row) + 1;
		genMove[count].xaxis = ((*cone).c_col - 'a') - 1;	
		count++;	
	} 
	else if(brd[(cone->c_row) + 1][(cone->c_col - 'a') - 1].type == 'B') // attack top-left
	{
		genMove[count].yaxis = (cone->c_row) + 1;
		genMove[count].xaxis = (cone->c_col - 'a') - 1;
	}

	if(brd[((*cone).c_row)- 1][(cone->c_col - 'a') - 1].type == 'S') // generate bottem-left moves
	{
		genMove[count].yaxis = (cone->c_row)- 1;
		genMove[count].xaxis = (cone->c_col - 'a') - 1;
		count++;
	}		
	else if(brd[((*cone).c_row)- 1][((*cone).c_col - 'a') - 1].type == 'B') // attack bottem-left
	{
		genMove[count].yaxis = (cone->c_row)- 1;
		genMove[count].xaxis = (cone->c_col - 'a') - 1;
		count++;
	}
	
	for(int i = 1; i < 4; i++) //left rook
	{	
		if(brd[cone->c_row][(cone->c_col - 'a') - i].type == 'S' && brd[cone->c_row][(cone->c_col - 'a')].piece == 'K')    
		{
			if(brd[cone->c_row][(cone->c_col - 'a') - 4].piece == 'R' &&
			   brd[cone->c_row][(cone->c_col - 'a') - 4].type == brd[(cone->c_row)][(cone->c_col - 'a')].type  && i == 3)
			{
				
				genMove[count].yaxis = ((*cone).c_row);
				genMove[count].xaxis = ((*cone).c_col - 'a')- 4;
				count++;
				puts("HiLRook");
				castling = 1;
			}
			
		}
	}
	for(int i = 1; i < 3; i++) // right rook
	{	
		if(brd[cone->c_row][(cone->c_col - 'a') + i].type == 'S' && brd[cone->c_row][(cone->c_col - 'a')].piece == 'K' )   
		{
			if(brd[cone->c_row][(cone->c_col - 'a') + 3].piece == 'R' &&
			   brd[cone->c_row][(cone->c_col - 'a') + 3].type == brd[(cone->c_row)][(cone->c_col - 'a')].type && i == 2)
			{
				
				genMove[count].yaxis = ((*cone).c_row);
				genMove[count].xaxis = ((*cone).c_col - 'a') + 3;
				count++;
				puts("HiRightRook");
				castling = 1;
			}
			
		}
	}
	
	return count;
}

void finput(int* bowtn, struct coord* cone, struct board brd[8][8], struct verisin genMove[30])
{
	if(checkeroo == 1)
	{
		puts("You are in check");
	}
	
	int reboot = 1;	
	// CHANGE ALL DIS SHIT 
	if(*bowtn == 1) //WHITE
	{	
		for(;reboot == 1;)
		{
			puts("White Player's turn\n"
				 "First Coordinate: ");
				 
			// PUT THE DO HERE FOR BOUNDS CHECKING
			scanf("%c%i", &cone->c_col, &cone->c_row);
			clear_input();
			(*cone).c_col = tolower((*cone).c_col);
			
			if(brd[ 8 - (*cone).c_row ][ (*cone).c_col - 'a' ].type != 'W')
			{
				puts("Not a valid piece choice!");			
				reboot = 1;
			}
			else
			{
				(*cone).c_row = 8 - (*cone).c_row;
				reboot = 0;
			}
		}
	}
	
	else if(*bowtn == 0) //Black
	{
		for(;reboot == 1;)
		{
			puts("Black Player's turn\n"
				 "First Coordinate: ");
				 
			scanf("%c%i", &cone->c_col, &cone->c_row);
			clear_input();
			(*cone).c_col = tolower((*cone).c_col);					
			
			if(brd[ 8 - (*cone).c_row ][ (*cone).c_col - 'a' ].type != 'B')
			{
				puts("Not a valid piece choice!");				
				reboot = 1;
			}
			else
			{
				(*cone).c_row = 8 - (*cone).c_row;
				reboot = 0;
			}
		}
	}
	
	if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'P' && *bowtn == 1)
	{
		Wpawn(brd, cone, genMove); //Wpawn
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'P' && *bowtn == 0)
	{
		Bpawn(brd, cone, genMove);
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'R') // rook
	{
		rook(brd, cone, genMove);
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'B') // bishop
	{
		bishop(brd, cone, genMove);
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'H') // knight
	{
		knight(brd, cone, genMove);
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'Q') // queen
	{
		queen(brd, cone, genMove);
	}
	else if(brd[(*cone).c_row][(*cone).c_col - 'a'].piece == 'K') // king
	{
		king(brd, cone, genMove);
	}
	
}

int sinput(struct coord* sone, struct board brd[8][8], struct verisin genMove[30], struct coord* cone)
{
	int count = 0; // for incorrect input
	
	puts("Second Coordinate: ");
	scanf("%c%i", &sone->c_col, &sone->c_row);
	clear_input();
	
	sone->c_col = tolower(sone->c_col);
	sone->c_row = 8 - sone->c_row;
	
	
	char promote = 'N';
	for(size_t i = 0; i < 31; i++) // checks user input against genmove
	{
		
		if(sone->c_row == genMove[i].yaxis && sone->c_col == genMove[i].xaxis + 'a')
		{
			if(brd[cone->c_row][cone->c_col - 'a'].type == 'W' && brd[cone->c_row][cone->c_col - 'a'].piece == 'K') // Check movement on Castable Pieces
			{
				Wking++;
			}
			else if(brd[cone->c_row][cone->c_col - 'a'].type == 'B' && brd[cone->c_row][cone->c_col - 'a'].piece == 'K')
			{
				Bking++;
			}
			
			if(brd[cone->c_row][cone->c_col - 'a'].type == 'W' && 
			   brd[cone->c_row][cone->c_col - 'a'].piece == 'R')
			{
				if(brd[cone->c_row][(cone->c_col - 'a')].col == 'H')
				{
					Wrightrook++;
				}
				else if(brd[cone->c_row][(cone->c_col - 'a') - 4].col == 'A')
				{
					Wleftrook++;
				}
			}
			else if(brd[cone->c_row][cone->c_col - 'a'].type == 'B' && 
					brd[cone->c_row][cone->c_col - 'a'].piece == 'R')
			{
				if(brd[cone->c_row][(cone->c_col - 'a')].col == 'H')
				{
					Brightrook++;
				}
				else if(brd[cone->c_row][(cone->c_col - 'a') - 4].col == 'A')
				{
					Bleftrook++;
				}
			}																										// Check movement on Castable Pieces is done
			
			struct board temp = {0};	
			do // piece promotion bounds check
			{		
				if(brd[genMove[i].yaxis][genMove[i].xaxis].piece == 'P' && brd[genMove[i].yaxis][genMove[i].xaxis].type == 'W' && genMove[i].yaxis == 0)//White
				{
					puts("What piece would you like?\n"
						 "(R)ook\t(H)orse\t(Q)ueen\t(B)ishop");
						 
					scanf("%c", &promote);
					clear_input();
					promote = toupper(promote);
					if(promote != 'Q' && promote != 'R' && promote != 'H' && promote != 'B' && promote != 'N')
					{
						puts("Invalid Input");
					}
					
				}
				else if(brd[genMove[i].yaxis][genMove[i].xaxis].piece == 'P' &&  brd[genMove[i].yaxis][genMove[i].xaxis].type == 'B' && genMove[i].yaxis == 7)
				{
					puts("What piece would you like?\n"
						 "(R)ook\t(H)orse\t(Q)ueen\t(B)ishop");
						 
					scanf("%c", &promote);
					clear_input();
					promote = toupper(promote);
					if(promote != 'Q' && promote != 'R' && promote != 'H' && promote != 'B' && promote != 'N')
					{
						puts("Invalid Input");
					}
				}
				
			} while(promote != 'Q' && promote != 'R' && promote != 'H' && promote != 'B' && promote != 'N');
			
				if(promote == 'N') 
				{
					temp.piece = brd[cone->c_row][cone->c_col - 'a'].piece; // stores first coordinate piece and type
					temp.type = brd[cone->c_row][cone->c_col - 'a'].type;
				}
				else if(promote != 'N')
				{
					temp.piece = promote;
					temp.type = brd[cone->c_row][cone->c_col - 'a'].type;
					
				}
				
				if(castling == 0)
				{
					brd[cone->c_row][cone->c_col - 'a'].piece = 'S';  //set them to Space Space
					brd[cone->c_row][cone->c_col - 'a'].type = 'S';
				}
				else if(castling == 1 && checkeroo == 0) // castling is equaling 0 fix
				{				
					if(brd[cone->c_row][cone->c_col - 'a'].type == 'W' && Wking == 0)
					{
						if(brd[sone->c_row][sone->c_col - 'a'].col == 'A' && Wleftrook == 0)
						{
							puts("Hi");
							brd[cone->c_row][cone->c_col - 'a'].type = 'W';
						}
						else if(brd[sone->c_row][sone->c_col - 'a'].col == 'H' && Wrightrook == 0)
						{
							puts("Hi2");
							brd[cone->c_row][cone->c_col - 'a'].type = 'W';
						}
					}
					else if(brd[cone->c_row][cone->c_col - 'a'].type == 'B' && Bking == 0)
					{
						if(brd[sone->c_row][sone->c_col - 'a'].col == 'A' && Bleftrook == 0)
						{
							puts("Hi3");
							brd[cone->c_row][cone->c_col - 'a'].type = 'B';
						}
						else if(brd[sone->c_row][sone->c_col - 'a'].col == 'H' && Brightrook == 0)
						{
							puts("Hi4");
							brd[cone->c_row][cone->c_col - 'a'].type = 'B';
						}
					}
					
					brd[cone->c_row][cone->c_col - 'a'].piece = 'R'; 
					castling -= 1;
				}
				
				brd[sone->c_row][sone->c_col - 'a'].piece = temp.piece; // Uses the temp to set new value
				brd[sone->c_row][sone->c_col - 'a'].type = temp.type;
				
				return 0;
		}
		else if(count == 30)//incorrect
		{
			puts("invalid input");
			break;
		}
		else//checks for failure
		{
			count++;
		}
	}
	
	return 1;
}

int checkMate(struct board brd[8][8], int* bowtn)
{
	int atk = 0;
	struct verisin genThreat[MAXMOVES] = {0};
	struct coord cone[16];
	
	for(int i = 0; i < 8; i++) //determining enemies
	{
		for(int j = 0; j < 8; j++)
		{
			if ((brd[i][j].type == 'B' && *bowtn == 0) || ((brd[i][j].type) == 'W' && *bowtn == 1)) //white = 0 black = 1
			{
				cone[atk].c_row = i;
				cone[atk].c_col = j + 'a';
				atk++;
				//printf("row: %i col: %c\n", i,  j + 'a');
			}
		}
	}
	
	puts("");
	int offset = 0;
	
	for(size_t i = 0; i < 16; i++)
	{
		
		if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'P' && *bowtn == 1) //switched
		{
			offset += Wpawn(brd, &cone[i], &(genThreat[offset])); //Wpawn
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'P' && *bowtn == 0) //switched
		{
			offset += Bpawn(brd, &cone[i], &(genThreat[offset]));
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'R') // rook
		{
			offset += rook(brd, &cone[i], &(genThreat[offset]));
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'B') // bishop
		{
			offset += bishop(brd, &cone[i], &(genThreat[offset]));
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'H') // knight
		{
			offset += knight(brd, &cone[i], &(genThreat[offset]));
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'Q') // queen
		{
			offset += queen(brd, &cone[i], &(genThreat[offset]));
		}
		else if(brd[cone[i].c_row][cone[i].c_col - 'a'].piece == 'K') // king
		{
			offset += king(brd, &cone[i], &(genThreat[offset]));
		}
	}
	
	for(int i = 0; i < MAXMOVES; i++)
	{
		//printf("%i\n\n", i);
		if(*bowtn == 0 &&
			genThreat[i].yaxis < 8 && genThreat[i].yaxis >= 0 &&
			genThreat[i].xaxis < 8 && genThreat[i].xaxis >= 0)
		{
			if(brd[genThreat[i].yaxis][genThreat[i].xaxis].type == 'W' &&
			   brd[genThreat[i].yaxis][genThreat[i].xaxis].piece == 'K')
			{
				puts("White is in check");
				return 1;
			}
		}
		else if(*bowtn == 1 &&
			genThreat[i].yaxis < 8 && genThreat[i].yaxis >= 0 &&
			genThreat[i].xaxis < 8 && genThreat[i].xaxis >= 0)
		{
			if(brd[genThreat[i].yaxis][genThreat[i].xaxis].type == 'B' &&
			   brd[genThreat[i].yaxis][genThreat[i].xaxis].piece == 'K')
			{
				puts("Black is in check");
				return 1;
			}
		}
	}
	return 0;
}

void saveBoard(struct board brd[8][8], struct board tempbrd[8][8])
{
	for(size_t i = 0; i < 8; i++)
	{
		for(size_t j = 0; j < 8; j++)
		{
			tempbrd[i][j].row = brd[i][j].row;
			tempbrd[i][j].col = brd[i][j].col;
			tempbrd[i][j].type = brd[i][j].type;
			tempbrd[i][j].piece = brd[i][j].piece;			
		}
	}
}

void loadBoard(struct board brd[8][8], struct board tempbrd[8][8])
{
	for(size_t i = 0; i < 8; i++)
	{
		for(size_t j = 0; j < 8; j++)
		{
			brd[i][j].row = tempbrd[i][j].row;
			brd[i][j].col = tempbrd[i][j].col;
			brd[i][j].type = tempbrd[i][j].type;
			brd[i][j].piece = tempbrd[i][j].piece;			
		}
	}
}

int main()
{
	struct board brd[8][8];
	int bowtn = 1; // Black or white turn
	
	int YN;
	do
	{
		puts("Instructions?\n"
			 "(Y)es \t (N)o");
		YN = getchar();
		clear_input();
		YN = tolower(YN);
		if(YN != 'y' && YN != 'n')
		{
			puts("Invalid input!\n");
		}
		if(YN == 'y')
		{
			puts("Find your piece, and enter in its coordinate\n"
				 "The coordinate should be entered in as this: A2\n"
				 "The second coordinate will be the location of where you would like to move that piece\n\n\n\n");
		}
		else if(YN == 'n')
		{
			puts("Alrighty then!\n\n");
		}
		
	} while(YN != 'y' && YN != 'n');
	
    createBd(brd);
	int restart = 0;
	struct coord cone; 
	struct verisin genMove[30];
	struct coord sone;
	struct board tempbrd[8][8];
	do
	{	
		do
		{
			puts("");
			puts("");
			showBoard(brd);	
			printf("\n\n\n");

			
			finput(&bowtn, &cone, brd, genMove); //gets first cordinate
			restart = sinput(&sone, brd, genMove, &cone); //gets second cordinate

			saveBoard(brd, tempbrd);			
			checkeroo = checkMate(brd, &bowtn);
			
			if(checkeroo == 1)
			{
				puts("Check!\tForfeit?\n(Y)es\t(N)o");
				int tiefrof = getchar();
				clear_input();	
				tiefrof = tolower(tiefrof);
				
				if(tiefrof == 'y')
				{
					break;
				}
				else
				{
					if(bowtn == 1) // white
					{
						bowtn -= 1; //black 0
					}
					else if(bowtn == 0) //black
					{
						bowtn += 1;//white 1
					}
					loadBoard(brd, tempbrd);
					showBoard(brd);
				}
				
			}
			/* printf("3rd checkeroo\t %i\n", checkeroo);
			checkeroo = checkMate(brd, &bowtn);
			printf("4th checkeroo\t %i\n", checkeroo); */
			
			//checkeroo = checkMate(brd, &bowtn);
			
		} while(checkeroo == 1 || restart == 1);
		
		if(bowtn == 1) // white
		{
			bowtn -= 1; //black 0
			puts("White to Black");
		}
		else if(bowtn == 0) //black
		{
			bowtn += 1;//white 1
			puts("Black to White");
		}
		
	} while(checkeroo == 0);
	
	if(bowtn == 0) // white
	{
		puts("White Wins");
	}
	else if(bowtn == 1) //black
	{
		puts("Black Wins");
	}

	return 0;
}