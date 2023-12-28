My C++ Web Server implementation using modern C++17/20.

For the concurrency model, I'm using a thread pool manually implemented with the C++ standard libraries but could be easily substituted by another model, for example, Boost.Asio libraries.

For networking, I'm using traditional sockets but these can be easily substituted by using Qt Network C++ Classes, for example.

For HTTP handling I just wrote a skeleton. I'm still working on implementing a robust and customized HTTP handler with SSL support and a REST API, or I can opt to use a framework.

Everything is reusable, scalable, testable, adaptable, and optimized.
