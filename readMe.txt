Run instructions(compiled on a linux machine)

Problem 1:  $g++ Problem1.cpp -pthread
	    $./a.out

Problem 2:  $g++ Problem2.cpp -pthread
	    $./a.out


Problem 1)

	*quick note*: was confused about the wording "The guests may enter his labyrinth, one at a time..." so I'm going to assume this mean only one guest can be in the maze at a time and this assumption applies to my solution

	My impementation is similar to the to the solution presented in class:

		1.Label each guest beforehand
		2.A list is made by the entrance of the maze (shared memory in the form of a boolean list)
		3.guests are selected using random numbers
		4.As each guest enters the maze they will change their respective part of their list to true 
		5.when the whole list is true, all guests have entered
		6.check is done after every guest has entered
		

	Statement of correctness:
		The program simulates guests taking turns to enter a maze until all guests have entered. It uses an array of threads to represent each guest and a bool array to keep track of which guests have gone. The program uses a mutex to ensure that multiple threads do not enter the maze at once. The program uses a global flag to determine when a guest is allowed to enter the maze. The program waits until all guests have gone before terminating. Overall, the program is correct in that it simulates the problem as described.

	Statement of efficiency:
		The program uses threads to simulate the guests, which can be an efficient way to handle multiple concurrent tasks. The program also uses a mutex to prevent race conditions when multiple threads access shared data. However, the program uses a busy wait loop to determine when a guest is allowed to enter the maze, which can be inefficient since it consumes CPU time. A better approach would be to use a condition variable that allows threads to wait until the maze is empty.	
	Experiemntal evaluation:
		The program was successful since it only terminates once the task in done therefor all threads had entered the maze atleast once
	
Problem 2)

	The best solution is the 3rd one 

	"3) The third strategy would allow the quests to line in a queue. Every guest exiting the
	room was responsible to notify the guest standing in front of the queue that the
	showroom is available. Guests were allowed to queue multiple times"
	
	Advantages:
    		This approach ensures a fair and organized way of viewing the vase, as guests will be served in the order they join the queue.
    		The strategy guarantees that a guest will see the vase after waiting for their turn, as there is no chance of the room being occupied by someone else.
    	
	Disadvantages:
    		Guests have to wait in line, which may take some time, especially if there are many guests at the party.

	Statement of Correctness:

		The program above simulates a queue of guests waiting to visit a crystal vase in a dedicated showroom, where only one guest is allowed to enter the room at a time. The program uses threads to simulate the guests, and a mutex and condition variables to manage the queue.

		Correctness is achieved by ensuring that each guest waits in the queue until it is their turn to enter the room. This is achieved by using a mutex to ensure that only one guest can check the current state of the queue at any given time, and a condition variable to allow each guest to wait until it is their turn. The program also uses a random number generator to simulate the decision of each guest to visit the vase or not, ensuring that the program is not deterministic.

		To ensure that the program is correct, we can verify that the following properties hold:

    			Safety: Only one guest can enter the room at a time.
    			Liveness: Every guest eventually gets a turn to visit the vase.
    			Liveness: Guests are allowed to visit the vase multiple times.

		Efficiency:
			The program uses a mutex and two condition variables to manage the queue, which ensures that each guest waits in the queue until it is their turn to enter the room. The program also uses a random number generator to simulate the decision of each guest to visit the vase or not.	
		
		Experiemntal evaluation:
			The program was successful since it only terminates once the task in done therefor all threads had entered the maze atleast once