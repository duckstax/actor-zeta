#include <actor-zeta/base/address_type.hpp>

namespace actor_zeta { namespace base {

    address_type::address_type(communication_module *aa) : ptr_(new control_block<communication_module>(aa)) {}

    address_type::~address_type() {}

}}
