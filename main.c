#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

struct list
{
	double columnIP;
	double columnDB;
};

double avgbrCounting(double **matrix1 ,int x);

void printavgbr(void);

void avbgrper5min(double **matrix1, double avgbr[],int x);

void printpayloadsizepercentage(double **matrix1,int x);

void IPcorrespondvolume(double **matrix1, int x );

void bubblesort(int x ,list *array);




int main ()
{
	//put data into array
	FILE *fp1;
	fp1 = fopen("dec-pkt-1.txt","r");
    int x = 0; //row size
    int i,j;
    double h;
    double avgbr[12] = {0};
	//checking the file is ready or not
	if(fp1==NULL)
	{
		printf ("cannot find the file... \n");
		exit(1);
	}
	while(!feof(fp1))
	{
		//printf("%d",x);
		fscanf (fp1, "%lf", &h);
		x++;
		/*if (x == 4){
         printf("%f",h);
         break;
         }
         //printf("%d",x);
         //if (feof(fp1))
         //	break;*/
	}
	x = x/6;
	//printf("%d",x);
	fclose(fp1);
	
	
	FILE *fp;
	fp = fopen("dec-pkt-1.txt","r");
	if(fp==NULL)
	{
		printf ("cannot find the file... \n");
		exit(1);
	}
    
	double **matrix1;
	matrix1 = (double **)malloc(sizeof(double*)*x);
	for (i = 0; i < x; i++)
		matrix1[i] = (double*)malloc(sizeof(double)*6);
	
	
	for (i = 0; i < x; i++)
    {for (j = 0; j < 6; j++)
    {
        fscanf(fp, "%lf",&matrix1[i][j]);
    }
    }
	/*checking the data can be exactly loaded
     //int temp;
     for (i = 0; i < x; i++)
     {for (j = 0; j < 6; j++)
     if (j == 0)
     printf("%f\t",matrix1[i][j]);
     else if (j > 0 && j < 5)
     {
     temp = (int)matrix1[i][j];
     printf("%d\t\t",temp);
     }
     else if (j == 5)
     {
     temp = (int)matrix1[i][j];
     printf("%d\n",temp);
     }
     }*/
	
	
    /*double tbr=0;//total byte
     double g;
     double avgbr; //average bit rate
     for (i = 0; i < x; i++)
     {
     tbr = tbr + matrix1[i][5]+20;
     }
     g=(matrix1[x-1][0]-matrix1[0][0]);
     avgbr = 8*(tbr/(matrix1[x-1][0]-matrix1[0][0])/1000);
     printf ("%f \n",g);
     make sure the calculation is right
     printf("last : %f \n", matrix1[x-1][5]);
     printf("Total bytes are : %d \n", tbr);*/
    
    
	//(A)start to compute the average bit rate
	//printf("================The answer of (A)================ \nAverage bit rate is : %lf kbps.\n", avgbrCounting(matrix1, x) );
    
    
    
	//(B)calculating average bit rate each 5-min windows//
	//avbgrper5min(matrix1, avgbr, x);
    
    
    
	//(C)distribution of packets based on the payload sizes.
	//printpayloadsizepercentage(matrix1,x);
    
    
    
	//(D)the top 3 source IP addresses and the corresponding traffic volume and the percentage in the total traffic volume.
	IPcorrespondvolume(matrix1, x);
    
    
    
	
    
    
    
    
    for(i=0; i < x; i++)
        free(matrix1[i]);
    free(matrix1);
	
	fclose(fp);
	return(0);
}





//This function is for average bit rate calculating//
double avgbrCounting(double **matrix1, int x)
{
	double tbr = 0;//total byte
	double avgbr = 0; //average bit rate
	for (int i = 0; i < x; i++)
	{
		tbr = tbr + matrix1[i][5]+20;
	}
	avgbr = 8 * (tbr / (matrix1[x-1][0] - matrix1[0][0]) /1000);
	printf("total bytes is %lf kbps.\n", tbr);
	return avgbr;
	//double g;
	//g=(matrix1[2153460][0]-matrix1[0][0]);
}

//this function is for printing //

void printavgbr(void)
{
	printf("The average bit rate ");
	return;
}


void avbgrper5min(double **matrix1,double avgbr[],int x)
{
    double tbr = 0;
    int a = 0;
    
    for (int i = 0; i < x; i++)
    {
        if (matrix1[i][0] < 300)
        {
            tbr = tbr + matrix1[i][5]+20;
            avgbr[0] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 300 && matrix1[i][0] < 600)
        { /*Because we can sure matrix1[i][0] in this interval is larger than 300,
           so matrix1[i-1][0] is less than 300. Under this condition tbr becomes zero to compute.*/
            if  (matrix1[i-1][0] < 300)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[1] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 600 && matrix1[i][0] < 900)
        {
            if  (matrix1[i-1][0] < 600)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[2] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 900 && matrix1[i][0] < 1200)
        {
            if  (matrix1[i-1][0] < 900)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[3] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 1200 && matrix1[i][0] < 1500)
        {
            if  (matrix1[i-1][0] < 1200)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[4] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 1500 && matrix1[i][0] < 1800)
        {
            if  (matrix1[i-1][0] < 1500)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[5] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 1800 && matrix1[i][0] < 2100)
        {
            if  (matrix1[i-1][0] < 1800)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[6] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 2100 && matrix1[i][0] < 2400)
        {
            if  (matrix1[i-1][0] < 2100)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[7] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 2400 && matrix1[i][0] < 2700)
        {
            if  (matrix1[i-1][0] < 2400)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[8] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 2700 && matrix1[i][0] < 3000)
        {
            if  (matrix1[i-1][0] < 2700)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[9] = 8 * (tbr / 299.999999 /1000);
        }
        else if  (matrix1[i][0] >= 3000 && matrix1[i][0] < 3300)
        {
            if  (matrix1[i-1][0] < 3000)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[10] = 8 * (tbr / 299.999999 /1000);
        }
        else
        {
            if  (matrix1[i-1][0] < 3300)
                tbr = 0;
            tbr = tbr + matrix1[i][5]+20;
            avgbr[11] = 8 * (tbr / 300.999999 /1000);
        }
    }
    printf("================The answer of (B)================ \n");
    for (int k = 0; k < 12; k++)
    {
        if (k == 11)
        {
            printavgbr();
            printf("(%d ~ %d) is %f kbps\n", a,a + 300,avgbr[k]);
        }
        else
        {
            printavgbr();
            printf("(%d ~ %d) is %f kbps\n", a,a + 299,avgbr[k]);
            a = a + 300;
        }
    }
}

void printpayloadsizepercentage(double **matrix1,int x)
{
    double payload[7] = {0};
	for(int i = 0; i < x; i++)
	{
		if(matrix1[i][5] == 0)
		{
			payload[0]++;
		}
		else if (matrix1[i][5] >= 1 && matrix1[i][5] <= 127)
		{
			payload[1]++;
		}
		else if (matrix1[i][5] >= 128 && matrix1[i][5] <= 255)
		{
			payload[2]++;
		}
		else if (matrix1[i][5] >= 256 && matrix1[i][5] <= 383)
		{
			payload[3]++;
		}
		else if (matrix1[i][5] >= 384 && matrix1[i][5] <= 511)
		{
			payload[4]++;
		}
		else if (matrix1[i][5] == 512)
		{
			payload[5]++;
		}
		else
		{
			payload[6]++;
		}
	}
    
	printf("=================The answer of (C)================= \n");
	
	int b = 0;
	
	for (int a = 0; a < 7;a++)
	{ 	if(a == 0)
    {
        printf("When the payload size(byte) is ( 0 ). Percentage based on the number of packets is %lf %% \n",100*(payload[a]/(x-1)));
        b++;
    }
    else if ( a == 1)
    {
        printf("When the payload size(byte) is (%d ~ %d). Percentage based on the number of packets is %lf %% \n",b ,b + 126,100*(payload[a]/(x-1)));
        b = b + 127;
    }
    else if ( a > 1 && a < 5)
    {
        printf("When the payload size(byte) is (%d ~ %d). Percentage based on the number of packets is %lf %% \n",b ,b + 127,100*(payload[a]/(x-1)));
        b = b + 128;
    }
    else if(a == 5)
    {
        printf("When the payload size(byte) is ( 512 ). Percentage based on the number of packets is %lf %% \n",100*(payload[a]/(x-1)));
    }
    else if (a > 5 && a < 7)
    {
        printf("When the payload size(byte) is ( > 512 ).Percentage based on the number of packets is %lf %% \n",100*(payload[a]/(x-1)));
    }
	}
}

void IPcorrespondvolume(double **matrix1, int x)
{
	int i,ip = 0;
	double *DBarray = (double *)malloc(sizeof(double)*x);
	memset(DBarray, 0,sizeof(double)*x);
	
	for (i = 0; i < x; i++)
	{
		ip = (int)matrix1[i][1];
		DBarray[ip] = DBarray[ip] + matrix1[i][5]+20;
	}
	for (i = 0; i <x; i++)
	{
		if(DBarray[i] != 0)
            printf("%lf \n",DBarray[i]);
	}
	
	
	free(DBarray);
    
    
}

/*void IPcorrespondvolume(double **matrix1, int x )
 {
 list *array = (list *)malloc(sizeof(list)*x);
 
 for (int i = 0; i < x; i++)
 {
 array[i].columnIP = matrix1[i][1];
 //array[i].columnDB = matrix1[i][5];
 }
 
 
 bubblesort(x, array);
 
 free (array);
 
 }
 
 
 void bubblesort(int x ,list *array)
 {
 int i, j, sp;
 list temp;
 for (i = x - 1; i > 0; i--)
 {
 sp = 1;
 for (j = 0; j <= i ; j++)
 {
 if (array[j].columnIP > array[j + 1].columnIP)
 {
 //change location
 temp = array[j];
 array[j] = array[j + 1];
 array[j + 1] = temp;
 sp = 0;
 }
 }
 if (sp == 1)
 break;
 }
 
 printf("%lf \n",array[2].columnIP);
 }*/
