#include <initializer_list>
#include <iostream>
#include <actor-zeta/behavior/reactions.hpp>
#include <actor-zeta/behavior/abstract_action.hpp>
#include <actor-zeta/behavior/context.hpp>
#include <memory>

namespace actor_zeta { namespace behavior {

        inline void error_duplicate_handler(const char *_error_) {
            std::cerr << "Duplicate" << std::endl;
            std::cerr << "Handler: " << _error_ << std::endl;
            std::cerr << "Duplicate" << std::endl;
        }


        void reactions::execute(context &d) {
            auto it = reactions_.find(d.message().command());
            if (it != reactions_.end()) {
                return it->second->invoke(d);
            } else {
                return reactions_.at("skip")->invoke(d);
            }
        }

        bool reactions::add(abstract_action *aa) {
            auto it = reactions_.find(aa->name());
            bool status = false ;
            if( it == reactions_.end() ) {
                auto it1 =  reactions_.emplace(aa->name(), std::unique_ptr<abstract_action>(aa));
                status = it1.second;
            } else {
                error_duplicate_handler(aa->name().to_string().c_str());
            }

            return status;
        }

        auto reactions::end() -> reactions::iterator {
            return reactions_.end();
        }

        auto reactions::begin() -> reactions::iterator {
            return reactions_.begin();
        }

        auto reactions::cend() -> reactions::const_iterator {
            return reactions_.cend();
        }

        auto reactions::cbegin() -> reactions::const_iterator {
            return reactions_.cbegin();
        }

        auto reactions::begin() const -> reactions::const_iterator {
            return reactions_.begin();
        }

        auto reactions::end() const -> reactions::const_iterator {
            return reactions_.end();
        }
    }}
