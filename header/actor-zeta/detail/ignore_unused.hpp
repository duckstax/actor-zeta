#pragma once

template<typename... args>
void ignore_unused(args const&...) {}

template<typename... args>
void ignore_unused() {}