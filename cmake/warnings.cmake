include_guard(GLOBAL)

set(MSVC_WARNINGS
    /permissive- # standards conformance.
    /W4 # Level 1, 2, 3 and 4 warnings.
)

set(GCC_CLANG_COMPATIBLE_WARNINGS
    -Wall
    -Wextra
    -Wextra-semi # Warn on extra semi-colon ourside of a function
    -Wimplicit-fallthrough # Warn on statement fallthrough without explicit annotation.
    -Wmisleading-indentation # Warn on misleading indentation.
    -Wmissing-include-dirs # Warn if a user-supplied include directory does not exist.
    -Wnull-dereference # Warn on null pointer dereference.
    -Wpedantic # Standard conformance.
    -Wshadow # Warning of a variabled shadows the declation of one from the parent context.
)

set(GCC_WARNINGS
   ${GCC_CLANG_COMPATIBLE_WARNINGS}
)

set(CLANG_WARNINGS
   ${GCC_CLANG_COMPATIBLE_WARNINGS}
    -Wextra-semi-stmt # warn about empty expression statements, for example extra ; like this: puts("string");;
)