#pragma once
#include <type_traits>
#include <cstddef>

#define decl(x) std::remove_cv<decltype(x)>::type

namespace type
{

}
