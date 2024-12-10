<h1 align="center">
    Server-Client Implementation
</h1>

## 🤷🏻 About
### Overview

This project implements a simple server-client application in C that supports multiple clients. The clients can send mathematical expressions (e.g., 3 + 4, 5 * 6) to the server, which evaluates the expressions and sends the results back to the respective clients.

### Features
**1. Multi-client Support: The server can handle multiple clients simultaneously.**

**2. Math Expression Parsing: The server evaluates basic mathematical expressions sent by the clients.**

**3. Environment Configuration: Uses a .env file for configurable settings like logs, server host, and port.**

**4. Simple Communication: The application uses basic socket programming for communication.**

### Prerequisites
**dotenv: Ensure that the application can parse environment variables from a .env file.**


## Configuration
### Set up environment variables:

   The application uses a .env file located in the root of the project directory to manage configurable settings.
   Create a .env file in the root of the project and include the following content:
   ```dotenv
        SERVER_LOGS_FILE="/home/gehovhan/Desktop/multi-clean-operation/log/server-logs.log"
        CLIENT_LOGS_FILE="/home/gehovhan/Desktop/multi-clean-operation/log/client-logs.log"
        SERVER_HOST="127.0.0.1"
        SERVER_PORT="8008"
        BACK_LOG="100"
   ```

## 🛠️ Usage

### Instructions

**1. Compiling the program**

To compile the program, run:

```shell
$ cd multi-clean-operation
```
```shell
$ make server
```

```shell
$ make client
```

**2. Executing the program**

To execute the program, run:

```shell
$ ./server
```

```shell
$ ./client
```
