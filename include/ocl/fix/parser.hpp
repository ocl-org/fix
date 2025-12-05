/*
 * File: fix/parser.hpp
 * Purpose: Financial Information Exchange parser in C++
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_FIX_PARSER
#define __OCL_FIX_PARSER

#include <ocl/fix/detail/config.hpp>
#include <string>

namespace ocl::fix
{
	class visitor;
	struct range;
	class range_buffer;

	/// @brief Buffer+Length structure
	using range_ptr_type = range*;

	using tag_type	 = std::string;
	using value_type = std::string;

	namespace detail
	{
		inline const char* begin_fix() noexcept
		{
			return "FIX.4.2";
		}
	} // namespace detail

	struct range final
	{
		char*  bytes_{nullptr};
		size_t length_{};

		bool is_valid() noexcept
		{
			return this->bytes_ && this->length_ > 0;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief Convert range to usable string.
	/// @note This function assumes that the range is valid and contains ASCII bytes.
	inline std::string to_string(range& range) noexcept
	{
		if (range.length_ < 1)
			return std::string{};

		return std::string(range.bytes_, range.length_);
	}

	/// @brief a range object containing the FIX packet values.
	class range_buffer final
	{
	public:
		std::size_t					magic_len_{};
		std::string					magic_{};
		string_hash_map<value_type> message_{};

		static inline const char* begin = detail::begin_fix();

		explicit range_buffer() = default;
		~range_buffer()			= default;

		range_buffer& operator=(const range_buffer&) = default;
		range_buffer(const range_buffer&)			 = default;

		value_type operator[](const tag_type& key)
		{
			if (key.empty())
				return value_type{};

			auto it = message_.find(key);
			if (it != message_.end())
				return it->second;

			return value_type{};
		}

		bool is_valid()
		{
			return this->operator[]("8").empty() == false;
		}

		explicit operator bool()
		{
			return this->is_valid();
		}
	};

	/// @brief visitor object which returns a fix::range_buffer instance.
	class visitor final
	{
	public:
		/// AMLALE: Yeah...
		static constexpr const int	soh	 = '\x01';
		static constexpr const char eq	 = '=';
		static constexpr uint32_t	base = 10U;

		explicit visitor() = default;
		~visitor()		   = default;

		visitor& operator=(const visitor&) = default;
		visitor(const visitor&)			   = default;

		range_buffer operator()(const std::string& in)
		{
			return this->visit(in);
		}

		/// @brief Visit a FIX message and parse it into a range_buffer object.
		/// @param in The input FIX message as a string.
		/// @warning This function may throw exceptions.
		range_buffer visit(const std::string& in)
		{
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

				std::string tag = in.substr(off, eq_pos - off);

				std::size_t soh_pos = in.find(soh, eq_pos + 1);
				if (soh_pos == std::string::npos)
					soh_pos = in.size();

				std::string value = in.substr(eq_pos + 1, soh_pos - eq_pos - 1);

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
} // namespace ocl::fix

#endif // ifndef __OCL_FIX_PARSER