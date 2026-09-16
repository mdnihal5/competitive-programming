#pragma once
//
// Debug header for competitive programming.
// Include AFTER <bits/stdc++.h> and `using namespace std;` (the template does).
//
// IMPORTANT -- the template defines these macros BEFORE including this file:
//   #define int long long   -> never write a bare `int` here; use size_t etc.
//   #define endl "\n"       -> never write std::endl here; it becomes std::"\n"
//

// Color definitions
#define COLOR_RESET "\033[0m"
#define COLOR_VAR "\033[1;32m" // Green color for variables
#define COLOR_VALUE "\033[1;34m" // Blue color for values
#define COLOR_BRACKET_1 "\033[1;93m" // Light yellow for first level brackets
#define COLOR_BRACKET_2 "\033[1;96m" // Light cyan for second level brackets
#define COLOR_BRACKET_3 "\033[1;95m" // Light purple for third level brackets

// ---------------------------------------------------------------------------
// Core overloads
// ---------------------------------------------------------------------------

template <class T1, class T2>
ostream &operator<< (ostream &os, const pair<T1, T2> &p) {
    return os << COLOR_BRACKET_1 << "{" << COLOR_RESET << COLOR_VAR << p.first << COLOR_RESET << ", " << COLOR_VALUE <<
           p.second << COLOR_RESET << COLOR_BRACKET_1 << "}";
}

template < class T, class = decltype (begin (declval<T>() ) ),
           class = enable_if_t < !is_same<T, string>::value >>
ostream & operator<< (ostream &os, const T &c) {
    os << COLOR_BRACKET_1 << "[" << COLOR_RESET;

    for (auto it = begin (c); it != end (c); ++it)
        os << (it == begin (c) ? "" : ", ") << COLOR_VALUE << *it << COLOR_RESET;

    return os << COLOR_BRACKET_1 << "]" << COLOR_RESET;
}

// Support for deque
template <class T>
ostream &operator<< (ostream &os, const deque<T> &c) {
    os << COLOR_BRACKET_2 << "[" << COLOR_RESET;

    for (auto it = c.begin(); it != c.end(); ++it)
        os << (it == c.begin() ? "" : ", ") << COLOR_VALUE << *it << COLOR_RESET;

    return os << COLOR_BRACKET_2 << "]" << COLOR_RESET;
}

// Support for priority_queue
template <class T, class Container, class Compare>
ostream &operator<< (ostream &os, const priority_queue<T, Container, Compare> &pq) {
    os << COLOR_BRACKET_3 << "priority_queue [" << COLOR_RESET;
    auto c = pq;

    while (!c.empty() ) {
        os << COLOR_VALUE << c.top() << COLOR_RESET;
        c.pop();

        if (!c.empty() ) os << ", ";
    }

    return os << COLOR_BRACKET_3 << "]" << COLOR_RESET;
}

// ---------------------------------------------------------------------------
// Added structures
// ---------------------------------------------------------------------------

// stack -- printed top-first (the order you pop them)
template <class T, class Container>
ostream &operator<< (ostream &os, const stack<T, Container> &st) {
    os << COLOR_BRACKET_3 << "stack top>[" << COLOR_RESET;
    auto c = st;

    while (!c.empty() ) {
        os << COLOR_VALUE << c.top() << COLOR_RESET;
        c.pop();

        if (!c.empty() ) os << ", ";
    }

    return os << COLOR_BRACKET_3 << "]" << COLOR_RESET;
}

// queue -- printed front-first
template <class T, class Container>
ostream &operator<< (ostream &os, const queue<T, Container> &q) {
    os << COLOR_BRACKET_3 << "queue front>[" << COLOR_RESET;
    auto c = q;

    while (!c.empty() ) {
        os << COLOR_VALUE << c.front() << COLOR_RESET;
        c.pop();

        if (!c.empty() ) os << ", ";
    }

    return os << COLOR_BRACKET_3 << "]" << COLOR_RESET;
}

// tuple of any arity
template <class Tup, size_t... Is>
void _dbg_tuple (ostream &os, const Tup &t, index_sequence<Is...>) {
    ( (os << (Is ? ", " : "") << COLOR_VALUE << get<Is> (t) << COLOR_RESET), ...);
}

template <class... Ts>
ostream &operator<< (ostream &os, const tuple<Ts...> &t) {
    os << COLOR_BRACKET_1 << "(" << COLOR_RESET;
    _dbg_tuple (os, t, index_sequence_for<Ts...> {});
    return os << COLOR_BRACKET_1 << ")" << COLOR_RESET;
}

// optional
template <class T>
ostream &operator<< (ostream &os, const optional<T> &o) {
    if (o) return os << *o;

    return os << COLOR_BRACKET_3 << "nullopt" << COLOR_RESET;
}

// variant
template <class... Ts>
ostream &operator<< (ostream &os, const variant<Ts...> &v) {
    visit ( [&] (const auto & x) { os << x; }, v);
    return os;
}

// ---------------------------------------------------------------------------
// Macros for debug output
// ---------------------------------------------------------------------------

#define _NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define _FE_6(_CALL, x, ...) _CALL(x) _FE_5(_CALL, __VA_ARGS__)
#define _FE_7(_CALL, x, ...) _CALL(x) _FE_6(_CALL, __VA_ARGS__)
#define _FE_8(_CALL, x, ...) _CALL(x) _FE_7(_CALL, __VA_ARGS__)
#define _FE_9(_CALL, x, ...) _CALL(x) _FE_8(_CALL, __VA_ARGS__)
#define _FE_10(_CALL, x, ...) _CALL(x) _FE_9(_CALL, __VA_ARGS__)
#define _FE_11(_CALL, x, ...) _CALL(x) _FE_10(_CALL, __VA_ARGS__)
#define _FE_12(_CALL, x, ...) _CALL(x) _FE_11(_CALL, __VA_ARGS__)
#define _FE_13(_CALL, x, ...) _CALL(x) _FE_12(_CALL, __VA_ARGS__)
#define _FE_14(_CALL, x, ...) _CALL(x) _FE_13(_CALL, __VA_ARGS__)
#define _FE_15(_CALL, x, ...) _CALL(x) _FE_14(_CALL, __VA_ARGS__)
#define _FE_16(_CALL, x, ...) _CALL(x) _FE_15(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...)                                             \
    _NTH_ARG(__VA_ARGS__, _FE_16, _FE_15, _FE_14, _FE_13, _FE_12, _FE_11, _FE_10, \
             _FE_9, _FE_8, _FE_7, _FE_6, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1)    \
    (MACRO, __VA_ARGS__)

#define watch(x) cout << "\033[1;32m" #x " = \033[1;34m" << (x) << "\033[0m; " << endl;
#define debug(...)                                                             \
    cout << "\033[2;31mLine " << __LINE__ << ": \033[0;m" << endl;              \
    FOR_EACH_MACRO(watch, __VA_ARGS__)                                           \
    cout << "\n"

// ---------------------------------------------------------------------------
// Extra helpers
// ---------------------------------------------------------------------------

// debugi(v) -- print a 1-D container with indices: 0:val  1:val  ...
#define debugi(v)                                                              \
    do {                                                                       \
        cout << "\033[2;31mLine " << __LINE__ << ": \033[0;m" << #v << "\n";   \
        size_t _i = 0;                                                         \
        for (const auto &_e : (v)) {                                           \
            cout << COLOR_VAR << _i++ << COLOR_RESET << ":"                    \
                 << COLOR_VALUE << _e << COLOR_RESET << "  ";                  \
        }                                                                      \
        cout << "\n";                                                          \
    } while (0)

// debugg(g) -- print an adjacency list / 2-D container, one row per line
#define debugg(g)                                                              \
    do {                                                                       \
        cout << "\033[2;31mLine " << __LINE__ << ": \033[0;m" << #g << "\n";   \
        size_t _i = 0;                                                         \
        for (const auto &_row : (g)) {                                         \
            cout << COLOR_VAR << _i++ << COLOR_RESET << " -> "                 \
                 << _row << "\n";                                              \
        }                                                                      \
    } while (0)
