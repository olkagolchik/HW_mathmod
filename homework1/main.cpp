#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;

int main() {
    std::string line;
    double xn=0,yn=0,fx_r =0,fy_r=0,fx_l=0,fy_l=0;
    double finde_value=1;
    double min_d_r=1;
    double min_d_l=1;
    bool isFirstLine= true;
    bool isTwiceLine_r= true,isTwiceLine_l= true;
    std::ifstream in("in.txt");
        in >> xn >> yn;

        double x =0;
        double y=0;
        while (in >> x >> y)
        {
                if(x==0 && y==0){
                    continue;
                }
                double _cos=(xn*x+yn*y)/(sqrt(pow(x,2)+pow(y,2))*sqrt(pow(xn,2)+pow(yn,2)));
                _cos = std::round(_cos * 10000000000.0) / 10000000000.0;
                if (_cos-min_d_l <= 0 && ((xn-0)*(y-0)-(yn-0)*(x-0))>0)
                {
                    min_d_l = _cos;
                    fx_r = x;
                    fy_r = y;

                }
                if (_cos-min_d_r <= 0 && ((xn-0)*(y-0)-(yn-0)*(x-0))<=0)
                {
                    min_d_r = _cos;
                    fx_l = x;
                    fy_l = y;
                }
            }
    in.close();
    std::cout << "Leftmost: " << fx_r << " " << fy_r << "\n";
    std::cout << "Rightmost: " << fx_l << " " << fy_l << "\n";

    return 0;
}
