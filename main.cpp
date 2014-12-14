#include <iostream>
#include <fstream>
#include <ctime>
#include "Bezier.h"
#include <iomanip>
using namespace std;

int main(int argc, char** argv)
{
    clock_t start, end;
    start = clock();

    if(argc != 3){
        cerr<< "Number of Input Arguments Mismatch!" <<endl;
        cerr<< "./bezier [test.in] [test.out]" <<endl;
    }    
    
    int n;//max index ( Degree = n - 1)

    unsigned int n_sample;//number of samples for the curve
    
    ifstream inf(argv[1]);
    
    if(!inf){
        cerr <<"Failed to open input file"<<endl;
        return 1;
    }    
    inf >> n;
    
    // Construct the 2-D array for storing all curves
    Bezier **B = new Bezier*[n];
    for(int i = 0; i < n; i++)
        B[i] = new Bezier[n];
    
    // Fill in all control points
    for(int i = 0; i < n; i++){

        inf >> B[0][i].m_x;  
        inf >> B[0][i].m_y;
    }
    inf >> n_sample;
    inf.close();

    ofstream outf(argv[2]);
    if(!outf){
        cerr <<"Failed to open output file"<<endl;
        return 1;
    }
    
    // Sampling
    double t = 0.0;
    double step = 1 / (double)(n_sample-1);

    for(unsigned int k = 0; k < n_sample; k++){
        
        // dynamic programming
        for(int i = 1; i < n; i++){
            for(int j = 0; j < n-i; j++)
                B[i][j] = Combine(B[i-1][j], B[i-1][j+1], t);
            
        }
        // output to file
        double x = B[n-1][0].m_x;
        double y = B[n-1][0].m_y;

        outf<< fixed << setprecision(2) << x << "\t" << y << endl;

        t += step;
    }
    
    outf.close();
    
    // memory clean up
    for(int i = 0; i < n; i++)
        delete [] B[i];
    delete [] B;
    
    end = clock();
    
    cout << "Execution time: " << (end-start)/(double)(CLOCKS_PER_SEC) << endl;
    
    return 0;
}
