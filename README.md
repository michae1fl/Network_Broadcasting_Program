# Network_Broadcasting_Program
Sample Network Broadcasting Project

Overview

  This program is designed to assist in the planning and optimization of a
distribution network for an internet-based television system. It leverages an
existing network of interconnected computers, located in various cities, to
determine the most efficient server configurations for content distribution.


Description

  The program models the network as a directed graph where each node represents a
computer named after its city. Edges between nodes symbolize network
connections with varying delay times. It's important to note that these 
connections are directional and can have different delays in each direction.

  The core functionality of the program is to identify the optimal 'servers'
within the network. These servers should be capable of transmitting content to
every other computer in the network with the minimum total delay. The total 
transmission delay from a server to the entire network is calculated as the sum
of the minimum delay times from the server to each computer.


Input

The input is a description of the network's existing configuration:
The first line contains an integer N (1 ≤ N ≤ 4000), representing the number of
network connections. 
The next N lines describe each directed connection: two connected computers' 
names and a connection delay, separated by spaces.
Computer names consist of 1 to 40 lowercase English letters or underscores.
Delays are integers (0 to 100 milliseconds).
Only computers with names ending in "_server" can be servers (max 50 servers).


Output

The program outputs the most efficient server configuration:
If no server can serve the entire network, it prints "no server can serve the
whole network."
If possible, it prints "total delay: x", where x is the shortest total delay
time.
Following this, it lists all servers capable of serving the entire network with
this delay, in alphabetical order.


Key Features

  Efficient graph-based representation of the network.
Identification of potential servers based on specific naming conventions.
Calculation of minimum transmission delays using optimized algorithms.
Output of the most efficient server(s) and corresponding total transmission
delay.


Usage

  This program is ideal for network administrators and planners involved in 
setting up or optimizing distribution networks for digital content, 
particularly in internet-based television systems. It offers a practical and
automated approach to identify the most efficient server configuration, 
ensuring minimal transmission delays in content delivery.
