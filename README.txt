Tested on:
    - Linux(Ubuntu and WSL)
    - MinGW under Msys2


Team:
	Zenovii Popenyuk
	Yevhenii Molodtsov
	Markiian Matsiuk

Description:
	Написаний для Linux та Windows. Також зроблене перше додаткове завдання.
	Додано q.
	Для того щоб скористатися функцією m під час введення ітеративно команд, необхідно спочатку ввести m, натиснути Enter, а потім ввести повідомлення.

Example of run:
    In general:
        Server:
            server <number> <number of threads>
                 -   Where number is PORT number
                 -  number of threads
        Client:
            client <address> <number> <type_of_message> <message>
                -   Where address is address of server.
                -   Where number is PORT number.
                -   Where message is your message that you send to server.

    Wxample of compilation:
        mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make
    Run server(one thread version):
        ./server 7500 1
    Run server(Multi thread version):
        ./server 7500 4
    Run client:
        ./client 127.0.0.1 7500 m "Hello World!"
    Remove compilation files:
        cd .. && rm -R build