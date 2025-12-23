/*
 * File: fix/parser_impl.cpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#define OCL_FIX_HAS_IMPL
#include <ocl/fix/parser.hpp>

namespace ocl::fix
{

	namespace detail
	{
		inline const char* begin_fix() noexcept
		{
			return "FIX.4.2";
		}
	} // namespace detail

	struct visitor::impl final
	{
	public:
		static constexpr int	  soh  = '\x01';
		static constexpr char	  eq   = '=';
		static constexpr unsigned base = 10U;

		explicit impl() = default;
		~impl()			= default;

		impl& operator=(const impl&) = delete;
		impl(const impl&)			 = delete;

		/// @brief Visits a FIX message and parse it into a range_buffer object.
		/// @param in The input FIX message as a string.
		/// @warning This function may throw exceptions.
		range_buffer visit(const boost::string_view& in)
		{
			if (auto begin = detail::begin_fix(); begin != range_buffer::begin)
				range_buffer::begin = begin;

			range_buffer ret{};

			if (in.empty())
				return ret;

			std::string key;

			std::size_t off = 0UL;

			while (off < in.size())
			{
				std::size_t eq_pos = in.find(eq, off);
				if (eq_pos == std::string::npos)
					break;

				std::string tag = in.substr(off, eq_pos - off).to_string();

				std::size_t soh_pos = in.find(soh, eq_pos + 1);
				if (soh_pos == std::string::npos)
					soh_pos = in.size();

				std::string value = in.substr(eq_pos + 1, soh_pos - eq_pos - 1).to_string();

				if (ret.magic_.empty())
				{
					ret.magic_	   = value;
					ret.magic_len_ = value.size();
				}

				ret.message_[tag] = value;

				off = soh_pos + 1;
			}

			return ret;
		}
	};

	/// \brief Alias of visit.
	range_buffer visitor::operator()(const std::string& in)
	{
		return impl_->visit(in);
	}

	/// @brief Visits a FIX message and parse it into a range_buffer object.
	/// @param in The input FIX message as a string.
	/// @warning This function may throw exceptions.
	range_buffer visitor::visit(const std::string& in)
	{
		return impl_->visit(in);
	}

} // namespace ocl::fix
