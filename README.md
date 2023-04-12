# Runner

Keep your head out of the clouds!

For this project, you will use C++ graphics with classes to create an interactive runner scene.

You may work individually or with a partner of your choosing.

Note to Windows users: remember to copy freeglut.dll from the cmake-build-debug folder of the Graphics-Starter activity
to the cmake-build-debug folder here.

Note to Mac users: if you are running Catalina, remember to multiply the width and height by 2 in the glViewport line.

Note to Linux users: remember to use the alternate CMakeLists.txt from the Graphics-Starter activity.

## Setup

Use this Guided Project template to create a new repository (
see [GitHub-with-CLion](https://github.com/uvmcs120s2023/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Runner-netid**, where netid is your UVM NetID username.

* If you are collaborating, the format is Runner-netid1-netid2. Have one partner create the repository and give the
  other partner access on GitHub: on the repository page, go to the Settings tab, choose Manage Access, and add the
  person with their GitHub username.

Remember to commit and push frequently.

# Requirements

1. Read through the header and .cpp files for Shape, Circle, and Rect.
    * Note: "Rectangle" is a keyword on some Windows machines, which can cause problems if you also create a data type
      named Rectangle. Hence the abbreviated name "Rect" for the class.
    * Note: There are many methods implemented in this project that are not used. These classes are robust with the
      intention that you use them for open-ended projects.
1. Implement the methods in Rect.cpp that have TODO comments.
1. Read through graphics.cpp. Notice the global objects at the top of the file.
1. Implement the TODO parts of graphics.cpp to initialize and move the rest of the buildings and the user's block.
1. Run the program. The user block should make the buildings change color when it overlaps with them, and the program
   should exit when the user block overlaps with a cloud.

## Grading

If you are collaborating, both partners have to submit the project.

### Grading Rubric

- [ ] (2 pts) Implement draw method in the Rect class.
- [ ] (2 pts) Implement isOverlapping method in the Rect class.
- [ ] (16 pts) Implement all TODOs in graphics.cpp.

## Notes:

- I chose to have rectangles "overlapping" when they are exactly adjacent to each other (so, <= rather than just <)
  because this kind of check will be useful for things like game development! Even if tangential rectangles may not be
  technically "overlapping."