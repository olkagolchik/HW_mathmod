#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;

int main() {
    std::string line;
    int xn=0,yn=0,fx_r =0,fy_r=0,fx_l=0,fy_l=0;
    double finde_value=1;
    double min_d_r=1;
    double min_d_l=1;
    bool isFirstLine= true;
    bool isTwiceLine_r= true,isTwiceLine_l= true;
    std::ifstream in("in.txt");
        in >> xn >> yn;

        int x =0;
        int y=0;
        while (in >> x >> y)
        {
                if(x==0 && y==0){
                    continue;
                }
                double _cos=(xn*x+yn*y)/(sqrt(x*x+y*y)*sqrt(xn*xn+yn*yn));
                _cos = std::round(_cos * 10000000000.0) / 10000000000.0;
                if (_cos-min_d_l <= 0 && (xn*y-yn*x)>0)
                {
                    min_d_l = _cos;
                    fx_r = x;
                    fy_r = y;

                }
                if (_cos-min_d_r <= 0 && (xn*y-yn*x)<=0)
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
