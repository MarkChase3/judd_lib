# Second Chapter: Drawing

## GL Loader

Now we've made the OpenGL context, the window and can receive input, we are almost ready to do some drawings. But first, we need to setup the OpenGL functions. A OpenGL context allows us to load the functions, but it isn't automatic.
We will use the judd_core OpenGL context to do this, but you can use as easily other APIs.

For loading the functions, you can use a tool like glad, but we are nerds and I want to implement this with my own hands.
For start, we need to declare the functions in a global scope:

    /* WIP */
