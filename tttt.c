#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct road{
    int flag;
    int distance;
    int quality;
    int rating;
}typedef road;
struct city
{
    int id;
	char* name;
    int population;
    int area;
    int date;
}typedef city;



//city_numing...
road **roads_arr;
int city_num = 0,i,j,pose;
city* citys;

int main(int argc, char const *argv[])
{
    FILE* fp = fopen("city.bin", "rb");
    if (fp == NULL)
    {
        printf("can't reed");
        exit(0);
    }
    size_t read = fread(&city_num, sizeof(int), 1, fp);
    roads_arr = (road **)malloc(city_num * sizeof(road *));
    for (i=0; i<city_num; i++){
        roads_arr[i] = (road *)malloc(city_num * sizeof(road));
    }
    citys = (city*)malloc(sizeof(city) * city_num);
    size_t check_mem ;
    check_mem = fread(&citys[0], sizeof(city), 1, fp);
    /*for (i = 0; i < city_num; i++)
    {
        check_mem = fread(&citys[i], sizeof(city), 1, fp);
        if (check_mem != 1)
        {
            printf("can't take citys");
            exit(0);
        }
        
    }*/
    /////////////////
    /*for (i = 0; i < city_num; i++)
    {
        printf("name= %s | id= %d\n", citys[i].name, i);
    }*/
    printf("name= %s \n", citys[0].name);
    fclose(fp);
    free(roads_arr);
    free(citys);
    printf("%d ok\n", city_num);
    return 0;
}
