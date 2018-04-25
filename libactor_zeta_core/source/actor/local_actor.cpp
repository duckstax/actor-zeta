#include <utility>
#include <iostream>

#include <actor-zeta/actor/local_actor.hpp>
#include <actor-zeta/standard_handlers/skip.hpp>
#include <actor-zeta/standard_handlers/sync_contacts.hpp>
#include <actor-zeta/executor/execution_device.hpp>
#include <actor-zeta/environment/environment.hpp>
#include <actor-zeta/messaging/message.hpp>
#include <actor-zeta/actor/actor_address.hpp>
#include <actor-zeta/messaging/message_priority.hpp>
#include <actor-zeta/standard_handlers/add_channel.hpp>
#include <actor-zeta/channel/channel.hpp>

namespace actor_zeta {

    namespace actor {
        local_actor::local_actor(
                environment::abstract_environment *env,
                mailbox_type* mail_ptr,
                behavior::abstract_behavior*behavior_ptr,
                const std::string &type
        ) :
                abstract_actor(env, type),
                life(behavior_ptr),
                mailbox_(mail_ptr){

            initialize();
            startup();
            type_.location = locations::local;
        }

        void local_actor::initialize() {
            attach(new sync_contacts());
            attach(new skip());
            attach(new add_channel());
        }

        void local_actor::startup() {

        }

        void local_actor::shutdown() {

        }

        messaging::message local_actor::next_message() {
            return mailbox().get();
        }

        void local_actor::send_channel(messaging::message && msg) const {
            channels.at(msg.recipient()->name())->send(std::move(msg));
        }

        void local_actor::attach(behavior::abstract_action *ptr_aa) {
            life->insert(ptr_aa);
        }

        auto local_actor::all_view_address() const -> void  {
          for (auto &i: contacts)
              std::cout << i.first << std::endl;
        }

        local_actor::~local_actor() {

        }

        bool local_actor::has_next_message() {
            messaging::message msg_ptr = mailbox().get();
            return push_to_cache(std::move(msg_ptr));
        }

        bool local_actor::push_to_cache(messaging::message &&msg_ptr) {
            return mailbox().push_to_cache(std::move(msg_ptr));
        }

        messaging::message local_actor::pop_to_cache() {
            return mailbox().pop_to_cache();
        }

        local_actor::mailbox_type &local_actor::mailbox() {
            return *mailbox_;
        }

        executor::execution_device *local_actor::device() const {
            return executor_;
        }

        void local_actor::device(executor::execution_device *e) {
            if (e!= nullptr) {
                executor_ = e;
            }
        }

        void local_actor::address(actor_address aa) {
            contacts.emplace(aa->name(), aa);
        }

        void local_actor::channel(channel::channel channel_) {
            channels.emplace(channel_->name(),channel_);
        }

        void local_actor::broadcast_channel(messaging::message &&msg) const {
            channels.at(msg.recipient()->name())->broadcast(std::move(msg));
        }

        actor_address local_actor::address(const std::string &name) {
            return contacts.at(name);
        }

        channel::channel local_actor::channel(const std::string &name) {
            return channels.at(name);
        }

    }
}