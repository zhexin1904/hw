/* 
simple demo of using Pangolin
originally create by gao.xiang.thu@gmail.com
https://github.com/gaoxiang12
 */

#include "include/visualize.h"

 
  
 
void DrawTrajectory(std::vector<Eigen::Isometry3d,Eigen::aligned_allocator<Eigen::Isometry3d>> poses){
    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer",1024,768); 
    
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
 
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000), 
        // pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0) // 
        pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0) 

    );
 
    pangolin::View &d_cam = pangolin::CreateDisplay()
        .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
        .SetHandler(new pangolin::Handler3D(s_cam));
 
    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        d_cam.Activate(s_cam); 
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
        glLineWidth(2); 
 
        for (size_t i = 0; i < poses.size(); i++) {
            Eigen::Vector3d Ow = poses[i].translation(); // get the translation part of poses
            Eigen::Vector3d Xw = poses[i] * (0.1 * Eigen::Vector3d(1, 0, 0)); // 0.1 can be adjusted, to better visualize the rotation
            Eigen::Vector3d Yw = poses[i] * (0.1 * Eigen::Vector3d(0, 1, 0)); 
            Eigen::Vector3d Zw = poses[i] * (0.1 * Eigen::Vector3d(0, 0, 1)); 
            
            glBegin(GL_LINES); 
            glColor3f(1.0, 0.0, 0.0); 
        
            glVertex3d(Ow[0], Ow[1], Ow[2]); // position of points
            glVertex3d(Xw[0], Xw[1], Xw[2]); // x axis, red
 
            glColor3f(0.0, 1.0, 0.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]); // position of points 
            glVertex3d(Yw[0], Yw[1], Yw[2]); // y axis, yellow
 
            glColor3f(0.0, 0.0, 1.0);
            glVertex3d(Ow[0], Ow[1], Ow[2]); // position of points
            glVertex3d(Zw[0], Zw[1], Zw[2]); // Z axis, blue
            glEnd(); 
        }
        
        // draw lines
        for (size_t i = 0; i < poses.size() - 1; i++) {
            glColor3f(0.0, 0.0, 0.0); 
            glBegin(GL_LINES); 
            auto p1 = poses[i], p2 = poses[i + 1]; 
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]); // draw line between points
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame(); 
        usleep(5000);   // rate
 
    }
}
 