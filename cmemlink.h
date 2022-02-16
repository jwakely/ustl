// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2005 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.

#pragma once
#include "ualgobase.h"

/// The ustl namespace contains all ustl classes and algorithms.
namespace ustl {

class istream;
class ostream;
class ostringstream;

/// \class cmemlink cmemlink.h ustl.h
/// \ingroup MemoryManagement
///
/// \brief A read-only pointer to a sized block of memory.
///
/// Use this class the way you would a const pointer to an allocated unstructured block.
/// The pointer and block size are available through member functions and cast operator.
///
/// Example usage:
///
/// \code
///     void* p = malloc (46721);
///     cmemlink a, b;
///     a.link (p, 46721);
///     assert (a.size() == 46721));
///     b = a;
///     assert (b.size() == 46721));
///     assert (b.DataAt(34) == a.DataAt(34));
///     assert (0 == memcmp (a, b, 12));
/// \endcode
///
class cmemlink {
public:
    using value_type	= char;
    using pointer	= const value_type*;
    using const_pointer	= const value_type*;
    using reference	= value_type;
    using const_reference = value_type;
    using size_type	= size_t;
    using written_size_type = uint32_t;
    using difference_type = ptrdiff_t;
    using const_iterator = const_pointer;
    using iterator	= const_iterator;
    using rcself_t	= const cmemlink&;
public:
    inline constexpr	cmemlink (void)				: _data (nullptr), _size (0) { }
    inline constexpr	cmemlink (const void* p, size_type n)	: _data (const_pointer(p)), _size (n) { assert (p || !n); }
    inline constexpr	cmemlink (const cmemlink& l)		: _data (l._data), _size (l._size) {}
    inline virtual     ~cmemlink (void) noexcept		{}
    void		link (const void* p, size_type n);
    inline void		link (const cmemlink& l)	{ link (l.begin(), l.size()); }
    inline void		link (const void* first, const void* last)	{ link (first, distance (first, last)); }
    constexpr void	relink (const void* p, size_type n) { _data = static_cast<const_pointer>(p); _size = n; }
    virtual void	unlink (void) noexcept		{ _data = nullptr; _size = 0; }
    inline rcself_t	operator= (const cmemlink& l)	{ link (l); return *this; }
    constexpr bool	operator== (const cmemlink& l) const
							{ return l._size == _size && (l._data == _data || 0 == __builtin_memcmp (l._data, _data, _size)); }
    constexpr void	swap (cmemlink& l)		{ ::ustl::swap (_data, l._data); ::ustl::swap (_size, l._size); }
    constexpr size_type	size (void) const		{ return _size; }
    constexpr size_type	max_size (void) const		{ return size(); }
    constexpr size_type	readable_size (void) const	{ return size(); }
    constexpr bool	empty (void) const		{ return !size(); }
    constexpr const_pointer	data (void) const	{ return _data; }
    constexpr const_pointer	cdata (void) const	{ return _data; }
    constexpr iterator	begin (void) const		{ return iterator (cdata()); }
    constexpr iterator	iat (size_type i) const		{ assert (i <= size()); return begin() + i; }
    constexpr iterator	end (void) const		{ return iat (size()); }
    constexpr void	resize (size_type n)		{ _size = n; }
    void		read (istream&)			{ assert (!"ustl::cmemlink is a read-only object."); }
    void		write (ostream& os) const;
    size_type		stream_size (void) const noexcept;
    void		text_write (ostringstream& os) const;
    void		write_file (const char* filename, int mode = 0644) const;
private:
    const_pointer	_data;		///< Pointer to the data block (const)
    size_type		_size;		///< size of the data block
};

//----------------------------------------------------------------------

/// Use with cmemlink-derived classes to link to a static array
#define static_link(v)	link (VectorBlock(v))

} // namespace ustl
