#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include "classes.hpp"

TEST_CASE("handler") {
    auto* mr_ptr = actor_zeta::detail::pmr::get_default_resource();
    auto supervisor_ = actor_zeta::spawn_supervisor<dummy_supervisor>(mr_ptr,1, 100);

    REQUIRE(dummy_supervisor::constructor_counter == 1);

    actor_zeta::send(supervisor_.get(),actor_zeta::address_t::empty_address(),"create_test_handlers");
    supervisor_->scheduler_test()->run_once();
    REQUIRE(dummy_supervisor::enqueue_base_counter == 1 /*add_link*/);
    REQUIRE(dummy_supervisor::add_actor_impl_counter == 1);
    REQUIRE(test_handlers::init_counter == 1);
    REQUIRE(static_cast<dummy_supervisor*>(supervisor_.get())->actors_count() == 1);

    REQUIRE(test_handlers::ptr_0_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),test_handlers_names::ptr_0);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(test_handlers::ptr_0_counter == 1);

    REQUIRE(test_handlers::ptr_1_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),test_handlers_names::ptr_1);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(test_handlers::ptr_1_counter == 1);

    REQUIRE(test_handlers::ptr_2_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),test_handlers_names::ptr_2, 1);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(test_handlers::ptr_2_counter == 1);

    REQUIRE(test_handlers::ptr_3_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),test_handlers_names::ptr_3, 1, 2);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(test_handlers::ptr_3_counter == 1);

    REQUIRE(test_handlers::ptr_4_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),test_handlers_names::ptr_4, 1, 2, std::string("test"));
    supervisor_->scheduler_test()->run_once();
    REQUIRE(test_handlers::ptr_4_counter == 1);

    actor_zeta::send(supervisor_.get(),actor_zeta::address_t::empty_address(),"create_storage");
    supervisor_->scheduler_test()->run_once();
    REQUIRE(dummy_supervisor::enqueue_base_counter == 2 /* add_link*/);
    REQUIRE(dummy_supervisor::add_actor_impl_counter == 2);
    REQUIRE(storage_t::constructor_counter == 1);
    REQUIRE(static_cast<dummy_supervisor*>(supervisor_.get())->actors_count() == 2);

    REQUIRE(storage_t::init_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),storage_names::init);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(storage_t::init_counter == 1);
    
    REQUIRE(storage_t::search_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),storage_names::search, std::string("key_1"));
    supervisor_->scheduler_test()->run_once();
    REQUIRE(storage_t::search_counter == 1);

    REQUIRE(storage_t::add_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),storage_names::add, std::string("key_1"), std::string("value_1"));
    supervisor_->scheduler_test()->run_once();
    REQUIRE(storage_t::add_counter == 1);

    REQUIRE(storage_t::delete_table_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),storage_names::delete_table, std::string("test"), std::string("/"), 12);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(storage_t::delete_table_counter == 1);

    REQUIRE(storage_t::create_table_counter == 0);
    actor_zeta::send(static_cast<dummy_supervisor*>(supervisor_.get())->last_actor(), supervisor_->address(),storage_names::create_table, std::string("test"), std::string("/"), 1, 12);
    supervisor_->scheduler_test()->run_once();
    REQUIRE(storage_t::create_table_counter == 1);
}
