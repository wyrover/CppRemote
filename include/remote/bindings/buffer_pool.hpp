// Copyright 2013 Ng Kwan Ti <ngkwanti -at- gmail.com>
//
// This file is distributed under GPL v3 license. You can redistribute it and/or
// modify it under the terms of the GNU General Public License version 3 as
// published by the Free Software Foundation. See <http://www.gnu.org/licenses/>.
//
// See www.cppremote.com for documentation.
//-----------------------------------------------------------------------------
#ifndef __REMOTE_BINDINGS_DETAIL_BUFFERPOOL_H__
#define __REMOTE_BINDINGS_DETAIL_BUFFERPOOL_H__

#include <remote/bindings/buffer.hpp>

#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>
#include <vector>


namespace remote
{
namespace bindings
{

class buffer_pool : boost::noncopyable
{
public:
	explicit buffer_pool(std::size_t size);

	buffer_ptr allocate();

	void collect();
	void collect_one();

private:
	typedef std::vector<buffer_ptr> buffers_type;

private:
	mutable boost::mutex m_mutex;
	std::size_t m_size;
	buffers_type m_buffers;

	static bool is_unique(buffer_ptr const& buf);
};

}
}

#endif

