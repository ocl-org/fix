/*
 * File: detail/config.hpp
 * Purpose: Config file of the OCL.FIX library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_FIX_CONFIG
#define __OCL_FIX_CONFIG

#include <ocl/detail/config.hpp>
#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>

namespace ocl::fix::detail
{

	inline void throw_runtime_error(const boost::source_location& location = BOOST_CURRENT_LOCATION)
	{
		throw std::runtime_error(location.to_string());
	}

	inline void unreachable() noexcept
	{
#if defined(__GNUC__) || defined(__clang__)
		__builtin_unreachable();
#elif defined(_MSC_VER)
		__assume(false);
#else
		std::abort();
#endif
	}

} // namespace ocl::fix::detail

#endif
