// Copyright (C) 2019 T. Zachary Laine
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#include <boost/iterator_facade/iterator_facade.hpp>

#include <cassert>


//[ repeated_chars_iterator
struct repeated_chars_iterator : boost::iterator_facade::iterator_facade<
                                     repeated_chars_iterator,
                                     std::random_access_iterator_tag,
                                     char,
                                     char const>
{
    constexpr repeated_chars_iterator() noexcept :
        first_(nullptr),
        size_(0),
        n_(0)
    {}
    constexpr repeated_chars_iterator(
        char const * first, difference_type size, difference_type n) noexcept :
        first_(first),
        size_(size),
        n_(n)
    {}

private:
    friend boost::iterator_facade::access;
    char const dereference() const { return first_[n_ % size_]; }
    void advance(std::ptrdiff_t i) { n_ += i; }
    auto compare(repeated_chars_iterator other) const { return n_ - other.n_; }

    char const * first_;
    difference_type size_;
    difference_type n_;
};
//]


int main()
{
    //[ repeated_chars_iterator_usage
    repeated_chars_iterator first("foo", 3, 0); // 3 is the length of "foo", 0 is this iterator's position.
    repeated_chars_iterator last("foo", 3, 7);  // Same as above, but now the iterator's position is 7.
    std::string result;
    std::copy(first, last, std::back_inserter(result));
    assert(result == "foofoof");
    //]
}
