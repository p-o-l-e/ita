int _kbhit();

#elif defined _WIN32
#include <conio.h>
#else

#endif

#include <string_view>

#include <stdio.h>
#include <cstdlib>
#include <memory>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include <bitset>

class scroller 
{
    public:
        enum class format { binary, string };
    
    private:
        const std::string txt { "" };
        const unsigned spacing { 8 };
        const int rows { 8 };
        std::unique_ptr<int[]> offset;
        static const std::string convert(const std::string&, const format&);
        void init();

    public:
        const std::string next_line();
        void iterate(const int& ms);
        scroller();
        scroller(const int&, const int&, const std::string&, const format&);
       ~scroller();
};

// https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
// Linux (POSIX) implementation of _kbhit().
// Morgan McGuire, morgan@cs.brown.edu
#ifdef __linux__
int _kbhit();
#endif

// https://en.cppreference.com/w/cpp/numeric/random/rand
// https://www.pcg-random.org/posts/bounded-rands.html#debiased-modulo-once-javas-method
const unsigned bounded_rand(const unsigned& range);
