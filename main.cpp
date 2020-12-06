#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "sweep_line.h"
#include <chrono>
#include <functional>
#include <exception>

using namespace sweep_line;
long run(std::function<seg_pair*(const seg_vect)> f,seg_vect inp)
{
     auto t1 = std::chrono::high_resolution_clock::now();
     auto res = f(inp);
     auto t2 = std::chrono::high_resolution_clock::now();
     if (res != nullptr)
         throw std::logic_error("Algo is wrong!");
     return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

int main()
{
    auto test_cont = {100, 300, 500,1000, 2000,5000,50000,100000,200000};
    int attempts = 3;
    auto sweep_line = sweep_line::Sweep_line::get_first_interception;
    auto straightforward = sweep_line::Sweep_line::get_first_interception_staidforward;
    // Test speed
    std::cout << "sweep_line / straightforward\n";
    for(auto &count : test_cont)
    {
        std::cout << "Count: " << count << '\n';
        for(int i = 0; i < attempts; i++)
        {
            std::cout << "Attempt: " << i << '\n';
            auto val = sweep_line::Sweep_line::gen_segments(count);
            std::cout << run(sweep_line,val.first) << " | " << run(straightforward,val.first) << '\n';
        }
    }



  return 0;

}
