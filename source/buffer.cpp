/*
MIT License

Copyright (c) 2019 Pranav Bhatnagar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Modified by Jeff Martin
*/

#include "buffer.hpp"

Buffer::Buffer() {
    buf.push_back("");
    line = 0;
    size = 1;
}

void Buffer::setLine(int n) {
    if (n > size)
        return;
    else
        line = n;
}

int Buffer::getLine() {
    return line;
}

void Buffer::display() {
    setLine(0);
    for (auto str : buf)
        std::cout << str << std::endl;
}

void Buffer::clear() {
    std::vector<std::string> t(1, "");
    buf = t;
}

Buffer &operator<<(Buffer &curr, const std::string &str) {
    if (str == "\n")
    {
        if (curr.line == curr.size - 1)
        {
            curr.buf.push_back("");
            ++curr.line;
            ++curr.size;
        }
        else
        {
            ++curr.line;
        }
    }
    else
        curr.buf[curr.line] += str;
    
    return curr;
}
