#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

struct road{
    int flag;
    int distance;
    int quality;
    int rating;
}typedef road;
struct city
{
    int id;
	char name[20];
    int population;
    int area;
    int date;
}typedef city;



//testing...
road **city_arr;
 int city_num = 4;
 city* citys;


int main(){
    citys = (city*)malloc(city_num*sizeof(city));
    city_arr = (road **)malloc(city_num * sizeof(road *));
    for (int i=0; i<city_num; i++){
        city_arr[i] = (road *)malloc(city_num * sizeof(road));
    }
    
    city_arr = (road **)malloc(city_num * sizeof(road *));
    for (int i=0; i<city_num; i++)
        city_arr[i] = (road *)malloc(city_num * sizeof(road));
    //city c0,c1,c2,c3;
    printf(" %d\n",city_num);
    
    
    citys[0].id = 0;
    citys[0].population = 15;
    citys[0].area = 100;
    citys[0].date = 12122020;
    strcpy(citys[0].name, "plovdiv");

    citys[1].id = 1;
    citys[1].population = 35;
    citys[1].area = 150;
    citys[1].date = 13112020;
    strcpy(citys[1].name, "burgas");

    citys[2].id = 2;
    citys[2].population = 19;
    citys[2].area = 110;
    citys[2].date = 22122020;
    strcpy(citys[2].name, "sofia");
    
    citys[3].id = 3;
    citys[3].population = 40;
    citys[3].area = 80;
    citys[3].date = 22122010;
    strcpy(citys[3].name, "pernik");
    ////////////////////////////////
    city_arr[0][1].flag =1;
    city_arr[1][0].flag =1;
    city_arr[0][1].distance =15;
    city_arr[1][0].distance =15;
    city_arr[1][0].rating =3;
    city_arr[0][1].rating =3;

    city_arr[0][2].flag =1;
    city_arr[2][0].flag =1;
    city_arr[0][2].distance =26;
    city_arr[2][0].distance =26;
    city_arr[0][2].rating =2;
    city_arr[2][0].rating =2;

    city_arr[2][3].flag =1;
    city_arr[3][2].flag =1;
    city_arr[2][3].distance =11;
    city_arr[3][2].distance =11;
    city_arr[2][3].rating =1;
    city_arr[3][2].rating =1;
    //printf("hello");

    FILE *fp = fopen("city.bin", "wb");

    if(fp  == NULL){
        printf("ERROR!");
        exit(1);
    }
    
    size_t ell =  fwrite(&city_num,sizeof(int),1, fp);
    //size_t el =  fwrite(&citys,sizeof(citys),1, fp);
    size_t el;
    
    for (int i = 0; i < city_num; i++)
    {
        el =  fwrite(&citys[i],sizeof(city),1, fp);
        if (el == 0)
        {
            printf("ERRor!");
            exit(3);
        }
    }
    
    for (int i = 0; i < city_num; i++)
    {
        
        for (int j = 0; j < city_num; j++)
        {
            size_t elno = fwrite(&city_arr[i][j], sizeof(road), 1, fp);
            if (elno == 0)
            {
                printf("ERRor!");
                exit(3);
            }
        }
    }
    
    
    for (int i = 0; i < city_num; i++)
    {
        printf("name= %s | id= %d\n", citys[i].name, i);
    }
    for (int i = 0; i < city_num; i++)
    {
        for (int j = 0; j < city_num; j++)
        {
            printf(" %d", city_arr[i][j].flag);
        }
        
        printf("\n");
    }
    
    fclose(fp);
    printf("ok!! %d", city_arr[0][0].flag);
    free(citys);
    free(city_arr);
    return 0;
    }
