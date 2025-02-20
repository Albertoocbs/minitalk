# MINITALK

<p align="center">
  <a href="https://github.com/Albertoocbs/minitalk">
    <img src="https://github.com/Albertoocbs/minitalk/blob/main/minitalk.png" width="100"/>
  </a>
</p>

The purpose of this project is to code a small data exchange program using UNIX signals. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.ighly interesting new concept in C programming: static variables.</small>

---
**Status**

Finished: 2025-02-25. Grade: 100/100.

-------
**Overview**

The goal of the Minitalk project is to develop a simple program that allows processes (= programs running on a computer) to communicate with each other using a communication protocol called "minitalk". It corresponds to the protocol that you need to code.
The minitalk communication protocol involves sending messages between two processes using a series of signals over a single wire. 
One process, called the "speaker/client" sends the message by transmitting a series of signals over the wire. 
The other process, called the "listener/server" receives the message by interpreting the series of signals as a message.

![Captura de pantalla 2025-02-10 a las 16 23 35](https://github.com/user-attachments/assets/64fdfc54-16f5-4ff8-8f60-29cf01ad1e78)

-------

 ## **Usage**

Minitalk is a project that allows **inter-process communication** using Unix signals.  
A client sends messages **bit by bit** to a server, which reconstructs and prints them.

---

**🛠️ Compilation**

To compile the project, run:
```sh
make
```

This will generate two executables:

server → Listens for signals and reconstructs messages.
client → Sends messages to the server.
To clean compiled files run:
```sh
make clean
```

To remove executables and compiled files run:
```sh
make fclean
```

To fully recompile the project run:
```sh
make re
```

**🖥️ Running the Server**

Before sending messages, you must start the server run:
```sh
./server
```

This will print the server's PID (Process ID).
Example output:
```sh
Server PID: 12345
```

💡 Keep this PID! You will need it to send messages from the client.

## 📡 Sending Messages with the Client
To send a message to the server, use:
```sh
./client <server_pid> "<message>"
```

<server_pid> → Replace with the PID printed by the server.
"<message>" → The message to send (must be inside quotes).

Example:
```sh
./client 12345 "Hello, world!"
```

The server will then print:
```sh
Hello, world!
```

**📌 Important Notes**
 - The server must be running before sending a message.
 - The client sends messages character by character, bit by bit using SIGUSR1 and SIGUSR2.
 - The server will automatically detect the end of a message and print a newline.
 - The server can handle multiple messages, but each client call sends only one message at a time.

------

Here is a useful guide to understand this project: https://42-cursus.gitbook.io/guide/rank-02/minitalk
