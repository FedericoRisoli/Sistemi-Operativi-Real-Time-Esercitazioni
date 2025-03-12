Esercizio 1 

●Try to execute a server process on one terminal, and executes different clients in different terminals
○ If you want, modify the server or client behavior
●Exercise: Implement a Client that perform multiple concurrently requests
○ Each Client must create multiple concurrent instances.
○ Each instance generates a unique number and sends it to the server, receives a response and
prints the sent and the received number.
○ Server simply take the number and add 1.
○ TIPS:
■ unique seed: srand(time(NULL) + ??? )
■ use sleep() to see client child processes prints (or loop wait())
