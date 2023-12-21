#pragma once
#include <memory>

namespace linky {

// template<typename T> using scope = std::unique_ptr<T>;

// template<typename T, typename ... Args>
// constexpr scope<T> create_scope(Args&& ... args)
// {
//     return std::make_unique<T>(std::forward<Args>(args)...);
// }

// template<typename T> using ref = std::shared_ptr<T>;

// template<typename T, typename ... Args>
// constexpr ref<T> create_ref(Args&& ... args)
// {
//     return std::make_shared<T>(std::forward<Args>(args)...);
// }

// template<typename T, typename ... Args>
// constexpr ref<T> cast_ref(Args&& ... args)
// {
//     return std::dynamic_pointer_cast<T>(std::forward<Args>(args)...);
// }
}
