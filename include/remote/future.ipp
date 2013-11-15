// Copyright 2013 Ng Kwan Ti <ngkwanti -at- gmail.com>
//
// This file is distributed under GPL v3 license. You can redistribute it and/or
// modify it under the terms of the GNU General Public License version 3 as
// published by the Free Software Foundation. See <http://www.gnu.org/licenses/>.
//
// See www.cppremote.com for documentation.
//-----------------------------------------------------------------------------
#ifndef __REMOTE_FUTURE_IPP__
#define __REMOTE_FUTURE_IPP__

#include <remote/future_error.hpp>
#include <remote/detail/result.hpp>

#include <boost/chrono.hpp>


namespace remote
{

template<typename T>
future<T>::future()
{}

template<typename T>
future<T>::future(impl_type const& impl)
: m_impl(impl)
{}

template<typename T>
future<T>::future(BOOST_RV_REF(future) src)
: m_impl(src.release())
{}

template<typename T>
future<T>& future<T>::operator = (BOOST_RV_REF(future) src)
{
	if(this != &src)
	{
		m_impl = src.release();
	}
	return *this;
}

template<typename T>
shared_future<T> future<T>::share()
{
	return shared_future<T>(release());
}


template<typename T>
typename future<T>::impl_type future<T>::release()
{
	impl_type impl = m_impl;
	m_impl.reset();
	return impl;
}


template<typename T>
bool future<T>::valid() const
{
	return m_impl;
}

template<typename T>
T future<T>::get()
{
	if(!valid())
		throw future_error(future_errc::no_state);

	return m_impl->get();
}

template<typename T>
bool future<T>::wait() const
{
	if(!valid())
		throw future_error(future_errc::no_state);

	return m_impl->wait();
}


template<typename T>
template<typename Rep, typename Period>
future_status future<T>::wait_for(boost::chrono::duration<Rep, Period> const& duration) const
{
	if(!valid())
		throw future_error(future_errc::no_state);

	return m_impl->wait_for(duration);
}

template<typename T>
template<typename Clock, typename Duration>
future_status future<T>::wait_until(boost::chrono::time_point<Clock, Duration> const& timeout_time)
{
	if(!valid())
		throw future_error(future_errc::no_state);

	return m_impl->wait_until(timeout_time);
}

}

#endif
