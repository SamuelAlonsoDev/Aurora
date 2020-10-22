#pragma once

namespace Aurora
{
    namespace Concepts
    {
        [[nodiscard]] inline constexpr bool IsConstantEvaluated() noexcept
        {
            return __builtin_is_constant_evaluated();
        }
    }
}