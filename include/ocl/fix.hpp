/*
 * File: fix.hpp
 * Purpose: Financial Information Exchange function and headers in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef OCL_FIX_HPP
#define OCL_FIX_HPP

#include <ocl/fix/detail/config.hpp>
#include <ocl/fix/checksum.hpp>
#include <ocl/fix/parser.hpp>

namespace ocl::fix
{

	template <typename It, class Pred>
	Pred find(It begin, It end, Pred callable);

	template <typename It, class Pred>
	Pred find_if(It begin, It end, Pred callable);

	template <typename It, class Pred>
	typename Pred::size_type erase(It begin, It end, Pred callable);

	template <typename It, class Pred>
	typename Pred::size_type erase_if(It begin, It end, Pred callable);

} // namespace ocl::fix

#endif
