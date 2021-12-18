#include <iostream>
#include <fstream>
#include <iomanip>
#include <valarray>

using namespace std;
string * StringToMass(string base_str, char delim, int size){

    size_t pos = 0;
    size_t base_str_size = base_str.size();
    size_t delim_size=1;
    string temp;
    int i=0;
    string *mass_str = new string[size];
    while (pos < base_str_size) {
        temp = temp.assign(base_str, pos, base_str.find(delim, pos) - pos);
        if (temp.size() > 0)  // проверка на пустую строку при необходимости
        {
            mass_str[i] = temp;
            i++;
            if(i==size){
                break;
            }
        }
        pos += temp.size() + delim_size;
    }

    return mass_str;
}
//functions
double calc(double y_0, int direction, double v_y, double v_x, double x, double x_0, double x_d, double g){
    return y_0+direction*(v_y/v_x)*(x-x_0-2*x_d)-g*(pow(x-x_0-2*x_d,2)/(2*pow(v_x,2)));
}
void flight(string file_name,int index, int mass_size,string *mass_bollards,int direction, double g, double y_0,double x_0, double x_d, double v_x, double v_y, int number_of_bollard){
    if(index == 0){// первый вход - наполняем массив столбов до первого пападания
        std::string line;
        std::ifstream in(file_name); // открываем файл для чтения
        std::ifstream in2(file_name); // открываем файл для чтения
        if (in.is_open())
        {

            int m=0;
            while (getline(in, line)) // перебераем столбы
            {
                if(line.length() != 0){
                    m++;
                }
            }

            string *mass_bollards = new string[m];

            int k= 0;
            double x=0,y=0,new_y=0;

            while (getline(in2, line)) // перебераем столбы
            {

                k++;

                if(k == 1){
                    mass_bollards[k-1]="0 "+line;
                    string *values_start=StringToMass("0 "+line,' ',2);
                    y_0=atof( values_start[1].c_str() );
                    x_0=atof( values_start[0].c_str() );
                    if(line.length() == 0){
                        std::cout <<"0" << std::endl;
                        break;
                    }
                    delete[] values_start;
                    continue;
                }
                if(k == 2){
                    string *values_start=StringToMass(line,' ',2);
                    x_d=0; // коэф смещения
                    v_x=atof( values_start[0].c_str() );
                    v_y=atof( values_start[1].c_str() );
                    if(line.length() == 0 || abs(v_x)+abs(v_y)==0 ){
                        std::cout <<"0" << std::endl;
                        break;
                    }
                    delete[] values_start;
                    continue;
                }
                string *values=StringToMass(line,' ',2);
                x=atof( values[0].c_str() );
                y=atof( values[1].c_str() );

                    //проверка столбика
                    new_y=calc(y_0, direction, v_y,  v_x,  x,  x_0,  x_d,  g);

                    if(x<=x_0){
                        std::cout <<"0" << std::endl;
                        break;
                    }
                    if(new_y <= 0){
                        std::cout <<to_string(number_of_bollard) << std::endl;
                        break;
                    }
                    if(new_y<=y){ // попали
                        mass_bollards[k-2]=line;
                        x_d=x-x_d; //смещение
                        //рекурсия
                        index++;
                        direction=-1*direction;
                        //развертываем массив координат столбов
                        if(k-1!= 2){

                            string *mass_bollards_2 = new string[k-1];
                            for(int i=0; i<k-1; i++){
                                mass_bollards_2[i]=mass_bollards[i];
                            }
                            delete[] mass_bollards;
                            string *mass_bollards_2_1 = new string[k-1];
                            for(int i=0; i<k-1; i++){
                                mass_bollards_2_1[i]=mass_bollards_2[k-2-i];

                            }
                            for(int i=0; i<k-1; i++){
                                mass_bollards_2[i]=mass_bollards_2_1[i];
                            }
                            delete[] mass_bollards_2_1;
                            mass_size=k-1;

                            delete[] values;
                            flight(file_name,index,mass_size,mass_bollards_2,direction, g, y_0, x_0,  x_d,  v_x,  v_y, number_of_bollard);
                            break;
                        }
                        else{
                            std::cout <<to_string(number_of_bollard) << std::endl;
                            break;
                        }
                    }
                    else{ // не попали
                        number_of_bollard+=direction*1;
                        //сохранение координат в массив
                        mass_bollards[k-2]=line;
                       if(k-1 == m-1){
                            std::cout <<to_string(number_of_bollard) << std::endl;
                        }
                    }
                delete[] values;
            }
        }
    }
//-----------------------------------------------------------------------------------------------
    else{
        int k=0;
        string line;
        double x,y,new_y;
        string *mass_bollards_1 = new string[mass_size];
        while (true){
            line =mass_bollards[k];
            k++;
            if(k == 1){
                mass_bollards_1[k-1]=line;
                continue;
            }
            string *values=StringToMass(line,' ',2);
            x=atof( values[0].c_str() );
            y=atof( values[1].c_str() );
            //проверка столбика
            new_y=calc(y_0, direction, v_y,  v_x,  x,  x_0,  x_d,  g);
            if(x==x_0){
                std::cout <<"0" << std::endl;
                break;
                break;
            }
            if(new_y <= 0){
                std::cout <<to_string(number_of_bollard) << std::endl;
                break;
            }
            if(new_y<=y){ // попал
                mass_bollards_1[k-1]=line;
                x_d=x-x_d; //смещение
                //рекурсия
                index++;
                direction=-1*direction;
                //разворачиваем массива координат столбов
                if(k!=2){

                    string *mass_bollards_2 = new string[k];
                    for(int i=0; i<k; i++){
                        mass_bollards_2[i]=mass_bollards_1[i];
                    }
                    delete[] mass_bollards;
                    delete[] mass_bollards_1;
                    string *mass_bollards_2_1 = new string[k];
                    for(int i=0; i<k; i++){
                        mass_bollards_2_1[i]=mass_bollards_2[k-1-i];

                    }
                    for(int i=0; i<k; i++){
                        mass_bollards_2[i]=mass_bollards_2_1[i];
                    }
                    delete[] mass_bollards_2_1;
                    mass_size=k;
                    //-------
                    flight(file_name,index,mass_size,mass_bollards_2,direction, g, y_0, x_0,  x_d,  v_x,  v_y, number_of_bollard);
                    break;
                }
                else{
                    std::cout <<to_string(number_of_bollard) << std::endl;
                    break;
                }
            }
            else{ // не попали

                //сохранение координат в массив
                if(x!=x_0){
                    number_of_bollard+=direction*1;
                    mass_bollards_1[k-1]=line;
                    //--------------
                }
                else{
                    std::cout <<"0" << std::endl;
                    break;
                }
            }
            delete[] values;
        }
    }
}
int main(int argc, char** argv) {
    if(argc == 2){
        // есть один агрумент
        // в argv[1] содержится строка с первым агрументом (имя файла)
    }else{
        // аргументов нет или их больше чем мы ожидаем
        return 1;
    }

    //на вход данные о полете
    double g=9.81; // ускорение по y
    double y_0=1; // стартовая по y
    double x_0=0; // стартовая по x
    double x_d=0; // коэффициент смещения
    double v_x=3; // компонента скорости по x
    double v_y=1; // компонента скорости по y
    int direction = 1; //направо - true; налево - false
    int index = 0;
    int mass_size=0;
    int number_of_bollard=0;
    std::string line;
    std::ifstream in(argv[1]); // открытие файла для чтения

    if (in.is_open()) {
        int m = 0;
        while (getline(in, line)) // перебор столбов
        {
            if (line.length() != 0) {
                m++;
            }
        }
        if(m >2){
            mass_size=m;
            string *mass_bollards = new string[m];
            flight(argv[1],index,mass_size, mass_bollards, direction, g, y_0, x_0, x_d, v_x, v_y,number_of_bollard);
        }
        else{
            std::cout <<"0" << std::endl;
        }
    }
    //
    return 0;
}
