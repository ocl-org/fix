#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;

    std::hash<ocl::crc_hash_trait> hash{};

    ocl::io::enable_stdio_sync(false);
	ocl::io::print(hash(argv[1]));

	return 0;
}
