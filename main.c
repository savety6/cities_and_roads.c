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
road **roads;
int city_num = 0;
city* citys;


//testing...

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
    for (int i = 0; i <= city_num; i++)
    {
        printf("name= %s | id= %d\n", _citys[i].name, _citys[i].id);
    }
    
}
//working...
void add_city(){
    city_num++;
    city *ptrToCity;
    ptrToCity = citys;

    printf("%ld\n", sizeof(roads));

    citys = (city*)malloc(sizeof(city) * 100);

    printf("%d\n", city_num);
    printf("%ld\n", sizeof(roads));

    
    roads[city_num].id=city_num;
    printf("city name:");
    scanf("%s", &roads[city_num].name);

    printf("city population:");
    scanf("%d", &roads[city_num].population);
    printf("city area:");
    scanf("%d", &roads[city_num].area);
    roads[city_num].date = Date_enter();
    


}




int main()
{
    FILE *fp = fopen("city.bin", "rb");
    if(fp  == NULL){
        printf("ERROR!");
        exit(1);
    }

    size_t read = fread(&city_num, sizeof(int), 1, fp);

    citys = (city*)malloc(city_num*sizeof(city));
    roads = (road **)malloc(city_num * sizeof(road *));
    for (int i=0; i<city_num; i++)
        roads[i] = (road *)malloc(city_num * sizeof(road));
    

    size_t checkBin;
    for (int i = 0; i <= city_num; i++)
    {
        checkBin = fread(&citys[i], sizeof(city), 1, fp);
        if (checkBin != 1)
        {
            printf("ErrOr");
            exit(0);            }  
        }
    for (int i = 0; i < city_num; i++)
    {
        for (int j = 0; j < city_num; j++)
        {
            checkBin = fread(&roads[i][j], sizeof(road), 1, fp);
            if (checkBin != 1)
            {
                printf("ErrOr");
                exit(0);
            }
        }   
    }
    fclose(fp);
    
    for (int i = 0; i < city_num; i++)
    {
        for (int j = 0; j < city_num; j++)
        {
            printf(" %d", roads[i][j].flag);
        }
        
        printf("\n");
    }
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
        //add();
        add_city(); 
        printf("add");
        break;
    
    case 2:
        //delete();
        printf("delete");
        break;
    
    case 3:
        //trip();
        printf("trip");
        break;
    case 4:
        list(citys);
        break;
    
    case 5:
        printf("goodbye");
        free(citys);
        return 0;
    }
    
    goto point;
  
}