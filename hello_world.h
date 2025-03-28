#ifdef __linux__
#include <sys/ioctl.h>
#include <termios.h>
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

class scroller 
{
    private:
        const std::string_view txt { "" };
        const unsigned spacing { 8 };
        const int rows { 8 };
        std::string line;
        std::unique_ptr<int[]> offset;
        void init();

    public:
        const std::string_view next_line();
        void iterate(const int& ms);
        scroller();
        scroller(const int&, const int&, const std::string_view&);
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
