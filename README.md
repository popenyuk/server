# Multi-threaded server on C.
## Tested on
```Linux(Ubuntu and WSL)
MinGW under Msys2```

## Team
```Zenovii Popenyuk
Markiian Matsiuk```

## Description
```The server that accepts the connection reads one letter from the client and, depending on it, sends in response:
	'd' -- the current date,
	't` -- the present time,
	'h' -- Hello or another fixed greeting.
	'm' - reads a formatted message from the client.
Written a multiuser version using pthread and WIN SOCKS.```
	

## Example of run:
### In general:
#### Server
    ```server <number> <number of threads>
	 -   Where number is PORT number
	 -  number of threads```
#### Client:
    ```client <address> <number> <type_of_message> <message>
	-   Where address is address of server.
	-   Where number is PORT number.
	-   Where message is your message that you send to server.```

### Example of compilation:
mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make
### Run server(one thread version):
./server 7500 1
### Run server(Multi thread version):
./server 7500 4
### Run client:
./client 127.0.0.1 7500 m "Hello World!"
### Remove compilation files:
cd .. && rm -R build
