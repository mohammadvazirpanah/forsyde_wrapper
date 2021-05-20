

#include "report.hpp"
#include "forsyde/ros_wrapper.hpp"
#include <iostream>
#include <forsyde.hpp>
#include "func.hpp"

using namespace sc_core;
using namespace ForSyDe;

SC_MODULE(top)
{
    SY::signal<int> srca, result;
    
    SC_CTOR(top)
    {
    
        std::cout<<"SC_CTOR \n";

        
        SY::make_ssource("source1", num_func, 1, 20, srca);
        
        //SY::roswrap<std::string,std::string> *ros1 = new SY::roswrap<std::string,std::string>("ros1","sender",result, srca);

        SY::make_roswrap("new","sender",result, srca);
    
        
        //SY::make_ssink("report1", report_func, result);
        
        

    }

};



