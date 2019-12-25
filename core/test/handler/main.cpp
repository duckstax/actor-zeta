#include <actor-zeta/actor/handler.hpp>
#include <iostream>

using actor_zeta::actor::make_handler;
using actor_zeta::actor::context;


int main() {

    /*auto* ptr_1 = */ make_handler(
            [](context&){
                std::cerr << "ptr_1"  << std::endl;
            }

    );

    /*auto* ptr_2 = */ make_handler(
            [](context&, int& data ){
                std::cerr << "ptr_2" << data << std::endl;
            }

    );


    /*auto* ptr_3 = */ make_handler(
            [](context&, int& data_1 , int& data_2  ){
                std::cerr << "ptr_3" << data_1 << "" << data_2 << std::endl;
            }

    );


    return 0;
}