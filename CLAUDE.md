# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

OCL.FIX is a C++20 library for parsing Financial Information Exchange (FIX) protocol messages. The library is part of the Open C++ Libraries (OCL) family and follows the Boost Software License.

## Build System

The project uses CMake as its build system.

### Building the Library

```bash
# Configure and build from project root
cmake -B build
cmake --build build

# Install the library
cmake --install build
```

### Building and Running Tests

Tests use Google Test and are located in `test/fix_basic/`:

```bash
# Build and run all tests
cd test/fix_basic
cmake -B build
cmake --build build
cd build && ctest

# Run specific test binary directly
./FIXTestBasic
```

### Building Examples

```bash
cd example/fix_tag_example
cmake -B build
cmake --build build
./build/FixExample
```

## Architecture

### Core Components

1. **Parser (`include/ocl/fix/parser.hpp`, `src/fix/parser_impl.cpp`)**
   - `ocl::fix::visitor`: The main parser class using the Pimpl idiom
   - `ocl::fix::range_buffer`: Container for parsed FIX message tags and values
   - `ocl::fix::range`: Buffer+Length structure for byte ranges
   - FIX message format: SOH-delimited (0x01) tag=value pairs

2. **Implementation Pattern**
   - Uses Pimpl (Pointer to Implementation) idiom to hide implementation details
   - `visitor::impl` is defined in `parser_impl.cpp` and forward-declared in the header
   - Conditional compilation controlled by `OCL_FIX_HAS_IMPL` macro
   - When `OCL_FIX_HAS_IMPL` is not defined, a stub `impl` struct is provided

3. **FIX Message Parsing**
   - Parses tag=value pairs separated by SOH (Start of Header, 0x01) character
   - Tag "8" contains the FIX version (e.g., "FIX.4.2")
   - `range_buffer::operator[]` retrieves values by tag number
   - `range_buffer::is_valid()` checks if tag "8" exists

### Dependencies

- **OCL.Core**: Parent library providing `ocl/detail/config.hpp`, `ocl/crc_hash.hpp`, and `ocl/print.hpp`
- **Boost**: Required for `boost::string_view` and other utilities
- **C++20**: Required for language features

### Directory Structure

```
include/ocl/fix/          # Public API headers
  parser.hpp              # Main parser interface
  checksum.hpp            # Checksum utilities (currently stub)
  detail/config.hpp       # Configuration and OCL dependencies
src/fix/                  # Implementation
  parser_impl.cpp         # Parser implementation with Pimpl
test/fix_basic/           # Google Test unit tests
example/fix_tag_example/  # Example usage
```

## Development Notes

### Code Style

- C++20 standard enforced
- Includes `.clang-format` configuration
- Run `./format.sh` to format code

### Working with the Parser

When modifying the parser:
- Implementation goes in `src/fix/parser_impl.cpp` with `OCL_FIX_HAS_IMPL` defined
- Public API changes go in `include/ocl/fix/parser.hpp`
- The `visitor::impl` struct contains the actual parsing logic
- Remember to handle both the constructor initialization and the Pimpl pointer

### Testing

- Test files should verify both valid and invalid FIX messages
- Use constexpr character arrays with SOH (0x01) separators for test messages
- Verify tag retrieval returns correct values and empty strings for missing tags
