#include <iostream>
#include "server.cpp"



int main()
{
    try
    {
	    // io_context предоставляет службы ввода-вывода, которые будет использовать сервер, такие как сокеты.
        boost::asio::io_context io_context;
        TcpServer server(io_context);

        // Запуск асинхронных операций.
        io_context.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}

