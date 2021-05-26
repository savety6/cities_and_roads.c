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
	char* name;
    int population;
    int area;
    int date;
}typedef city;



//city_numing...
road **roads_arr;
int city_num = 0,i,j,pose;
city* citys;

int Date_enter(){
    int dd,mm,yy;
    int date = 0;
     
    printf("Enter date (dd/mm/yy) format: ");
    scanf("%d/%d/%d",&dd,&mm,&yy);

    date |= (dd&0xff);
    date |= (mm&0xff)<<8;
    date |= (yy&0xffff)<<16;
    
    return date;
}
void Date_print(int _date){
    int dd,mm,yy;
    dd = (_date &0xff);
    mm = ((_date>>8)& 0xff);
    yy = ((_date>>16)&0xffff);
    printf("Date: %02d/%02d/%04d\n",dd,mm,yy);
}

void list(city* _citys){
    printf("city num %d\n", city_num);
    for (i = 0; i < city_num; i++)
    {
        printf("name= %s | id= %d\n", _citys[i].name, i);
    }
    
}
int trip(){
    int p1,p2,p3;
    printf("enter citys id: ");
    scanf("%d", &p1);
    scanf("%d", &p2);
    scanf("%d", &p3);

    if (roads_arr[p1][p2].flag == 1 & roads_arr[p2][p3].flag == 1)
    {
        printf("total distance is %dkm\n", roads_arr[p1][p2].distance + roads_arr[p2][p3].distance);
        printf("total distance is %dkm\n", (roads_arr[p1][p2].rating + roads_arr[p2][p3].rating) / 2);
        return 1;
    }
    else{
        printf("there is no way");
        return 0;
    }
}

void delete(int pos, city* _citys){
    for (i =  pos; i < city_num; i++)
    {
        _citys[i-1]= _citys[i];
        
    }
    --city_num;
    city* ptrTo_arr = _citys;
    _citys=(city*)malloc(sizeof(city)* city_num);
    for ( i = 0; i < city_num; i++)
    {
        _citys[i] = ptrTo_arr[i];
    }
    //free(ptrTo_arr);
}

void add(city* _citys,road** _roads){
    city_num++;
    city* ptrCitys = _citys;
    _citys = (city*)malloc(sizeof(city) * city_num);
    for ( i = 0; i < city_num - 1; i++)
    {
        _citys[i] = ptrCitys[i];
    }
    
    _citys[city_num].id = city_num;
    _citys->name = (char*)malloc(sizeof(char) * 20);
    printf("name of the city: ");
    scanf("%s", &_citys[city_num].name);
    printf("city area: ");
    scanf("%d ", &_citys[city_num].area );
    printf("city population: ");
    scanf("%d ", &_citys[city_num].population );
    _citys->date = Date_enter(); 
}

void bin( city* _citys, road** _roads, int n){
    FILE *fp = fopen("city.bin", "wb");

    if(fp  == NULL){
        printf("ERROR!");
        exit(1);
    }
    size_t ell =  fwrite(&n,sizeof(int),1, fp);
    size_t el;
    for (i = 0; i <= n; i++)
    {
        el =  fwrite(&_citys[i],sizeof(city),1, fp);
        if (el == 0)
        {
            printf("ERRor!");
            exit(3);
        }
    }
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            size_t elno = fwrite(&_roads[i][j], sizeof(road), 1, fp);
            if (elno == 0)
            {
                printf("ERRor!");
                exit(3);
            }
        }
    }
    fclose(fp);
}


int main(){
    //city c1,c2,c3;
    //load(citys, roads_arr);
    
    FILE *fp = fopen("city.bin", "rb");

    if(fp  == NULL){
        printf("ERROR!");
        exit(1);
    }

    size_t read = fread(&city_num, sizeof(int), 1, fp);
    roads_arr = (road **)malloc(city_num * sizeof(road *));
    for (i=0; i<city_num; i++){
        roads_arr[i] = (road *)malloc(city_num * sizeof(road));
    }
    citys = (city*)malloc(city_num*sizeof(city));
    size_t check_mem ;
    for (i = 0; i <= city_num; i++)
    {
        check_mem = fread(&citys[i], sizeof(city), 1, fp);
        if (check_mem != 1)
        {
            printf("ErrOr111");
            exit(0);
        }
        
    }
    for (i = 0; i < city_num; i++)
    {
        
        
        for (j = 0; j < city_num; j++)
        {
            check_mem = fread(&roads_arr[i][j], sizeof(road), 1, fp);
            if (check_mem != 1)
            {
                printf("ErrOr");
                exit(0);
            }
        }
        
    }

    fclose(fp);
    
    
    printf("%d  ok!!\n", city_num);
    for (i = 0; i < city_num; i++)
    {
        for (j = 0; j < city_num; j++)
        {
            printf(" %d", roads_arr[i][j].flag);
        }
        
        printf("\n");
    }
    ////////////////////////////////////////////////////////
    int check = 0;
    do
    {
        point:
        printf("press: 1 to add : 2 to delete : 3 trip lenght : 4 print all : 5 exit - ");
        
        scanf("%d", &check);
    } while (check == 1 && check == 2 && check == 3 && check == 4 && check == 5);
    
    switch (check)
    {
    case 1:
        
        add(citys, roads_arr); 
        printf("add");
        break;
    
    case 2:
        printf("pick city to delete: ");
        scanf("%d", &pose);
        delete(pose, citys);
        //printf("delete");
        break;
    
    case 3:
        trip();
        //printf("trip");
        break;
    case 4:
        list(citys);
        break;
    
    case 5:
        printf("goodbye\n");
        bin(citys, roads_arr, city_num);
        //printf("%d", city_num);
        free(citys);
        free(roads_arr);
        return 0;
    }
    
    goto point;
    
    
}
