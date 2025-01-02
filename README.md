Followed guides:

- [GLFW Getting Started guide](https://www.glfw.org/docs/latest/quick_guide.html)
- [GLFW Building applications guide](https://www.glfw.org/docs/latest/build_guide.html#build_link_osx)

## Resources

I'm following the [OpenGL Course from freecodecamp](https://youtu.be/45MIykWJ-C4).

In the middle I got a bit confused about all the buffers (VAOs, VBOs, etc.) so to better understand what buffers are in
OpenGL, [I watched From CPU to GPU: Understanding Data Transfer with Buffers in OpenGL](https://youtu.be/DsMohErqXzg).

### Buffers

First, I have to ask OpenGL for a buffer:

```c
int size = 1;
int bufferName; // this variable could be called VBO (Vertex Buffer Object)
glGenBuffers(size, &bufferName);
```

Then `bufferName` may be e.g., 124 (yes, this number is a name).

We now have a buffer name but it's empty.

Then the buffer has to be binded ("made bound") to specific target using `glBindBuffer`.
The target specifies how you intend to use the buffer (e.g., for vertex attributes, indices, etc.).

```c
glBindBuffer(GL_ARRAY_BUFFER, bufferName);
```

This tells OpenGL that the bufferName should now be used as the current buffer for the GL_ARRAY_BUFFER target.
The GL_ARRAY_BUFFER target is typically used for vertex attribute data.

Finally, I can put data into the buffer (this is the "from CPU to GPU" move of data) with `glBufferData`.

```c
// A simple triangle
GLfloat vertices[] = {
    0.5f, 0.5f, 0,
    1.5f, 0.5f, 0,
    1.0f, 1.5f, 0,
    };
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

> [!NOTE]
>
> Turns out there's quite a good official wiki on OpenGL: https://www.khronos.org/opengl/wiki/Main_Page.