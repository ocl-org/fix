#include <ocl/unique_socket.hpp>
#include <ocl/print.hpp>

/// @brief Basic Send test
int main()
{
	ocl::unique_socket sock = ocl::unique_socket::make_socket<8005>(ocl::unique_socket::any_address, true);

	char buf_dst[512] = {"HELLO, WORLD\0"};

	ocl::unique_socket sock2 = ocl::unique_socket::make_socket<8005>(ocl::unique_socket::any_address, false);

	char buf_dst2[512] = {0};

	auto new_sock = sock.accept();
	new_sock.write_from_buffer(buf_dst, strlen(buf_dst));
	sock2.read_client_buffer(buf_dst2, strlen(buf_dst));
	std::cout << "result:" << buf_dst2 << "\n";


	return EXIT_SUCCESS;
}
