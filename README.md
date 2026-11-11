# E-Class - Desktop E-Learning and Class Management Application

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt6-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-003B57?style=for-the-badge&logo=sqlite&logoColor=white)

A lightweight and high-performance desktop application developed in **C++** to digitize and centralize educational interactions between professors and students. 

Developed as part of the Object-Oriented Programming module (Semester 4) at the Faculty of Sciences of El Jadida (Chouaïb Doukkali University).

## About the Project

Higher education requires a fast, organized, and accessible digital extension. Manual management (emails, USB flash drives, WhatsApp) quickly shows its limitations and leads to disorganization. 

E-Class addresses this issue by providing a centralized solution, avoiding the overhead of heavy web platforms. The application is designed to be ergonomic and focused on essential features, while offering low-level control over hardware resources through C++.

## Architecture & Technical Choices

This project is not merely functional; it was designed with strict architectural rigor (UML Modeling, Relational Database Schema):

*   **Adapted MVC Architecture:** The system strictly separates the graphical user interface (View) from the control logic and data access (Model/Database). The database class acts as an independent controller. The advantage? The backend can be migrated from SQLite to PostgreSQL or MySQL by modifying a single class.
*   **Lazy Loading & RAM Optimization:** Instead of loading and storing all associated objects in RAM during execution—risking memory waste—the application stores only the IDs of associated instances in the database. Full data is fetched only at the exact moment it is needed.
*   **Memory Management (QWidgets):** The application heavily utilizes polymorphism and dynamic casting (`dynamic_cast`) to adapt views (e.g., Professor vs. Student Dashboard) on the fly. To prevent memory leaks during navigation, the `Qt::WA_DeleteOnClose` attribute is assigned to windows to ensure proper memory deallocation upon closing.

## Core Features

### Professor Dashboard
*   **Class Management:** Create virtual classrooms with unique access code generation (based on QDateTime).
*   **Resources & Assignments:** Upload documents (.pdf, .docx, etc.) and video lectures with secure local duplication and archiving. Assign homework with strict deadlines and guidelines.
*   **Interactions:** Approve or deny student access requests.
*   **Communication:** Publish global announcements and provide centralized responses to student questions.

### Student Dashboard
*   **Course Access:** Search for classes using a unique code and send enrollment requests.
*   **Resources:** View and download course materials, videos, and assignments.
*   **Tracking & Q&A:** Ask questions directly to professors and track the status of replies.
*   **Dashboard:** A comprehensive overview of announcements, enrolled classes, and recent activity.

## Development Environment

*   **Language:** C++ (Backend Logic)
*   **Graphical Interface:** Qt6 Framework (Widgets, QSS for CSS-like styling)
*   **Database:** SQLite (DB Browser)
*   **Tools & Modeling:** CLion, Qt Designer, Git, Astah UML

## Installation & Compilation

1. Ensure you have a C++ compiler installed (GCC/MinGW) as well as CMake.
2. Install the **Qt6** Framework libraries (including Qt SQL for database management).
3. Clone this repository:
   ```bash
   git clone [https://github.com/Med-Atir/e-class.git](https://github.com/Med-Atir/e-class.git)
4. Open the project in your IDE (recommended: CLion or Qt Creator).

5. Compile and run the project. Note: The SQLite .db database file must be placed in the active execution directory.

## License

This project is licensed under the MIT License - see the LICENSE file for details. You are free to use, modify, and distribute this software for academic, personal, or commercial purposes.
Third-Party Software

    Qt 6: This project dynamically links to the Qt 6 Framework, utilized under the terms of the GNU Lesser General Public License v3 (LGPLv3). Qt is a registered trademark of The Qt Company Ltd. This project complies with LGPLv3 by dynamically linking Qt libraries and not modifying the Qt source code.

Developed by Mohammed Atir.
