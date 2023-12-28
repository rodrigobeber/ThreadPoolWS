C++ Web Server with Sockets and a Thread Pool using only the standard libraries. I applied design patterns and high scalability. My next steps are handling SSL, parsing HTTP headers, writing a REST API, and tests with Google Test and Google Mock.

Everything is reusable, scalable, testable, adaptable, and optimized.

For the concurrency model, I'm using a thread pool manually implemented with the C++ standard libraries but could be easily substituted by another model, for example, Boost.Asio libraries.

For networking, I'm using traditional sockets but these can be easily substituted by using Qt TCP Server, for example.

For HTTP handling I just wrote a skeleton. I'm still working on implementing a robust and customized HTTP handler with SSL support and a REST API, or I can opt to use the Qt framework, for example.