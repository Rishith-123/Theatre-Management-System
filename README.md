# Theatre-Management-System
**Theatre Management Project Readme**

This readme file provides an overview of the Theatre Management Project implemented in C++ using Leftist Heap Tree, AVL Tree, and Splay Tree. The project focuses on creating a system for theatre management, allowing administrators to add or remove movies and enabling users to book tickets.

**Project Overview:**
The Theatre Management Project is designed to streamline the process of managing movies and ticket bookings in a theatre. It employs three different types of trees for efficient data management:

1. **Leftist Heap Tree:**  Employed for user-specific functionalities, such as booking tickets. This tree optimizes the search for a particular user, bringing them to the root of the tree for faster access in subsequent operations.

2. **AVL Tree:** Used for storing information about booked tickets. This self-balancing binary search tree maintains the balance of the tree, ensuring quick retrieval and modification of ticket booking details.

3. **Splay Tree:** Used for managing the list of movies and their details. This data structure ensures that the movies are ordered based on some criteria (e.g., release date) while providing efficient insertion and removal operations.

**Functionalities:**
The project offers the following functionalities:

**For Administrators:**
1. **Add Movie:** Administrators can add new movies to the theatre's collection. Details such as movie name, release date, genre, and cast can be added.

2. **Remove Movie:** Administrators can remove movies that are no longer being screened.

**For Users:**
1. **Browse Movies:** Users can browse the list of available movies, sorted based on the chosen criterion (e.g., release date).

2. **Book Tickets:** Users can select a movie and book tickets for specific showtimes. They can choose the number of tickets and the desired seats.

3. **View Booked Tickets:** Users can view their booked tickets and the details associated with each booking.

4.**Edit Personal Details** Users can edit their personal details. 

**Tree Implementation:**
1. **Leftist Heap Tree:** Leftist Heap trees are utilized for user-specific operations like booking tickets. The tree is splayed (restructured) with each access, bringing the accessed node to the root for quicker future access.

2. **AVL Tree:** The AVL tree is used to store booking information. Each node in the tree contains data about a particular booking, such as the user's name, booked seats, and showtime. The tree is self-balancing, ensuring quick access to booking information.

3. **Splay Tree:**  This tree is employed to maintain the list of movies. Movies are ordered based on their release dates, with the movie released earliest at the root. This tree allows efficient addition and removal of movies.

**Usage:**
1. The project can be compiled using a C++ compiler that supports C++11 or later.

2. Run the compiled executable to start the theatre management system.

3. The system will provide options for both administrators and users. Administrators can manage movies, while users can explore movies and book tickets.

**Note:** This readme provides a high-level overview of the Theatre Management Project. To understand the implementation details and algorithms used for the various tree structures, refer to the source code and relevant documentation.

**Contributors:**
- V.Rishith Kumar, B.Agilan, V.S.Athiraj
