// Color definitions
#define COLOR_RESET "\033[0m"
#define COLOR_VAR "\033[1;32m" // Green color for variables
#define COLOR_VALUE "\033[1;34m" // Blue color for values
#define COLOR_BRACKET_1 "\033[1;93m" // Light yellow for first level brackets
#define COLOR_BRACKET_2 "\033[1;96m" // Light cyan for second level brackets
#define COLOR_BRACKET_3 "\033[1;95m" // Light purple for third level brackets

// Operator overloads for custom types
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

// Macros for debug output
#define _NTH_ARG(_1, _2, _3, _4, _5, _6, N, ...) N
#define _FE_1(_CALL, x) _CALL(x)
#define _FE_2(_CALL, x, ...) _CALL(x) _FE_1(_CALL, __VA_ARGS__)
#define _FE_3(_CALL, x, ...) _CALL(x) _FE_2(_CALL, __VA_ARGS__)
#define _FE_4(_CALL, x, ...) _CALL(x) _FE_3(_CALL, __VA_ARGS__)
#define _FE_5(_CALL, x, ...) _CALL(x) _FE_4(_CALL, __VA_ARGS__)
#define _FE_6(_CALL, x, ...) _CALL(x) _FE_5(_CALL, __VA_ARGS__)
#define FOR_EACH_MACRO(MACRO, ...)                                             \
    _NTH_ARG(__VA_ARGS__, _FE_6, _FE_5, _FE_4, _FE_3, _FE_2, _FE_1)              \
    (MACRO, __VA_ARGS__)

#define watch(x) cout << "\033[1;32m" #x " = \033[1;34m" << (x) << "\033[0m; " << endl;
#define debug(...)                                                             \
    cout << "\033[2;31mLine " << __LINE__ << ": \033[0;m" << endl;              \
    FOR_EACH_MACRO(watch, __VA_ARGS__)                                           \
    cout << "\n"

