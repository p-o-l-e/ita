#include "hello_world.h"


int main (int argc, char *argv[]) 
{
    scroller hw(128, 256, "HELLO WORLD!", scroller::format::binary);
    hw.iterate(30);
    return 0;
}

void scroller::init() 
{ 
    offset = std::make_unique<int[]>(rows);
    std::srand(std::time({}));
    for(int x = 0; x < rows; ++x) offset[x] = -bounded_rand(spacing); 
};

const std::string scroller::convert(const std::string& str, const format& f)
{
    if(f == format::binary)
    {
        std::string r {};

        for(int i = 0; i < str.length(); ++i)
        {
            r += ' ';
            r.append(std::bitset<8>(str.at(i)).to_string().c_str());
        }

        return r;
    }
    return str;
}

const std::string scroller::next_line() 
{
    std::string line(rows, ' '); 
    for(int x = 0; x < rows; ++x)
    {
        if(offset[x] >= txt.length()) offset[x] = -bounded_rand(spacing);
        if(offset[x] < 0) line.at(x) = ' ';
        else line.at(x) = txt.at(offset[x]);

        offset[x]++;
    }
    return line;        
}

void scroller::iterate(const int& ms)
{
    while (true) 
    { 
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout<<next_line()<<"\n";
        if(_kbhit()) break;
    }
}

scroller::scroller() 
{ 
    init(); 
}
 
scroller::scroller(const int& _rows, const int& spaces, const std::string& text, const format& f): rows(_rows), txt(convert(text, f)), spacing(spaces)  
{ 
    init(); 
}; 

scroller::~scroller() {};

// https://www.flipcode.com/archives/_kbhit_for_Linux.shtml
// Linux (POSIX) implementation of _kbhit().
// Morgan McGuire, morgan@cs.brown.edu
#ifdef __linux__
int _kbhit() 
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}
#endif

// https://en.cppreference.com/w/cpp/numeric/random/rand
// https://www.pcg-random.org/posts/bounded-rands.html#debiased-modulo-once-javas-method

const unsigned bounded_rand(const unsigned& range)
{
    for (unsigned x, r;;)
        if (x = rand(), r = x % range, x - r <= -range)
            return r;
}
