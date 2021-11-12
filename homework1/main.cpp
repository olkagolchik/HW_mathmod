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
        if (temp.size() > 0)
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
std::tuple<int, int> step(int dividend, int divisor) {
    return  std::make_tuple(dividend / divisor, dividend % divisor);
}
int main() {
    std::string line;
    int xn=0,yn=0,fx_r =0,fy_r=0,fx_l=0,fy_l=0;
    double finde_value=1;
    double min_d_r=1;
    double min_d_l=1;
    bool isFirstLine= true;
    bool isTwiceLine_r= true,isTwiceLine_l= true;
    std::ifstream in("in.txt");
    if (in.is_open())
    {
        int x =0;
        int y=0;
        while (getline(in, line))
        {

            if(line.length() == 0){
                continue;
            }
            string *values=StringToMass(line,' ',2);

            x=atoi( values[0].c_str() );
            y=atoi( values[1].c_str() );

            if(isFirstLine){
                isFirstLine= false;
                xn=(-1)*x;
                yn=(-1)*y;
                if(x==0 && y==0){
                    break;
                }
            }
            else{
                if(x==0 && y==0){
                    continue;
                }
                double _cos=(xn*x+yn*y)/(sqrt(pow(x,2)+pow(y,2))*sqrt(pow(xn,2)+pow(yn,2)));
                _cos = std::round(_cos * 10000000000.0) / 10000000000.0;
                if(((xn-0)*(y-0)-(yn-0)*(x-0))<0){
                    if(isTwiceLine_r){
                        isTwiceLine_r= false;
                        min_d_r=finde_value-_cos;
                        fx_r=x;
                        fy_r=y;
                    }
                    else{
                        if(finde_value-_cos<=min_d_r){
                            min_d_r=finde_value-_cos;
                            fx_r=x;
                            fy_r=y;
                        }
                    }
                }
                else{

                    if(isTwiceLine_l){
                        isTwiceLine_l= false;
                        min_d_l=finde_value-_cos;
                        fx_l=x;
                        fy_l=y;

                    }
                    else{

                        if(finde_value-_cos<=min_d_l){
                            min_d_l=finde_value-_cos;
                            fx_l=x;
                            fy_l=y;
                        }
                    }
                }
            }
            delete[] values;
        }
    }
    in.close();

    std::cout << "Leftmost: " << fx_r << " " << fy_r << "\n";
    std::cout << "Rightmost: " << fx_l << " " << fy_l << "\n";

    return 0;
}
