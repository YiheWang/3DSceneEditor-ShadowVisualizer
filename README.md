# 3DSceneEditor-ShadowVisualizer

## Introduction
This is a simple 3D scene editor writen by C++ and OpenGL. Users are allowed to create, edit and delete multiple 3D objects by using mouse and keyboard. There are two light sources in the scene. One is directional light and one is point light.

## Techniques
- Mesh file reading and creating multiple objects.
- Objects rendering using **Phong lighting**.
- **Mouse picking** for 3D objects. 
- 3D object **scaling, translation, rotation and deletion**.
- Camera moving using **trackball control**.
- Using **texture** to render floor.
- Light source moving.
- **Directional shadow mapping** and **omnidirectional shadow mapping**.
- Simple circular motion **animation**.

## Play The App
  Find floder ***cmake-build-debug***, click ***FinalProject_bin.exe*** in the floder.
### Mouse Controls:
 - Use mouse to pick the object you want to play with.
 - Scroll mouse to Stretch camera view.

### Keyboard Controls:
#### 1) Create Objects
*Tip: All the object will be add to scene at origin initially.* 
 - **Key1**: add an unit cube 
 - **Key2**: add a bumpy cube 
 - **Key3**: add a bunny

#### 2) Edit Objects
*Tip: When you picking an object, the color of that object will change, then you can use keyboard to edit it.*
	
 - **KeyF**: positive object translation on x axis
 - **KeyG**: negative object translation on x axis
 - **KeyH**: positive object translation on y axis
 - **KeyJ**: negative object translation on y axis
 - **KeyK**: positive object translation on z axis
 -  **KeyL**: negative object translation on z axis
 - **KeyEqual**: scale object up
 - **KeyMinus**: scale object down
 - **KeyX**: rotate object around x axis
 - **KeyY**: rotate object around y axis
 -  **KeyZ**: rotate object around z axis
 - **KeyDelete**: delete the chosen object

#### 3) Camera Moving
*Tip: Functions of Q and E is same as scrolling mouse.*
 -  **KeyW** and **KeyS**: move camera up and down on sphere coordinate
 - **KeyA** and **KeyD**: move camera left and right on sphere coordinate
 -  **KeyQ** and **KeyE**: strench the camera view
 

#### 4) Light Source Moving
*Tip: There are two light sources in scene.  You can only move one light source one time. The default light source control is for directional light. Press Key P to switch to point light. There will be a message on terminal to infer you current light control. Moving light source to see the shadow changing.* 
 - **KeyP**: switch the light source to control
 - **KeyUp** and **KeyDown**: change z axis value of light source
 - **KeyLeft** and **KeyRight**: change x axis value of light source
 - **KeyN** and **KeyM**: change y axis value of light source
  
#### 5) Animation
*Tip: All the objects will do circular motion around the origin. If the centroid of the object is origin, this object will rotate at origin.*
- **KeyR**: turn on or off the animation

#### 6) Window

 - **KeyESC**:  Press ESC to close the window.

## Demo Video
https://youtu.be/Mcga910gKZw


## Reference

1.  Ben Cook, "*Computer Graphics with Modern OpenGL and C++*," Udemy, July 2019, https://www.udemy.com/course/graphics-with-modern-opengl/.
2. Joey de Vries, "*Learning OpenGL*",  June 2017, https://learnopengl.com/.
3. Eisemann, Elmar. _Real-Time Shadows_. Boca Raton, FL: CRC Press, 2012.
4. A K Peters. _Fundamentals of computer graphics_. CRC Press, 2018.
