#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <actor-zeta/mailbox/priority.hpp>

namespace actor_zeta { namespace mailbox {

class message_id  {
public:
  /// The first bit flags response messages.
  static constexpr uint64_t response_flag_mask = 0x8000000000000000;

  /// The second bit flags whether the actor already responded.
  static constexpr uint64_t answered_flag_mask = 0x4000000000000000;

  // The third and fourth bit are used to categorize messages.
  static constexpr uint64_t category_flag_mask = 0x3000000000000000;

  /// The trailing 60 bits are used for the actual ID.
  static constexpr uint64_t request_id_mask = 0x0FFFFFFFFFFFFFFF;

  /// Identifies one-to-one messages with high priority.
  static constexpr uint64_t urgent_message_category = 0;

  /// Identifies one-to-one messages with normal priority.
  static constexpr uint64_t normal_message_category = 1;

  /// Number of bits trailing the category.
  static constexpr uint64_t category_offset = 60;

  /// Default value for asynchronous messages with normal message category.
  static constexpr uint64_t default_async_value = 0x1000000000000000;

  /// Constructs a message ID for asynchronous messages with normal priority.
  constexpr message_id() : value_(default_async_value) {

  }

  constexpr explicit message_id(uint64_t value) : value_(value) {

  }

  ///template<class Value>
  //constexpr explicit message_id(Value value) : value_(static_cast<uint64_t>(value)) {
  //}

  message_id(const message_id&) = default;
  message_id& operator=(const message_id&) = default;

  bool operator==(const message_id& rhs) {
      value_ == rhs.value_;
  }

  /// Returns the message category, i.e., one of `normal_message_category`,
  /// `upstream_message_category`, `downstream_message_category`, or
  /// `urgent_message_category`.
  constexpr uint64_t category() const noexcept {
    return (value_ & category_flag_mask) >> category_offset;
  }

  /// Returns a new message ID with given category.
  constexpr message_id with_category(uint64_t x) const noexcept {
    return message_id{(value_ & ~category_flag_mask) | (x << category_offset)};
  }

  /// Returns whether a message is asynchronous, i.e., neither a request, nor a
  /// response, nor a stream message.
  constexpr bool is_async() const noexcept {
    return value_ == 0 || value_ == default_async_value;
  }

  /// Returns whether a message is a request.
  constexpr bool is_request() const noexcept {
    return (value_ & request_id_mask) != 0 && !is_response();
  }

  /// Returns whether a message is a response to a previously send request.
  constexpr bool is_response() const noexcept {
    return (value_ & response_flag_mask) != 0;
  }

  /// Returns whether a message is tagged as answered by the receiving actor.
  constexpr bool is_answered() const noexcept {
    return (value_ & answered_flag_mask) != 0;
  }

  /// Returns whether `category() == urgent_message_category`.
  constexpr bool is_urgent_message() const noexcept {
    return category() == urgent_message_category;
  }

  /// Returns whether `category() == normal_message_category`.
  constexpr bool is_normal_message() const noexcept {
    return category() == normal_message_category;
  }

  /// Returns a response ID for the current request or an asynchronous ID with
  /// the same priority as this ID.
  constexpr message_id response_id() const noexcept {
    return is_request()
             ? message_id{value_ | response_flag_mask}
             : message_id{is_urgent_message() ? 0 : default_async_value};
  }

  /// Extracts the request number part of this ID.
  constexpr message_id request_id() const noexcept {
    return message_id{value_ & request_id_mask};
  }

  /// Returns the same ID but high message priority.
  /// @pre `!is_stream_message()`
  constexpr message_id with_high_priority() const noexcept {
    return message_id{value_ & ~category_flag_mask};
  }

  /// Returns the same ID with normal message priority.
  /// @pre `!is_stream_message()`
  constexpr message_id with_normal_priority() const noexcept {
    return message_id{value_ | default_async_value};
  }

  /// Returns the "raw bytes" for this ID.
  constexpr uint64_t integer_value() const noexcept {
    return value_;
  }

  /// Sets the flag for marking an incoming message as answered.
  void mark_as_answered() noexcept {
    value_ |= answered_flag_mask;
  }
  message_id& operator++() noexcept {
    ++value_;
    return *this;
  }

private:
  uint64_t value_;
};

/// Generates a `message_id` with given integer value.
/// @relates message_id
constexpr message_id
make_message_id(normal_priority_constant , uint64_t value) {
  return message_id{value | message_id::default_async_value};
}

/// Generates a `message_id` with given integer value.
/// @relates message_id
constexpr message_id
make_message_id(high_priority_constant , uint64_t value) {
  return message_id{value};
}

/// Generates a `message_id` with given integer value.
/// @relates message_id
template <priority P = priority::normal>
constexpr message_id make_message_id(uint64_t value = 0) {
  return make_message_id(std::integral_constant<priority, P>{}, value);
}

/// Generates a `message_id` with given priority.
/// @relates message_id
constexpr message_id make_message_id(mailbox::priority p) {
  return message_id{static_cast<uint64_t>(p) << message_id::category_offset};
}

}} // namespace caf

namespace std {

    bool operator==(const actor_zeta::mailbox::message_id& lhs, const actor_zeta::mailbox::message_id & rhs){
        return lhs == rhs;
    }

template <>
struct hash<actor_zeta::mailbox::message_id> {
  size_t operator()(actor_zeta::mailbox::message_id x) const noexcept {
    hash<uint64_t> f;
    return f(x.integer_value());
  }
};

} // namespace std
