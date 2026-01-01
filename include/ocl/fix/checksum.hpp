/*
 * File: fix/checksum.hpp
 * Purpose: Financial Information Exchange checksum in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_FIX_CHECKSUM
#define __OCL_FIX_CHECKSUM

#include <ocl/fix/detail/config.hpp>
#include <ocl/fix/parser.hpp>
#include <boost/core/detail/string_view.hpp>

namespace ocl::fix
{

	/// \brief Returns the checksum index of a FIX message.
	/// \param range the range_buffer containing the message.
	/// \throws runtime_error if the FIX message is invalid (missing tag "8").
	inline std::string try_index_checksum(range_buffer& fix)
	{
		if (fix.is_valid())
			return fix["10"];
		else
			detail::throw_runtime_error();
	}

	/// \brief FIX message operators namespace.
	namespace operators::fix
	{
		using checksum_type = long long;

		/// \brief Calculates the FIX protocol checksum for a message.
		/// \param in_ Pointer to the message buffer.
		/// \param len Length of the message in bytes.
		/// \return The checksum value (sum of all bytes modulo 256).
		inline constexpr checksum_type
			checksum(const char* in_,
				 const std::size_t  len)
		{
			if (len < 1)
				return 0L;

			checksum_type cks{};

			for (std::size_t idx{}; idx < len; ++idx)
			{
				cks += static_cast<uint8_t>(in_[idx]);
			}

			return cks % 256;
		}
	} // namespace operators::fix

} // namespace ocl::fix

#endif
